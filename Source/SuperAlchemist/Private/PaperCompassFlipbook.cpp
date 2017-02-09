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
	if (DirectionalCapability != EDirectionalCapabilities::RC_Detect)
		return DirectionalCapability;

	// we have to detect it if it isn't specified
	if (North && NorthEast && East && SouthEast && South && SouthWest && West && NorthWest)
		return EDirectionalCapabilities::RC_ExtendedCompass;
	else if(North && East && South && West)
		return EDirectionalCapabilities::RC_Compass;
	else
		return EDirectionalCapabilities::RC_FrontBack;
}

UPaperFlipbook* UPaperCompassFlipbook::GetPaperFlipbook(EDirectionalDirections Direction)
{
	switch (Direction) {
	default:
		return North;
		break;
	case EDirectionalDirections::RD_NorthEast:
		return NorthEast;
		break;
	case EDirectionalDirections::RD_East:
		return East;
		break;
	case EDirectionalDirections::RD_SouthEast:
		return SouthEast;
		break;
	case EDirectionalDirections::RD_South:
		return South;
		break;
	case EDirectionalDirections::RD_SouthWest:
		return SouthWest;
		break;
	case EDirectionalDirections::RD_West:
		return West;
		break;
	case EDirectionalDirections::RD_NorthWest:
		return NorthWest;
		break;
	}
}
