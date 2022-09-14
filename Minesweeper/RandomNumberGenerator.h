#pragma once
#include <random>

using namespace std;

class RandomNumberGenerator
{
private:
	//One instance of the x variable, and all instances SHARE this variable
	//Static variables/functions exist for the lifetime of your program
	static mt19937 random;
public:
	//One and only one of this function
	static int Int(int min, int max);
	static float Float(float min, float max);
};
