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

#include <cstdio>
#include <cstring>
#include <cerrno>
#include <sstream>
#include "fontcache.h"
#include "../../pluginpath.h"


namespace PPLNAMESPACE {

FontCache::FontCache(FontMgr& manager, const std::string& monospacePath, const std::string& proportionalPath) :
    fontManager_(manager),
    monospacePath(monospacePath),
    proportionalPath(proportionalPath)
{
    // Check that the typeface files are actually there. If they do not exist,
    // libfreetype will cause a crash and provide little information on what is wrong.
    checkFileExists(monospacePath);
    checkFileExists(proportionalPath);
}

FontHandle FontCache::get(GraphicsContext::Typeface font, unsigned int size) {
    
    // Select map to use based on 
    std::unordered_map<unsigned int, FontHandle>* map;
    if(font == GraphicsContext::Monospace) {
        map = &monospaceCache;
    }
    else if(font == GraphicsContext::Proportional) {
        map = &proportionalCache;
    } else {
        throw std::logic_error("FontCache: Unrecognized font");
    }
    
    try {
        return map->at(size);
    }
    catch (std::out_of_range&) {
        // Load
        FontHandle handle = load(font, size);
        // Insert into cache
        (*map)[size] = handle;
        
        return handle;
    }
    
}

FontHandle FontCache::load(GraphicsContext::Typeface font, unsigned int size) {
    std::string path;
    if(font == GraphicsContext::Monospace) {
        path = monospacePath;
    }
    else if(font == GraphicsContext::Proportional) {
        path = proportionalPath;
    } else {
        throw std::logic_error("FontCache: Unrecognized font");
    }
    
    return fontManager_.loadFont(path.c_str(), 0, 0, size, true); // Yes, require exact size
}

FontCache::~FontCache() {
    // Unload all fonts
    for(auto it = proportionalCache.begin(); it != proportionalCache.end(); it++) {
        fontManager_.unloadFont(it->second);
    }
    for(auto it = monospaceCache.begin(); it != monospaceCache.end(); it++) {
        fontManager_.unloadFont(it->second);
    }
}

FontMgr& FontCache::fontManager() {
    return fontManager_;
}

void FontCache::checkFileExists(const std::string& path) {
    std::FILE* file = std::fopen(path.c_str(), "r");
    if(!file) {
        std::stringstream stream;
        stream << "The font file " << path << " could not be opened: " << std::strerror(errno);
        throw std::runtime_error(stream.str());
    }
    std::fclose(file);
}

}
