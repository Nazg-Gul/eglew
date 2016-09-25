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

#ifndef __EGLEW_H__
#define __EGLEW_H__

#ifdef __cplusplus
extern "C" {
#endif

#define EGLAPI
#define EGLAPIENTRY
#define EGL_EGLEXT_PROTOTYPES

#ifndef __eglplatform_h_
#define __eglplatform_h_

/*
** Copyright (c) 2007-2013 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

/* Platform-specific types and definitions for egl.h
 * $Revision: 30994 $ on $Date: 2015-04-30 13:36:48 -0700 (Thu, 30 Apr 2015) $
 *
 * Adopters may modify khrplatform.h and this file to suit their platform.
 * You are encouraged to submit all modifications to the Khronos group so that
 * they can be included in future versions of this file.  Please submit changes
 * by sending them to the public Khronos Bugzilla (http://khronos.org/bugzilla)
 * by filing a bug against product "EGL" component "Registry".
 */

#include <KHR/khrplatform.h>

/* Macros used in EGL function prototype declarations.
 *
 * EGL functions should be prototyped as:
 *
 * EGLAPI return-type EGLAPIENTRY eglFunction(arguments);
 * typedef return-type (EXPAPIENTRYP PFNEGLFUNCTIONPROC) (arguments);
 *
 * KHRONOS_APICALL and KHRONOS_APIENTRY are defined in KHR/khrplatform.h
 */

#ifndef EGLAPI
#define EGLAPI KHRONOS_APICALL
#endif

#ifndef EGLAPIENTRY
#define EGLAPIENTRY  KHRONOS_APIENTRY
#endif
#define EGLAPIENTRYP EGLAPIENTRY*

/* The types NativeDisplayType, NativeWindowType, and NativePixmapType
 * are aliases of window-system-dependent types, such as X Display * or
 * Windows Device Context. They must be defined in platform-specific
 * code below. The EGL-prefixed versions of Native*Type are the same
 * types, renamed in EGL 1.3 so all types in the API start with "EGL".
 *
 * Khronos STRONGLY RECOMMENDS that you use the default definitions
 * provided below, since these changes affect both binary and source
 * portability of applications using EGL running on different EGL
 * implementations.
 */

#if defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>

typedef HDC     EGLNativeDisplayType;
typedef HBITMAP EGLNativePixmapType;
typedef HWND    EGLNativeWindowType;

#elif defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

typedef int   EGLNativeDisplayType;
typedef void *EGLNativeWindowType;
typedef void *EGLNativePixmapType;

#elif defined(WL_EGL_PLATFORM)

typedef struct wl_display     *EGLNativeDisplayType;
typedef struct wl_egl_pixmap  *EGLNativePixmapType;
typedef struct wl_egl_window  *EGLNativeWindowType;

#elif defined(__GBM__)

typedef struct gbm_device  *EGLNativeDisplayType;
typedef struct gbm_bo      *EGLNativePixmapType;
typedef void               *EGLNativeWindowType;

#elif defined(__ANDROID__) || defined(ANDROID)

#include <android/native_window.h>

struct egl_native_pixmap_t;

typedef struct ANativeWindow*           EGLNativeWindowType;
typedef struct egl_native_pixmap_t*     EGLNativePixmapType;
typedef void*                           EGLNativeDisplayType;

#elif defined(__unix__) || defined(__APPLE__)

#if defined(MESA_EGL_NO_X11_HEADERS)

typedef void            *EGLNativeDisplayType;
typedef khronos_uintptr_t EGLNativePixmapType;
typedef khronos_uintptr_t EGLNativeWindowType;

#else

/* X11 (tentative)  */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef Display *EGLNativeDisplayType;
typedef Pixmap   EGLNativePixmapType;
typedef Window   EGLNativeWindowType;

#endif /* MESA_EGL_NO_X11_HEADERS */

#elif __HAIKU__
#include <kernel/image.h>
typedef void				*EGLNativeDisplayType;
typedef khronos_uintptr_t	 EGLNativePixmapType;
typedef khronos_uintptr_t	 EGLNativeWindowType;

#else
#error "Platform not recognized"
#endif

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
typedef EGLNativeDisplayType NativeDisplayType;
typedef EGLNativePixmapType  NativePixmapType;
typedef EGLNativeWindowType  NativeWindowType;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
typedef khronos_int32_t EGLint;

#endif /* __eglplatform_h */
#ifndef __egl_h_
#define __egl_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

/*
** Copyright (c) 2013-2014 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/
/*
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   http://www.opengl.org/registry/
**
** Khronos $Revision: 31039 $ on $Date: 2015-05-04 17:01:57 -0700 (Mon, 04 May 2015) $
*/


/* Generated on date 20150504 */

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: .*
 * Default extensions included: None
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#ifndef EGL_VERSION_1_0
#define EGL_VERSION_1_0 1
typedef unsigned int EGLBoolean;
typedef void *EGLDisplay;
#include <KHR/khrplatform.h>
typedef void *EGLConfig;
typedef void *EGLSurface;
typedef void *EGLContext;
typedef void (*__eglMustCastToProperFunctionPointerType)(void);
#define EGL_ALPHA_SIZE                    0x3021
#define EGL_BAD_ACCESS                    0x3002
#define EGL_BAD_ALLOC                     0x3003
#define EGL_BAD_ATTRIBUTE                 0x3004
#define EGL_BAD_CONFIG                    0x3005
#define EGL_BAD_CONTEXT                   0x3006
#define EGL_BAD_CURRENT_SURFACE           0x3007
#define EGL_BAD_DISPLAY                   0x3008
#define EGL_BAD_MATCH                     0x3009
#define EGL_BAD_NATIVE_PIXMAP             0x300A
#define EGL_BAD_NATIVE_WINDOW             0x300B
#define EGL_BAD_PARAMETER                 0x300C
#define EGL_BAD_SURFACE                   0x300D
#define EGL_BLUE_SIZE                     0x3022
#define EGL_BUFFER_SIZE                   0x3020
#define EGL_CONFIG_CAVEAT                 0x3027
#define EGL_CONFIG_ID                     0x3028
#define EGL_CORE_NATIVE_ENGINE            0x305B
#define EGL_DEPTH_SIZE                    0x3025
#define EGL_DONT_CARE                     ((EGLint)-1)
#define EGL_DRAW                          0x3059
#define EGL_EXTENSIONS                    0x3055
#define EGL_FALSE                         0
#define EGL_GREEN_SIZE                    0x3023
#define EGL_HEIGHT                        0x3056
#define EGL_LARGEST_PBUFFER               0x3058
#define EGL_LEVEL                         0x3029
#define EGL_MAX_PBUFFER_HEIGHT            0x302A
#define EGL_MAX_PBUFFER_PIXELS            0x302B
#define EGL_MAX_PBUFFER_WIDTH             0x302C
#define EGL_NATIVE_RENDERABLE             0x302D
#define EGL_NATIVE_VISUAL_ID              0x302E
#define EGL_NATIVE_VISUAL_TYPE            0x302F
#define EGL_NONE                          0x3038
#define EGL_NON_CONFORMANT_CONFIG         0x3051
#define EGL_NOT_INITIALIZED               0x3001
#define EGL_NO_CONTEXT                    ((EGLContext)0)
#define EGL_NO_DISPLAY                    ((EGLDisplay)0)
#define EGL_NO_SURFACE                    ((EGLSurface)0)
#define EGL_PBUFFER_BIT                   0x0001
#define EGL_PIXMAP_BIT                    0x0002
#define EGL_READ                          0x305A
#define EGL_RED_SIZE                      0x3024
#define EGL_SAMPLES                       0x3031
#define EGL_SAMPLE_BUFFERS                0x3032
#define EGL_SLOW_CONFIG                   0x3050
#define EGL_STENCIL_SIZE                  0x3026
#define EGL_SUCCESS                       0x3000
#define EGL_SURFACE_TYPE                  0x3033
#define EGL_TRANSPARENT_BLUE_VALUE        0x3035
#define EGL_TRANSPARENT_GREEN_VALUE       0x3036
#define EGL_TRANSPARENT_RED_VALUE         0x3037
#define EGL_TRANSPARENT_RGB               0x3052
#define EGL_TRANSPARENT_TYPE              0x3034
#define EGL_TRUE                          1
#define EGL_VENDOR                        0x3053
#define EGL_VERSION                       0x3054
#define EGL_WIDTH                         0x3057
#define EGL_WINDOW_BIT                    0x0004
typedef EGLAPI EGLBoolean EGLAPIENTRY teglChooseConfig (EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglCopyBuffers (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target);
typedef EGLAPI EGLContext EGLAPIENTRY teglCreateContext (EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list);
typedef EGLAPI EGLSurface EGLAPIENTRY teglCreatePbufferSurface (EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list);
typedef EGLAPI EGLSurface EGLAPIENTRY teglCreatePixmapSurface (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint *attrib_list);
typedef EGLAPI EGLSurface EGLAPIENTRY teglCreateWindowSurface (EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglDestroyContext (EGLDisplay dpy, EGLContext ctx);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglDestroySurface (EGLDisplay dpy, EGLSurface surface);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglGetConfigAttrib (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglGetConfigs (EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config);
typedef EGLAPI EGLDisplay EGLAPIENTRY teglGetCurrentDisplay (void);
typedef EGLAPI EGLSurface EGLAPIENTRY teglGetCurrentSurface (EGLint readdraw);
typedef EGLAPI EGLDisplay EGLAPIENTRY teglGetDisplay (EGLNativeDisplayType display_id);
typedef EGLAPI EGLint EGLAPIENTRY teglGetError (void);
typedef EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY teglGetProcAddress (const char *procname);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglInitialize (EGLDisplay dpy, EGLint *major, EGLint *minor);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglMakeCurrent (EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglQueryContext (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value);
typedef EGLAPI const char *EGLAPIENTRY teglQueryString (EGLDisplay dpy, EGLint name);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglQuerySurface (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglSwapBuffers (EGLDisplay dpy, EGLSurface surface);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglTerminate (EGLDisplay dpy);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglWaitGL (void);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglWaitNative (EGLint engine);
extern teglChooseConfig *eglChooseConfig;
extern teglCopyBuffers *eglCopyBuffers;
extern teglCreateContext *eglCreateContext;
extern teglCreatePbufferSurface *eglCreatePbufferSurface;
extern teglCreatePixmapSurface *eglCreatePixmapSurface;
extern teglCreateWindowSurface *eglCreateWindowSurface;
extern teglDestroyContext *eglDestroyContext;
extern teglDestroySurface *eglDestroySurface;
extern teglGetConfigAttrib *eglGetConfigAttrib;
extern teglGetConfigs *eglGetConfigs;
extern teglGetCurrentDisplay *eglGetCurrentDisplay;
extern teglGetCurrentSurface *eglGetCurrentSurface;
extern teglGetDisplay *eglGetDisplay;
extern teglGetError *eglGetError;
extern teglGetProcAddress *eglGetProcAddress;
extern teglInitialize *eglInitialize;
extern teglMakeCurrent *eglMakeCurrent;
extern teglQueryContext *eglQueryContext;
extern teglQueryString *eglQueryString;
extern teglQuerySurface *eglQuerySurface;
extern teglSwapBuffers *eglSwapBuffers;
extern teglTerminate *eglTerminate;
extern teglWaitGL *eglWaitGL;
extern teglWaitNative *eglWaitNative;
#endif /* EGL_VERSION_1_0 */

#ifndef EGL_VERSION_1_1
#define EGL_VERSION_1_1 1
#define EGL_BACK_BUFFER                   0x3084
#define EGL_BIND_TO_TEXTURE_RGB           0x3039
#define EGL_BIND_TO_TEXTURE_RGBA          0x303A
#define EGL_CONTEXT_LOST                  0x300E
#define EGL_MIN_SWAP_INTERVAL             0x303B
#define EGL_MAX_SWAP_INTERVAL             0x303C
#define EGL_MIPMAP_TEXTURE                0x3082
#define EGL_MIPMAP_LEVEL                  0x3083
#define EGL_NO_TEXTURE                    0x305C
#define EGL_TEXTURE_2D                    0x305F
#define EGL_TEXTURE_FORMAT                0x3080
#define EGL_TEXTURE_RGB                   0x305D
#define EGL_TEXTURE_RGBA                  0x305E
#define EGL_TEXTURE_TARGET                0x3081
typedef EGLAPI EGLBoolean EGLAPIENTRY teglBindTexImage (EGLDisplay dpy, EGLSurface surface, EGLint buffer);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglReleaseTexImage (EGLDisplay dpy, EGLSurface surface, EGLint buffer);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglSurfaceAttrib (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglSwapInterval (EGLDisplay dpy, EGLint interval);
extern teglBindTexImage *eglBindTexImage;
extern teglReleaseTexImage *eglReleaseTexImage;
extern teglSurfaceAttrib *eglSurfaceAttrib;
extern teglSwapInterval *eglSwapInterval;
#endif /* EGL_VERSION_1_1 */

#ifndef EGL_VERSION_1_2
#define EGL_VERSION_1_2 1
typedef unsigned int EGLenum;
typedef void *EGLClientBuffer;
#define EGL_ALPHA_FORMAT                  0x3088
#define EGL_ALPHA_FORMAT_NONPRE           0x308B
#define EGL_ALPHA_FORMAT_PRE              0x308C
#define EGL_ALPHA_MASK_SIZE               0x303E
#define EGL_BUFFER_PRESERVED              0x3094
#define EGL_BUFFER_DESTROYED              0x3095
#define EGL_CLIENT_APIS                   0x308D
#define EGL_COLORSPACE                    0x3087
#define EGL_COLORSPACE_sRGB               0x3089
#define EGL_COLORSPACE_LINEAR             0x308A
#define EGL_COLOR_BUFFER_TYPE             0x303F
#define EGL_CONTEXT_CLIENT_TYPE           0x3097
#define EGL_DISPLAY_SCALING               10000
#define EGL_HORIZONTAL_RESOLUTION         0x3090
#define EGL_LUMINANCE_BUFFER              0x308F
#define EGL_LUMINANCE_SIZE                0x303D
#define EGL_OPENGL_ES_BIT                 0x0001
#define EGL_OPENVG_BIT                    0x0002
#define EGL_OPENGL_ES_API                 0x30A0
#define EGL_OPENVG_API                    0x30A1
#define EGL_OPENVG_IMAGE                  0x3096
#define EGL_PIXEL_ASPECT_RATIO            0x3092
#define EGL_RENDERABLE_TYPE               0x3040
#define EGL_RENDER_BUFFER                 0x3086
#define EGL_RGB_BUFFER                    0x308E
#define EGL_SINGLE_BUFFER                 0x3085
#define EGL_SWAP_BEHAVIOR                 0x3093
#define EGL_UNKNOWN                       ((EGLint)-1)
#define EGL_VERTICAL_RESOLUTION           0x3091
typedef EGLAPI EGLBoolean EGLAPIENTRY teglBindAPI (EGLenum api);
typedef EGLAPI EGLenum EGLAPIENTRY teglQueryAPI (void);
typedef EGLAPI EGLSurface EGLAPIENTRY teglCreatePbufferFromClientBuffer (EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglReleaseThread (void);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglWaitClient (void);
extern teglBindAPI *eglBindAPI;
extern teglQueryAPI *eglQueryAPI;
extern teglCreatePbufferFromClientBuffer *eglCreatePbufferFromClientBuffer;
extern teglReleaseThread *eglReleaseThread;
extern teglWaitClient *eglWaitClient;
#endif /* EGL_VERSION_1_2 */

#ifndef EGL_VERSION_1_3
#define EGL_VERSION_1_3 1
#define EGL_CONFORMANT                    0x3042
#define EGL_CONTEXT_CLIENT_VERSION        0x3098
#define EGL_MATCH_NATIVE_PIXMAP           0x3041
#define EGL_OPENGL_ES2_BIT                0x0004
#define EGL_VG_ALPHA_FORMAT               0x3088
#define EGL_VG_ALPHA_FORMAT_NONPRE        0x308B
#define EGL_VG_ALPHA_FORMAT_PRE           0x308C
#define EGL_VG_ALPHA_FORMAT_PRE_BIT       0x0040
#define EGL_VG_COLORSPACE                 0x3087
#define EGL_VG_COLORSPACE_sRGB            0x3089
#define EGL_VG_COLORSPACE_LINEAR          0x308A
#define EGL_VG_COLORSPACE_LINEAR_BIT      0x0020
#endif /* EGL_VERSION_1_3 */

#ifndef EGL_VERSION_1_4
#define EGL_VERSION_1_4 1
#define EGL_DEFAULT_DISPLAY               ((EGLNativeDisplayType)0)
#define EGL_MULTISAMPLE_RESOLVE_BOX_BIT   0x0200
#define EGL_MULTISAMPLE_RESOLVE           0x3099
#define EGL_MULTISAMPLE_RESOLVE_DEFAULT   0x309A
#define EGL_MULTISAMPLE_RESOLVE_BOX       0x309B
#define EGL_OPENGL_API                    0x30A2
#define EGL_OPENGL_BIT                    0x0008
#define EGL_SWAP_BEHAVIOR_PRESERVED_BIT   0x0400
typedef EGLAPI EGLContext EGLAPIENTRY teglGetCurrentContext (void);
extern teglGetCurrentContext *eglGetCurrentContext;
#endif /* EGL_VERSION_1_4 */

#ifndef EGL_VERSION_1_5
#define EGL_VERSION_1_5 1
typedef void *EGLSync;
typedef intptr_t EGLAttrib;
typedef khronos_utime_nanoseconds_t EGLTime;
typedef void *EGLImage;
#define EGL_CONTEXT_MAJOR_VERSION         0x3098
#define EGL_CONTEXT_MINOR_VERSION         0x30FB
#define EGL_CONTEXT_OPENGL_PROFILE_MASK   0x30FD
#define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY 0x31BD
#define EGL_NO_RESET_NOTIFICATION         0x31BE
#define EGL_LOSE_CONTEXT_ON_RESET         0x31BF
#define EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT 0x00000001
#define EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT 0x00000002
#define EGL_CONTEXT_OPENGL_DEBUG          0x31B0
#define EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE 0x31B1
#define EGL_CONTEXT_OPENGL_ROBUST_ACCESS  0x31B2
#define EGL_OPENGL_ES3_BIT                0x00000040
#define EGL_CL_EVENT_HANDLE               0x309C
#define EGL_SYNC_CL_EVENT                 0x30FE
#define EGL_SYNC_CL_EVENT_COMPLETE        0x30FF
#define EGL_SYNC_PRIOR_COMMANDS_COMPLETE  0x30F0
#define EGL_SYNC_TYPE                     0x30F7
#define EGL_SYNC_STATUS                   0x30F1
#define EGL_SYNC_CONDITION                0x30F8
#define EGL_SIGNALED                      0x30F2
#define EGL_UNSIGNALED                    0x30F3
#define EGL_SYNC_FLUSH_COMMANDS_BIT       0x0001
#define EGL_FOREVER                       0xFFFFFFFFFFFFFFFFull
#define EGL_TIMEOUT_EXPIRED               0x30F5
#define EGL_CONDITION_SATISFIED           0x30F6
#define EGL_NO_SYNC                       ((EGLSync)0)
#define EGL_SYNC_FENCE                    0x30F9
#define EGL_GL_COLORSPACE                 0x309D
#define EGL_GL_COLORSPACE_SRGB            0x3089
#define EGL_GL_COLORSPACE_LINEAR          0x308A
#define EGL_GL_RENDERBUFFER               0x30B9
#define EGL_GL_TEXTURE_2D                 0x30B1
#define EGL_GL_TEXTURE_LEVEL              0x30BC
#define EGL_GL_TEXTURE_3D                 0x30B2
#define EGL_GL_TEXTURE_ZOFFSET            0x30BD
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x30B3
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x30B4
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x30B5
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x30B6
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x30B7
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x30B8
#define EGL_IMAGE_PRESERVED               0x30D2
#define EGL_NO_IMAGE                      ((EGLImage)0)
typedef EGLAPI EGLSync EGLAPIENTRY teglCreateSync (EGLDisplay dpy, EGLenum type, const EGLAttrib *attrib_list);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglDestroySync (EGLDisplay dpy, EGLSync sync);
typedef EGLAPI EGLint EGLAPIENTRY teglClientWaitSync (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglGetSyncAttrib (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib *value);
typedef EGLAPI EGLImage EGLAPIENTRY teglCreateImage (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLAttrib *attrib_list);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglDestroyImage (EGLDisplay dpy, EGLImage image);
typedef EGLAPI EGLDisplay EGLAPIENTRY teglGetPlatformDisplay (EGLenum platform, void *native_display, const EGLAttrib *attrib_list);
typedef EGLAPI EGLSurface EGLAPIENTRY teglCreatePlatformWindowSurface (EGLDisplay dpy, EGLConfig config, void *native_window, const EGLAttrib *attrib_list);
typedef EGLAPI EGLSurface EGLAPIENTRY teglCreatePlatformPixmapSurface (EGLDisplay dpy, EGLConfig config, void *native_pixmap, const EGLAttrib *attrib_list);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglWaitSync (EGLDisplay dpy, EGLSync sync, EGLint flags);
extern teglCreateSync *eglCreateSync;
extern teglDestroySync *eglDestroySync;
extern teglClientWaitSync *eglClientWaitSync;
extern teglGetSyncAttrib *eglGetSyncAttrib;
extern teglCreateImage *eglCreateImage;
extern teglDestroyImage *eglDestroyImage;
extern teglGetPlatformDisplay *eglGetPlatformDisplay;
extern teglCreatePlatformWindowSurface *eglCreatePlatformWindowSurface;
extern teglCreatePlatformPixmapSurface *eglCreatePlatformPixmapSurface;
extern teglWaitSync *eglWaitSync;
#endif /* EGL_VERSION_1_5 */

#ifdef __cplusplus
}
#endif

#endif
#ifndef __eglext_h_
#define __eglext_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

/*
** Copyright (c) 2013-2014 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/
/*
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   http://www.opengl.org/registry/
**
** Khronos $Revision$ on $Date$
*/


#define EGL_EGLEXT_VERSION 20150508

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: _nomatch_^
 * Default extensions included: egl
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#ifndef EGL_KHR_cl_event
#define EGL_KHR_cl_event 1
#define EGL_CL_EVENT_HANDLE_KHR           0x309C
#define EGL_SYNC_CL_EVENT_KHR             0x30FE
#define EGL_SYNC_CL_EVENT_COMPLETE_KHR    0x30FF
#endif /* EGL_KHR_cl_event */

#ifndef EGL_KHR_cl_event2
#define EGL_KHR_cl_event2 1
typedef void *EGLSyncKHR;
typedef intptr_t EGLAttribKHR;
typedef EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNC64KHRPROC) (EGLDisplay dpy, EGLenum type, const EGLAttribKHR *attrib_list);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLSyncKHR EGLAPIENTRY teglCreateSync64KHR (EGLDisplay dpy, EGLenum type, const EGLAttribKHR *attrib_list);
extern teglCreateSync64KHR *eglCreateSync64KHR;
#endif
#endif /* EGL_KHR_cl_event2 */

#ifndef EGL_KHR_client_get_all_proc_addresses
#define EGL_KHR_client_get_all_proc_addresses 1
#endif /* EGL_KHR_client_get_all_proc_addresses */

#ifndef EGL_KHR_config_attribs
#define EGL_KHR_config_attribs 1
#define EGL_CONFORMANT_KHR                0x3042
#define EGL_VG_COLORSPACE_LINEAR_BIT_KHR  0x0020
#define EGL_VG_ALPHA_FORMAT_PRE_BIT_KHR   0x0040
#endif /* EGL_KHR_config_attribs */

#ifndef EGL_KHR_create_context
#define EGL_KHR_create_context 1
#define EGL_CONTEXT_MAJOR_VERSION_KHR     0x3098
#define EGL_CONTEXT_MINOR_VERSION_KHR     0x30FB
#define EGL_CONTEXT_FLAGS_KHR             0x30FC
#define EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR 0x30FD
#define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR 0x31BD
#define EGL_NO_RESET_NOTIFICATION_KHR     0x31BE
#define EGL_LOSE_CONTEXT_ON_RESET_KHR     0x31BF
#define EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR  0x00000001
#define EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR 0x00000002
#define EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR 0x00000004
#define EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR 0x00000001
#define EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR 0x00000002
#define EGL_OPENGL_ES3_BIT_KHR            0x00000040
#endif /* EGL_KHR_create_context */

#ifndef EGL_KHR_create_context_no_error
#define EGL_KHR_create_context_no_error 1
#define EGL_CONTEXT_OPENGL_NO_ERROR_KHR   0x31B3
#endif /* EGL_KHR_create_context_no_error */

#ifndef EGL_KHR_fence_sync
#define EGL_KHR_fence_sync 1
typedef khronos_utime_nanoseconds_t EGLTimeKHR;
#ifdef KHRONOS_SUPPORT_INT64
#define EGL_SYNC_PRIOR_COMMANDS_COMPLETE_KHR 0x30F0
#define EGL_SYNC_CONDITION_KHR            0x30F8
#define EGL_SYNC_FENCE_KHR                0x30F9
typedef EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, const EGLint *attrib_list);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
typedef EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *value);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLSyncKHR EGLAPIENTRY teglCreateSyncKHR (EGLDisplay dpy, EGLenum type, const EGLint *attrib_list);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglDestroySyncKHR (EGLDisplay dpy, EGLSyncKHR sync);
typedef EGLAPI EGLint EGLAPIENTRY teglClientWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglGetSyncAttribKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *value);
extern teglCreateSyncKHR *eglCreateSyncKHR;
extern teglDestroySyncKHR *eglDestroySyncKHR;
extern teglClientWaitSyncKHR *eglClientWaitSyncKHR;
extern teglGetSyncAttribKHR *eglGetSyncAttribKHR;
#endif
#endif /* KHRONOS_SUPPORT_INT64 */
#endif /* EGL_KHR_fence_sync */

#ifndef EGL_KHR_get_all_proc_addresses
#define EGL_KHR_get_all_proc_addresses 1
#endif /* EGL_KHR_get_all_proc_addresses */

#ifndef EGL_KHR_gl_colorspace
#define EGL_KHR_gl_colorspace 1
#define EGL_GL_COLORSPACE_KHR             0x309D
#define EGL_GL_COLORSPACE_SRGB_KHR        0x3089
#define EGL_GL_COLORSPACE_LINEAR_KHR      0x308A
#endif /* EGL_KHR_gl_colorspace */

#ifndef EGL_KHR_gl_renderbuffer_image
#define EGL_KHR_gl_renderbuffer_image 1
#define EGL_GL_RENDERBUFFER_KHR           0x30B9
#endif /* EGL_KHR_gl_renderbuffer_image */

#ifndef EGL_KHR_gl_texture_2D_image
#define EGL_KHR_gl_texture_2D_image 1
#define EGL_GL_TEXTURE_2D_KHR             0x30B1
#define EGL_GL_TEXTURE_LEVEL_KHR          0x30BC
#endif /* EGL_KHR_gl_texture_2D_image */

#ifndef EGL_KHR_gl_texture_3D_image
#define EGL_KHR_gl_texture_3D_image 1
#define EGL_GL_TEXTURE_3D_KHR             0x30B2
#define EGL_GL_TEXTURE_ZOFFSET_KHR        0x30BD
#endif /* EGL_KHR_gl_texture_3D_image */

#ifndef EGL_KHR_gl_texture_cubemap_image
#define EGL_KHR_gl_texture_cubemap_image 1
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_X_KHR 0x30B3
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X_KHR 0x30B4
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Y_KHR 0x30B5
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_KHR 0x30B6
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Z_KHR 0x30B7
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_KHR 0x30B8
#endif /* EGL_KHR_gl_texture_cubemap_image */

#ifndef EGL_KHR_image
#define EGL_KHR_image 1
typedef void *EGLImageKHR;
#define EGL_NATIVE_PIXMAP_KHR             0x30B0
#define EGL_NO_IMAGE_KHR                  ((EGLImageKHR)0)
typedef EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEIMAGEKHRPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEKHRPROC) (EGLDisplay dpy, EGLImageKHR image);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLImageKHR EGLAPIENTRY teglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglDestroyImageKHR (EGLDisplay dpy, EGLImageKHR image);
extern teglCreateImageKHR *eglCreateImageKHR;
extern teglDestroyImageKHR *eglDestroyImageKHR;
#endif
#endif /* EGL_KHR_image */

#ifndef EGL_KHR_image_base
#define EGL_KHR_image_base 1
#define EGL_IMAGE_PRESERVED_KHR           0x30D2
#endif /* EGL_KHR_image_base */

#ifndef EGL_KHR_image_pixmap
#define EGL_KHR_image_pixmap 1
#endif /* EGL_KHR_image_pixmap */

#ifndef EGL_KHR_lock_surface
#define EGL_KHR_lock_surface 1
#define EGL_READ_SURFACE_BIT_KHR          0x0001
#define EGL_WRITE_SURFACE_BIT_KHR         0x0002
#define EGL_LOCK_SURFACE_BIT_KHR          0x0080
#define EGL_OPTIMAL_FORMAT_BIT_KHR        0x0100
#define EGL_MATCH_FORMAT_KHR              0x3043
#define EGL_FORMAT_RGB_565_EXACT_KHR      0x30C0
#define EGL_FORMAT_RGB_565_KHR            0x30C1
#define EGL_FORMAT_RGBA_8888_EXACT_KHR    0x30C2
#define EGL_FORMAT_RGBA_8888_KHR          0x30C3
#define EGL_MAP_PRESERVE_PIXELS_KHR       0x30C4
#define EGL_LOCK_USAGE_HINT_KHR           0x30C5
#define EGL_BITMAP_POINTER_KHR            0x30C6
#define EGL_BITMAP_PITCH_KHR              0x30C7
#define EGL_BITMAP_ORIGIN_KHR             0x30C8
#define EGL_BITMAP_PIXEL_RED_OFFSET_KHR   0x30C9
#define EGL_BITMAP_PIXEL_GREEN_OFFSET_KHR 0x30CA
#define EGL_BITMAP_PIXEL_BLUE_OFFSET_KHR  0x30CB
#define EGL_BITMAP_PIXEL_ALPHA_OFFSET_KHR 0x30CC
#define EGL_BITMAP_PIXEL_LUMINANCE_OFFSET_KHR 0x30CD
#define EGL_LOWER_LEFT_KHR                0x30CE
#define EGL_UPPER_LEFT_KHR                0x30CF
typedef EGLBoolean (EGLAPIENTRYP PFNEGLLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface, const EGLint *attrib_list);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLUNLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglLockSurfaceKHR (EGLDisplay dpy, EGLSurface surface, const EGLint *attrib_list);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglUnlockSurfaceKHR (EGLDisplay dpy, EGLSurface surface);
extern teglLockSurfaceKHR *eglLockSurfaceKHR;
extern teglUnlockSurfaceKHR *eglUnlockSurfaceKHR;
#endif
#endif /* EGL_KHR_lock_surface */

#ifndef EGL_KHR_lock_surface2
#define EGL_KHR_lock_surface2 1
#define EGL_BITMAP_PIXEL_SIZE_KHR         0x3110
#endif /* EGL_KHR_lock_surface2 */

#ifndef EGL_KHR_lock_surface3
#define EGL_KHR_lock_surface3 1
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACE64KHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *value);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglQuerySurface64KHR (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *value);
extern teglQuerySurface64KHR *eglQuerySurface64KHR;
#endif
#endif /* EGL_KHR_lock_surface3 */

#ifndef EGL_KHR_partial_update
#define EGL_KHR_partial_update 1
#define EGL_BUFFER_AGE_KHR                0x313D
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSETDAMAGEREGIONKHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglSetDamageRegionKHR (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
extern teglSetDamageRegionKHR *eglSetDamageRegionKHR;
#endif
#endif /* EGL_KHR_partial_update */

#ifndef EGL_KHR_platform_android
#define EGL_KHR_platform_android 1
#define EGL_PLATFORM_ANDROID_KHR          0x3141
#endif /* EGL_KHR_platform_android */

#ifndef EGL_KHR_platform_gbm
#define EGL_KHR_platform_gbm 1
#define EGL_PLATFORM_GBM_KHR              0x31D7
#endif /* EGL_KHR_platform_gbm */

#ifndef EGL_KHR_platform_wayland
#define EGL_KHR_platform_wayland 1
#define EGL_PLATFORM_WAYLAND_KHR          0x31D8
#endif /* EGL_KHR_platform_wayland */

#ifndef EGL_KHR_platform_x11
#define EGL_KHR_platform_x11 1
#define EGL_PLATFORM_X11_KHR              0x31D5
#define EGL_PLATFORM_X11_SCREEN_KHR       0x31D6
#endif /* EGL_KHR_platform_x11 */

#ifndef EGL_KHR_reusable_sync
#define EGL_KHR_reusable_sync 1
#ifdef KHRONOS_SUPPORT_INT64
#define EGL_SYNC_STATUS_KHR               0x30F1
#define EGL_SIGNALED_KHR                  0x30F2
#define EGL_UNSIGNALED_KHR                0x30F3
#define EGL_TIMEOUT_EXPIRED_KHR           0x30F5
#define EGL_CONDITION_SATISFIED_KHR       0x30F6
#define EGL_SYNC_TYPE_KHR                 0x30F7
#define EGL_SYNC_REUSABLE_KHR             0x30FA
#define EGL_SYNC_FLUSH_COMMANDS_BIT_KHR   0x0001
#define EGL_FOREVER_KHR                   0xFFFFFFFFFFFFFFFFull
#define EGL_NO_SYNC_KHR                   ((EGLSyncKHR)0)
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLenum mode);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglSignalSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLenum mode);
extern teglSignalSyncKHR *eglSignalSyncKHR;
#endif
#endif /* KHRONOS_SUPPORT_INT64 */
#endif /* EGL_KHR_reusable_sync */

#ifndef EGL_KHR_stream
#define EGL_KHR_stream 1
typedef void *EGLStreamKHR;
typedef khronos_uint64_t EGLuint64KHR;
#ifdef KHRONOS_SUPPORT_INT64
#define EGL_NO_STREAM_KHR                 ((EGLStreamKHR)0)
#define EGL_CONSUMER_LATENCY_USEC_KHR     0x3210
#define EGL_PRODUCER_FRAME_KHR            0x3212
#define EGL_CONSUMER_FRAME_KHR            0x3213
#define EGL_STREAM_STATE_KHR              0x3214
#define EGL_STREAM_STATE_CREATED_KHR      0x3215
#define EGL_STREAM_STATE_CONNECTING_KHR   0x3216
#define EGL_STREAM_STATE_EMPTY_KHR        0x3217
#define EGL_STREAM_STATE_NEW_FRAME_AVAILABLE_KHR 0x3218
#define EGL_STREAM_STATE_OLD_FRAME_AVAILABLE_KHR 0x3219
#define EGL_STREAM_STATE_DISCONNECTED_KHR 0x321A
#define EGL_BAD_STREAM_KHR                0x321B
#define EGL_BAD_STATE_KHR                 0x321C
typedef EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMKHRPROC) (EGLDisplay dpy, const EGLint *attrib_list);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLint value);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLint *value);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMU64KHRPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLuint64KHR *value);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLStreamKHR EGLAPIENTRY teglCreateStreamKHR (EGLDisplay dpy, const EGLint *attrib_list);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglDestroyStreamKHR (EGLDisplay dpy, EGLStreamKHR stream);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglStreamAttribKHR (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLint value);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglQueryStreamKHR (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLint *value);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglQueryStreamu64KHR (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLuint64KHR *value);
extern teglCreateStreamKHR *eglCreateStreamKHR;
extern teglDestroyStreamKHR *eglDestroyStreamKHR;
extern teglStreamAttribKHR *eglStreamAttribKHR;
extern teglQueryStreamKHR *eglQueryStreamKHR;
extern teglQueryStreamu64KHR *eglQueryStreamu64KHR;
#endif
#endif /* KHRONOS_SUPPORT_INT64 */
#endif /* EGL_KHR_stream */

#ifndef EGL_KHR_stream_consumer_gltexture
#define EGL_KHR_stream_consumer_gltexture 1
#ifdef EGL_KHR_stream
#define EGL_CONSUMER_ACQUIRE_TIMEOUT_USEC_KHR 0x321E
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglStreamConsumerGLTextureExternalKHR (EGLDisplay dpy, EGLStreamKHR stream);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglStreamConsumerAcquireKHR (EGLDisplay dpy, EGLStreamKHR stream);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglStreamConsumerReleaseKHR (EGLDisplay dpy, EGLStreamKHR stream);
extern teglStreamConsumerGLTextureExternalKHR *eglStreamConsumerGLTextureExternalKHR;
extern teglStreamConsumerAcquireKHR *eglStreamConsumerAcquireKHR;
extern teglStreamConsumerReleaseKHR *eglStreamConsumerReleaseKHR;
#endif
#endif /* EGL_KHR_stream */
#endif /* EGL_KHR_stream_consumer_gltexture */

#ifndef EGL_KHR_stream_cross_process_fd
#define EGL_KHR_stream_cross_process_fd 1
typedef int EGLNativeFileDescriptorKHR;
#ifdef EGL_KHR_stream
#define EGL_NO_FILE_DESCRIPTOR_KHR        ((EGLNativeFileDescriptorKHR)(-1))
typedef EGLNativeFileDescriptorKHR (EGLAPIENTRYP PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream);
typedef EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLNativeFileDescriptorKHR EGLAPIENTRY teglGetStreamFileDescriptorKHR (EGLDisplay dpy, EGLStreamKHR stream);
typedef EGLAPI EGLStreamKHR EGLAPIENTRY teglCreateStreamFromFileDescriptorKHR (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
extern teglGetStreamFileDescriptorKHR *eglGetStreamFileDescriptorKHR;
extern teglCreateStreamFromFileDescriptorKHR *eglCreateStreamFromFileDescriptorKHR;
#endif
#endif /* EGL_KHR_stream */
#endif /* EGL_KHR_stream_cross_process_fd */

#ifndef EGL_KHR_stream_fifo
#define EGL_KHR_stream_fifo 1
#ifdef EGL_KHR_stream
#define EGL_STREAM_FIFO_LENGTH_KHR        0x31FC
#define EGL_STREAM_TIME_NOW_KHR           0x31FD
#define EGL_STREAM_TIME_CONSUMER_KHR      0x31FE
#define EGL_STREAM_TIME_PRODUCER_KHR      0x31FF
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMTIMEKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLTimeKHR *value);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglQueryStreamTimeKHR (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLTimeKHR *value);
extern teglQueryStreamTimeKHR *eglQueryStreamTimeKHR;
#endif
#endif /* EGL_KHR_stream */
#endif /* EGL_KHR_stream_fifo */

#ifndef EGL_KHR_stream_producer_aldatalocator
#define EGL_KHR_stream_producer_aldatalocator 1
#ifdef EGL_KHR_stream
#endif /* EGL_KHR_stream */
#endif /* EGL_KHR_stream_producer_aldatalocator */

#ifndef EGL_KHR_stream_producer_eglsurface
#define EGL_KHR_stream_producer_eglsurface 1
#ifdef EGL_KHR_stream
#define EGL_STREAM_BIT_KHR                0x0800
typedef EGLSurface (EGLAPIENTRYP PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC) (EGLDisplay dpy, EGLConfig config, EGLStreamKHR stream, const EGLint *attrib_list);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLSurface EGLAPIENTRY teglCreateStreamProducerSurfaceKHR (EGLDisplay dpy, EGLConfig config, EGLStreamKHR stream, const EGLint *attrib_list);
extern teglCreateStreamProducerSurfaceKHR *eglCreateStreamProducerSurfaceKHR;
#endif
#endif /* EGL_KHR_stream */
#endif /* EGL_KHR_stream_producer_eglsurface */

#ifndef EGL_KHR_surfaceless_context
#define EGL_KHR_surfaceless_context 1
#endif /* EGL_KHR_surfaceless_context */

#ifndef EGL_KHR_swap_buffers_with_damage
#define EGL_KHR_swap_buffers_with_damage 1
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglSwapBuffersWithDamageKHR (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
extern teglSwapBuffersWithDamageKHR *eglSwapBuffersWithDamageKHR;
#endif
#endif /* EGL_KHR_swap_buffers_with_damage */

#ifndef EGL_KHR_vg_parent_image
#define EGL_KHR_vg_parent_image 1
#define EGL_VG_PARENT_IMAGE_KHR           0x30BA
#endif /* EGL_KHR_vg_parent_image */

#ifndef EGL_KHR_wait_sync
#define EGL_KHR_wait_sync 1
typedef EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLint EGLAPIENTRY teglWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
extern teglWaitSyncKHR *eglWaitSyncKHR;
#endif
#endif /* EGL_KHR_wait_sync */

#ifndef EGL_ANDROID_blob_cache
#define EGL_ANDROID_blob_cache 1
typedef khronos_ssize_t EGLsizeiANDROID;
typedef void (*EGLSetBlobFuncANDROID) (const void *key, EGLsizeiANDROID keySize, const void *value, EGLsizeiANDROID valueSize);
typedef EGLsizeiANDROID (*EGLGetBlobFuncANDROID) (const void *key, EGLsizeiANDROID keySize, void *value, EGLsizeiANDROID valueSize);
typedef void (EGLAPIENTRYP PFNEGLSETBLOBCACHEFUNCSANDROIDPROC) (EGLDisplay dpy, EGLSetBlobFuncANDROID set, EGLGetBlobFuncANDROID get);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI void EGLAPIENTRY teglSetBlobCacheFuncsANDROID (EGLDisplay dpy, EGLSetBlobFuncANDROID set, EGLGetBlobFuncANDROID get);
extern teglSetBlobCacheFuncsANDROID *eglSetBlobCacheFuncsANDROID;
#endif
#endif /* EGL_ANDROID_blob_cache */

#ifndef EGL_ANDROID_framebuffer_target
#define EGL_ANDROID_framebuffer_target 1
#define EGL_FRAMEBUFFER_TARGET_ANDROID    0x3147
#endif /* EGL_ANDROID_framebuffer_target */

#ifndef EGL_ANDROID_image_native_buffer
#define EGL_ANDROID_image_native_buffer 1
#define EGL_NATIVE_BUFFER_ANDROID         0x3140
#endif /* EGL_ANDROID_image_native_buffer */

#ifndef EGL_ANDROID_native_fence_sync
#define EGL_ANDROID_native_fence_sync 1
#define EGL_SYNC_NATIVE_FENCE_ANDROID     0x3144
#define EGL_SYNC_NATIVE_FENCE_FD_ANDROID  0x3145
#define EGL_SYNC_NATIVE_FENCE_SIGNALED_ANDROID 0x3146
#define EGL_NO_NATIVE_FENCE_FD_ANDROID    -1
typedef EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLint EGLAPIENTRY teglDupNativeFenceFDANDROID (EGLDisplay dpy, EGLSyncKHR sync);
extern teglDupNativeFenceFDANDROID *eglDupNativeFenceFDANDROID;
#endif
#endif /* EGL_ANDROID_native_fence_sync */

#ifndef EGL_ANDROID_recordable
#define EGL_ANDROID_recordable 1
#define EGL_RECORDABLE_ANDROID            0x3142
#endif /* EGL_ANDROID_recordable */

#ifndef EGL_ANGLE_d3d_share_handle_client_buffer
#define EGL_ANGLE_d3d_share_handle_client_buffer 1
#define EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE 0x3200
#endif /* EGL_ANGLE_d3d_share_handle_client_buffer */

#ifndef EGL_ANGLE_device_d3d
#define EGL_ANGLE_device_d3d 1
#define EGL_D3D9_DEVICE_ANGLE             0x33A0
#define EGL_D3D11_DEVICE_ANGLE            0x33A1
#endif /* EGL_ANGLE_device_d3d */

#ifndef EGL_ANGLE_query_surface_pointer
#define EGL_ANGLE_query_surface_pointer 1
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACEPOINTERANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, void **value);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglQuerySurfacePointerANGLE (EGLDisplay dpy, EGLSurface surface, EGLint attribute, void **value);
extern teglQuerySurfacePointerANGLE *eglQuerySurfacePointerANGLE;
#endif
#endif /* EGL_ANGLE_query_surface_pointer */

#ifndef EGL_ANGLE_surface_d3d_texture_2d_share_handle
#define EGL_ANGLE_surface_d3d_texture_2d_share_handle 1
#endif /* EGL_ANGLE_surface_d3d_texture_2d_share_handle */

#ifndef EGL_ANGLE_window_fixed_size
#define EGL_ANGLE_window_fixed_size 1
#define EGL_FIXED_SIZE_ANGLE              0x3201
#endif /* EGL_ANGLE_window_fixed_size */

#ifndef EGL_ARM_pixmap_multisample_discard
#define EGL_ARM_pixmap_multisample_discard 1
#define EGL_DISCARD_SAMPLES_ARM           0x3286
#endif /* EGL_ARM_pixmap_multisample_discard */

#ifndef EGL_EXT_buffer_age
#define EGL_EXT_buffer_age 1
#define EGL_BUFFER_AGE_EXT                0x313D
#endif /* EGL_EXT_buffer_age */

#ifndef EGL_EXT_client_extensions
#define EGL_EXT_client_extensions 1
#endif /* EGL_EXT_client_extensions */

#ifndef EGL_EXT_create_context_robustness
#define EGL_EXT_create_context_robustness 1
#define EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT 0x30BF
#define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT 0x3138
#define EGL_NO_RESET_NOTIFICATION_EXT     0x31BE
#define EGL_LOSE_CONTEXT_ON_RESET_EXT     0x31BF
#endif /* EGL_EXT_create_context_robustness */

#ifndef EGL_EXT_device_base
#define EGL_EXT_device_base 1
typedef void *EGLDeviceEXT;
#define EGL_NO_DEVICE_EXT                 ((EGLDeviceEXT)(0))
#define EGL_BAD_DEVICE_EXT                0x322B
#define EGL_DEVICE_EXT                    0x322C
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEATTRIBEXTPROC) (EGLDeviceEXT device, EGLint attribute, EGLAttrib *value);
typedef const char *(EGLAPIENTRYP PFNEGLQUERYDEVICESTRINGEXTPROC) (EGLDeviceEXT device, EGLint name);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *num_devices);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBEXTPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *value);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglQueryDeviceAttribEXT (EGLDeviceEXT device, EGLint attribute, EGLAttrib *value);
typedef EGLAPI const char *EGLAPIENTRY teglQueryDeviceStringEXT (EGLDeviceEXT device, EGLint name);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglQueryDevicesEXT (EGLint max_devices, EGLDeviceEXT *devices, EGLint *num_devices);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglQueryDisplayAttribEXT (EGLDisplay dpy, EGLint attribute, EGLAttrib *value);
extern teglQueryDeviceAttribEXT *eglQueryDeviceAttribEXT;
extern teglQueryDeviceStringEXT *eglQueryDeviceStringEXT;
extern teglQueryDevicesEXT *eglQueryDevicesEXT;
extern teglQueryDisplayAttribEXT *eglQueryDisplayAttribEXT;
#endif
#endif /* EGL_EXT_device_base */

#ifndef EGL_EXT_device_drm
#define EGL_EXT_device_drm 1
#define EGL_DRM_DEVICE_FILE_EXT           0x3233
#endif /* EGL_EXT_device_drm */

#ifndef EGL_EXT_device_enumeration
#define EGL_EXT_device_enumeration 1
#endif /* EGL_EXT_device_enumeration */

#ifndef EGL_EXT_device_openwf
#define EGL_EXT_device_openwf 1
#define EGL_OPENWF_DEVICE_ID_EXT          0x3237
#endif /* EGL_EXT_device_openwf */

#ifndef EGL_EXT_device_query
#define EGL_EXT_device_query 1
#endif /* EGL_EXT_device_query */

#ifndef EGL_EXT_image_dma_buf_import
#define EGL_EXT_image_dma_buf_import 1
#define EGL_LINUX_DMA_BUF_EXT             0x3270
#define EGL_LINUX_DRM_FOURCC_EXT          0x3271
#define EGL_DMA_BUF_PLANE0_FD_EXT         0x3272
#define EGL_DMA_BUF_PLANE0_OFFSET_EXT     0x3273
#define EGL_DMA_BUF_PLANE0_PITCH_EXT      0x3274
#define EGL_DMA_BUF_PLANE1_FD_EXT         0x3275
#define EGL_DMA_BUF_PLANE1_OFFSET_EXT     0x3276
#define EGL_DMA_BUF_PLANE1_PITCH_EXT      0x3277
#define EGL_DMA_BUF_PLANE2_FD_EXT         0x3278
#define EGL_DMA_BUF_PLANE2_OFFSET_EXT     0x3279
#define EGL_DMA_BUF_PLANE2_PITCH_EXT      0x327A
#define EGL_YUV_COLOR_SPACE_HINT_EXT      0x327B
#define EGL_SAMPLE_RANGE_HINT_EXT         0x327C
#define EGL_YUV_CHROMA_HORIZONTAL_SITING_HINT_EXT 0x327D
#define EGL_YUV_CHROMA_VERTICAL_SITING_HINT_EXT 0x327E
#define EGL_ITU_REC601_EXT                0x327F
#define EGL_ITU_REC709_EXT                0x3280
#define EGL_ITU_REC2020_EXT               0x3281
#define EGL_YUV_FULL_RANGE_EXT            0x3282
#define EGL_YUV_NARROW_RANGE_EXT          0x3283
#define EGL_YUV_CHROMA_SITING_0_EXT       0x3284
#define EGL_YUV_CHROMA_SITING_0_5_EXT     0x3285
#endif /* EGL_EXT_image_dma_buf_import */

#ifndef EGL_EXT_multiview_window
#define EGL_EXT_multiview_window 1
#define EGL_MULTIVIEW_VIEW_COUNT_EXT      0x3134
#endif /* EGL_EXT_multiview_window */

#ifndef EGL_EXT_output_base
#define EGL_EXT_output_base 1
typedef void *EGLOutputLayerEXT;
typedef void *EGLOutputPortEXT;
#define EGL_NO_OUTPUT_LAYER_EXT           ((EGLOutputLayerEXT)0)
#define EGL_NO_OUTPUT_PORT_EXT            ((EGLOutputPortEXT)0)
#define EGL_BAD_OUTPUT_LAYER_EXT          0x322D
#define EGL_BAD_OUTPUT_PORT_EXT           0x322E
#define EGL_SWAP_INTERVAL_EXT             0x322F
typedef EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTLAYERSEXTPROC) (EGLDisplay dpy, const EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *num_layers);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTPORTSEXTPROC) (EGLDisplay dpy, const EGLAttrib *attrib_list, EGLOutputPortEXT *ports, EGLint max_ports, EGLint *num_ports);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib value);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *value);
typedef const char *(EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERSTRINGEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputPortEXT port, EGLint attribute, EGLAttrib value);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputPortEXT port, EGLint attribute, EGLAttrib *value);
typedef const char *(EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTSTRINGEXTPROC) (EGLDisplay dpy, EGLOutputPortEXT port, EGLint name);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglGetOutputLayersEXT (EGLDisplay dpy, const EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *num_layers);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglGetOutputPortsEXT (EGLDisplay dpy, const EGLAttrib *attrib_list, EGLOutputPortEXT *ports, EGLint max_ports, EGLint *num_ports);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib value);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglQueryOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *value);
typedef EGLAPI const char *EGLAPIENTRY teglQueryOutputLayerStringEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglOutputPortAttribEXT (EGLDisplay dpy, EGLOutputPortEXT port, EGLint attribute, EGLAttrib value);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglQueryOutputPortAttribEXT (EGLDisplay dpy, EGLOutputPortEXT port, EGLint attribute, EGLAttrib *value);
typedef EGLAPI const char *EGLAPIENTRY teglQueryOutputPortStringEXT (EGLDisplay dpy, EGLOutputPortEXT port, EGLint name);
extern teglGetOutputLayersEXT *eglGetOutputLayersEXT;
extern teglGetOutputPortsEXT *eglGetOutputPortsEXT;
extern teglOutputLayerAttribEXT *eglOutputLayerAttribEXT;
extern teglQueryOutputLayerAttribEXT *eglQueryOutputLayerAttribEXT;
extern teglQueryOutputLayerStringEXT *eglQueryOutputLayerStringEXT;
extern teglOutputPortAttribEXT *eglOutputPortAttribEXT;
extern teglQueryOutputPortAttribEXT *eglQueryOutputPortAttribEXT;
extern teglQueryOutputPortStringEXT *eglQueryOutputPortStringEXT;
#endif
#endif /* EGL_EXT_output_base */

#ifndef EGL_EXT_output_drm
#define EGL_EXT_output_drm 1
#define EGL_DRM_CRTC_EXT                  0x3234
#define EGL_DRM_PLANE_EXT                 0x3235
#define EGL_DRM_CONNECTOR_EXT             0x3236
#endif /* EGL_EXT_output_drm */

#ifndef EGL_EXT_output_openwf
#define EGL_EXT_output_openwf 1
#define EGL_OPENWF_PIPELINE_ID_EXT        0x3238
#define EGL_OPENWF_PORT_ID_EXT            0x3239
#endif /* EGL_EXT_output_openwf */

#ifndef EGL_EXT_platform_base
#define EGL_EXT_platform_base 1
typedef EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, void *native_display, const EGLint *attrib_list);
typedef EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, void *native_window, const EGLint *attrib_list);
typedef EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, void *native_pixmap, const EGLint *attrib_list);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLDisplay EGLAPIENTRY teglGetPlatformDisplayEXT (EGLenum platform, void *native_display, const EGLint *attrib_list);
typedef EGLAPI EGLSurface EGLAPIENTRY teglCreatePlatformWindowSurfaceEXT (EGLDisplay dpy, EGLConfig config, void *native_window, const EGLint *attrib_list);
typedef EGLAPI EGLSurface EGLAPIENTRY teglCreatePlatformPixmapSurfaceEXT (EGLDisplay dpy, EGLConfig config, void *native_pixmap, const EGLint *attrib_list);
extern teglGetPlatformDisplayEXT *eglGetPlatformDisplayEXT;
extern teglCreatePlatformWindowSurfaceEXT *eglCreatePlatformWindowSurfaceEXT;
extern teglCreatePlatformPixmapSurfaceEXT *eglCreatePlatformPixmapSurfaceEXT;
#endif
#endif /* EGL_EXT_platform_base */

#ifndef EGL_EXT_platform_device
#define EGL_EXT_platform_device 1
#define EGL_PLATFORM_DEVICE_EXT           0x313F
#endif /* EGL_EXT_platform_device */

#ifndef EGL_EXT_platform_wayland
#define EGL_EXT_platform_wayland 1
#define EGL_PLATFORM_WAYLAND_EXT          0x31D8
#endif /* EGL_EXT_platform_wayland */

#ifndef EGL_EXT_platform_x11
#define EGL_EXT_platform_x11 1
#define EGL_PLATFORM_X11_EXT              0x31D5
#define EGL_PLATFORM_X11_SCREEN_EXT       0x31D6
#endif /* EGL_EXT_platform_x11 */

#ifndef EGL_EXT_protected_surface
#define EGL_EXT_protected_surface 1
#define EGL_PROTECTED_CONTENT_EXT         0x32C0
#endif /* EGL_EXT_protected_surface */

#ifndef EGL_EXT_stream_consumer_egloutput
#define EGL_EXT_stream_consumer_egloutput 1
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMEROUTPUTEXTPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLOutputLayerEXT layer);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglStreamConsumerOutputEXT (EGLDisplay dpy, EGLStreamKHR stream, EGLOutputLayerEXT layer);
extern teglStreamConsumerOutputEXT *eglStreamConsumerOutputEXT;
#endif
#endif /* EGL_EXT_stream_consumer_egloutput */

#ifndef EGL_EXT_swap_buffers_with_damage
#define EGL_EXT_swap_buffers_with_damage 1
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglSwapBuffersWithDamageEXT (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
extern teglSwapBuffersWithDamageEXT *eglSwapBuffersWithDamageEXT;
#endif
#endif /* EGL_EXT_swap_buffers_with_damage */

#ifndef EGL_EXT_yuv_surface
#define EGL_EXT_yuv_surface 1
#define EGL_YUV_ORDER_EXT                 0x3301
#define EGL_YUV_NUMBER_OF_PLANES_EXT      0x3311
#define EGL_YUV_SUBSAMPLE_EXT             0x3312
#define EGL_YUV_DEPTH_RANGE_EXT           0x3317
#define EGL_YUV_CSC_STANDARD_EXT          0x330A
#define EGL_YUV_PLANE_BPP_EXT             0x331A
#define EGL_YUV_BUFFER_EXT                0x3300
#define EGL_YUV_ORDER_YUV_EXT             0x3302
#define EGL_YUV_ORDER_YVU_EXT             0x3303
#define EGL_YUV_ORDER_YUYV_EXT            0x3304
#define EGL_YUV_ORDER_UYVY_EXT            0x3305
#define EGL_YUV_ORDER_YVYU_EXT            0x3306
#define EGL_YUV_ORDER_VYUY_EXT            0x3307
#define EGL_YUV_ORDER_AYUV_EXT            0x3308
#define EGL_YUV_SUBSAMPLE_4_2_0_EXT       0x3313
#define EGL_YUV_SUBSAMPLE_4_2_2_EXT       0x3314
#define EGL_YUV_SUBSAMPLE_4_4_4_EXT       0x3315
#define EGL_YUV_DEPTH_RANGE_LIMITED_EXT   0x3318
#define EGL_YUV_DEPTH_RANGE_FULL_EXT      0x3319
#define EGL_YUV_CSC_STANDARD_601_EXT      0x330B
#define EGL_YUV_CSC_STANDARD_709_EXT      0x330C
#define EGL_YUV_CSC_STANDARD_2020_EXT     0x330D
#define EGL_YUV_PLANE_BPP_0_EXT           0x331B
#define EGL_YUV_PLANE_BPP_8_EXT           0x331C
#define EGL_YUV_PLANE_BPP_10_EXT          0x331D
#endif /* EGL_EXT_yuv_surface */

#ifndef EGL_HI_clientpixmap
#define EGL_HI_clientpixmap 1
struct EGLClientPixmapHI {
    void  *pData;
    EGLint iWidth;
    EGLint iHeight;
    EGLint iStride;
};
#define EGL_CLIENT_PIXMAP_POINTER_HI      0x8F74
typedef EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEHIPROC) (EGLDisplay dpy, EGLConfig config, struct EGLClientPixmapHI *pixmap);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLSurface EGLAPIENTRY teglCreatePixmapSurfaceHI (EGLDisplay dpy, EGLConfig config, struct EGLClientPixmapHI *pixmap);
extern teglCreatePixmapSurfaceHI *eglCreatePixmapSurfaceHI;
#endif
#endif /* EGL_HI_clientpixmap */

#ifndef EGL_HI_colorformats
#define EGL_HI_colorformats 1
#define EGL_COLOR_FORMAT_HI               0x8F70
#define EGL_COLOR_RGB_HI                  0x8F71
#define EGL_COLOR_RGBA_HI                 0x8F72
#define EGL_COLOR_ARGB_HI                 0x8F73
#endif /* EGL_HI_colorformats */

#ifndef EGL_IMG_context_priority
#define EGL_IMG_context_priority 1
#define EGL_CONTEXT_PRIORITY_LEVEL_IMG    0x3100
#define EGL_CONTEXT_PRIORITY_HIGH_IMG     0x3101
#define EGL_CONTEXT_PRIORITY_MEDIUM_IMG   0x3102
#define EGL_CONTEXT_PRIORITY_LOW_IMG      0x3103
#endif /* EGL_IMG_context_priority */

#ifndef EGL_MESA_drm_image
#define EGL_MESA_drm_image 1
#define EGL_DRM_BUFFER_FORMAT_MESA        0x31D0
#define EGL_DRM_BUFFER_USE_MESA           0x31D1
#define EGL_DRM_BUFFER_FORMAT_ARGB32_MESA 0x31D2
#define EGL_DRM_BUFFER_MESA               0x31D3
#define EGL_DRM_BUFFER_STRIDE_MESA        0x31D4
#define EGL_DRM_BUFFER_USE_SCANOUT_MESA   0x00000001
#define EGL_DRM_BUFFER_USE_SHARE_MESA     0x00000002
typedef EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEDRMIMAGEMESAPROC) (EGLDisplay dpy, const EGLint *attrib_list);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDRMIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLImageKHR EGLAPIENTRY teglCreateDRMImageMESA (EGLDisplay dpy, const EGLint *attrib_list);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglExportDRMImageMESA (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
extern teglCreateDRMImageMESA *eglCreateDRMImageMESA;
extern teglExportDRMImageMESA *eglExportDRMImageMESA;
#endif
#endif /* EGL_MESA_drm_image */

#ifndef EGL_MESA_image_dma_buf_export
#define EGL_MESA_image_dma_buf_export 1
typedef EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC) (EGLDisplay dpy, EGLImageKHR image, int *fourcc, int *num_planes, EGLuint64KHR *modifiers);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, int *fds, EGLint *strides, EGLint *offsets);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglExportDMABUFImageQueryMESA (EGLDisplay dpy, EGLImageKHR image, int *fourcc, int *num_planes, EGLuint64KHR *modifiers);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglExportDMABUFImageMESA (EGLDisplay dpy, EGLImageKHR image, int *fds, EGLint *strides, EGLint *offsets);
extern teglExportDMABUFImageQueryMESA *eglExportDMABUFImageQueryMESA;
extern teglExportDMABUFImageMESA *eglExportDMABUFImageMESA;
#endif
#endif /* EGL_MESA_image_dma_buf_export */

#ifndef EGL_MESA_platform_gbm
#define EGL_MESA_platform_gbm 1
#define EGL_PLATFORM_GBM_MESA             0x31D7
#endif /* EGL_MESA_platform_gbm */

#ifndef EGL_NOK_swap_region
#define EGL_NOK_swap_region 1
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGIONNOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint numRects, const EGLint *rects);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglSwapBuffersRegionNOK (EGLDisplay dpy, EGLSurface surface, EGLint numRects, const EGLint *rects);
extern teglSwapBuffersRegionNOK *eglSwapBuffersRegionNOK;
#endif
#endif /* EGL_NOK_swap_region */

#ifndef EGL_NOK_swap_region2
#define EGL_NOK_swap_region2 1
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGION2NOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint numRects, const EGLint *rects);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglSwapBuffersRegion2NOK (EGLDisplay dpy, EGLSurface surface, EGLint numRects, const EGLint *rects);
extern teglSwapBuffersRegion2NOK *eglSwapBuffersRegion2NOK;
#endif
#endif /* EGL_NOK_swap_region2 */

#ifndef EGL_NOK_texture_from_pixmap
#define EGL_NOK_texture_from_pixmap 1
#define EGL_Y_INVERTED_NOK                0x307F
#endif /* EGL_NOK_texture_from_pixmap */

#ifndef EGL_NV_3dvision_surface
#define EGL_NV_3dvision_surface 1
#define EGL_AUTO_STEREO_NV                0x3136
#endif /* EGL_NV_3dvision_surface */

#ifndef EGL_NV_coverage_sample
#define EGL_NV_coverage_sample 1
#define EGL_COVERAGE_BUFFERS_NV           0x30E0
#define EGL_COVERAGE_SAMPLES_NV           0x30E1
#endif /* EGL_NV_coverage_sample */

#ifndef EGL_NV_coverage_sample_resolve
#define EGL_NV_coverage_sample_resolve 1
#define EGL_COVERAGE_SAMPLE_RESOLVE_NV    0x3131
#define EGL_COVERAGE_SAMPLE_RESOLVE_DEFAULT_NV 0x3132
#define EGL_COVERAGE_SAMPLE_RESOLVE_NONE_NV 0x3133
#endif /* EGL_NV_coverage_sample_resolve */

#ifndef EGL_NV_cuda_event
#define EGL_NV_cuda_event 1
#define EGL_CUDA_EVENT_HANDLE_NV          0x323B
#define EGL_SYNC_CUDA_EVENT_NV            0x323C
#define EGL_SYNC_CUDA_EVENT_COMPLETE_NV   0x323D
#endif /* EGL_NV_cuda_event */

#ifndef EGL_NV_depth_nonlinear
#define EGL_NV_depth_nonlinear 1
#define EGL_DEPTH_ENCODING_NV             0x30E2
#define EGL_DEPTH_ENCODING_NONE_NV        0
#define EGL_DEPTH_ENCODING_NONLINEAR_NV   0x30E3
#endif /* EGL_NV_depth_nonlinear */

#ifndef EGL_NV_device_cuda
#define EGL_NV_device_cuda 1
#define EGL_CUDA_DEVICE_NV                0x323A
#endif /* EGL_NV_device_cuda */

#ifndef EGL_NV_native_query
#define EGL_NV_native_query 1
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEDISPLAYNVPROC) (EGLDisplay dpy, EGLNativeDisplayType *display_id);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEWINDOWNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNativeWindowType *window);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEPIXMAPNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglQueryNativeDisplayNV (EGLDisplay dpy, EGLNativeDisplayType *display_id);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglQueryNativeWindowNV (EGLDisplay dpy, EGLSurface surf, EGLNativeWindowType *window);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglQueryNativePixmapNV (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
extern teglQueryNativeDisplayNV *eglQueryNativeDisplayNV;
extern teglQueryNativeWindowNV *eglQueryNativeWindowNV;
extern teglQueryNativePixmapNV *eglQueryNativePixmapNV;
#endif
#endif /* EGL_NV_native_query */

#ifndef EGL_NV_post_convert_rounding
#define EGL_NV_post_convert_rounding 1
#endif /* EGL_NV_post_convert_rounding */

#ifndef EGL_NV_post_sub_buffer
#define EGL_NV_post_sub_buffer 1
#define EGL_POST_SUB_BUFFER_SUPPORTED_NV  0x30BE
typedef EGLBoolean (EGLAPIENTRYP PFNEGLPOSTSUBBUFFERNVPROC) (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint width, EGLint height);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglPostSubBufferNV (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint width, EGLint height);
extern teglPostSubBufferNV *eglPostSubBufferNV;
#endif
#endif /* EGL_NV_post_sub_buffer */

#ifndef EGL_NV_stream_sync
#define EGL_NV_stream_sync 1
#define EGL_SYNC_NEW_FRAME_NV             0x321F
typedef EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESTREAMSYNCNVPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLenum type, const EGLint *attrib_list);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLSyncKHR EGLAPIENTRY teglCreateStreamSyncNV (EGLDisplay dpy, EGLStreamKHR stream, EGLenum type, const EGLint *attrib_list);
extern teglCreateStreamSyncNV *eglCreateStreamSyncNV;
#endif
#endif /* EGL_NV_stream_sync */

#ifndef EGL_NV_sync
#define EGL_NV_sync 1
typedef void *EGLSyncNV;
typedef khronos_utime_nanoseconds_t EGLTimeNV;
#ifdef KHRONOS_SUPPORT_INT64
#define EGL_SYNC_PRIOR_COMMANDS_COMPLETE_NV 0x30E6
#define EGL_SYNC_STATUS_NV                0x30E7
#define EGL_SIGNALED_NV                   0x30E8
#define EGL_UNSIGNALED_NV                 0x30E9
#define EGL_SYNC_FLUSH_COMMANDS_BIT_NV    0x0001
#define EGL_FOREVER_NV                    0xFFFFFFFFFFFFFFFFull
#define EGL_ALREADY_SIGNALED_NV           0x30EA
#define EGL_TIMEOUT_EXPIRED_NV            0x30EB
#define EGL_CONDITION_SATISFIED_NV        0x30EC
#define EGL_SYNC_TYPE_NV                  0x30ED
#define EGL_SYNC_CONDITION_NV             0x30EE
#define EGL_SYNC_FENCE_NV                 0x30EF
#define EGL_NO_SYNC_NV                    ((EGLSyncNV)0)
typedef EGLSyncNV (EGLAPIENTRYP PFNEGLCREATEFENCESYNCNVPROC) (EGLDisplay dpy, EGLenum condition, const EGLint *attrib_list);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCNVPROC) (EGLSyncNV sync);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLFENCENVPROC) (EGLSyncNV sync);
typedef EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCNVPROC) (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCNVPROC) (EGLSyncNV sync, EGLenum mode);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBNVPROC) (EGLSyncNV sync, EGLint attribute, EGLint *value);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLSyncNV EGLAPIENTRY teglCreateFenceSyncNV (EGLDisplay dpy, EGLenum condition, const EGLint *attrib_list);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglDestroySyncNV (EGLSyncNV sync);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglFenceNV (EGLSyncNV sync);
typedef EGLAPI EGLint EGLAPIENTRY teglClientWaitSyncNV (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglSignalSyncNV (EGLSyncNV sync, EGLenum mode);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglGetSyncAttribNV (EGLSyncNV sync, EGLint attribute, EGLint *value);
extern teglCreateFenceSyncNV *eglCreateFenceSyncNV;
extern teglDestroySyncNV *eglDestroySyncNV;
extern teglFenceNV *eglFenceNV;
extern teglClientWaitSyncNV *eglClientWaitSyncNV;
extern teglSignalSyncNV *eglSignalSyncNV;
extern teglGetSyncAttribNV *eglGetSyncAttribNV;
#endif
#endif /* KHRONOS_SUPPORT_INT64 */
#endif /* EGL_NV_sync */

#ifndef EGL_NV_system_time
#define EGL_NV_system_time 1
typedef khronos_utime_nanoseconds_t EGLuint64NV;
#ifdef KHRONOS_SUPPORT_INT64
typedef EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC) (void);
typedef EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMENVPROC) (void);
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLuint64NV EGLAPIENTRY teglGetSystemTimeFrequencyNV (void);
typedef EGLAPI EGLuint64NV EGLAPIENTRY teglGetSystemTimeNV (void);
extern teglGetSystemTimeFrequencyNV *eglGetSystemTimeFrequencyNV;
extern teglGetSystemTimeNV *eglGetSystemTimeNV;
#endif
#endif /* KHRONOS_SUPPORT_INT64 */
#endif /* EGL_NV_system_time */

#ifndef EGL_TIZEN_image_native_buffer
#define EGL_TIZEN_image_native_buffer 1
#define EGL_NATIVE_BUFFER_TIZEN           0x32A0
#endif /* EGL_TIZEN_image_native_buffer */

#ifndef EGL_TIZEN_image_native_surface
#define EGL_TIZEN_image_native_surface 1
#define EGL_NATIVE_SURFACE_TIZEN          0x32A1
#endif /* EGL_TIZEN_image_native_surface */


#ifdef __cplusplus
}
#endif

#endif
// Copyright (c) 2013 The Chromium Authors. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// This file contains Chromium-specific EGL extensions declarations.

#ifndef GPU_EGL_EGLEXTCHROMIUM_H_
#define GPU_EGL_EGLEXTCHROMIUM_H_

#ifdef __cplusplus
extern "C" {
#endif


/* EGLSyncControlCHROMIUM requires 64-bit uint support */
#if KHRONOS_SUPPORT_INT64
#ifndef EGL_CHROMIUM_sync_control
#define EGL_CHROMIUM_sync_control 1
typedef khronos_uint64_t EGLuint64CHROMIUM;
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglGetSyncValuesCHROMIUM(
    EGLDisplay dpy, EGLSurface surface, EGLuint64CHROMIUM *ust,
    EGLuint64CHROMIUM *msc, EGLuint64CHROMIUM *sbc);
extern teglGetSyncValuesCHROMIUM *eglGetSyncValuesCHROMIUM;
#endif /* EGL_EGLEXT_PROTOTYPES */
typedef EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCVALUESCHROMIUMPROC)
    (EGLDisplay dpy, EGLSurface surface, EGLuint64CHROMIUM *ust,
     EGLuint64CHROMIUM *msc, EGLuint64CHROMIUM *sbc);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif // GPU_EGL_EGLEXTCHROMIUM_H_
/**************************************************************************
 *
 * Copyright 2008 VMware, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#ifndef __eglmesaext_h_
#define __eglmesaext_h_

#ifdef __cplusplus
extern "C" {
#endif


#ifndef EGL_MESA_drm_display
#define EGL_MESA_drm_display 1

#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLDisplay EGLAPIENTRY teglGetDRMDisplayMESA(int fd);
extern teglGetDRMDisplayMESA *eglGetDRMDisplayMESA;
#endif /* EGL_EGLEXT_PROTOTYPES */

typedef EGLDisplay (EGLAPIENTRYP PFNEGLGETDRMDISPLAYMESA) (int fd);

#endif /* EGL_MESA_drm_display */

#ifdef EGL_MESA_drm_image
/* Mesa's extension to EGL_MESA_drm_image... */
#ifndef EGL_DRM_BUFFER_USE_CURSOR_MESA
#define EGL_DRM_BUFFER_USE_CURSOR_MESA		0x0004
#endif
#endif

#ifndef EGL_WL_bind_wayland_display
#define EGL_WL_bind_wayland_display 1

#define EGL_WAYLAND_BUFFER_WL		0x31D5 /* eglCreateImageKHR target */
#define EGL_WAYLAND_PLANE_WL		0x31D6 /* eglCreateImageKHR target */

#define EGL_WAYLAND_Y_INVERTED_WL	0x31DB /* eglQueryWaylandBufferWL attribute */

#define EGL_TEXTURE_Y_U_V_WL            0x31D7
#define EGL_TEXTURE_Y_UV_WL             0x31D8
#define EGL_TEXTURE_Y_XUXV_WL           0x31D9

struct wl_display;
struct wl_resource;
#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI EGLBoolean EGLAPIENTRY teglBindWaylandDisplayWL(EGLDisplay dpy, struct wl_display *display);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglUnbindWaylandDisplayWL(EGLDisplay dpy, struct wl_display *display);
typedef EGLAPI EGLBoolean EGLAPIENTRY teglQueryWaylandBufferWL(EGLDisplay dpy, struct wl_resource *buffer, EGLint attribute, EGLint *value);
extern teglBindWaylandDisplayWL *eglBindWaylandDisplayWL;
extern teglUnbindWaylandDisplayWL *eglUnbindWaylandDisplayWL;
extern teglQueryWaylandBufferWL *eglQueryWaylandBufferWL;
#endif
typedef EGLBoolean (EGLAPIENTRYP PFNEGLBINDWAYLANDDISPLAYWL) (EGLDisplay dpy, struct wl_display *display);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLUNBINDWAYLANDDISPLAYWL) (EGLDisplay dpy, struct wl_display *display);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYWAYLANDBUFFERWL) (EGLDisplay dpy, struct wl_resource *buffer, EGLint attribute, EGLint *value);

#endif

#ifndef EGL_WL_create_wayland_buffer_from_image
#define EGL_WL_create_wayland_buffer_from_image 1

#ifdef EGL_EGLEXT_PROTOTYPES
typedef EGLAPI struct wl_buffer * EGLAPIENTRY teglCreateWaylandBufferFromImageWL(EGLDisplay dpy, EGLImageKHR image);
extern teglCreateWaylandBufferFromImageWL *eglCreateWaylandBufferFromImageWL;
#endif
typedef struct wl_buffer * (EGLAPIENTRYP PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWL) (EGLDisplay dpy, EGLImageKHR image);

#endif

/* remnant of EGL_NOK_swap_region kept for compatibility because of a non-standard type name */
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGIONNOK) (EGLDisplay dpy, EGLSurface surface, EGLint numRects, const EGLint* rects);

#ifndef EGL_MESA_configless_context
#define EGL_MESA_configless_context 1
#define EGL_NO_CONFIG_MESA			((EGLConfig)0)
#endif

#ifdef __cplusplus
}
#endif

#endif

enum {
  EGLEW_SUCCESS = 0,
  EGLEW_ERROR_OPEN_FAILED = -1,
  EGLEW_ERROR_ATEXIT_FAILED = -2,
};

int eglwInit(void);

#ifdef __cplusplus
}
#endif

#endif  /* __EGLEW_H__ */
