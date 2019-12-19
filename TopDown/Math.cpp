#include "pch.h"
#include "Math.h"


Math::Math()
{
}


Math::~Math()
{
}

float Math::AngleBetweenPoints(sf::Vector2f somePosition1, sf::Vector2f somePosition2)
{
	float tempDeltaX = somePosition1.x - somePosition2.x;
	float tempDeltaY = somePosition1.y - somePosition2.y;
	return std::atan2f(tempDeltaY, tempDeltaX);
}

float Math::DegToRad(float someDegrees)
{
	return someDegrees * 180 / Pi();
}

float Math::VectorLength(sf::Vector2f someVector)
{	
	return std::sqrt(Square(someVector.x) + Square(someVector.y));
}

sf::Vector2f Math::NormalizeVector(sf::Vector2f someVector)
{
	if (someVector == sf::Vector2f(0, 0))
	{
		return someVector;
	}

	return someVector / VectorLength(someVector);
}

float Math::Square(float someNumber)
{
	return someNumber * someNumber;
}

double Math::Pi()
{
	return 3.14159265359f;
}