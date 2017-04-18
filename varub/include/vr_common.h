#ifndef VR_COMMON_H
#define VR_COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER 
#define VR_DECLARE_EXPORT __declspec(dllexport)
#elif defined(__GNUC__)
#define VR_DECLARE_EXPORT __attribute__((visibility("default")))
#else
#define VR_DECLARE_EXPORT
#endif

#endif

