#pragma once

#include "SDL_image.h"
#include "Renderer.h"
#include "Camera.h"

class Map 
{
public:
	Uint8* colormap = nullptr;
	Uint8* heightmap = nullptr;
	SDL_Palette* palette = nullptr;
	int width = 0;

	Map(const char* colorMapPath, const char* heigthMapPath);
	~Map();

	void Draw(Renderer* renderer, Camera* camera);
private:
	const Uint32 SCALE_FACTOR = 255;
	Uint8* LoadPixels(const char* path);
};