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

#ifndef PPL_EXCEPTIONS_H
#define PPL_EXCEPTIONS_H
#include <stdexcept>
#include "../namespaces.h"

namespace PPLNAMESPACE {


/**
 * @brief Superclass for exceptions thrown from failed airport searches
 */
class AirportSearchException : public std::runtime_error {
public:
    AirportSearchException(const std::string& what_arg) : std::runtime_error(what_arg) {}
    AirportSearchException(const char* what_arg) : std::runtime_error(what_arg) {}
};
/**
 * @brief An exception thrown when a search was perfomed for an airport
 * that does not exist
 */
class NoSuchAirportException : public AirportSearchException {
public:
    NoSuchAirportException(const std::string& what_arg) : AirportSearchException(what_arg) {}
    NoSuchAirportException(const char* what_arg) : AirportSearchException(what_arg) {}
};

/**
 * @brief An exception thrown when a search was performed for an airport that may exist,
 * but the airport data file is still being parsed
 */
class ReadInProgressException : public AirportSearchException {
public:
    ReadInProgressException(const std::string& what_arg) : AirportSearchException(what_arg) {}
    ReadInProgressException(const char* what_arg) : AirportSearchException(what_arg) {}
};
/**
 * @brief An exception thrown when a Navaid subclass constructor
 * is called but no navaid matching the specified criteria could be found
 */
class NoSuchNavaidException : public std::runtime_error {
    NoSuchNavaidException(const std::string& what_arg) : std::runtime_error(what_arg) {}
    NoSuchNavaidException(const char* what_arg) : std::runtime_error(what_arg) {}
};

}

#endif // PPL_EXCEPTIONS_H
