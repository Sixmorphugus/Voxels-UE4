// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperAlchemist.h"
#include "DirectionalCompassLibrary.h"

EDirectionalDirections UDirectionalCompassLibrary::GetVectorCompassDirection(const FVector& v, float errorTolerence)
{
	bool pointsNorth = false;
	bool pointsEast = false;
	bool pointsSouth = false;
	bool pointsWest = false;

	if (v.Y > errorTolerence) {
		pointsEast = true;
	}
	else if (v.Y < -errorTolerence) {
		pointsWest = true;
	}

	if (v.X > errorTolerence) {
		pointsNorth = true;
	}
	else if (v.X < -errorTolerence) {
		pointsSouth = true;
	}

	// calculate which direction it is from what we know
	if (pointsNorth && pointsEast) {
		return EDirectionalDirections::DD_NorthEast;
	}
	else if (pointsNorth && pointsWest) {
		return EDirectionalDirections::DD_NorthWest;
	}
	else if (pointsNorth) {
		return EDirectionalDirections::DD_North;
	}
	else if (pointsSouth && pointsEast) {
		return EDirectionalDirections::DD_SouthEast;
	}
	else if (pointsSouth && pointsWest) {
		return EDirectionalDirections::DD_SouthWest;
	}
	else if (pointsEast) {
		return EDirectionalDirections::DD_East;
	}
	else if (pointsWest) {
		return EDirectionalDirections::DD_West;
	}

	return EDirectionalDirections::DD_South;
}
