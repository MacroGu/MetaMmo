﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MetaMmoWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Overlay.h"
#include "Engine/KBEngine.h"
#include "Scripts/ExEventData.h"
#include "BagWidget/MetaEquipBag.h"
#include "BagWidget/MetaMainBag.h"
#include "BagWidget/MetaBuffBag.h"
#include "BagWidget/MetaSkillBag.h"
#include "Player/MetaPlayerCharacter.h"
#include <Scripts/ExCommon.h>
#include "MetaChatRoom.h"





void UMetaMmoWidget::InstallEvents(FText RoomName)
{
	// 设置房间名字
	RoomText->SetText(RoomName);

	// 设置倒计时 60S
	TimeCountdown->SetText(FText::FromString("60"));

	// 绑定背包更新委托
	UMetaDataMgr::Get()->UpdateBagBlockDel.BindUObject(this, &UMetaMmoWidget::UpdateBagBlock);

	// 绑定注册事件
	KBENGINE_REGISTER_EVENT("OnReqBagList", OnReqBagList);
	KBENGINE_REGISTER_EVENT("OnPassGood", OnPassGood);
	KBENGINE_REGISTER_EVENT("OnReduceGood", OnReduceGood);
	KBENGINE_REGISTER_EVENT("OnIncreaseGood", OnIncreaseGood);
	KBENGINE_REGISTER_EVENT("UpdateCountDown", UpdateCountDown);
	KBENGINE_REGISTER_EVENT("ShowResultList", ShowResultList);

	ChatRoom->InstallEvent();

	Countdown->SetVisibility(ESlateVisibility::Visible);		// 默认不显示 排行榜

	RankList->SetVisibility(ESlateVisibility::Hidden);		// 默认不显示 排行榜

}

void UMetaMmoWidget::UnInstallEvents()
{
	// 注销该对象绑定的所有KBE事件
	KBENGINE_DEREGISTER_ALL_EVENT();

	// 告诉聊天室注销KBE事件
	ChatRoom->UnInstallEvents();

}

void UMetaMmoWidget::SetName(FString InName)
{
	NameText->SetText(FText::FromString(InName));
}

void UMetaMmoWidget::SetHpPercent(float InPercent)
{
	BloodProgress->SetPercent(InPercent);
	BloodProgress->SetFillColorAndOpacity(FLinearColor(1.f - InPercent, InPercent, 0.f));

	// 如果 HP 为0， 显示复活UI
	if (InPercent == 0.f)
	{
		if (ReliveBox->GetVisibility() == ESlateVisibility::Hidden)
		{
			ReliveBox->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		if (ReliveBox->GetVisibility() == ESlateVisibility::Visible)
		{
			ReliveBox->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UMetaMmoWidget::ReliveEvent()
{
	KBENGINE_EVENT_FIRE("Relive", NewObject<UKBEventData>());
}

void UMetaMmoWidget::LeaveRoom()
{
	// 离开房间， 返回选择角色界面
	KBENGINE_EVENT_FIRE("LeaveRoom", NewObject<UKBEventData>());
}

void UMetaMmoWidget::OpenOrCloseBag(bool IsOpen)
{
	if (IsOpen)
	{
		MainBag->SetVisibility(ESlateVisibility::Visible);
		EquipBag->SetVisibility(ESlateVisibility::Visible);
		ChatRoom->ShowOrHideInput(true);
	}
	else
	{
		MainBag->SetVisibility(ESlateVisibility::Hidden);
		EquipBag->SetVisibility(ESlateVisibility::Hidden);
		ChatRoom->ShowOrHideInput(false);
	}
}

void UMetaMmoWidget::ReviseDragGood()
{
	UMetaDataMgr::Get()->ReviseHandGood();
}

void UMetaMmoWidget::SetBaseHp(int32 InBaseHp)
{
	EquipBag->SetBaseHp(InBaseHp);
}

void UMetaMmoWidget::SetDefense(int32 InDefense)
{
	EquipBag->SetDefense(InDefense);
}

void UMetaMmoWidget::SetPowerRatio(float InPowerRatio)
{
	EquipBag->SetPowerRatio(InPowerRatio);
}

void UMetaMmoWidget::SetSpeedRatio(float InSpeedRatio)
{
	EquipBag->SetSpeedRatio(InSpeedRatio);
}

void UMetaMmoWidget::UpdateSkillOn()
{
	SkillBag->UpdateSkillOn();
}

void UMetaMmoWidget::OnReqBagList(const UKBEventData* EventData)
{
	const UKBEventData_OnReqBagList* ServerData = Cast<UKBEventData_OnReqBagList>(EventData);

	for (auto Info : ServerData->MainBag)
	{
		FGoodInfo GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		UMetaDataMgr::Get()->ChangeGoodInfo(EBagType::MainBag, GoodInfo);
	}

	for (auto Info : ServerData->SkillBag)
	{
		FGoodInfo GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		UMetaDataMgr::Get()->ChangeGoodInfo(EBagType::SkillBag, GoodInfo);
	}

	for (auto Info : ServerData->BuffBag)
	{
		FGoodInfo GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		UMetaDataMgr::Get()->ChangeGoodInfo(EBagType::BuffBag, GoodInfo);
	}

	for (auto Info : ServerData->EquipBag)
	{
		FGoodInfo GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		UMetaDataMgr::Get()->ChangeGoodInfo(EBagType::EquipBag, GoodInfo);
	}
}

void UMetaMmoWidget::UpdateBagBlock(EBagType BagType, uint8 BlockId)
{
	switch (BagType)
	{
	case EBagType::MainBag:
		MainBag->UpdateBlock(BlockId);
		break;
	case EBagType::SkillBag:
		SkillBag->UpdateBlock(BlockId);
		break;
	case EBagType::BuffBag:
		BuffBag->UpdateBlock(BlockId);
		break;
	case EBagType::EquipBag:
		EquipBag->UpdateBlock(BlockId);
		break;
	default:
		break;
	}
}

void UMetaMmoWidget::OnPassGood(const UKBEventData* EventData)
{
	const UKBEventData_OnPassGood* ServerData = Cast<UKBEventData_OnPassGood>(EventData);
	EBagType ArcBagType = (EBagType)ServerData->ArcBagType;
	FGoodInfo ArcGoodInfo;
	ArcGoodInfo.InitInfo(ServerData->ArcGoodInfo.BlockId, ServerData->ArcGoodInfo.GoodId, ServerData->ArcGoodInfo.Number);

	EBagType DesBagType = (EBagType)ServerData->DesBagType;
	FGoodInfo DesGoodInfo;
	DesGoodInfo.InitInfo(ServerData->DesGoodInfo.BlockId, ServerData->DesGoodInfo.GoodId, ServerData->DesGoodInfo.Number);

	// 直接更新DataMgr的背包数据
	UMetaDataMgr::Get()->ChangeGoodInfo(ArcBagType, ArcGoodInfo);
	UMetaDataMgr::Get()->ChangeGoodInfo(DesBagType, DesGoodInfo);

}

void UMetaMmoWidget::OnReduceGood(const UKBEventData* EventData)
{
	const UKBEventData_OnReduceGood* ServerData = Cast<UKBEventData_OnReduceGood>(EventData);

	// 获取数据
	EBagType BagType = (EBagType)ServerData->BagType;
	FGoodInfo GoodInfo;
	GoodInfo.InitInfo(ServerData->GoodInfo.BlockId, ServerData->GoodInfo.GoodId, ServerData->GoodInfo.Number);

	if (ServerData->ReduceRes == 1)
	{
		// 如果使用成功，区分技能和buff来做效果
		if (GoodInfo.GoodType == EGoodType::Skill)
		{
			// 告诉Character请求服务器进行攻击
			if (PlayerCharacter)
			{
				PlayerCharacter->Attack(GoodInfo.GoodKind);
			}
		}
		else
		{
			// buff, 加人身上特效
		}
	}

	// 无论使用是否成功都要更新背包物品
	// 先更新数据
	UMetaDataMgr::Get()->ChangeGoodInfo(BagType, GoodInfo);
}

void UMetaMmoWidget::OnIncreaseGood(const UKBEventData* EventData)
{
	const UKBEventData_OnIncreaseGood* ServerData = Cast<UKBEventData_OnIncreaseGood>(EventData);

	EBagType BagType = (EBagType)ServerData->BagType;
	FGoodInfo GoodInfo;
	GoodInfo.InitInfo(ServerData->GoodInfo.BlockId, ServerData->GoodInfo.GoodId, ServerData->GoodInfo.Number);

	// 增加物品不存在传过来物品为空的问题， 这里直接增加背包物品
	UMetaDataMgr::Get()->ChangeGoodInfo(BagType, GoodInfo);


}

void UMetaMmoWidget::UpdateCountDown(const UKBEventData* EventData)
{
	const UKBEventData_UpdateCountDown* ServerData = Cast<UKBEventData_UpdateCountDown>(EventData);

	TimeCountdown->SetText(FText::FromString(FString::FromInt(ServerData->CountDown)));

}

void UMetaMmoWidget::ShowResultList(const UKBEventData* EventData)
{
	const UKBEventData_ShowResultList* ServerData = Cast<UKBEventData_ShowResultList>(EventData);
	RankList->SetVisibility(ESlateVisibility::Visible);		// 显示 排行榜
	Countdown->SetVisibility(ESlateVisibility::Hidden);		// 默认不显示 排行榜

	FString one_player = "NO1: " + ServerData->NameOne + "  Count: " + FString::FromInt(ServerData->CountOne);
	RankOne->SetText(FText::FromString(one_player));

	FString two_player = "NO2: " + ServerData->NameTwo + "  Count: " + FString::FromInt(ServerData->CountTwo);
	RankTwo->SetText(FText::FromString(two_player));

	FString three_player = "NO3: " + ServerData->NameThree + "  Count: " + FString::FromInt(ServerData->CountThree);
	RankThree->SetText(FText::FromString(three_player));
}
