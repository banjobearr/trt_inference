#pragma once
#ifdef TRTDLL_EXPORTS
#define TRTDLL_API __declspec(dllexport)
#else
#define TRTDLL_API __declspec(dllimport)
#endif
#include <stdint.h>
#include <stddef.h>

extern "C" {

TRTDLL_API void* TrtCreate(const wchar_t* modelPath,
                           const wchar_t* engineCacheDir,
                           const wchar_t* cachePrefix,
                           int imageSize,
                           int* outOutputElements);

TRTDLL_API void* TrtCreateFromMemory(const uint8_t* modelData,
                                     size_t modelSize,
                                     const wchar_t* engineCacheDir,
                                     const wchar_t* cachePrefix,
                                     int imageSize,
                                     int* outOutputElements);

// Returns pointer to the pinned host input buffer — write float data here,
// then call TrtRunFromPinned.
TRTDLL_API float* TrtGetInputBuffer(void* handle);

// Run inference using whatever is already in the pinned input buffer.
TRTDLL_API int TrtRunFromPinned(void* handle, float* outputData, int outputElements);

// Run inference copying from an arbitrary host pointer.
TRTDLL_API int TrtRun(void* handle,
                      const float* inputData,
                      float* outputData,
                      int outputElements);

TRTDLL_API void TrtDestroy(void* handle);

TRTDLL_API const char* TrtGetLastError();

} // extern "C"
