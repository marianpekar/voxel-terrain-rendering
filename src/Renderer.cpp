#include <iostream>
#include "Renderer.h"

bool Renderer::Setup()
{
	return InitSDL() && CreateWindow() && CreateRenderer() && SetBuffer();
}

bool Renderer::InitSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error initializing SDL" << std::endl;
		return false;
	}

	return true;
}

bool Renderer::CreateWindow() 
{
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_BORDERLESS);
	if (!window)
	{
		std::cerr << "Error initializing SDL window" << std::endl;
		return false;
	}

	return true;
}

bool Renderer::CreateRenderer()
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		std::cerr << "Error initializing SDL renderer" << std::endl;
		return false;
	}

	return true;
}

bool Renderer::SetBuffer()
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	colorBuffer = static_cast<Uint32*>(malloc(sizeof(Uint32) * static_cast<Uint32>(windowWidth) * static_cast<Uint32>(windowHeight)));

	colorBufferTexture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		windowWidth,
		windowHeight
	);

	return colorBuffer != nullptr && colorBufferTexture != nullptr;
}

void Renderer::DrawPoint(const int x, const int y, const Uint8 color, const SDL_Palette* palette)
{
	SDL_Color sdlColor = palette->colors[color];
	Uint32 argb = (sdlColor.a << 24) | (sdlColor.r << 16) | (sdlColor.g << 8) | sdlColor.b;

	colorBuffer[windowWidth * y + x] = argb;
}

void Renderer::ClearScreen(Uint32 color)
{
	for (size_t x = 0; x < windowWidth; x++) 
	{
		for (size_t y = 0; y < windowHeight; y++) 
		{
			colorBuffer[windowWidth * y + x] = color;
		}
	}
}

void Renderer::Render() const
{
	SDL_UpdateTexture(
		colorBufferTexture,
		nullptr,
		colorBuffer,
		static_cast<int>(static_cast<Uint32>(windowWidth) * sizeof(Uint32))
	);
	SDL_RenderCopy(renderer, colorBufferTexture, nullptr, nullptr);

	SDL_RenderPresent(renderer);
}

Renderer::~Renderer()
{
	free(colorBuffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}