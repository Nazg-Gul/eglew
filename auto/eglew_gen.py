#!/usr/bin/env python3
#
# Copyright 2016 Blender Foundation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License
#
# Example usage: ./eglew_gen.py /usr/include/EGL/ ../

import os
import sys


def processHeaderFile(filepath, global_symbols):
    wrangler_lines = []
    current_symbols = []
    with open(filepath) as f:
        lines = f.readlines()
        for line in lines:
            if line.startswith("EGLAPI"):
                token = line.split("EGLAPIENTRY ")[1]
                symbol = token.split(' ')[0].split('(')[0]
                line = "typedef " + line
                line = line.replace("EGLAPIENTRY egl", "EGLAPIENTRY tegl")
                wrangler_lines.append(line)
                current_symbols.append(symbol)
                global_symbols.append(symbol)
            elif line.startswith('#endif') or line.startswith('#ifdef'):
                for symbol in current_symbols:
                    wrangler_lines.append("extern t{} *{};\n" .
                                          format(symbol, symbol))
                current_symbols = []
                wrangler_lines.append(line)
            elif line.startswith("#include <EGL"):
                line = "// " + line
                wrangler_lines.append(line)
            elif line.startswith("#include <KHR"):
                line = "// " + line
                wrangler_lines.append(line)
            elif line.startswith("#define WIN32_LEAN_AND_MEAN 1"):
                wrangler_lines.append(line)
                wrangler_lines.append("#endif\n")
                wrangler_lines.append("#ifndef NOGDI\n")
                wrangler_lines.append("#define NOGDI 1\n")
            else:
                wrangler_lines.append(line)
    return wrangler_lines


def copyTemplateFile(template, destination, replacement):
    template_dir = os.path.join(os.path.abspath(os.path.dirname(sys.argv[0])),
                                "templates")
    with open(os.path.join(template_dir, template)) as template_stream:
        filename = template.rstrip(".in")
        with open(os.path.join(destination, filename), 'w') as output_stream:
            lines = template_stream.readlines()
            for line in lines:
                if line.startswith('%'):
                    token = line.strip().strip('%')
                    output_stream.writelines(replacement[token])
                else:
                    output_stream.write(line)


def usage():
    print("Usage: {} </path/to/EGL/headers> </output/path>" .
          format(sys.argv[0]))


if __name__ == '__main__':
    if len(sys.argv) != 3:
        usage()
        exit(1)

    path = sys.argv[1]
    output_path = sys.argv[2]

    if not os.path.exists(path):
        print("Requested {} does not exist" . format(path))
        exit(1)
    if not os.path.isdir(path):
        print("Specified {} is not a directory" . format(path))
        exit(1)

    if not os.path.exists(output_path):
        print("Requested {} does not exist" . format(output_path))
        exit(1)
    if not os.path.isdir(output_path):
        print("Specified {} is not a directory" . format(output_path))
        exit(1)

    global_symbols = {}
    wrangler_lines = []
    headers = ["eglplatform.h",
               "egl.h",
               "eglext.h",
               "eglextchromium.h",
               "eglmesaext.h"]
    for filename in headers:
        if filename.endswith(".h"):
            filepath = os.path.join(path, filename)
            global_symbols[filename] = []
            wrangler_lines.extend(processHeaderFile(filepath,
                                                    global_symbols[filename]))

    function_definitions = []
    function_library_find = []
    for module in sorted(global_symbols):
        if not global_symbols[module]:
            continue
        function_definitions.append("/* {} */\n" . format(module))
        function_library_find.append("  /* {} */\n" . format(module))
        for symbol in sorted(global_symbols[module]):
            function_definitions.append("t{} *{};\n" . format(symbol, symbol))
            function_library_find.append("  EGL_LIBRARY_FIND({});\n" .
                                         format(symbol))

    template_args = {'FUNCTION_DEFINITIONS': function_definitions,
                     'FUNCTION_LIBRARY_FIND': function_library_find,
                     'WRANGLER_LINES': wrangler_lines}
    copyTemplateFile("eglew.c.in",
                     os.path.join(output_path, "source"),
                     template_args)
    copyTemplateFile("eglew.h.in",
                     os.path.join(output_path, "include"),
                     template_args)
