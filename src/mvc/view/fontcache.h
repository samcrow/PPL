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

#ifndef FONTCACHE_H
#define FONTCACHE_H
#include "../../namespaces.h"
#include <unordered_map>
#include "../../fontmgr.h"
#include "graphicscontext.h"

namespace PPLNAMESPACE {

class FontCache
{
public:
    /**
     * Constructor
     * @param manager The font manager to use to load fonts
     * @param monospacePath The path to a .ttf file for a monospace typeface
     * @param proportionalPath The path to a .ttf file for a proportional typeface
     */
    FontCache(FontMgr& manager, const std::string& monospacePath, const std::string& proportionalPath);
    
    FontHandle get(GraphicsContext::Typeface font, unsigned int size);
    
    /**
     *
     * @return A reference to the font manager that this cache uses
     */
    FontMgr& fontManager();

    ~FontCache();
    
private:
    
    FontMgr& fontManager_;

    std::string monospacePath;
    std::string proportionalPath;
    
    std::unordered_map<unsigned int, FontHandle> proportionalCache;
    std::unordered_map<unsigned int, FontHandle> monospaceCache;
    
    FontHandle load(GraphicsContext::Typeface font, unsigned int size);

    void checkFileExists(const std::string& path);
};

}
#endif // FONTCACHE_H
