#include "cursor.h"
#include "../texture.h"
#include <cstring>
#include <iostream>

namespace PPLNAMESPACE {

Cursor::Cursor(int textureId, GLfloat width, GLfloat height, const GLfloat* textureCoordinates, GLfloat xOffset, GLfloat yOffset) :
    textureId(textureId),
    width(width),
    height(height),
    xOffset(xOffset),
    yOffset(yOffset)
{
    // Copy texture coordinates
    std::memcpy(this->textureCoordinates, textureCoordinates, 8 * sizeof(GLfloat));
}


void Cursor::draw(float x, float y) const {
    
    const GLfloat left = x - width / 2 + xOffset;
    const GLfloat right = x + width / 2 + xOffset;
    const GLfloat top = y + height / 2 + yOffset;
    const GLfloat bottom = y - height / 2 + yOffset;
    
#ifdef BUILD_FOR_STANDALONE
    glBindTexture(GL_TEXTURE_2D, m_id);
#else
    XPLMBindTexture2d(textureId, 0);
    XPLMSetGraphicsState(0,1,0,0,1,0,0);
#endif

    glColor4f(1,1,1,1);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glBegin(GL_QUADS);
            glTexCoord2f(textureCoordinates[0], textureCoordinates[1]); glVertex2f(right, bottom);
            glTexCoord2f(textureCoordinates[2], textureCoordinates[3]); glVertex2f(left, bottom);
            glTexCoord2f(textureCoordinates[4], textureCoordinates[5]); glVertex2f(left, top);
            glTexCoord2f(textureCoordinates[6], textureCoordinates[7]); glVertex2f(right, top);
    glEnd();

#ifndef BUILD_FOR_STANDALONE
    XPLMSetGraphicsState(0,0,0,0,1,0,0);
#endif
}

}

