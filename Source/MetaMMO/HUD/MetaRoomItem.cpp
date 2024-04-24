// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MetaRoomItem.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"



void UMetaRoomItem::ItemButtonEvent()
{
	RoomItemSelectDel.ExecuteIfBound(RoomInfo.RoomId);
}

void UMetaRoomItem::InitItem(FROOM_INFO InRoomInfo)
{
	RoomInfo = InRoomInfo;
	ItemName->SetText(FText::FromString(RoomInfo.Name));
}

void UMetaRoomItem::ItemSelect()
{
	IsSelected = true;
	OutLineImage->SetVisibility(ESlateVisibility::Visible);
}

void UMetaRoomItem::UnItemSelect()
{
	IsSelected = false;
	OutLineImage->SetVisibility(ESlateVisibility::Hidden);
}
