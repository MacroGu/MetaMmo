// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/MetaDataMgr.h"
#include "MetaGoodDrag.generated.h"


class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class METAMMO_API UMetaGoodDrag : public UUserWidget
{
	GENERATED_BODY()
	


public:

	UFUNCTION(BlueprintCallable)
		void InitGoodInfo(uint8 GoodId, uint8 Number);

	UPROPERTY(Meta = (BindWidget))
		UImage* GoodImage;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* NumberText;

};
