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
	return std::sqrt(std::pow(someVector.x, 2) + std::pow(someVector.y, 2));
}

float Math::DistanceBetweenPoints(sf::Vector2f someVector1, sf::Vector2f someVector2)
{
	sf::Vector2f tempVector;
	tempVector = someVector2 - someVector1;

	return VectorLength(tempVector);
}

sf::Vector2f Math::DirectionBetweenPoitns(sf::Vector2f someVector1, sf::Vector2f someVector2)
{
	sf::Vector2f tempVector;

	tempVector = someVector2 - someVector1;

	return NormalizeVector(tempVector);
	
}

sf::Vector2f Math::NormalizeVector(sf::Vector2f someVector)
{
	if (someVector == sf::Vector2f(0, 0))
	{
		return someVector;
	}

	return someVector / VectorLength(someVector);
}

double Math::Pi()
{
	return 3.14159265359f;
}