#ifndef MATH_HEADER
#define MATH_HEADER

#include <SFML/Graphics.hpp>

static class Math
{
public:
	Math();
	~Math();

	static float AngleBetweenPoints(sf::Vector2f somePoint1, sf::Vector2f somePoint2);
	static float DegToRad(float someDegrees);
	static float VectorLength(sf::Vector2f someVector);	
	static float DistanceBetweenPoints(sf::Vector2f someVector1, sf::Vector2f someVector2);
	static sf::Vector2f DirectionBetweenPoitns(sf::Vector2f someVector1, sf::Vector2f someVector2);
	static sf::Vector2f NormalizeVector(sf::Vector2f someVector);
	static float Square(float someNumber);
	static double Pi();

};

#endif