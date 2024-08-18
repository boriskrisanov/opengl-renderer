#pragma once

#include "../Scene.hpp"

void updateRenderSystem(const EcsRegistry &ecsRegistry);

/**
 * Responds to keyboard and mouse movement and updates the relevant matrices. This system is not responsible for
 * actually rendering anything or setting the matrix uniforms in the shader, that is done by the render system.
 */
void updateCameraMovementSystem(const EcsRegistry &ecsRegistry);