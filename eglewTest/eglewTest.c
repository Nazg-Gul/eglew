/*
 * Copyright 2016 Blender Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License
 */

#include <stdlib.h>
#include <stdio.h>
#include "eglew.h"

int main(int argc, char* argv[]) {
  if (eglewInit() == EGLEW_SUCCESS) {
    EGLDisplay egl_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    EGLint major, minor;
    printf("EGL found\n");
    if (!eglInitialize(egl_display, &major, &minor)) {
      printf("Error initializing EGL\n");
    }
    printf("Initialized EGL %d.%d\n", major, minor);
    eglTerminate(egl_display);
  } else {
    printf("EGL not found\n");
  }
  return EXIT_SUCCESS;
}
