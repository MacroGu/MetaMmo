// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/BagWidget/MetaBaseBag.h"
#include "MetaSkillBag.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class METAMMO_API UMetaSkillBag : public UExBaseBag
{
	GENERATED_BODY()
	
public:

	void UpdateSkillOn();

	UPROPERTY(BlueprintReadWrite)
		TArray<UTextBlock*> OnTextGroup;

};
