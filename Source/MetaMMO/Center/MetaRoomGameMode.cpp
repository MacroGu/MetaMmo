// Fill out your copyright notice in the Description page of Project Settings.


#include "Center/MetaRoomGameMode.h"
#include <Kismet/GameplayStatics.h>

#include "Engine/KBEngine.h"
#include "Scripts/ExCommon.h"
#include "Scripts/ExEventData.h"
#include "HUD/MetaRoomWidget.h"




void AMetaRoomGameMode::OnReqRoomList(const UKBEventData* EventData)
{
	const UKBEventData_OnReqRoomList* ServerData = Cast<UKBEventData_OnReqRoomList>(EventData);
	RoomWidget->OnReqRoomList(ServerData->RoomList);
}

void AMetaRoomGameMode::OnCreateRoom(const UKBEventData* EventData)
{
	const UKBEventData_OnCreateRoom* ServerData = Cast<UKBEventData_OnCreateRoom>(EventData);
	RoomWidget->OnCreateRoom(ServerData->RoomInfo);
}

void AMetaRoomGameMode::AddSpaceGeometryMapping(const UKBEventData* EventData)
{
	const UKBEventData_addSpaceGeometryMapping* ServerData = Cast<UKBEventData_addSpaceGeometryMapping>(EventData);

	FString MapName;		// MmoMapOne
	FString TempStr;
	ServerData->spaceResPath.Split("/", &TempStr, &MapName);

	UGameplayStatics::OpenLevel(GetWorld(), FName(*MapName));
}

void AMetaRoomGameMode::BeginPlay()
{

	RoomWidget = CreateWidget<UMetaRoomWidget>(GetWorld(), RoomWidgetClass);
	RoomWidget->AddToViewport();
	RoomWidget->RoomGameMode = this;

	Super::BeginPlay();

	// 请求房间列表
	KBENGINE_EVENT_FIRE("ReqRoomList", NewObject<UKBEventData>());


}



void AMetaRoomGameMode::InstallEvent()
{
	Super::InstallEvent();

	KBENGINE_REGISTER_EVENT("OnReqRoomList", OnReqRoomList);
	KBENGINE_REGISTER_EVENT("OnCreateRoom", OnCreateRoom);

	// 这个时间触发时我们需要切换地图到游戏世界
	KBENGINE_REGISTER_EVENT("addSpaceGeometryMapping", AddSpaceGeometryMapping);

}
