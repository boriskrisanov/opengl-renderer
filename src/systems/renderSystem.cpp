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
//            mat4 model = glm::mat4(1.0f);
////            model = glm::rotate(model, glm::radians(0.0), glm::vec3(1, 0, 0));
//            model = glm::translate(model, glm::vec3{1, 0, 1});
//            mat4 view = glm::mat4(1.0f);
////            view = glm::translate(view, glm::vec3(-1.0f, -1.0f, 0.0f));
            // TODO: This doesn't need to be recomputed every frame
            double aspectRatio = (double) ecsRegistry.renderer.getWindowSize().x / (double) ecsRegistry.renderer.getWindowSize().y;
            mat4 projectionMatrix = glm::perspective(radians(camera->fov), aspectRatio, 0.1, 100.0);

            // TODO: Set model matrix (GameObject transform)

            mat4 viewMatrix = glm::lookAt((glm::vec3) gameObject->position, (glm::vec3) (gameObject->position + camera->front), (glm::vec3)camera->up);
//            viewMatrix = glm::translate(viewMatrix, (glm::vec3) gameObject.position);

            glUniformMatrix4fv(ecsRegistry.shader.getUniformLocation("transform"), 1, false, glm::value_ptr(glm::mat4{1.0f}));
            glUniformMatrix4fv(ecsRegistry.shader.getUniformLocation("projectionMatrix"), 1, false, glm::value_ptr(projectionMatrix));
            glUniformMatrix4fv(ecsRegistry.shader.getUniformLocation("viewMatrix"), 1, false, glm::value_ptr(viewMatrix));
        }
    }

    glfwSwapBuffers(ecsRegistry.renderer.window);
    glfwPollEvents();
}