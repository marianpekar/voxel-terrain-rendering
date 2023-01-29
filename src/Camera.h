#pragma once

#include <SDL.h>

class Camera 
{
public:
	Camera() = default;

	void ProcessInput(bool* isRunning, const float deltaTime);

	float x = 512.f;
	float y = 512.f;
	float moveSpeed = 33.f;
	float height = 70.f;
	float horizon = 60.f;
	float zfar = 2048.f;
	float angle = 1.5f * 3.141592f;
};