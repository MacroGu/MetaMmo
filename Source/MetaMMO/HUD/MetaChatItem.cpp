// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MetaChatItem.h"
#include "Engine/Engine.h"
#include "TextBlock.h"


void UMetaChatItem::InitItem(FString Name, FString Date, FString Message)
{

	FString UserItem = FString::Printf(TEXT("%s  %s  :"), *Date, *Name);
	UserText->SetText(FText::FromString(UserItem));

	InfoText->SetText(FText::FromString(Message));

}
