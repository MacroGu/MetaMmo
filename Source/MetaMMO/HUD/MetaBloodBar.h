// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MetaBloodBar.generated.h"


class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS()
class METAMMO_API UMetaBloodBar : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetHpPercent(float InPercent);

	void SetRole(uint8 RoleType, FString InName);


public:

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* NameText;

	UPROPERTY(Meta = (BindWidget))
		UProgressBar* BloodProgress;



};
