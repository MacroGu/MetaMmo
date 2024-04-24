// Fill out your copyright notice in the Description page of Project Settings.


#include "Center/MetaAvatarGameMode.h"
#include <Kismet/GameplayStatics.h>

#include "Scripts/ExEventData.h"
#include "Scripts/ExCommon.h"
#include "Engine/KBEngine.h"
#include "HUD/MetaAvatarWidget.h"
#include "Scene/MetaRenderActor.h"
#include "EngineUtils.h"

#include "Components/TextBlock.h"



void AMetaAvatarGameMode::InstallEvent()
{

	Super::InstallEvent();

	KBENGINE_REGISTER_EVENT("OnReqRoleList", OnReqRoleList);
	KBENGINE_REGISTER_EVENT("OnCreateRole", OnCreateRole);
	KBENGINE_REGISTER_EVENT("OnRemoveRole", OnRemoveRole);
	KBENGINE_REGISTER_EVENT("OnSelectRoleGame", OnSelectRoleGame);

}

void AMetaAvatarGameMode::BeginPlay()
{
	// 生成界面以及获取渲染Actor
	for (TActorIterator<AUMetaRenderActor> ActorIt(GetWorld()); ActorIt; ++ActorIt)
	{
		RenderActor = Cast<AUMetaRenderActor>(*ActorIt);
	}
	
	RoleWidget = CreateWidget<UMetaAvatarWidget>(GetWorld(), RoleWidgetClass);
	RoleWidget->AddToViewport();
	RoleWidget->RoleGameMode = this;

	Super::BeginPlay();

}

void AMetaAvatarGameMode::OnReqRoleList(const UKBEventData* EventData)
{
	const UKBEventData_OnReqRoleList* ServerData = Cast<UKBEventData_OnReqRoleList>(EventData);
	// 告诉角色界面角色列表来生成角色表
	RoleWidget->OnReqRoleList(ServerData->RoleList);

}

void AMetaAvatarGameMode::OnCreateRole(const UKBEventData* EventData)
{
	const UKBEventData_OnCreateRole* ServerData = Cast<UKBEventData_OnCreateRole>(EventData);
	// 如果 errorcode 不为 0 ， 说明创建不成功
	if (ServerData->ErrorCode == 0)
	{
		RoleWidget->OnCreateRole(ServerData->RoleInfo);
	}
}

void AMetaAvatarGameMode::OnRemoveRole(const UKBEventData* EventData)
{
	const UKBEventData_OnRemoveRole* ServerData = Cast<UKBEventData_OnRemoveRole>(EventData);

	RoleWidget->OnRemoveRole(ServerData->RoleInfo);
}

void AMetaAvatarGameMode::OnSelectRoleGame(const UKBEventData* EventData)
{
	const UKBEventData_OnSelectRoleGame* ServerData = Cast<UKBEventData_OnSelectRoleGame>(EventData);

	// 直接跳转选择房间场景
	UGameplayStatics::OpenLevel(GetWorld(), FName("RoomMap"));

}
