// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperFlipbook.h"
#include "PaperCompassFlipbook.generated.h"

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
