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
#include <limits>
#include <iostream>

namespace PPLNAMESPACE {
namespace detail {

AptDatReader::AptDatReader(const std::string& filePath) :
    filePath(filePath)
{
    readInProgress_.store(false);
}


const std::string& AptDatReader::path() const {
    return filePath;
}

bool AptDatReader::allAirportsRead() const {
    return allAirportsRead_;
}

bool AptDatReader::readInProgress() const {
    return readInProgress_.load();
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
    // Dismiss errors
    stream.clear();
    stream.seekg(0);
    
    skipLine();
    skipLine();
}


void AptDatReader::skipLine() {
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string AptDatReader::readLine() {
    const auto readMoreLineTerminators = [this] {
        while(true) {
            char c = stream.peek();
            if(c == '\n' || c == '\r') {
                // Read and ignore that character
                stream.get();
            }
            else {
                break;
            }
        }
    };
    
    std::string line;
    while(!stream.eof()) {
        stream.clear();
        char c = stream.get();
        if(c == '\n' || c == '\r') {
            readMoreLineTerminators();
            break;
        }
        line.push_back(c);
    }
    stream.clear();
    return line;
}

}
}
