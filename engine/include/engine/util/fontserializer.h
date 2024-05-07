#pragma once
#include <string>
#include "engine/graphics/fontcharacterinfo.h"
#include <iostream>
#include <fstream>
#include <sstream>

class FontSerializer{
public:

	/*
	* Deserializes .fnt files into FontInfo structs
	*/
	std::vector<FontCharacterInfo> deserializeFontInfo(const std::string& filename) {
        std::vector<FontCharacterInfo> charInfos;
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line)) {
            if (line.find("char id=") == std::string::npos)
                continue;

            FontCharacterInfo info;
            std::stringstream ss(line);

            ss.ignore(1000, '=');
            ss >> info.id;

            ss.ignore(1000, '=');
            ss >> info.x;

            ss.ignore(1000, '=');
            ss >> info.y;

            ss.ignore(1000, '=');
            ss >> info.width;

            ss.ignore(1000, '=');
            ss >> info.height;

            ss.ignore(1000, '=');
            ss >> info.xoffset;

            ss.ignore(1000, '=');
            ss >> info.yoffset;

            ss.ignore(1000, '=');
            ss >> info.xadvance;

            charInfos.push_back(info);
        }

        return charInfos;
	}
};
