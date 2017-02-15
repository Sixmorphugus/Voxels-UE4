// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "PaperCompassFlipbook.h"
#include "DirectionalCompassLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SUPERALCHEMIST_API UDirectionalCompassLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure)
	static EDirectionalDirections GetVectorCompassDirection(const FVector& v, float errorTolerence = 0.001);
};
