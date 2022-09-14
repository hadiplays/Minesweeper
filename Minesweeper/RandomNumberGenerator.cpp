#include "RandomNumberGenerator.h"
#include <ctime>
using namespace std;

// Static variables must be redeclared in global space
mt19937 RandomNumberGenerator::random(time(0));

int RandomNumberGenerator::Int(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random);

}
float RandomNumberGenerator::Float(float min, float max)
{
	uniform_real_distribution<float> dist(min, max);
	return dist(random);
}