// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MetaChatItem.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class METAMMO_API UMetaChatItem : public UUserWidget
{
	GENERATED_BODY()
	

public:

	// ��ʼ������
	void InitItem(FString Name, FString Date, FString Message);


public:

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* UserText;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* InfoText;

};
