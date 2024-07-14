#include "renderSystem.hpp"
#include "../Shader.hpp"
#include "../components/CameraComponent.hpp"
#include "../components/MaterialComponent.hpp"
#include "../components/MeshComponent.hpp"
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

using glm::mat4;

void updateRenderSystem(const EcsRegistry &ecsRegistry)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    bool updatedCamera = false;
    // TODO: Improve camera/skybox rendering
    // This is needed so that the skybox renders first
    for (GameObject* gameObject : ecsRegistry.getGameObjects())
    {
        if (auto camera = gameObject->getComponent<CameraComponent>())
        {
            if (updatedCamera)
            {
                DEBUG_LOG("warning: multiple cameras in scene");
                continue;
            }
            updatedCamera = true;
            // This is needed because the skybox shader might be selected before this
            ecsRegistry.shader.select();

            // TODO: Use own implementation of matrices
            // TODO: Set model matrix (GameObject transform)

            mat4 viewMatrix = glm::lookAt((glm::vec3) gameObject->position, (glm::vec3) (gameObject->position + camera->front), (glm::vec3)camera->up);
            //            viewMatrix = glm::translate(viewMatrix, (glm::vec3) gameObject.position);

            glUniformMatrix4fv(ecsRegistry.shader.getUniformLocation("transform"), 1, false, glm::value_ptr(glm::mat4{1.0f}));
            glUniformMatrix4fv(ecsRegistry.shader.getUniformLocation("projectionMatrix"), 1, false, glm::value_ptr(camera->projectionMatrix));
            glUniformMatrix4fv(ecsRegistry.shader.getUniformLocation("viewMatrix"), 1, false, glm::value_ptr(viewMatrix));

            if (ecsRegistry.skybox != nullptr)
            {
                glDepthMask(false);
                ecsRegistry.skybox->shader.select();

                const glm::mat4 viewMatrixWithoutTranslation = glm::mat3(viewMatrix);
                glUniformMatrix4fv(ecsRegistry.skybox->shader.getUniformLocation("viewMatrix"), 1, false, glm::value_ptr(viewMatrixWithoutTranslation));
                glUniformMatrix4fv(ecsRegistry.skybox->shader.getUniformLocation("projectionMatrix"), 1, false, glm::value_ptr(camera->projectionMatrix));

                glBindVertexArray(ecsRegistry.skybox->getVertexArrayId());
                glBindTexture(GL_TEXTURE_CUBE_MAP, ecsRegistry.skybox->getCubemapTextureId());
                glDrawArrays(GL_TRIANGLES, 0, 36);

                glDepthMask(true);
            }
        }
    }

    for (GameObject* gameObject : ecsRegistry.getGameObjects())
    {
        if (auto meshComponent = gameObject->getComponent<MeshComponent>())
        {
            // TODO: Don't call shader.select() on every gameObject
            meshComponent->shader.select();
            glBindVertexArray(meshComponent->getVertexArray());

            if (auto material = gameObject->getComponent<MaterialComponent>())
            {
                // TODO: Batch materials for performance?
                material->texture.select();
            }

            glDrawArrays(GL_TRIANGLES, 0, meshComponent->mesh.vertexCount);
        }
    }

    glfwSwapBuffers(ecsRegistry.renderer.window);
    glfwPollEvents();
}