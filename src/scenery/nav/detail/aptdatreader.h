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

#ifndef APTDATREADER_H
#define APTDATREADER_H
#include <fstream>
#include <initializer_list>
#include "../../../namespaces.h"
#include "airportreader.h"

namespace PPLNAMESPACE {
namespace detail {

/**
 * @brief The AptDatReader class parses an apt.dat file and provides access to
 * other objects used to read specific entries from the file.
 */
class AptDatReader
{
public:
    AptDatReader(const std::string& filePath);
    
    /**
     * @brief Creates and returns an AirportReader that can be used to access
     * information on the airport with the requested code
     * @param code
     * @return 
     * @throws std::runtime_error if no airport with the provided code could be found
     */
    AirportReader getAirportByCode(const std::string& code);
    
private:
    const std::string filePath;
    
    std::ifstream stream;
    
    /**
     * @brief Opens the stream if it is not open
     */
    void ensureOpen();
    
    /**
     * @brief Moves the stream to the beginning of the file,
     * and then skips two lines to get past the headers
     */
    void moveToBeginning();
    
    /**
     * @brief Reads and discards characters from the stream until \n is read,
     * then returns
     */
    void skipLine();
    
    /**
     * @brief Reads characters from the stream until a line with the given line code
     * is found, then seeks back to a position before the line code
     * @param code The line code to search for
     * @return true if a line was found, false if the end of file was reached or some other
     * problem occurred
     */
    bool nextLineWithCode(int code);
    
    /**
     * @brief Like readUntilLineCode(int), but reads until any of the provided codes is found
     * @param codes
     * @return 
     */
    bool nextLineWithCode(std::initializer_list<int> codes);
    
    std::string readLine();
};

}
}
#endif // APTDATREADER_H
