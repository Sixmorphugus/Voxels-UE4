// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperAlchemist.h"
#include "PaperCompassFlipbook.h"

UPaperCompassFlipbook::UPaperCompassFlipbook(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	North = nullptr;
	NorthEast = nullptr;
	East = nullptr;
	SouthEast = nullptr;
	South = nullptr;
	SouthWest = nullptr;
	West = nullptr;
	NorthWest = nullptr;
}

EDirectionalCapabilities UPaperCompassFlipbook::GetDirectionalCapability()
{
	if (DirectionalCapability != EDirectionalCapabilities::DC_Detect)
		return DirectionalCapability;

	// we have to detect it if it isn't specified
	if (North && NorthEast && East && SouthEast && South && SouthWest && West && NorthWest)
		return EDirectionalCapabilities::DC_ExtendedCompass;
	else if(North && East && South && West)
		return EDirectionalCapabilities::DC_Compass;
	else
		return EDirectionalCapabilities::DC_FrontBack;
}

UPaperFlipbook* UPaperCompassFlipbook::GetPaperFlipbook(EDirectionalDirections Direction)
{
	switch (Direction) {
	default:
		return North;
		break;

	case EDirectionalDirections::DD_NorthEast:
		if (GetDirectionalCapability() == EDirectionalCapabilities::DC_FrontBack)
			return North;
		else if (GetDirectionalCapability() == EDirectionalCapabilities::DC_Compass)
			return East;

		return NorthEast;

	case EDirectionalDirections::DD_East:
		if (GetDirectionalCapability() == EDirectionalCapabilities::DC_FrontBack)
			return North;

		return East;

	case EDirectionalDirections::DD_SouthEast:
		if (GetDirectionalCapability() == EDirectionalCapabilities::DC_FrontBack)
			return South;
		else if (GetDirectionalCapability() == EDirectionalCapabilities::DC_Compass)
			return East;

		return SouthEast;

	case EDirectionalDirections::DD_South:
		return South;

	case EDirectionalDirections::DD_SouthWest:
		if (GetDirectionalCapability() == EDirectionalCapabilities::DC_FrontBack)
			return South;
		else if (GetDirectionalCapability() == EDirectionalCapabilities::DC_Compass)
			return West;

		return SouthWest;

	case EDirectionalDirections::DD_West:
		if (GetDirectionalCapability() == EDirectionalCapabilities::DC_FrontBack)
			return North;

		return West;

	case EDirectionalDirections::DD_NorthWest:
		if (GetDirectionalCapability() == EDirectionalCapabilities::DC_FrontBack)
			return North;
		else if (GetDirectionalCapability() == EDirectionalCapabilities::DC_Compass)
			return West;

		return NorthWest;
	}
}
