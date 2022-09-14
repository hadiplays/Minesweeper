#include "TextureMaker.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>

using namespace std;


// "redeclare" the variable, so this file knows it exists and can use it
unordered_map<string, sf::Texture> TextureMaker::textures;

void TextureMaker::LoadTexture(string fileName)
{
	string path = "images/";
	path += fileName + ".png";

	textures[fileName].loadFromFile(path);
}

sf::Texture& TextureMaker::GetTexture(string textureName)
{
	// if the texture DOESN'T exist...
	if (textures.find(textureName) == textures.end()) // we didn't find it
		LoadTexture(textureName);

	// load it first? Then return it?
	return textures[textureName];

}

void TextureMaker::Clear()
{
	textures.clear(); // get rid of all stored objects
}