// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCompassComponent.h"
#include "PaperBodyPartComponent.generated.h"

/**
 * Extends the PaperCompassComponent from a simple object to a more complex one.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class SUPERALCHEMIST_API UPaperBodyPartComponent : public UPaperCompassComponent
{
	GENERATED_BODY()

private:
	// check if a given component (on the same actor) is oriented in a way that the orientation of this component "allows".
	// if not, we have to flip it around and reverse its animation.
	UFUNCTION(BlueprintCallable)
	virtual void CheckCompassComponentTwist(UPaperCompassComponent* CompassComponent);

public:
	// Dictates how much this body part can rotate away from another one before it has to rotate the other body part.
	// E.g. how far a character's torso can rotate away from his legs before he has to start running backwards.
	// If it is 90 the behavior is normal.
	// If it is 180 the character can literally turn around on themselves with no consequences.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paper BodyPart")
	EDirectionalOffset TwistLimit;
};
