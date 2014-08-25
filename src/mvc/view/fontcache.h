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
    FontCache(FontMgr& manager);
    
    FontHandle get(GraphicsContext::Typeface font, unsigned int size);
    
    ~FontCache();
    
private:
    
    FontMgr& fontManager;
    
    std::unordered_map<unsigned int, FontHandle> proportionalCache;
    std::unordered_map<unsigned int, FontHandle> monospaceCache;
    
    FontHandle load(GraphicsContext::Typeface font, unsigned int size);
};

}
#endif // FONTCACHE_H
