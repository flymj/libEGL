#ifndef __ATITYPES_H__
#define __ATITYPES_H__

//
// The data types defined herein are only valid for the Microsoft
// and gcc compiler sets targetted for Intel/AMD processors.  All
// others need to have their own typedefs added here (or confirmed
// that these are appropriate for the new compiler and/or processor
// architecture).
//
#if !defined(_MSC_VER) && !defined(__GNUC__)
#error "Unknown compiler, need to explicitly define data types!!!"
#endif // !MSC_VER && !__GNUC__

#if defined(ATI_OS_WIN)
#include <stddef.h>
#elif defined(ATI_OS_LINUX)
#include <stdint.h>
#include <stdbool.h>
#else
#error Unsupported OS.
#endif

#include "atidefines.h"
//
/// @file atitypes.h
/// @brief Standard Types
//

//
// typedefs
//

#if defined(ATI_COMP_VC)
/// 64-bit signed integer
typedef signed __int64 int64, *pint64;

/// 64-bit unsigned integer
typedef unsigned __int64 uint64, *puint64;
#endif // ATI_COMP_VC


#if defined(ATI_COMP_GCC)
/// 64-bit signed integer
typedef signed long long int64, *pint64;;

/// 64-bit unsigned integer
typedef unsigned long long uint64, *puint64;
#endif  // ATI_COMP_GCC



/// 8-bit character
typedef unsigned char char8, *pchar8;

/// 8-bit signed integer
typedef signed char int8, *pint8;

/// 16-bit signed integer
typedef signed short int16, *pint16;

/// 32-bit signed integer
typedef signed int int32, *pint32;

/// 8-bit unsigned integer
typedef unsigned char uint8, *puint8;

/// 16-bit unsigned integer
typedef unsigned short uint16, *puint16;

/// 32-bit unsigned integer
typedef unsigned int uint32, *puint32;

/// 32-bit floating point
typedef float float32, *pfloat32;

/// 64-bit floating point
typedef double float64, *pfloat64;

/// pointer to void
typedef void *pvoid;

/// unsigned integer, the same size as a pointer
typedef uintptr_t uintp;

/// signed integer, the same size as a pointer
typedef intptr_t intp;

/// mc address
typedef long long mcaddr, *pmcaddr;
//typedef uint32 mcaddr, *pmcaddr;

/// memory size
typedef long long mcsize, *pmcsize;
//typedef uint32 mcsize, *pmcsize;

/// mc address offset
typedef long long mcoffset, *pmcoffset;
//typedef uint32 mcoffset, *pmcoffset;

//
// enums
//

//
/// Standard Boolean Type
//
typedef enum _bool32 {
    ATIGL_FALSE,    ///< False
    ATIGL_TRUE,     ///< True
} bool32;

//
/// float16 type
//
typedef union _float16
{
    uint16 u16;                  ///< 16-bit float (whole)

    //
    ///  Individual bits
    //
    struct 
    {
#if defined(qLittleEndian)
        uint16 mantissa : 10;    ///< mantissa
        uint16 exp      : 5;     ///< exp
        uint16 sign     : 1;     ///< sign
#else
        uint16 sign     : 1;     ///< sign
        uint16 exp      : 5;     ///< exp
        uint16 mantissa : 10;    ///< mantissa
#endif
    } bits;                      ///< individual bits
} float16;

//
/// fixed 16.16 type
//
typedef union _fixed16_16
{
    int32 i32;                  ///< 32-bit fixed (whole)
} fixed16_16;

//
/// Indicates module ownership in ORCA
//
typedef enum _AtiDriverModule
{
    DRIVER_MODULE_UNKNOWN,
    DRIVER_MODULE_WSI,
    DRIVER_MODULE_GLL,
    DRIVER_MODULE_SCL,
    DRIVER_MODULE_OS,
    DRIVER_MODULE_GSL,
    DRIVER_MODULE_HWL,
    DRIVER_MODULE_IOL,
    DRIVER_MODULE_Last = DRIVER_MODULE_IOL
} AtiDriverModule;

#ifdef ATI_COMP_VC
    #define ALIGNED(X,Y) __declspec(align(Y)) X
#elif defined(ATI_COMP_GCC)
    #define ALIGNED(X,Y)  X __attribute__ ((aligned(Y)))
#else
#error Unsupported compiler
#endif



#endif // __ATITYPES_H__



