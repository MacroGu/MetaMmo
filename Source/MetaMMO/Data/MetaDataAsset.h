// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MetaDataAsset.generated.h"


class UTexture;

/**
 * 
 */
UCLASS(Blueprintable)
class METAMMO_API UMetaDataAsset : public UDataAsset
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere)
		TArray<UTexture*> GoodTextures;
};
