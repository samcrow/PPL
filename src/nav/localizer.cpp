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

#include "localizer.h"

namespace PPLNAMESPACE {

Localizer::Localizer(const std::string &id) :
    Navaid(findNavRef(id))
{
    getFrequency();
}

Localizer::Localizer(XPLMNavRef ref) :
    Navaid(ref)
{
    getFrequency();
}

void Localizer::getFrequency() {
    // Get frequency
    int rawFrequency;
    XPLMGetNavAidInfo(ref_, nullptr, nullptr, nullptr, nullptr, &rawFrequency, &heading_, nullptr, nullptr, nullptr);

    frequency_ = Frequency(rawFrequency * 10000);
}

Navaid::Type Localizer::navaidType() const {
    return Type::Localizer;
}

float Localizer::heading() const {
    return heading_;
}

XPLMNavRef Localizer::findNavRef(const std::string& id) {
    return XPLMFindNavAid(nullptr, id.data(), nullptr, nullptr, nullptr, xplm_Nav_Localizer);
}

Frequency Localizer::frequency() const {
    return frequency_;
}

}
