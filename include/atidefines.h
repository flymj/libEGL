#ifndef ATI_DEFINES_H
#define ATI_DEFINES_H

//
/// @file atidefines.h
/// @brief Standard Defines
//

//
// defines
//

#if defined(ATI_COMP_VC)

//
/// Extern, dll, and calling convention definitions
//
#define DLLEXPORT __declspec(dllexport) ///< Function is exported from DLL
#define EXTERN    extern                ///< Function is Externally defined
#define CONV      __stdcall             ///< Calling convention for internal Function
#define INLINE    __forceinline         ///< Function is inlined (compiler decision)
#define FINLINE   __forceinline         ///< Function is inlined (always)
#define NAKED     __declspec(naked)     ///< Function is naked
#ifndef APIENTRY
#define APIENTRY  __stdcall             ///< Calling convention for function exposed in the API
#endif
#define WINCONV   __cdecl               ///< Calling convention for WINAPIV functions

// VC does not support strtoull thus we have to use this macro to "emulate" it
#define strtoull(nptr, endptr, ibase)   _strtoui64(nptr, endptr, ibase)

#elif defined(ATI_COMP_GCC)
//
/// Extern, dll, and calling convention definitions
//
#define DLLEXPORT extern                ///< Function is exported from DLL
#define EXTERN    extern                ///< Function is Externally defined
#define CONV                            ///< Calling convention for internal Function
#define INLINE    inline                ///< Function is inlined (compiler decision)
#define FINLINE   inline                ///< Function is inlined (always)
#define NAKED                           ///< Function is naked
#ifndef APIENTRY
#define APIENTRY                        ///< Calling convention for function exposed in the API
#endif
#define WINCONV                         ///< Calling convention for WINAPIV functions
#else

#error "Unknown compiler"

#endif

#define EXTERNC   EXTERN "C"            ///< Function are mangled as a c interface

#define RESTRICTED_PTR  __restrict      ///< Indicates pointer data does not alias any other
                                        ///< pointer data also declared as restricted

//
/// Assert that will be checked at compile time.
/// the predicate needs to be decidable at compile time.
/// The call can only be made were a C statement is expected.
//
#if defined(_MSC_VER) && (_MSC_VER >= 1700)
#define COMPILE_TIME_ASSERT(pred) static_assert(pred, #pred)
#else
#define COMPILE_TIME_ASSERT(pred) switch(0) { case 0: case (pred): break; }
#endif

#if !defined(UINT_MAX)                  ///< limits.h on linux
#define UINT_MAX 0xffffffff             ///< maximum unsigned int value 
#endif 

#ifndef ATI_UNREFERENCED_PARAMETER
/// use this macro on unreferenced variables to avoid compiler warnings.
#define ATI_UNREFERENCED_PARAMETER(P)          \
    /*lint -save -e527 -e530 */ \
    { \
        (P) = (P); \
    } \
    /*lint -restore */
#endif

#endif // ATI_DEFINES
