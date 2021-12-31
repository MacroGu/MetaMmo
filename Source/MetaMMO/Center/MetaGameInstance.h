// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MetaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class METAMMO_API UMetaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FText RoomName;

	
};
