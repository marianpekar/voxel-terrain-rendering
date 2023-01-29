#include "Map.h"

Map::Map(const char* colorMapPath, const char* heigthMapPath)
{
    heightmap = LoadPixels(heigthMapPath);
    colormap = LoadPixels(colorMapPath);
}

Map::~Map()
{
    delete heightmap;
    delete colormap;
}

Uint8* Map::LoadPixels(const char* path)
{
    auto image = IMG_Load(path);  
    width = image->w;  
    palette = image->format->palette;

    return static_cast<Uint8*>(image->pixels);
}

void Map::Draw(Renderer* renderer, Camera* camera)
{
    float sinangle = sin(camera->angle);
    float cosangle = cos(camera->angle);

    float plx = cosangle * camera->zfar + sinangle * camera->zfar;
    float ply = sinangle * camera->zfar - cosangle * camera->zfar;

    float prx = cosangle * camera->zfar - sinangle * camera->zfar;
    float pry = sinangle * camera->zfar + cosangle * camera->zfar;

    for (size_t i = 0; i < renderer->windowWidth; i++)
    {
        float dx = (plx + (prx - plx) / renderer->windowWidth * i) / camera->zfar;
        float dy = (ply + (pry - ply) / renderer->windowWidth * i) / camera->zfar;

        float rx = camera->x;
        float ry = camera->y;

        float tallestHeight = renderer->windowHeight;

        for (size_t z = 1; z < camera->zfar; z++)
        {
            rx += dx;
            ry += dy;

            Uint32 mapOffset = ((width * ((Uint32)(ry) & (width - 1))) + ((Uint32)(rx) & (width - 1)));
            Uint32 projectHeight = (Uint32)((camera->height - heightmap[mapOffset]) / z * SCALE_FACTOR + camera->horizon);

            if (projectHeight < tallestHeight)
            {
                for (size_t y = projectHeight; y < tallestHeight; y++)
                {
                    if (y >= 0)
                    {
                        renderer->DrawPoint(i, y, colormap[mapOffset], palette);
                    }
                }
                tallestHeight = projectHeight;
            }
        }
    }
}
