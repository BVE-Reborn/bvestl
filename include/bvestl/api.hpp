
#ifndef BVESTL_EXPORT_H
#define BVESTL_EXPORT_H

#ifdef BVESTL_STATIC_DEFINE
#  define BVESTL_EXPORT
#  define BVESTL_NO_EXPORT
#else
#  ifndef BVESTL_EXPORT
#    ifdef bvestl_EXPORTS
        /* We are building this library */
#      define BVESTL_EXPORT 
#    else
        /* We are using this library */
#      define BVESTL_EXPORT 
#    endif
#  endif

#  ifndef BVESTL_NO_EXPORT
#    define BVESTL_NO_EXPORT 
#  endif
#endif

#ifndef BVESTL_DEPRECATED
#  define BVESTL_DEPRECATED __declspec(deprecated)
#endif

#ifndef BVESTL_DEPRECATED_EXPORT
#  define BVESTL_DEPRECATED_EXPORT BVESTL_EXPORT BVESTL_DEPRECATED
#endif

#ifndef BVESTL_DEPRECATED_NO_EXPORT
#  define BVESTL_DEPRECATED_NO_EXPORT BVESTL_NO_EXPORT BVESTL_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef BVESTL_NO_DEPRECATED
#    define BVESTL_NO_DEPRECATED
#  endif
#endif

#endif /* BVESTL_EXPORT_H */
