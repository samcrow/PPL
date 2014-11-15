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

#ifndef NAVAID_H
#define NAVAID_H
#include "positioned.h"
#include <XPLMNavigation.h>

namespace PPLNAMESPACE {

/**
 * Represents a navaid of one of the following types:
 *
 * * Airport
 * * NDB
 * * VOR
 * * ILS
 * * Localizer
 * * Glideslope
 * * Outer marker
 * * Middle marker
 * * Inner marker
 * * Fix
 * * DME
 * * Latitude/longitude (used only in the FMS)
 */
class Navaid : public Positioned
{
public:

    /// Types of supported navaids
    enum class Type {
        Unknown      = xplm_Nav_Unknown,
        Airport      = xplm_Nav_Airport,
        NDB          = xplm_Nav_NDB,
        VOR          = xplm_Nav_VOR,
        ILS          = xplm_Nav_ILS,
        Localizer    = xplm_Nav_Localizer,
        Glideslope   = xplm_Nav_GlideSlope,
        OuterMarker  = xplm_Nav_OuterMarker,
        MiddleMarker = xplm_Nav_MiddleMarker,
        InnerMarker  = xplm_Nav_InnerMarker,
        Fix          = xplm_Nav_Fix,
        DME          = xplm_Nav_DME,
        LatLon       = xplm_Nav_LatLon,
    };
    typedef std::underlying_type<Type>::type type_underlying;

    float elevation() const;
    std::string id() const;
    std::string name() const;

    /// Returns the type of this navaid
    virtual Type navaidType() const;

    /**
     * Safely downcasts this navaid to a subtype
     */
    template < typename T >
    T* downcast();
    /**
     * Safely downcasts this navaid to a subtype
     */
    template < typename T >
    const T* downcast() const;

    /**
     * Creates and returns an instance of the appropriate
     * Navaid subclass for the provided navaid reference.
     *
     * @param ref
     * @return
     */
    static Navaid* build(XPLMNavRef ref);

protected:

    Navaid(XPLMNavRef ref);

    XPLMNavRef ref_;
    /// Elevation, in feet
    float elevation_;

    std::string id_;
    std::string name_;


};

// Navaid type operators
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

#endif // NAVAID_H
