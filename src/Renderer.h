#pragma once

#include "SDL.h"

class Renderer 
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

public:
	Renderer() = default;
	~Renderer();

	int windowWidth = 800, windowHeight = 600;

	bool Setup();

	void DrawPoint(const int x, const int y, const Uint8 color, const SDL_Palette* palette);
	void ClearScreen(const Uint32 color);
	void Render() const;

private:
	Uint32* colorBuffer = nullptr;
	SDL_Texture* colorBufferTexture = nullptr;

	bool InitSDL();
	bool CreateWindow();
	bool CreateRenderer();
	bool SetBuffer();
};