#include "utils.hpp"
#include "world.hpp"

namespace world
{
void Block::initVertexBuffer()
{
    std::vector<float> vertexBufferData;
  
    if (positiveXFaceVisible)
    {
        utils::pushBackArrayToVector(vertexBufferData, positiveXFaceVertexes);
				vertexCount += 6;
    }
    if (negativeXFaceVisible)
    {
        utils::pushBackArrayToVector(vertexBufferData, negativeXFaceVertexes);
				vertexCount += 6;
    }

    if (positiveYFaceVisible)
    {
        utils::pushBackArrayToVector(vertexBufferData, positiveYFaceVertexes);
				vertexCount += 6;
    }
    if (negativeYFaceVisible)
    {
        utils::pushBackArrayToVector(vertexBufferData, negativeYFaceVertexes);
				vertexCount += 6;
    }

    if (positiveZFaceVisible)
    {
        utils::pushBackArrayToVector(vertexBufferData, positiveZFaceVertexes);
				vertexCount += 6;
    }
    if (negativeZFaceVisible)
    {
        utils::pushBackArrayToVector(vertexBufferData, negativeZFaceVertexes);
				vertexCount += 6;
    }

    DEBUG_LOG(vertexBufferData.size()); // Should not be 6

    // Set up OpenGL buffers
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, utils::sizeOfVectorInBytes(vertexBufferData), &vertexBufferData.front(), GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 5, 0);
    glEnableVertexAttribArray(0);

    // Texture coordinate
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 5, (const void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}
} // namespace world