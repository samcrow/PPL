// Copyright (c) 2014, Sam Crow samcrow@uw.edu
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

#ifndef VARADICCOMPILER_H
#define VARADICCOMPILER_H
#include "../namespaces.h"
#include <array>

namespace PPLNAMESPACE {

/**
 * @brief Provides a method that compiles
 * varadic arguments into a list
 */
class VaradicCompiler
{
public:
    
    /**
     * Returns an array of objects containing the provided varadic arguments.
     * Each argument after the first argument must be implicitly convertible to the
     * type of the first argument.
     */
    template < typename T, typename... As >
    static std::array< T, 1 + sizeof...(As) > compile(T first, As... others) {
        // Create an array
        std::array< T, 1 + sizeof...(As) > vector;
        // Create another array from the compilation of the others
        const std::array< T, sizeof...(As) > supplement = compile(others...);
        
        // Put item 0 in the array
        vector[0] = first;
        // Copy other items starting at index 1
        typename std::array< T, 1 + sizeof...(As) >::iterator item1 = vector.begin();
        std::advance(item1, 1);
        std::copy(supplement.begin(), supplement.end(), item1);
        
        return vector;
    }
    
    template < typename T >
    static std::array<T, 1> compile(T arg) {
        std::array<T, 1> vector;
        vector[0] = arg;
        return vector;
    }
    
    template < typename T >
    static std::array<T, 0> compile() {
        return std::array<T, 0>();
    }
    
    VaradicCompiler() = delete;
};

}
#endif // VARADICCOMPILER_H
