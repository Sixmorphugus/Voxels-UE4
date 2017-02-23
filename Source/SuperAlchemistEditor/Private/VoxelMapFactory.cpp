#include "SuperAlchemistEditor.h"
#include "VoxelMapFactory.h"
#include "VoxelMap.h"

UVoxelMapFactory::UVoxelMapFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;

	SupportedClass = UVoxelMap::StaticClass();
}

UObject* UVoxelMapFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UVoxelMap>(InParent, Class, Name, Flags | RF_Transactional);
}