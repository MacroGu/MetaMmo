// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BagWidget/MetaGoodDrag.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


void UMetaGoodDrag::InitGoodInfo(uint8 GoodId, uint8 Number)
{
	GoodImage->SetBrushFromTexture((UTexture2D*)UMetaDataMgr::Get()->GetGoodTexture(GoodId));
	NumberText->SetText(FText::FromString(FString::FromInt(Number)));

	// 把自己保存到数据管理器
	UMetaDataMgr::Get()->GoodDrag = this;

}
