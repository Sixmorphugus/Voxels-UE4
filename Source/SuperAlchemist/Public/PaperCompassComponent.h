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
UCLASS(meta = (BlueprintSpawnableComponent))
class SUPERALCHEMIST_API UPaperCompassComponent : public UPaperFlipbookComponent
{
	GENERATED_UCLASS_BODY()

private:
	// Functions
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e);
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	void UpdateSourceFlipbook();

public:
	UFUNCTION(BlueprintCallable)
	EDirectionalDirections GetWorldDirection();
	UFUNCTION(BlueprintCallable)
	void SetWorldDirection(const EDirectionalDirections& dd);

	UFUNCTION(BlueprintCallable)
	UPaperCompassFlipbook* GetCompassFlipbook();
	UFUNCTION(BlueprintCallable)
	void SetCompassFlipbook(UPaperCompassFlipbook* dd);

public:
	// Additional Compass Flipbooks (public)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paper Compass")
	TArray<UPaperCompassFlipbook*> AdditionalCompassFlipbooks;

private:
	// Directional sprite to use
	UPROPERTY(EditAnywhere, Category = "Paper Compass")
	EDirectionalDirections WorldDirection;

	// Source Compass Flipbook
	UPROPERTY(EditAnywhere, Category = "Paper Compass")
	UPaperCompassFlipbook* CompassFlipbook;
};
