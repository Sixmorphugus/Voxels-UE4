// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperAlchemist.h"
#include "PaperCompassComponent.h"


UPaperCompassComponent::UPaperCompassComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPaperCompassComponent::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UPaperCompassComponent, WorldDirection) || PropertyName == GET_MEMBER_NAME_CHECKED(UPaperCompassComponent, CompassFlipbook))
	{
		if (CompassFlipbook)
			SourceFlipbook = CompassFlipbook->GetPaperFlipbook(GetViewedDirection());
	}

	Super::PostEditChangeProperty(e);
}

void UPaperCompassComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

EDirectionalDirections UPaperCompassComponent::GetViewedDirection()
{
	return WorldDirection;
}
