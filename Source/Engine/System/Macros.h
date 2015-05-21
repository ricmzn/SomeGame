#ifndef MACROS_H
#define MACROS_H

#if defined _WIN32
  #if defined ENGINE_EXPORTS
    #define api_public __declspec(dllexport)
    #define api_private
  #else
    #define api_public __declspec(dllimport)
    #define api_private
  #endif
#elif defined __GNUC__
  #define api_public __attribute__((visibility("default")))
  #define api_private __attribute__((visibility("hidden")))
#else
  #define api_public
  #define api_private
#endif

#endif // MACROS_H
