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

#ifdef _MSC_VER
#  define snprintf _snprintf
#  define _CRT_SECURE_NO_WARNINGS
#endif

#include <eglew.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  define VC_EXTRALEAN
#  include <windows.h>

/* Utility macros. */

typedef HMODULE DynamicLibrary;

#  define dynamic_library_open(path)         LoadLibraryA(path)
#  define dynamic_library_close(lib)         FreeLibrary(lib)
#  define dynamic_library_find(lib, symbol)  GetProcAddress(lib, symbol)
#else
#  include <dlfcn.h>

typedef void* DynamicLibrary;

#  define dynamic_library_open(path)         dlopen(path, RTLD_NOW)
#  define dynamic_library_close(lib)         dlclose(lib)
#  define dynamic_library_find(lib, symbol)  dlsym(lib, symbol)
#endif

#define _LIBRARY_FIND_CHECKED(lib, name) \
        name = (t##name *)dynamic_library_find(lib, #name); \
        assert(name);

#define _LIBRARY_FIND(lib, name) \
        name = (t##name *)dynamic_library_find(lib, #name);

#define EGL_LIBRARY_FIND_CHECKED(name) \
        _LIBRARY_FIND_CHECKED(egl_lib, name)
#define EGL_LIBRARY_FIND(name) _LIBRARY_FIND(egl_lib, name)

static DynamicLibrary egl_lib;

/* Function definitions. */
/* egl.h */
teglBindAPI *eglBindAPI;
teglBindTexImage *eglBindTexImage;
teglChooseConfig *eglChooseConfig;
teglClientWaitSync *eglClientWaitSync;
teglCopyBuffers *eglCopyBuffers;
teglCreateContext *eglCreateContext;
teglCreateImage *eglCreateImage;
teglCreatePbufferFromClientBuffer *eglCreatePbufferFromClientBuffer;
teglCreatePbufferSurface *eglCreatePbufferSurface;
teglCreatePixmapSurface *eglCreatePixmapSurface;
teglCreatePlatformPixmapSurface *eglCreatePlatformPixmapSurface;
teglCreatePlatformWindowSurface *eglCreatePlatformWindowSurface;
teglCreateSync *eglCreateSync;
teglCreateWindowSurface *eglCreateWindowSurface;
teglDestroyContext *eglDestroyContext;
teglDestroyImage *eglDestroyImage;
teglDestroySurface *eglDestroySurface;
teglDestroySync *eglDestroySync;
teglGetConfigAttrib *eglGetConfigAttrib;
teglGetConfigs *eglGetConfigs;
teglGetCurrentContext *eglGetCurrentContext;
teglGetCurrentDisplay *eglGetCurrentDisplay;
teglGetCurrentSurface *eglGetCurrentSurface;
teglGetDisplay *eglGetDisplay;
teglGetError *eglGetError;
teglGetPlatformDisplay *eglGetPlatformDisplay;
teglGetProcAddress *eglGetProcAddress;
teglGetSyncAttrib *eglGetSyncAttrib;
teglInitialize *eglInitialize;
teglMakeCurrent *eglMakeCurrent;
teglQueryAPI *eglQueryAPI;
teglQueryContext *eglQueryContext;
teglQueryString *eglQueryString;
teglQuerySurface *eglQuerySurface;
teglReleaseTexImage *eglReleaseTexImage;
teglReleaseThread *eglReleaseThread;
teglSurfaceAttrib *eglSurfaceAttrib;
teglSwapBuffers *eglSwapBuffers;
teglSwapInterval *eglSwapInterval;
teglTerminate *eglTerminate;
teglWaitClient *eglWaitClient;
teglWaitGL *eglWaitGL;
teglWaitNative *eglWaitNative;
teglWaitSync *eglWaitSync;
/* eglext.h */
teglClientWaitSyncKHR *eglClientWaitSyncKHR;
teglClientWaitSyncNV *eglClientWaitSyncNV;
teglCreateDRMImageMESA *eglCreateDRMImageMESA;
teglCreateFenceSyncNV *eglCreateFenceSyncNV;
teglCreateImageKHR *eglCreateImageKHR;
teglCreatePixmapSurfaceHI *eglCreatePixmapSurfaceHI;
teglCreatePlatformPixmapSurfaceEXT *eglCreatePlatformPixmapSurfaceEXT;
teglCreatePlatformWindowSurfaceEXT *eglCreatePlatformWindowSurfaceEXT;
teglCreateStreamFromFileDescriptorKHR *eglCreateStreamFromFileDescriptorKHR;
teglCreateStreamKHR *eglCreateStreamKHR;
teglCreateStreamProducerSurfaceKHR *eglCreateStreamProducerSurfaceKHR;
teglCreateStreamSyncNV *eglCreateStreamSyncNV;
teglCreateSync64KHR *eglCreateSync64KHR;
teglCreateSyncKHR *eglCreateSyncKHR;
teglDestroyImageKHR *eglDestroyImageKHR;
teglDestroyStreamKHR *eglDestroyStreamKHR;
teglDestroySyncKHR *eglDestroySyncKHR;
teglDestroySyncNV *eglDestroySyncNV;
teglDupNativeFenceFDANDROID *eglDupNativeFenceFDANDROID;
teglExportDMABUFImageMESA *eglExportDMABUFImageMESA;
teglExportDMABUFImageQueryMESA *eglExportDMABUFImageQueryMESA;
teglExportDRMImageMESA *eglExportDRMImageMESA;
teglFenceNV *eglFenceNV;
teglGetOutputLayersEXT *eglGetOutputLayersEXT;
teglGetOutputPortsEXT *eglGetOutputPortsEXT;
teglGetPlatformDisplayEXT *eglGetPlatformDisplayEXT;
teglGetStreamFileDescriptorKHR *eglGetStreamFileDescriptorKHR;
teglGetSyncAttribKHR *eglGetSyncAttribKHR;
teglGetSyncAttribNV *eglGetSyncAttribNV;
teglGetSystemTimeFrequencyNV *eglGetSystemTimeFrequencyNV;
teglGetSystemTimeNV *eglGetSystemTimeNV;
teglLockSurfaceKHR *eglLockSurfaceKHR;
teglOutputLayerAttribEXT *eglOutputLayerAttribEXT;
teglOutputPortAttribEXT *eglOutputPortAttribEXT;
teglPostSubBufferNV *eglPostSubBufferNV;
teglQueryDeviceAttribEXT *eglQueryDeviceAttribEXT;
teglQueryDeviceStringEXT *eglQueryDeviceStringEXT;
teglQueryDevicesEXT *eglQueryDevicesEXT;
teglQueryDisplayAttribEXT *eglQueryDisplayAttribEXT;
teglQueryNativeDisplayNV *eglQueryNativeDisplayNV;
teglQueryNativePixmapNV *eglQueryNativePixmapNV;
teglQueryNativeWindowNV *eglQueryNativeWindowNV;
teglQueryOutputLayerAttribEXT *eglQueryOutputLayerAttribEXT;
teglQueryOutputLayerStringEXT *eglQueryOutputLayerStringEXT;
teglQueryOutputPortAttribEXT *eglQueryOutputPortAttribEXT;
teglQueryOutputPortStringEXT *eglQueryOutputPortStringEXT;
teglQueryStreamKHR *eglQueryStreamKHR;
teglQueryStreamTimeKHR *eglQueryStreamTimeKHR;
teglQueryStreamu64KHR *eglQueryStreamu64KHR;
teglQuerySurface64KHR *eglQuerySurface64KHR;
teglQuerySurfacePointerANGLE *eglQuerySurfacePointerANGLE;
teglSetBlobCacheFuncsANDROID *eglSetBlobCacheFuncsANDROID;
teglSetDamageRegionKHR *eglSetDamageRegionKHR;
teglSignalSyncKHR *eglSignalSyncKHR;
teglSignalSyncNV *eglSignalSyncNV;
teglStreamAttribKHR *eglStreamAttribKHR;
teglStreamConsumerAcquireKHR *eglStreamConsumerAcquireKHR;
teglStreamConsumerGLTextureExternalKHR *eglStreamConsumerGLTextureExternalKHR;
teglStreamConsumerOutputEXT *eglStreamConsumerOutputEXT;
teglStreamConsumerReleaseKHR *eglStreamConsumerReleaseKHR;
teglSwapBuffersRegion2NOK *eglSwapBuffersRegion2NOK;
teglSwapBuffersRegionNOK *eglSwapBuffersRegionNOK;
teglSwapBuffersWithDamageEXT *eglSwapBuffersWithDamageEXT;
teglSwapBuffersWithDamageKHR *eglSwapBuffersWithDamageKHR;
teglUnlockSurfaceKHR *eglUnlockSurfaceKHR;
teglWaitSyncKHR *eglWaitSyncKHR;
/* eglextchromium.h */
teglGetSyncValuesCHROMIUM *eglGetSyncValuesCHROMIUM;
/* eglmesaext.h */
teglBindWaylandDisplayWL *eglBindWaylandDisplayWL;
teglCreateWaylandBufferFromImageWL *eglCreateWaylandBufferFromImageWL;
teglGetDRMDisplayMESA *eglGetDRMDisplayMESA;
teglQueryWaylandBufferWL *eglQueryWaylandBufferWL;
teglUnbindWaylandDisplayWL *eglUnbindWaylandDisplayWL;

static DynamicLibrary dynamic_library_open_find(const char **paths) {
  int i = 0;
  while (paths[i] != NULL) {
      DynamicLibrary lib = dynamic_library_open(paths[i]);
      if (lib != NULL) {
        return lib;
      }
      ++i;
  }
  return NULL;
}

static void eglewExit(void) {
  if(egl_lib != NULL) {
    /* Ignore errors. */
    dynamic_library_close(egl_lib);
    egl_lib = NULL;
  }
}

/* Implementation function. */
int eglewInit(void) {
  /* Library paths. */
#ifdef _WIN32
  /* Expected in c:/windows/system or similar, no path needed. */
  const char *egl_paths[] = {"egl.dll", NULL};
#elif defined(__APPLE__)
  /* Default installation path. */
  /* TODO(sergey): This requires double-check. */
  const char *egl_paths[] = {"libegl.dylib", NULL};
#else
  /* TODO(sergey): How can we make ABI detection more reliable? */
  const char *egl_paths[] = {"libEGL.so",
                             "libEGL.so.1",
                             "libEGL.so.2",
                             "libEGL.so.3",
                             NULL};
#endif
  static int initialized = 0;
  static int result = 0;
  int error, driver_version;

  if (initialized) {
    return result;
  }

  initialized = 1;

  error = atexit(eglewExit);
  if (error) {
    result = EGLEW_ERROR_ATEXIT_FAILED;
    return result;
  }

  /* Load library. */
  egl_lib = dynamic_library_open_find(egl_paths);

  /* EGL library is mandatory to have. */
  if (egl_lib == NULL) {
    result = EGLEW_ERROR_OPEN_FAILED;
    return result;
  }

  /* Fetch all function pointers. */
  /* egl.h */
  EGL_LIBRARY_FIND(eglBindAPI);
  EGL_LIBRARY_FIND(eglBindTexImage);
  EGL_LIBRARY_FIND(eglChooseConfig);
  EGL_LIBRARY_FIND(eglClientWaitSync);
  EGL_LIBRARY_FIND(eglCopyBuffers);
  EGL_LIBRARY_FIND(eglCreateContext);
  EGL_LIBRARY_FIND(eglCreateImage);
  EGL_LIBRARY_FIND(eglCreatePbufferFromClientBuffer);
  EGL_LIBRARY_FIND(eglCreatePbufferSurface);
  EGL_LIBRARY_FIND(eglCreatePixmapSurface);
  EGL_LIBRARY_FIND(eglCreatePlatformPixmapSurface);
  EGL_LIBRARY_FIND(eglCreatePlatformWindowSurface);
  EGL_LIBRARY_FIND(eglCreateSync);
  EGL_LIBRARY_FIND(eglCreateWindowSurface);
  EGL_LIBRARY_FIND(eglDestroyContext);
  EGL_LIBRARY_FIND(eglDestroyImage);
  EGL_LIBRARY_FIND(eglDestroySurface);
  EGL_LIBRARY_FIND(eglDestroySync);
  EGL_LIBRARY_FIND(eglGetConfigAttrib);
  EGL_LIBRARY_FIND(eglGetConfigs);
  EGL_LIBRARY_FIND(eglGetCurrentContext);
  EGL_LIBRARY_FIND(eglGetCurrentDisplay);
  EGL_LIBRARY_FIND(eglGetCurrentSurface);
  EGL_LIBRARY_FIND(eglGetDisplay);
  EGL_LIBRARY_FIND(eglGetError);
  EGL_LIBRARY_FIND(eglGetPlatformDisplay);
  EGL_LIBRARY_FIND(eglGetProcAddress);
  EGL_LIBRARY_FIND(eglGetSyncAttrib);
  EGL_LIBRARY_FIND(eglInitialize);
  EGL_LIBRARY_FIND(eglMakeCurrent);
  EGL_LIBRARY_FIND(eglQueryAPI);
  EGL_LIBRARY_FIND(eglQueryContext);
  EGL_LIBRARY_FIND(eglQueryString);
  EGL_LIBRARY_FIND(eglQuerySurface);
  EGL_LIBRARY_FIND(eglReleaseTexImage);
  EGL_LIBRARY_FIND(eglReleaseThread);
  EGL_LIBRARY_FIND(eglSurfaceAttrib);
  EGL_LIBRARY_FIND(eglSwapBuffers);
  EGL_LIBRARY_FIND(eglSwapInterval);
  EGL_LIBRARY_FIND(eglTerminate);
  EGL_LIBRARY_FIND(eglWaitClient);
  EGL_LIBRARY_FIND(eglWaitGL);
  EGL_LIBRARY_FIND(eglWaitNative);
  EGL_LIBRARY_FIND(eglWaitSync);
  /* eglext.h */
  EGL_LIBRARY_FIND(eglClientWaitSyncKHR);
  EGL_LIBRARY_FIND(eglClientWaitSyncNV);
  EGL_LIBRARY_FIND(eglCreateDRMImageMESA);
  EGL_LIBRARY_FIND(eglCreateFenceSyncNV);
  EGL_LIBRARY_FIND(eglCreateImageKHR);
  EGL_LIBRARY_FIND(eglCreatePixmapSurfaceHI);
  EGL_LIBRARY_FIND(eglCreatePlatformPixmapSurfaceEXT);
  EGL_LIBRARY_FIND(eglCreatePlatformWindowSurfaceEXT);
  EGL_LIBRARY_FIND(eglCreateStreamFromFileDescriptorKHR);
  EGL_LIBRARY_FIND(eglCreateStreamKHR);
  EGL_LIBRARY_FIND(eglCreateStreamProducerSurfaceKHR);
  EGL_LIBRARY_FIND(eglCreateStreamSyncNV);
  EGL_LIBRARY_FIND(eglCreateSync64KHR);
  EGL_LIBRARY_FIND(eglCreateSyncKHR);
  EGL_LIBRARY_FIND(eglDestroyImageKHR);
  EGL_LIBRARY_FIND(eglDestroyStreamKHR);
  EGL_LIBRARY_FIND(eglDestroySyncKHR);
  EGL_LIBRARY_FIND(eglDestroySyncNV);
  EGL_LIBRARY_FIND(eglDupNativeFenceFDANDROID);
  EGL_LIBRARY_FIND(eglExportDMABUFImageMESA);
  EGL_LIBRARY_FIND(eglExportDMABUFImageQueryMESA);
  EGL_LIBRARY_FIND(eglExportDRMImageMESA);
  EGL_LIBRARY_FIND(eglFenceNV);
  EGL_LIBRARY_FIND(eglGetOutputLayersEXT);
  EGL_LIBRARY_FIND(eglGetOutputPortsEXT);
  EGL_LIBRARY_FIND(eglGetPlatformDisplayEXT);
  EGL_LIBRARY_FIND(eglGetStreamFileDescriptorKHR);
  EGL_LIBRARY_FIND(eglGetSyncAttribKHR);
  EGL_LIBRARY_FIND(eglGetSyncAttribNV);
  EGL_LIBRARY_FIND(eglGetSystemTimeFrequencyNV);
  EGL_LIBRARY_FIND(eglGetSystemTimeNV);
  EGL_LIBRARY_FIND(eglLockSurfaceKHR);
  EGL_LIBRARY_FIND(eglOutputLayerAttribEXT);
  EGL_LIBRARY_FIND(eglOutputPortAttribEXT);
  EGL_LIBRARY_FIND(eglPostSubBufferNV);
  EGL_LIBRARY_FIND(eglQueryDeviceAttribEXT);
  EGL_LIBRARY_FIND(eglQueryDeviceStringEXT);
  EGL_LIBRARY_FIND(eglQueryDevicesEXT);
  EGL_LIBRARY_FIND(eglQueryDisplayAttribEXT);
  EGL_LIBRARY_FIND(eglQueryNativeDisplayNV);
  EGL_LIBRARY_FIND(eglQueryNativePixmapNV);
  EGL_LIBRARY_FIND(eglQueryNativeWindowNV);
  EGL_LIBRARY_FIND(eglQueryOutputLayerAttribEXT);
  EGL_LIBRARY_FIND(eglQueryOutputLayerStringEXT);
  EGL_LIBRARY_FIND(eglQueryOutputPortAttribEXT);
  EGL_LIBRARY_FIND(eglQueryOutputPortStringEXT);
  EGL_LIBRARY_FIND(eglQueryStreamKHR);
  EGL_LIBRARY_FIND(eglQueryStreamTimeKHR);
  EGL_LIBRARY_FIND(eglQueryStreamu64KHR);
  EGL_LIBRARY_FIND(eglQuerySurface64KHR);
  EGL_LIBRARY_FIND(eglQuerySurfacePointerANGLE);
  EGL_LIBRARY_FIND(eglSetBlobCacheFuncsANDROID);
  EGL_LIBRARY_FIND(eglSetDamageRegionKHR);
  EGL_LIBRARY_FIND(eglSignalSyncKHR);
  EGL_LIBRARY_FIND(eglSignalSyncNV);
  EGL_LIBRARY_FIND(eglStreamAttribKHR);
  EGL_LIBRARY_FIND(eglStreamConsumerAcquireKHR);
  EGL_LIBRARY_FIND(eglStreamConsumerGLTextureExternalKHR);
  EGL_LIBRARY_FIND(eglStreamConsumerOutputEXT);
  EGL_LIBRARY_FIND(eglStreamConsumerReleaseKHR);
  EGL_LIBRARY_FIND(eglSwapBuffersRegion2NOK);
  EGL_LIBRARY_FIND(eglSwapBuffersRegionNOK);
  EGL_LIBRARY_FIND(eglSwapBuffersWithDamageEXT);
  EGL_LIBRARY_FIND(eglSwapBuffersWithDamageKHR);
  EGL_LIBRARY_FIND(eglUnlockSurfaceKHR);
  EGL_LIBRARY_FIND(eglWaitSyncKHR);
  /* eglextchromium.h */
  EGL_LIBRARY_FIND(eglGetSyncValuesCHROMIUM);
  /* eglmesaext.h */
  EGL_LIBRARY_FIND(eglBindWaylandDisplayWL);
  EGL_LIBRARY_FIND(eglCreateWaylandBufferFromImageWL);
  EGL_LIBRARY_FIND(eglGetDRMDisplayMESA);
  EGL_LIBRARY_FIND(eglQueryWaylandBufferWL);
  EGL_LIBRARY_FIND(eglUnbindWaylandDisplayWL);

  result = EGLEW_SUCCESS;
  return result;
}
