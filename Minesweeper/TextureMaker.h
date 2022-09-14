#pragma once
#include <unordered_map>
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;

class TextureMaker
{
	//static == one and only one of these in memory, ever
	static unordered_map<string, sf::Texture> textures;
	static void LoadTexture(string textureName); // LoadTexteure("space");

public:
	static sf::Texture& GetTexture(string textureName);
	static void Clear(); // Call this once, at the end of main()
};

