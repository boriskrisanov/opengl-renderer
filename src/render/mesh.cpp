#include "defs.hpp"

render::Mesh::Mesh(std::vector<float> vertexes)
{
    this->vertexes = vertexes;

    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(float), &vertexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Load texture
    Texture texture{"assets/textures/container.jpg"};

    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.textureData);
    glGenerateMipmap(GL_TEXTURE_2D);
}

render::Mesh::~Mesh()
{
    // TODO
}

void render::Mesh::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
