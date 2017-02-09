// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperFlipbookComponent.h"
#include "PaperCompassFlipbook.h"
#include "PaperCompassComponent.generated.h"

/**
 * This is a section of an object's body that can:
 * - Rotate in 2, 4, or 8 directions
 * - Hold a number of animations for each
 */
UCLASS(meta = (BlueprintSpawnableComponent), HideCategories = ("Sprite"))
class SUPERALCHEMIST_API UPaperCompassComponent : public UPaperFlipbookComponent
{
	GENERATED_UCLASS_BODY()
	
public:
	// Functions
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e);
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
	EDirectionalDirections GetViewedDirection();

public:
	// Directional sprite to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Section")
	EDirectionalDirections WorldDirection;

	// Source Compass Flipbook
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Section")
	UPaperCompassFlipbook* CompassFlipbook;
};
