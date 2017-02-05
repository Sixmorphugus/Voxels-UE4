// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperFlipbook.h"
#include "PaperCompassFlipbooks.generated.h"

// Which directions can this body part rotate - rotation directions of a character will be locked to ones that fit into the category.
UENUM(BlueprintType)
enum class EDirectionalCapabilities : uint8
{
	RC_Detect 	UMETA(DisplayName = "Unspecified"),
	RC_FrontBack 	UMETA(DisplayName = "Front/Back"),
	RC_Compass 	UMETA(DisplayName = "Compass"),
	RC_ExtendedCompass	UMETA(DisplayName = "Extended Compass")
};

// Which direction is a body part facing on the extended compass?
// Note that this has NO BEARING on anything other than what the player sees head on and should never be used to judge the actual rotation of an object.
UENUM(BlueprintType)
enum class EDirectionalDirections : uint8
{
	RD_North 	UMETA(DisplayName = "North"),
	RD_NorthEast 	UMETA(DisplayName = "North East"),
	RD_East 	UMETA(DisplayName = "East"),
	RD_SouthEast 	UMETA(DisplayName = "South East"),
	RD_South 	UMETA(DisplayName = "South"),
	RD_SouthWest 	UMETA(DisplayName = "South West"),
	RD_West 	UMETA(DisplayName = "West"),
	RD_NorthWest	UMETA(DisplayName = "North West")
};

UCLASS()
class UPaperCompassFlipbook : public UObject {
	GENERATED_BODY()

public:
	// functions
	UFUNCTION(BlueprintCallable)
	EDirectionalCapabilities DetectDirectionalCapability();

	UFUNCTION(BlueprintCallable)
	UPaperFlipbook* GetPaperFlipbook(EDirectionalDirections Direction);

public:
	// properties
	UPROPERTY(EditAnywhere)
	EDirectionalCapabilities DirectionalCapability;

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
};
