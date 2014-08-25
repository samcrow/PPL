#include "fontcache.h"
#include "../../pluginpath.h"


namespace PPLNAMESPACE {

FontCache::FontCache(FontMgr &manager) :
    fontManager(manager)
{
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
        path = PluginPath::prependPluginResourcesPath("fonts/DejaVuSansMono-Bold.ttf");
    }
    else if(font == GraphicsContext::Proportional) {
        path = PluginPath::prependPluginResourcesPath("fonts/DejaVuSans.ttf");
    } else {
        throw std::logic_error("FontCache: Unrecognized font");
    }
    
    return fontManager.loadFont(path.c_str(), 0, 0, size, true); // Yes, require exact size
}

FontCache::~FontCache() {
    // Unload all fonts
    for(auto it = proportionalCache.begin(); it != proportionalCache.end(); it++) {
        fontManager.unloadFont(it->second);
    }
    for(auto it = monospaceCache.begin(); it != monospaceCache.end(); it++) {
        fontManager.unloadFont(it->second);
    }
}

}
