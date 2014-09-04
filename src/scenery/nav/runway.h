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

#ifndef RUNWAY_H
#define RUNWAY_H
#include <string>
#include "../../namespaces.h"
#include "../../util/uncertain.h"

namespace PPLNAMESPACE {

/**
 * @brief The Runway class stores information on a runway
 */
class Runway
{
public:
    /// Runway surface types
    enum class Surface {
        Asphalt = 1,
        Concrete = 2,
        Grass = 3,
        Dirt = 4,
        Gravel = 5,
        DryLakebed = 12,
        Water = 13,
        Snow = 14,
        Transparent = 15,
    };
    
    /// Runway marking types
    enum class Markings {
        None = 0,
        Visual = 1,
        NonPrecision = 2,
        Precision = 3,
        UKNonPrecision = 4,
        UKPrecision = 5,
    };
    /// Runway shoulder types
    enum class Shoulder {
        None = 0,
        Asphalt = 1,
        Concrete = 2,
    };
    /// Runway edge light type
    enum class EdgeLights {
        None = 0,
        LowIntensity = 1,
        MediumIntensity = 2,
        HighIntensity = 3,
    };
    
    class End {
    public:
        /// Suffixes for left, center, and right
        enum class Suffix : char {
            None = ' ',
            L = 'L',
            C = 'C',
            R = 'R',
        };
        /// Approach lighting types
        enum class ApproachLighting {
            None = 0,
            ALSF1 = 1,
            ALSF2 = 2,
            Calvert = 3,
            CalvertILS = 4,
            SSALR = 5,
            SSALF = 6,
            SALS = 7,
            MALSR = 8,
            MALSF = 9,
            MALS = 10,
            ODALS = 11,
            RAIL = 12,
        };
        enum class RunwayEndIdentifierLights {
            None = 0,
            Omnidirectional = 1,
            Unidirectional = 2,
        };
        
        /// Returns the 2-digit heading
        int heading() const {
            return heading_;
        }
        /// Returns the suffix (L, C, R, or None) of this runway end
        Suffix suffix() const {
            return suffix_;
        }
        /// Returns a name, like "16R" or "28L", for this runway end
        std::string name() {
            if(!name_.known()) {
                std::string nameString = std::to_string(heading_);
                if(suffix_ != Suffix::None) {
                    nameString.append({ static_cast<char>( suffix_ ) });
                }
                name_ = nameString;
            }
            return name_.value();
        }
        /// Returns a name, like "16R" or "28L", for this runway end
        std::string name() const {
            std::string nameString = std::to_string(heading_);
            if(suffix_ != Suffix::None) {
                nameString.append({ static_cast<char>( suffix_ ) });
            }
            return nameString;
        }
        /// Returns the latitude of this end
        double latitude() const {
            return latitude_;
        }
        /// Returns the longitude of this end
        double longitude() const {
            return longitude_;
        }
        /// Returns the length of this runway's displaced threshold on this end
        float displacedThresholdLength() const {
            return displacedThresholdLength_;
        }
        /// Return the length of the runway's blast pad on this end
        float blastPadLength() const {
            return blastPadLength_;
        }
        /// Returns the runway's approach lighting on this end
        ApproachLighting approachLighting() const {
            return approachLighting_;
        }
        /// Returns true if this end has touchdown zone lighting, otherwise returns false
        bool hasTouchdownZoneLighting() const {
            return touchdownZoneLighting_;
        }
        /// Returns the type of runway end identifier lights on this end
        RunwayEndIdentifierLights reil() const {
            return reil_;
        }
        
        void setHeading(int newHeading) {
            heading_ = newHeading;
        }
        void setSuffix(Suffix newSuffix) {
            suffix_ = newSuffix;
        }
        void setLatitude(double newLatitude) {
            latitude_ = newLatitude;
        }
        void setLongitude(double newLongitude) {
            longitude_ = newLongitude;
        }
        void setDisplacedThresholdLength(float newLength) {
            displacedThresholdLength_ = newLength;
        }
        void setBlastPadLength(float newLength) {
            blastPadLength_ = newLength;
        }
        void setApproachLighting(ApproachLighting newLighting) {
            approachLighting_ = newLighting;
        }
        void setTouchdownZoneLighting(bool hasLighting) {
            touchdownZoneLighting_ = hasLighting;
        }
        void setRunwayEndIdentifierLights(RunwayEndIdentifierLights newReil) {
            reil_ = newReil;
        }
        
    protected:
        
        /// The two-digit heading
        int heading_;
        /// The suffix
        Suffix suffix_ = Suffix::None;
        
        uncertain<std::string> name_;
        
        double latitude_;
        double longitude_;
        float displacedThresholdLength_;
        float blastPadLength_;
        ApproachLighting approachLighting_;
        bool touchdownZoneLighting_;
        RunwayEndIdentifierLights reil_;
    };
    
    
    const End& end1() const {
        return end1_;
    }
    
    const End& end2() const {
        return end2_;
    }
    
    Markings markings() const {
        return markings_;
    }
    Surface surface() const {
        return surface_;
    }
    Shoulder shoulder() const {
        return shoulder_;
    }
    float roughness() const {
        return roughness_;
    }
    float width() const {
        return width_;
    }
    
    bool hasCenterlineLights() const {
        return hasCenterlineLights_;
    }
    EdgeLights edgeLights() const {
        return edgeLights_;
    }
    bool hasGeneratedDistanceSigns() const {
        return hasGeneratedDistanceSigns_;
    }
    
    /// Returns a descriptive name for this runway, like "28R/10L"
    std::string name() const;
    /// Returns a descriptive name for this runway, like "28R/10L"
    std::string name();
    
    /// Returns the length of the runway in meters
    double length() const;
    /// Returns the length of the runway in meters
    double length();
    
    
    void setEnd1(const End& newEnd) {
        end1_ = newEnd;
    }
    void setEnd2(const End& newEnd) {
        end2_ = newEnd;
    }
    void setMarkings(Markings newMarkings) {
        markings_ = newMarkings;
    }
    void setSurface(Surface newSurface) {
        surface_ = newSurface;
    }
    void setShoulder(Shoulder newShoulder) {
        shoulder_ = newShoulder;
    }
    void setRoughness(float newRoughness) {
        roughness_ = newRoughness;
    }
    void setWidth(float newWidth) {
        width_ = newWidth;
    }
    void setHasCenterlineLights(bool hasLights) {
        hasCenterlineLights_ = hasLights;
    }
    void setEdgeLights(EdgeLights lights) {
        edgeLights_ = lights;
    }
    void setHasGeneratedDistanceSigns(bool hasSigns) {
        hasGeneratedDistanceSigns_ = hasSigns;
    }
    
protected:
    friend class AirportReader;
    
    Markings markings_;
    Surface surface_;
    Shoulder shoulder_;
    float roughness_;
    float width_;
    
    bool hasCenterlineLights_;
    EdgeLights edgeLights_;
    bool hasGeneratedDistanceSigns_;
    
    End end1_;
    End end2_;
    
    uncertain<std::string> name_;
    /// Length of the runway, in meters
    uncertain<double> length_;
    
};

}
#endif // RUNWAY_H
