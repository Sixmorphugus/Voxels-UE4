// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperFlipbook.h"
#include "PaperCompassFlipbook.generated.h"

// Which directions can this object rotate - rotation directions of a character will be locked to ones that fit into the category.
UENUM(BlueprintType)
enum class EDirectionalCapabilities : uint8
{
	DC_Detect 	UMETA(DisplayName = "Unspecified"),
	DC_FrontBack 	UMETA(DisplayName = "Front/Back"),
	DC_Compass 	UMETA(DisplayName = "Compass"),
	DC_ExtendedCompass	UMETA(DisplayName = "Extended Compass")
};

// How far can some object rotate from another's direction
UENUM(BlueprintType)
enum class EDirectionalOffset : uint8
{
	DO_90 	UMETA(DisplayName = "90"),
	DO_180 	UMETA(DisplayName = "180 (not limited)"),
};

// Which direction is a body part facing on the extended compass?
UENUM(BlueprintType)
enum class EDirectionalDirections : uint8
{
	DD_North 	UMETA(DisplayName = "North"),
	DD_NorthEast 	UMETA(DisplayName = "North East"),
	DD_East 	UMETA(DisplayName = "East"),
	DD_SouthEast 	UMETA(DisplayName = "South East"),
	DD_South 	UMETA(DisplayName = "South"),
	DD_SouthWest 	UMETA(DisplayName = "South West"),
	DD_West 	UMETA(DisplayName = "West"),
	DD_NorthWest	UMETA(DisplayName = "North West")
};

UCLASS(BlueprintType)
class SUPERALCHEMIST_API UPaperCompassFlipbook : public UObject {
	GENERATED_UCLASS_BODY()

public:
	// functions
	UFUNCTION(BlueprintCallable)
	EDirectionalCapabilities GetDirectionalCapability();

	UFUNCTION(BlueprintCallable)
	UPaperFlipbook* GetPaperFlipbook(EDirectionalDirections Direction);

public:
	// properties
	UPROPERTY(EditAnywhere, Category = "Directions")
	UPaperFlipbook* North;
	UPROPERTY(EditAnywhere, Category = "Directions")
	UPaperFlipbook* NorthEast;
	UPROPERTY(EditAnywhere, Category = "Directions")
	UPaperFlipbook* East;
	UPROPERTY(EditAnywhere, Category = "Directions")
	UPaperFlipbook* SouthEast;
	UPROPERTY(EditAnywhere, Category = "Directions")
	UPaperFlipbook* South;
	UPROPERTY(EditAnywhere, Category = "Directions")
	UPaperFlipbook* SouthWest;
	UPROPERTY(EditAnywhere, Category = "Directions")
	UPaperFlipbook* West;
	UPROPERTY(EditAnywhere, Category = "Directions")
	UPaperFlipbook* NorthWest;

private:
	UPROPERTY(EditAnywhere)
	EDirectionalCapabilities DirectionalCapability;
};
