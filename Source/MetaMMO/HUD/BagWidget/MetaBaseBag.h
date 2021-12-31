// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/MetaDataMgr.h"
#include "MetaBaseBag.generated.h"

class UMetaBagBlock;

/**
 * 
 */
UCLASS()
class METAMMO_API UExBaseBag : public UUserWidget
{
	GENERATED_BODY()
	
public:


	virtual void UpdateBlock(uint8 BlockId);


public:

	UPROPERTY(BlueprintReadWrite)
		TArray<UMetaBagBlock*> BlockGroup;


};
