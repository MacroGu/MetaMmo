// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MetaAvatarWidget.h"

#include "Scripts/ExCommon.h"
#include "Scripts/ExEventData.h"
#include "Engine/KBEngine.h"
#include "MetaRoleItem.h"

#include "Center/MetaAvatarGameMode.h"
#include "Scene/MetaRenderActor.h"

#include "Blueprint/WidgetTree.h"
#include "Components/EditableTextBox.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"



void UMetaAvatarWidget::OnReqRoleList(TArray<FROLE_INFO> RoleList)
{
	for (int i = 0; i < RoleList.Num(); ++i)
	{
		// 创建RoleItem
		UMetaRoleItem* RoleItem = WidgetTree->ConstructWidget<UMetaRoleItem>(RoleItemClass);
		UScrollBoxSlot* RoleItemSlot = Cast<UScrollBoxSlot>(RoleItemScroll->AddChild(RoleItem));
		RoleItemSlot->SetPadding(FMargin(0.f, 5.f, 0.f, 5.f));

		// 设置角色信息
		RoleItem->InitItem(RoleList[i]);
		RoleItem->RoleItemSelectDel.BindUObject(this, &UMetaAvatarWidget::RoleItemSelect);

		// 保存角色条目到本地数组
		RoleItemGroup.Add(RoleItem);

		if (RoleItem->RoleInfo.IsLastRole)
		{
			RoleItemSelect(RoleItem->RoleInfo.Dbid);
		}
	}
}

void UMetaAvatarWidget::OnCreateRole(FROLE_INFO RoleInfo)
{
	// 创建 RoleItem 并且添加到界面
	UMetaRoleItem* RoleItem = WidgetTree->ConstructWidget<UMetaRoleItem>(RoleItemClass);
	UScrollBoxSlot* RoleItemSlot = Cast<UScrollBoxSlot>(RoleItemScroll->AddChild(RoleItem));
	RoleItemSlot->SetPadding(FMargin(0.f, 5.f, 0.f, 5.f));

	// 设置角色信息
	RoleItem->InitItem(RoleInfo);
	RoleItem->RoleItemSelectDel.BindUObject(this, &UMetaAvatarWidget::RoleItemSelect);

	// 保存角色条目到本地数组
	RoleItemGroup.Add(RoleItem);

	// 如果当前只有一个角色, 就选择该角色
	if (RoleItemGroup.Num() == 1)
	{
		RoleItemSelect(RoleInfo.Dbid);
	}

}

void UMetaAvatarWidget::OnRemoveRole(FROLE_INFO RoleInfo)
{
	// 获取移除的角色
	UMetaRoleItem* RoleItem = NULL;
	for (int i = 0; i < RoleItemGroup.Num(); ++i)
	{
		if (RoleItemGroup[i]->RoleInfo.Dbid == RoleInfo.Dbid)
		{
			RoleItem = RoleItemGroup[i];
		}
	}
	// 如果角色不存在
	if (!RoleItem)
	{
		DDH::Debug() << "UMetaAvatarWidget::OnRemoveRole : No RoleInfo Exit By Dbid --> " << RoleInfo.Dbid << DDH::Endl();
		return;
	}

	// 移除RoleItem
	RoleItemScroll->RemoveChild(RoleItem);
	RoleItemGroup.Remove(RoleItem);

	// 如果角色列表不为空，  请选择第一个角色
	if (RoleItemGroup.Num() > 0)
	{
		RoleItemSelect(RoleItemGroup[0]->RoleInfo.Dbid);
	}

}

void UMetaAvatarWidget::EnterGameEvent()
{
	// 获取当前选择的角色
	for (int i = 0; i < RoleItemGroup.Num(); ++i)
	{
		if (RoleItemGroup[i]->RoleInfo.IsLastRole)
		{
			UKBEventData_ReqSelectRoleGame* EventData = NewObject<UKBEventData_ReqSelectRoleGame>();
			EventData->RoleInfo = RoleItemGroup[i]->RoleInfo;
			KBENGINE_EVENT_FIRE("ReqSelectRoleGame", EventData);
			return;
		}
	}

	// 如果运行到这里说明没有选择任何角色
	DDH::Debug() << "UMetaAvatarWidget::EnterGameEvent : No Role Selected" << DDH::Endl();

}

void UMetaAvatarWidget::CreateRoleEvent()
{
	EnterGameButton->SetVisibility(ESlateVisibility::Hidden);
	RoleTypeBox->SetVisibility(ESlateVisibility::Visible);

	CreateRoleButton->SetVisibility(ESlateVisibility::Hidden);
	RoleNameTextBox->SetVisibility(ESlateVisibility::Visible);

	RemoveRoleButton->SetVisibility(ESlateVisibility::Hidden);
	SureButton->SetVisibility(ESlateVisibility::Visible);
	CancelButton->SetVisibility(ESlateVisibility::Visible);

}

void UMetaAvatarWidget::RemoveRoleEvent()
{
	// 获取当前选择的角色
	for (int i = 0; i < RoleItemGroup.Num(); ++i)
	{
		if (RoleItemGroup[i]->RoleInfo.IsLastRole)
		{
			UKBEventData_ReqRemoveRole* EventData = NewObject<UKBEventData_ReqRemoveRole>();
			EventData->RoleInfo = RoleItemGroup[i]->RoleInfo;
			KBENGINE_EVENT_FIRE("ReqRemoveRole", EventData);
			return;
		}
	}

	// 如果运行到这里说明没有选择任何角色
	DDH::Debug() << "UMetaAvatarWidget::RemoveRoleEvent : No Role Selected" << DDH::Endl();

}

void UMetaAvatarWidget::SureEvent()
{
	EnterGameButton->SetVisibility(ESlateVisibility::Visible);
	RoleTypeBox->SetVisibility(ESlateVisibility::Hidden);

	CreateRoleButton->SetVisibility(ESlateVisibility::Visible);
	RoleNameTextBox->SetVisibility(ESlateVisibility::Hidden);

	RemoveRoleButton->SetVisibility(ESlateVisibility::Visible);
	SureButton->SetVisibility(ESlateVisibility::Hidden);
	CancelButton->SetVisibility(ESlateVisibility::Hidden);

	// 获取新角色的名字
	FString RoleName = RoleNameTextBox->GetText().ToString();

	if (RoleName.IsEmpty())
	{
		DDH::Debug() << "Please Input Role Name " << DDH::Endl();
		return;
	}

	// 获取到新角色的类型
	uint8 RoleType = ShooterCheckBox->GetCheckedState() == ECheckBoxState::Checked ? 0 : 1;
	UKBEventData_ReqCreateRole* EventData = NewObject<UKBEventData_ReqCreateRole>();
	EventData->RoleType = RoleType;
	EventData->Name = RoleName;
	KBENGINE_EVENT_FIRE("ReqCreateRole", EventData);

	// 清空输入框
	RoleNameTextBox->SetText(FText());

}

void UMetaAvatarWidget::CancelEvent()
{
	EnterGameButton->SetVisibility(ESlateVisibility::Visible);
	RoleTypeBox->SetVisibility(ESlateVisibility::Hidden);

	CreateRoleButton->SetVisibility(ESlateVisibility::Visible);
	RoleNameTextBox->SetVisibility(ESlateVisibility::Hidden);

	RemoveRoleButton->SetVisibility(ESlateVisibility::Visible);
	SureButton->SetVisibility(ESlateVisibility::Hidden);
	CancelButton->SetVisibility(ESlateVisibility::Hidden);

	// 清空输入框
	RoleNameTextBox->SetText(FText());
}

void UMetaAvatarWidget::RoleItemSelect(uint64 Dbid)
{
	// 取消其他角色的选定
	for (int i = 0; i < RoleItemGroup.Num(); ++i)
	{
		if (RoleItemGroup[i]->RoleInfo.Dbid != Dbid)
		{
			RoleItemGroup[i]->UnItemSelect();
		}
		else
		{
			RoleItemGroup[i]->ItemSelect();
			// 设置显示在界面上的角色模型和名字
			RoleTypeTitle->SetText(RoleTypeName[RoleItemGroup[i]->RoleInfo.RoleType]);
			// 渲染角色图片
			RoleGameMode->RenderActor->SwitchRoleMesh(RoleItemGroup[i]->RoleInfo.RoleType);
		}
	}
}
