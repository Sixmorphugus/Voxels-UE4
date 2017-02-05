// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperFlipbookComponent.h"
#include "PaperCompassFlipbooks.h"
#include "PaperCompassComponent.generated.h"

/**
 * This is a section of character's body that can:
 * - Rotate in 2, 4, or 8 directions
 * - Hold a number of animations
 */
UCLASS(meta = (BlueprintSpawnableComponent), HideCategories = ("Sprite"))
class SUPERALCHEMIST_API UPaperCompassComponent : public UPaperFlipbookComponent
{
	GENERATED_BODY()
	UPaperCompassComponent(); // (todo: PrimaryComponentTick.bCanEverTick = true;)
	
public:
	// Functions
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
	
public:
	// Properties
	UPROPERTY(EditAnywhere, Category = "Section")
	EDirectionalDirections WorldDirection;

	UPROPERTY(EditAnywhere, Category = "Section")
	UPaperCompassFlipbook* CompassFlipbook;
};
