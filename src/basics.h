// Copyright (c) 2013, Philipp Muenzel mail@philippmuenzel.de
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// The views and conclusions contained in the software and documentation are those
// of the authors and should not be interpreted as representing official policies,
// either expressed or implied, of the FreeBSD Project.

#ifndef BASICS_H
#define BASICS_H
#include <type_traits>

#if (defined(_WIN32) || defined(__CYGWIN__)) && defined(_MSC_VER)   // Windows && MS Visual C
#    define MSVC_EXPORT __declspec(dllexport)
#    pragma warning( disable : 4996 )   // disable deprecation warnings
#    pragma warning( disable : 4091 )   // disable typedef warning without variable declaration
#    pragma warning( disable : 4275 )   // non &#8211; DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
#    pragma warning( disable : 4251 )   // like warning above but for templates (like std::string)
#    pragma warning( disable : 4290 )   // exception handling of MSVC is lousy
#else
#    define MSVC_EXPORT
#endif

#if defined(_MSC_VER)

#    include <float.h>
#    define isnan _isnan

inline int my_snprintf(char* str, size_t size, const char* format, ...)
{
    size_t count;
    va_list ap;
    va_start(ap, format);
    count = _vscprintf(format, ap);
    _vsnprintf_s(str, size, _TRUNCATE, format, ap);
    va_end(ap);
    return count;
}
#   define snprintf my_snprintf

#endif
#include <cmath>

#include "namespaces.h"


namespace PPLNAMESPACE {

template <typename T>
T round(T r)
{
    return (r > 0.0) ? std::floor(r + 0.5) : std::ceil(r - 0.5);
}

template <typename T>
T min(const T& a, const T& b)
{
    return (a<b)?a:b;
}

template <typename T>
T max(const T& a, const T& b)
{
    return (a<b)?b:a;
}

inline long ipow(long base, long exp)
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
}

inline double mods(double y, double x)
{
    return y - x*std::floor(y/x);
}

}

#endif // BASICS_H
