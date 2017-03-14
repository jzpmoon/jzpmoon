#ifndef VR_COMMON_H
#define VR_COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER 
#define VR_DECLARE_EXPORT __declspec(dllexport)
#elif define(_GNUC_)
#define VR_DECLARE_EXPORT __attribute((visibility("default")))
#else
#define VR_DECLARE_EXPORT
#endif

#endif
