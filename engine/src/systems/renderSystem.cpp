#include <GL/glew.h>
#include "../Shader.hpp"
#include "../components/CameraComponent.hpp"
#include "../components/MaterialComponent.hpp"
#include "../components/MeshComponent.hpp"
#include "systems.hpp"
#include <glm/ext.hpp>
#include <glm/glm.hpp>

using glm::mat4;

void updateRenderSystem(const EcsRegistry &ecsRegistry)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const Scene &scene = ecsRegistry.getScene();
    const Renderer &renderer = scene.getRenderer();
    Vector3<float> cameraPosition;

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
            cameraPosition = static_cast<Vector3<float>>(gameObject->position);
            // This is needed because the skybox shader might be selected before this
            renderer.shader->select();

            // TODO: Use own implementation of matrices
            // TODO: Set model matrix (GameObject transform)

            mat4 viewMatrix = glm::lookAt(static_cast<glm::vec3>(gameObject->position), static_cast<glm::vec3>(gameObject->position + camera->front), static_cast<glm::vec3>(camera->up));
            //            viewMatrix = glm::translate(viewMatrix, (glm::vec3) gameObject.position);

            renderer.shader->setUniform("modelMatrix", glm::mat4{1.0f});
            renderer.shader->setUniform("projectionMatrix", camera->projectionMatrix);
            renderer.shader->setUniform("viewMatrix", viewMatrix);

            if (scene.skybox != nullptr)
            {
                glDepthMask(false);
                scene.skybox->shader.select();

                const glm::mat4 viewMatrixWithoutTranslation = glm::mat3(viewMatrix);
                scene.skybox->shader.setUniform("viewMatrix", viewMatrixWithoutTranslation);
                scene.skybox->shader.setUniform("projectionMatrix", camera->projectionMatrix);

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
            meshComponent->shader.setUniform("lightPosition", Vector3<float>{2.0, 2.0, 2.0});
            meshComponent->shader.setUniform("cameraPosition", cameraPosition);
            meshComponent->shader.setUniform("worldSpacePosition", static_cast<Vector3<float>>(gameObject->position));

            glBindVertexArray(meshComponent->getVertexArray());

            if (const auto material = gameObject->getComponent<MaterialComponent>())
            {
                // TODO: Batch materials for performance?
                material->texture.select();
            }

            glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(meshComponent->mesh.vertexCount));
        }
    }
}

void updateEndRenderSystem(const EcsRegistry &ecsRegistry)
{
    // This is a separate system to allow multiple rendering passes after the initial render, such as UI
    glfwSwapBuffers(ecsRegistry.getScene().getRenderer().window);
    glfwPollEvents();
}