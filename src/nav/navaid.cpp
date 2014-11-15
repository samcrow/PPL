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

#include "navaid.h"
#include "airport.h"
#include "ndb.h"
#include "vor.h"
#include "ils.h"
#include "localizer.h"
#include "glideslope.h"
#include "outermarker.h"
#include "middlemarker.h"
#include "innermarker.h"
#include "fix.h"
#include "dme.h"

namespace PPLNAMESPACE {

Navaid::Navaid(XPLMNavRef ref) :
    ref_(ref)
{
    // Check reference
    if(ref == XPLM_NAV_NOT_FOUND) {
        throw std::invalid_argument("Navaid cannot be instantiated with an inavlid nav reference");
    }

    // Set up position and other information
    // Allocate space for name and ID
    id_.resize(32);
    name_.resize(256);
    float latitude;
    float longitude;

    XPLMGetNavAidInfo(ref_,
                      nullptr,
                      &latitude,
                      &longitude,
                      &elevation_,
                      nullptr,
                      nullptr,
                      &id_.front(),
                      &name_.front(),
                      nullptr
                      );

    setPosition({ latitude, longitude });

    // Because id_ and name were resized to be unnecessarily large
    // and then null-terminated by the C function.
    // Remove all the null termination and possible extraneous characters
    auto trim = [](std::string& str) {
        auto iter = str.cbegin();
        while(*iter != 0 && iter != str.cend()) {
            iter++;
        }
        // Now either iter points to the first null byte or to the end
        // This should be the character after the end of the new string
        str.resize( std::distance(str.cbegin(), iter) );
    };
    trim(id_);
    trim(name_);
}

float Navaid::elevation() const {
    return elevation_;
}
std::string Navaid::id() const {
    return id_;
}
std::string Navaid::name() const {
    return name_;
}

Navaid::Type Navaid::navaidType() const {
    // Default
    return Type::Unknown;
}

Navaid* Navaid::build(XPLMNavRef ref) {
    // Get type
    XPLMNavType type;
    XPLMGetNavAidInfo(ref, &type, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    switch(type) {
    case xplm_Nav_Airport:
        return new Airport(ref);
        break;
    case xplm_Nav_NDB:
        return new NDB(ref);
        break;
    case xplm_Nav_VOR:
        return new VOR(ref);
        break;
    case xplm_Nav_ILS:
        return new ILS(ref);
        break;
    case xplm_Nav_Localizer:
        return new Localizer(ref);
        break;
    case xplm_Nav_GlideSlope:
        return new Glideslope(ref);
        break;
    case xplm_Nav_OuterMarker:
        return new OuterMarker(ref);
        break;
    case xplm_Nav_MiddleMarker:
        return new MiddleMarker(ref);
        break;
    case xplm_Nav_InnerMarker:
        return new InnerMarker(ref);
        break;
    case xplm_Nav_Fix:
        return new Fix(ref);
        break;
    case xplm_Nav_DME:
        return new DME(ref);
        break;

    case xplm_Nav_Unknown: // Intentional fallthrough
    default:
        throw std::runtime_error("Unknown navaid type");
    }
}

// Specialize downcast for every subclass

template<>
Airport* Navaid::downcast() {
    if(navaidType() != Type::Airport) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< Airport* >(this);
}

template<>
const Airport* Navaid::downcast() const {
    if(navaidType() != Type::Airport) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< const Airport* >(this);
}
template<>
NDB* Navaid::downcast() {
    if(navaidType() != Type::NDB) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< NDB* >(this);
}

template<>
const NDB* Navaid::downcast() const {
    if(navaidType() != Type::NDB) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< const NDB* >(this);
}
template<>
VOR* Navaid::downcast() {
    if(navaidType() != Type::VOR) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< VOR* >(this);
}

template<>
const VOR* Navaid::downcast() const {
    if(navaidType() != Type::VOR) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< const VOR* >(this);
}
template<>
ILS* Navaid::downcast() {
    if(navaidType() != Type::ILS) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< ILS* >(this);
}

template<>
const ILS* Navaid::downcast() const {
    if(navaidType() != Type::ILS) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< const ILS* >(this);
}
template<>
Localizer* Navaid::downcast() {
    if(navaidType() != Type::Localizer) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< Localizer* >(this);
}

template<>
const Localizer* Navaid::downcast() const {
    if(navaidType() != Type::Localizer) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< const Localizer* >(this);
}
template<>
Glideslope* Navaid::downcast() {
    if(navaidType() != Type::Glideslope) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< Glideslope* >(this);
}

template<>
const Glideslope* Navaid::downcast() const {
    if(navaidType() != Type::Glideslope) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< const Glideslope* >(this);
}
template<>
OuterMarker* Navaid::downcast() {
    if(navaidType() != Type::OuterMarker) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< OuterMarker* >(this);
}

template<>
const OuterMarker* Navaid::downcast() const {
    if(navaidType() != Type::OuterMarker) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< const OuterMarker* >(this);
}
template<>
MiddleMarker* Navaid::downcast() {
    if(navaidType() != Type::MiddleMarker) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< MiddleMarker* >(this);
}

template<>
const MiddleMarker* Navaid::downcast() const {
    if(navaidType() != Type::MiddleMarker) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< const MiddleMarker* >(this);
}
template<>
InnerMarker* Navaid::downcast() {
    if(navaidType() != Type::InnerMarker) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< InnerMarker* >(this);
}

template<>
const InnerMarker* Navaid::downcast() const {
    if(navaidType() != Type::InnerMarker) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< const InnerMarker* >(this);
}
template<>
Fix* Navaid::downcast() {
    if(navaidType() != Type::Fix) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< Fix* >(this);
}

template<>
const Fix* Navaid::downcast() const {
    if(navaidType() != Type::Fix) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< const Fix* >(this);
}
template<>
DME* Navaid::downcast() {
    if(navaidType() != Type::DME) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< DME* >(this);
}

template<>
const DME* Navaid::downcast() const {
    if(navaidType() != Type::DME) {
        throw std::runtime_error("Can't downcast a navaid to an inappropriate type");
    }
    return static_cast< const DME* >(this);
}

// Navaid::Type operators
Navaid::Type operator | (Navaid::Type left, Navaid::Type right) {
    return static_cast<Navaid::Type>( static_cast<Navaid::type_underlying>(left) | static_cast<Navaid::type_underlying>(right) );
}
Navaid::Type operator & (Navaid::Type left, Navaid::Type right) {
    return static_cast<Navaid::Type>( static_cast<Navaid::type_underlying>(left) & static_cast<Navaid::type_underlying>(right) );
}
Navaid::Type operator ^ (Navaid::Type left, Navaid::Type right) {
    return static_cast<Navaid::Type>( static_cast<Navaid::type_underlying>(left) ^ static_cast<Navaid::type_underlying>(right) );
}
Navaid::Type operator ~ (Navaid::Type original) {
    return static_cast<Navaid::Type>( ~ static_cast<Navaid::type_underlying>( original ));
}
Navaid::Type& operator |= (Navaid::Type& left, Navaid::Type right) {
    left = left | right;
    return left;
}
Navaid::Type& operator &= (Navaid::Type& left, Navaid::Type right) {
    left = left & right;
    return left;
}
Navaid::Type& operator ^= (Navaid::Type& left, Navaid::Type right) {
    left = left ^ right;
    return left;
}

}
