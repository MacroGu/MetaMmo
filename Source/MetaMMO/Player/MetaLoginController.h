// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MetaLoginController.generated.h"

/**
 * 
 */
UCLASS()
class METAMMO_API AMetaLoginController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	int32 ScreenWidth;

	UPROPERTY(EditAnywhere)
	int32 ScreenHeight;


protected:

	virtual void BeginPlay() override;

};
