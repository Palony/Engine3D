#ifndef BITMAP_HANDLER_H
#define BITMAP_HANDLER_H

#include <GL/freeglut.h>
#include <string>

class BitmapHandler {
public:
    BitmapHandler();
    ~BitmapHandler();

    GLuint loadTexture(const std::string& filePath); // £adowanie tekstury
    void bindTexture(GLuint textureID);             // Wi¹zanie tekstury

private:
    void setTextureParameters();                    // Ustawienia tekstury
};

#endif
