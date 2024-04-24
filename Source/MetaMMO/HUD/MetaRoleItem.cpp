// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MetaRoleItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Scripts/ExEventData.h"





void UMetaRoleItem::ItemButtonEvent()
{
	RoleItemSelectDel.ExecuteIfBound(RoleInfo.Dbid);


}

void UMetaRoleItem::InitItem(FROLE_INFO InRoleInfo)
{
	RoleInfo = InRoleInfo;
	ItemName->SetText(FText::FromString(RoleInfo.Name));
	// 如果该角色是上次游戏退出时选中的， 就设置选定该条目
	if (RoleInfo.IsLastRole)
	{
		RoleItemSelectDel.ExecuteIfBound(RoleInfo.Dbid);
	}
}

void UMetaRoleItem::ItemSelect()
{
	RoleInfo.IsLastRole = true;
	OutLineImage->SetVisibility(ESlateVisibility::Visible);
}

void UMetaRoleItem::UnItemSelect()
{
	RoleInfo.IsLastRole = false;
	OutLineImage->SetVisibility(ESlateVisibility::Hidden);
}
