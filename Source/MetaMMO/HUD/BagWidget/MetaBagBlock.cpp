// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BagWidget/MetaBagBlock.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "MetaGoodItem.h"
#include "MetaGoodDrag.h"
#include "Scripts/ExEventData.h"
#include "Engine/KBEngine.h"


void UMetaBagBlock::UpdateBlock()
{
	// 从MetaDataMgr 获取该格子对应的物品信息
	if (!UMetaDataMgr::Get()->IsGoodExist(BagType, BlockId))
	{
		if (GoodItem)
		{
			GoodItem->RemoveFromParent();
			GoodItem = NULL;
		}
	}
	else
	{
		const FGoodInfo GoodInfo = UMetaDataMgr::Get()->GetGoodInfo(BagType, BlockId);
		// 如果GoodItem 不存在
		if (!GoodItem)
		{
			GoodItem = CreateWidget<UMetaGoodItem>(this, GoodItemClass);
			UOverlaySlot* ItemSlot = RootBox->AddChildToOverlay(GoodItem);
			ItemSlot->SetHorizontalAlignment(HAlign_Center);
			ItemSlot->SetVerticalAlignment(VAlign_Center);

			// 绑定委托
			GoodItem->LeaveBagBlockDel.BindLambda([this]() {
				GoodItem = NULL;
				});

		}
		//  添加数据给GoodItem
		GoodItem->InitGoodItem(BagType, BlockId);
	}
}

void UMetaBagBlock::InitBlockInfo(EBagType InType, uint8 InId)
{
	BagType = InType;
	BlockId = InId;
}

void UMetaBagBlock::IsAllowDropDown(bool& DropResult)
{
	DropResult = false;

	// 判断框里是否有物品
	if (GoodItem)
	{
		return;
	}

	// 是否是原格子
	if (UMetaDataMgr::Get()->HandBagType == BagType && UMetaDataMgr::Get()->HandBlockId == BlockId)
	{
		return;
	}

	const FGoodInfo HandGoodInfo = UMetaDataMgr::Get()->GetHandGoodInfo();

	// 判断是否匹配
	switch (BagType)
	{
	case EBagType::MainBag:
		DropResult = true;
		break;
	case EBagType::SkillBag:
		if (HandGoodInfo.GoodType == EGoodType::Skill)
		{
			DropResult = true;
		}
		break;
	case EBagType::BuffBag:
		if (HandGoodInfo.GoodType == EGoodType::Buff)
		{
			DropResult = true;
		}
		break;
	case EBagType::EquipBag:
		if (HandGoodInfo.GoodType == EGoodType::Equip)
		{
			// 装备需要判断格子ID
			if (HandGoodInfo.GoodKind == BlockId)
			{
				DropResult = true;
			}
		}
		break;
	default:
		break;
	}
}

void UMetaBagBlock::RequestPassGood()
{
	// 向服务器申请移动物品
	UKBEventData_PassGood* EventData = NewObject<UKBEventData_PassGood>();
	EventData->ArcBagType = (uint8)UMetaDataMgr::Get()->HandBagType;
	EventData->ArcBlockId = UMetaDataMgr::Get()->HandBlockId;
	EventData->DesBagType = (uint8)BagType;
	EventData->DesBlockId = BlockId;
	KBENGINE_EVENT_FIRE("PassGood", EventData);

	// 清空拖拽的物品信息
	if (UMetaDataMgr::Get()->GoodDrag)
	{
		UMetaDataMgr::Get()->GoodDrag->RemoveFromParent();
	}
	UMetaDataMgr::Get()->GoodDrag = NULL;

	// 创建空的物品信息和空的格子数据, 给移出物品格子使用
	FGoodInfo ArcGoodInfo;
	ArcGoodInfo.InitInfo(UMetaDataMgr::Get()->HandBlockId, 0, 0);

	// 当前格子更新的物品的信息
	FGoodInfo DesGoodInfo = UMetaDataMgr::Get()->GetHandGoodInfo();
	// 修改格子id
	DesGoodInfo.BlockId = BlockId;

	// 交换格子数据
	UMetaDataMgr::Get()->ChangeGoodInfo(UMetaDataMgr::Get()->HandBagType, ArcGoodInfo);
	UMetaDataMgr::Get()->ChangeGoodInfo(BagType, DesGoodInfo);
}

void UMetaBagBlock::ReviseDragGood()
{
	UMetaDataMgr::Get()->ReviseHandGood();
}
