#include "renderSystem.hpp"
#include "../Shader.hpp"
#include "../components/CameraComponent.hpp"
#include "../components/MeshComponent.hpp"
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

using glm::mat4;

void updateRenderSystem(const EcsRegistry &ecsRegistry)
{
    glClear(GL_COLOR_BUFFER_BIT);

    bool updatedCamera = false;
    for (GameObject* gameObject : ecsRegistry.getGameObjects())
    {
        if (gameObject->hasComponent<MeshComponent>())
        {
            auto meshComponent = gameObject->getComponent<MeshComponent>();
            glBindVertexArray(meshComponent->getVertexArray());
            glDrawArrays(GL_TRIANGLES, 0, meshComponent->mesh.vertexCount);
        }
        else if (gameObject->hasComponent<CameraComponent>())
        {
            if (updatedCamera)
            {
                DEBUG_LOG("warning: multiple cameras in scene");
                continue;
            }
            updatedCamera = true;
            auto camera = gameObject->getComponent<CameraComponent>();

            // TODO: Use own implementation of matrices
            // TODO: Set model matrix (GameObject transform)

            mat4 viewMatrix = glm::lookAt((glm::vec3) gameObject->position, (glm::vec3) (gameObject->position + camera->front), (glm::vec3)camera->up);
//            viewMatrix = glm::translate(viewMatrix, (glm::vec3) gameObject.position);

            glUniformMatrix4fv(ecsRegistry.shader.getUniformLocation("transform"), 1, false, glm::value_ptr(glm::mat4{1.0f}));
            glUniformMatrix4fv(ecsRegistry.shader.getUniformLocation("projectionMatrix"), 1, false, glm::value_ptr(camera->projectionMatrix));
            glUniformMatrix4fv(ecsRegistry.shader.getUniformLocation("viewMatrix"), 1, false, glm::value_ptr(viewMatrix));
        }
    }

    glfwSwapBuffers(ecsRegistry.renderer.window);
    glfwPollEvents();
}