#ifndef PNGIO_H
#define PNGIO_H
#include "../namespaces.h"
#include <string>

#if IBM
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#elif LIN
#include <GL/gl.h>
#include <GL/glu.h>
#else
#if __GNUC__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <gl.h>
#include <glu.h>
#endif
#endif


namespace PPLNAMESPACE {
struct IMAGEDATA;

/**
 * @brief The PngIO class reads PNG (Portable Network Graphics) image files
 */
class PngIO
{
public:
    
    static void read(IMAGEDATA& image, GLuint &type, const std::string& path);
    
private:
    PngIO() {}
};

}
#endif // PNGIO_H
