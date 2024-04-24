// Fill out your copyright notice in the Description page of Project Settings.


#include "Center/MetaKbeGameMode.h"
#include "Engine/KBEngine.h"
#include "Scripts/ExCommon.h"
#include "Engine/World.h"
#include "TimerManager.h"



AMetaKbeGameMode::AMetaKbeGameMode()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AMetaKbeGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnInstallEvent();

}

void AMetaKbeGameMode::BeginPlay()
{
	Super::BeginPlay();
	InstallEvent();

}

void AMetaKbeGameMode::InstallEvent()
{
	// 注册最基本的回调事件
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onKicked, OnKicked);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onDisconnected, OnDisconnected);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onConnectionState, OnConnectionState);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappSuccessfully, OnReloginBaseappSuccessfully);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappFailed, OnReloginBaseappFailed);


}

void AMetaKbeGameMode::UnInstallEvent()
{
	KBENGINE_DEREGISTER_ALL_EVENT();

}

void AMetaKbeGameMode::OnKicked(const UKBEventData* EventData)
{
	const UKBEventData_onKicked* ServerData = Cast<UKBEventData_onKicked>(EventData);

	DDH::Debug() << "OnKicked: failedcode --> " << ServerData->failedcode << "; errorstr -- > " << ServerData->errorStr << DDH::Endl();

}

void AMetaKbeGameMode::OnDisconnected(const UKBEventData* EventData)
{

	const UKBEventData_onDisconnected* ServerData = Cast<UKBEventData_onDisconnected>(EventData);
	DDH::Debug() << "UKBEventData_onDisconnected: eventName --> " << ServerData->eventName << DDH::Endl();

}

void AMetaKbeGameMode::OnConnectionState(const UKBEventData* EventData)
{
	const UKBEventData_onConnectionState* ServerData = Cast<UKBEventData_onConnectionState>(EventData);
	DDH::Debug() << "UKBEventData_onConnectionState: address --> " << ServerData->address << " success: " << ServerData->success << DDH::Endl();
}

void AMetaKbeGameMode::OnReloginBaseappSuccessfully(const UKBEventData* EventData)
{
	const UKBEventData_onReloginBaseappSuccessfully* ServerData = Cast<UKBEventData_onReloginBaseappSuccessfully>(EventData);
	DDH::Debug() << "UKBEventData_onReloginBaseappSuccessfully, EventName:  " << ServerData->eventName << DDH::Endl();

	StopReloginBaseapp();

}

void AMetaKbeGameMode::OnReloginBaseappFailed(const UKBEventData* EventData)
{
	const UKBEventData_onReloginBaseappFailed* ServerData = Cast<UKBEventData_onReloginBaseappFailed>(EventData);
	DDH::Debug() << "UKBEventData_onReloginBaseappFailed, failedcode:  " << ServerData->failedcode << " errorStr: " << ServerData->errorStr << DDH::Endl();
}

void AMetaKbeGameMode::StartReloginBaseapp()
{
	if (!ReloginHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(ReloginHandle, this, &AMetaKbeGameMode::OnReloginBaseappTimer, 1.f, true);

	}

}

void AMetaKbeGameMode::StopReloginBaseapp()
{
	if (ReloginHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ReloginHandle);
	}

}

void AMetaKbeGameMode::OnReloginBaseappTimer()
{
	// 断线重连事件
	KBEngine::KBEngineApp::getSingleton().reloginBaseapp();

}