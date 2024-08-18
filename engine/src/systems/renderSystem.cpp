#include "../Shader.hpp"
#include "../components/CameraComponent.hpp"
#include "../components/MaterialComponent.hpp"
#include "../components/MeshComponent.hpp"
#include "systems.hpp"
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

using glm::mat4;

void updateRenderSystem(const EcsRegistry &ecsRegistry)
{
    const Scene &scene = ecsRegistry.getScene();
    const Renderer &renderer = scene.getRenderer();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    bool updatedCamera = false;
    // TODO: Improve camera/skybox rendering
    // This is needed so that the skybox renders first
    for (GameObject *gameObject : ecsRegistry.getGameObjects())
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
            renderer.shader->select();

            // TODO: Use own implementation of matrices
            // TODO: Set model matrix (GameObject transform)

            mat4 viewMatrix = glm::lookAt((glm::vec3)gameObject->position, (glm::vec3)(gameObject->position + camera->front), (glm::vec3)camera->up);
            //            viewMatrix = glm::translate(viewMatrix, (glm::vec3) gameObject.position);

            glUniformMatrix4fv(renderer.shader->getUniformLocation("transform"), 1, false, glm::value_ptr(glm::mat4{1.0f}));
            glUniformMatrix4fv(renderer.shader->getUniformLocation("projectionMatrix"), 1, false, glm::value_ptr(camera->projectionMatrix));
            glUniformMatrix4fv(renderer.shader->getUniformLocation("viewMatrix"), 1, false, glm::value_ptr(viewMatrix));

            if (scene.skybox != nullptr)
            {
                glDepthMask(false);
                scene.skybox->shader.select();

                const glm::mat4 viewMatrixWithoutTranslation = glm::mat3(viewMatrix);
                glUniformMatrix4fv(scene.skybox->shader.getUniformLocation("viewMatrix"), 1, false, glm::value_ptr(viewMatrixWithoutTranslation));
                glUniformMatrix4fv(scene.skybox->shader.getUniformLocation("projectionMatrix"), 1, false, glm::value_ptr(camera->projectionMatrix));

                glBindVertexArray(scene.skybox->getVertexArrayId());
                glBindTexture(GL_TEXTURE_CUBE_MAP, scene.skybox->getCubemapTextureId());
                glDrawArrays(GL_TRIANGLES, 0, 36);

                glDepthMask(true);
            }
        }
    }

    for (GameObject *gameObject : ecsRegistry.getGameObjects())
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

            glDrawArrays(GL_TRIANGLES, 0, (int)meshComponent->mesh.vertexCount);
        }
    }

    glfwSwapBuffers(renderer.window);
    glfwPollEvents();
}