#include "texture_loader.hpp"
#include <iostream>

GLuint earthTexture;  // Define texture variable

void loadEarthTexture() {
    earthTexture = SOIL_load_OGL_texture(
        "textures/earthmap1k.jpg",  // Texture file
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    if (!earthTexture) {
        std::cerr << "Failed to load Earth texture!" << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, earthTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
