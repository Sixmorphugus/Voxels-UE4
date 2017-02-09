// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperAlchemistEditor.h"
#include "PaperCompassFlipbook.h"
#include "PaperCompassFlipbookFactory.h"

UPaperCompassFlipbookFactory::UPaperCompassFlipbookFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;

	SupportedClass = UPaperCompassFlipbook::StaticClass();
}

UObject* UPaperCompassFlipbookFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UPaperCompassFlipbook>(InParent, Class, Name, Flags | RF_Transactional);
}