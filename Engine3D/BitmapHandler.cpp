#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "BitmapHandler.h"
#include <iostream>

BitmapHandler::BitmapHandler() {}

BitmapHandler::~BitmapHandler() {}

GLuint BitmapHandler::loadTexture(const std::string& filePath) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width, height, channels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Nie uda³o siê za³adowaæ tekstury: " << filePath << std::endl;
        return 0;
    }

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

    // Przekazanie danych tekstury do OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    // Ustawienia filtrowania i powielania
    setTextureParameters();

    // Zwolnienie pamiêci za³adowanej tekstury
    stbi_image_free(data);

    return textureID;
}

void BitmapHandler::bindTexture(GLuint textureID) {
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void BitmapHandler::setTextureParameters() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
