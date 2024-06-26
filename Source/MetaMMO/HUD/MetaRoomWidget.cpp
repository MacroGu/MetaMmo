﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MetaRoomWidget.h"
#include "Scripts/ExEventData.h"
#include "Engine/KBEngine.h"
#include "Components/TextBlock.h"
#include "MetaRoomItem.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "Scripts/ExCommon.h"
#include "Blueprint/WidgetTree.h"
#include "Components/EditableTextBox.h"
#include "Center/MetaRoomGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "Center/MetaGameInstance.h"



void UMetaRoomWidget::OnReqRoomList(TArray<FROOM_INFO> RoomList)
{
	// 把旧的列表移除
	for (int i = 0; i < RoomItemGroup.Num(); ++i)
	{
		RoomItemGroup[i]->RemoveFromParent();
		RoomItemGroup[i]->ConditionalBeginDestroy();
	}
	// 清空数组
	RoomItemGroup.Empty();

	// 循环创建 RoomItem
	for (int i = 0; i < RoomList.Num(); ++i)
	{
		// 创建RoomItem
		UMetaRoomItem* RoomItem = WidgetTree->ConstructWidget<UMetaRoomItem>(RoomItemClass);
		UScrollBoxSlot* RoomItemSlot = Cast<UScrollBoxSlot>(RoomListScroll->AddChild(RoomItem));
		RoomItemSlot->SetPadding(FMargin(0.f, 5.f, 0.f, 5.f));

		// 设置房间信息
		RoomItem->InitItem(RoomList[i]);
		RoomItem->RoomItemSelectDel.BindUObject(this, &UMetaRoomWidget::RoomItemSelect);

		// 保存房间条目到本地数组
		RoomItemGroup.Add(RoomItem);
	}

	// 如果只有一个房间， 直接选中该房间
	if (RoomItemGroup.Num() == 1)
	{
		RoomItemSelect(RoomItemGroup[0]->RoomInfo.RoomId);
	}
}

void UMetaRoomWidget::OnCreateRoom(FROOM_INFO RoomInfo)
{

	// 创建RoomItem
	UMetaRoomItem* RoomItem = WidgetTree->ConstructWidget<UMetaRoomItem>(RoomItemClass);
	UScrollBoxSlot* RoomItemSlot = Cast<UScrollBoxSlot>(RoomListScroll->AddChild(RoomItem));
	RoomItemSlot->SetPadding(FMargin(0.f, 5.f, 0.f, 5.f));

	// 设置房间信息
	RoomItem->InitItem(RoomInfo);
	RoomItem->RoomItemSelectDel.BindUObject(this, &UMetaRoomWidget::RoomItemSelect);

	// 保存房间条目到本地数组
	RoomItemGroup.Add(RoomItem);

	// 如果只有一个房间， 直接选中该房间
	if (RoomItemGroup.Num() == 1)
	{
		RoomItemSelect(RoomItemGroup[0]->RoomInfo.RoomId);
	}

}

void UMetaRoomWidget::RefreshEvent()
{
	KBENGINE_EVENT_FIRE("ReqRoomList", NewObject<UKBEventData>());
}

void UMetaRoomWidget::CreateRoomEvent()
{
	// 获取房间名字
	FString RoomName = RoomNameTextBox->GetText().ToString();

	RoomNameTextBox->SetText(FText());

	if (RoomName.IsEmpty())
	{
		DDH::Debug() << "Please Enter Room Name" << DDH::Endl();
		return;
	}

	UKBEventData_ReqCreateRoom* EventData = NewObject<UKBEventData_ReqCreateRoom>();
	EventData->RoomName = RoomName;

	KBENGINE_EVENT_FIRE("ReqCreateRoom", EventData);

}

void UMetaRoomWidget::EnterGameEvent()
{
	for (int i = 0; i < RoomItemGroup.Num(); ++i)
	{
		if (RoomItemGroup[i]->IsSelected)
		{
			// 保存选中的房间名字到 GameInstance
			UMetaGameInstance* GameInstance = Cast<UMetaGameInstance>(UGameplayStatics::GetGameInstance(RoomGameMode->GetWorld()));
			GameInstance->RoomName = FText::FromString(RoomItemGroup[i]->RoomInfo.Name);

			UKBEventData_SelectRoomGame* EventData = NewObject<UKBEventData_SelectRoomGame>();
			EventData->RoomId = RoomItemGroup[i]->RoomInfo.RoomId;
			KBENGINE_EVENT_FIRE("SelectRoomGame", EventData);
			return;
		}
	}

	DDH::Debug() << "Please Select Room" << DDH::Endl();

}

void UMetaRoomWidget::RoomItemSelect(uint64 RoomId)
{
	// 取消其他角色的选定
	for (int i = 0; i < RoomItemGroup.Num(); ++i)
	{
		if (RoomItemGroup[i]->RoomInfo.RoomId != RoomId)
		{
			RoomItemGroup[i]->UnItemSelect();
		}
		else
		{
			RoomItemGroup[i]->ItemSelect();
		}
	}
}
