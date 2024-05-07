#pragma once
#include <vector>
#include <string>
#include <engine/graphics/fontcharacterinfo.h>

struct FontCharacterInfo {
    int id;
    int x;
    int y;
    int width;
    int height;
    int xoffset;
    int yoffset;
    int xadvance;
    int page;
    int chnl;
};
