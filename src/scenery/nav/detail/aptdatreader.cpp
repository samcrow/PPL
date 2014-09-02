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

#include "aptdatreader.h"
#include <sstream>

namespace PPLNAMESPACE {
namespace detail {

AptDatReader::AptDatReader(const std::string& filePath) :
    filePath(filePath)
{
}

AirportReader AptDatReader::getAirportByCode(const std::string& code) {
    ensureOpen();
    moveToBeginning();
    
    // Read airports (code 1, 16, or 17)
    while(nextLineWithCode({1, 16, 17})) {
        // Cursor is now before the beginning of the line
        const std::streamsize lineStart = stream.tellg();
        // Read and ignore code, elevation, and two depreciated values
        int dummy;
        for(int i = 0; i < 4; i++) {
            stream >> dummy;
        }
        
        std::string foundCode;
        stream >> foundCode;
        
        if(code == foundCode) {
            return AirportReader(filePath, lineStart);
        }
        // Not the right airport
        // Skip the rest of the line and continue
        skipLine();
    }
    
    // Nothing found
    throw std::runtime_error("No airport with the requested ID found");
}

void AptDatReader::ensureOpen() {
    if(!stream.is_open()) {
        stream.open(filePath, std::ios::in);
        if(stream.rdstate() & std::ios::failbit) {
            throw std::runtime_error("Could not open apt.dat file");
        }
    }
}

void AptDatReader::moveToBeginning() {
    stream.seekg(0);
    // Dismiss errors
    stream.clear();
    
    skipLine();
    skipLine();
}

bool AptDatReader::nextLineWithCode(std::initializer_list<int> codes) {
    while(!stream.eof()) {
        
        int foundCode;
        const std::streamsize lineStart = stream.tellg();
        std::istringstream stream(readLine());
        stream >> foundCode;
        
        
        for(int code : codes) {
            // Check for a matching code
            if(foundCode == code) {
                // Seek back to before the code
                stream.seekg(lineStart);
                return true;
            }
        }
    }
    
    return false;
}

bool AptDatReader::nextLineWithCode(int code) {
    // Delegate to initializer list version
    return nextLineWithCode({code});
}

void AptDatReader::skipLine() {
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string AptDatReader::readLine() {
    std::string line;
    while(!stream.eof()) {
        char c = stream.get();
        if(c == '\n') {
            break;
        }
        line.push_back(c);
    }
    stream.clear();
    return line;
}

}
}
