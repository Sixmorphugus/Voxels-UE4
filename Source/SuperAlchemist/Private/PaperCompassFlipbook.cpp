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
	// TODO: take directional capability into account
	switch (Direction) {
	default:
		return North;
		break;
	case EDirectionalDirections::DD_NorthEast:
		return NorthEast;
		break;
	case EDirectionalDirections::DD_East:
		return East;
		break;
	case EDirectionalDirections::DD_SouthEast:
		return SouthEast;
		break;
	case EDirectionalDirections::DD_South:
		return South;
		break;
	case EDirectionalDirections::DD_SouthWest:
		return SouthWest;
		break;
	case EDirectionalDirections::DD_West:
		return West;
		break;
	case EDirectionalDirections::DD_NorthWest:
		return NorthWest;
		break;
	}
}
