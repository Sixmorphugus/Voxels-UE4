#pragma once

#include "Factories/Factory.h"
#include "VoxelMapFactory.generated.h"

UCLASS()
class SUPERALCHEMISTEDITOR_API UVoxelMapFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
	
	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// End of UFactory interface
};
