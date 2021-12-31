// Fill out your copyright notice in the Description page of Project Settings.


#include "Center/MetaLoginGameMode.h"
#include "Engine/KBEngine.h"
#include "Scripts/ExCommon.h"
#include "Engine/KBEvent.h"
#include "Engine/KBEMain.h"
#include "HUD/ExLoginWidget.h"
#include "MetaKBEClient.h"



void AMetaLoginGameMode::InstallEvent()
{
	Super::InstallEvent();

	//创建用户入口实体回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onCreateAccountResult, OnCreateAccountResult);
	//登陆失败回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginFailed, OnLoginFailed);
	//版本匹配回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onVersionNotMatch, OnVersionNotMatch);
	//版本不匹配回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onScriptVersionNotMatch, OnScriptVersionNotMatch);
	//登陆baseapp失败回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseappFailed, OnLoginBaseappFailed);
	//登陆baseapp回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseapp, OnLoginBaseapp);
	//登陆成功回调, 生成ExAccount后在__init__()时调用, 在这里跳转到选择角色场景
	KBENGINE_REGISTER_EVENT("onLoginSuccessfully", OnLoginSuccessfully);

}

void AMetaLoginGameMode::BeginPlay()
{
	// 每次进入到登录界面时先清理一次KBE， 否则KBE插件缓存内容一直存在
	KBEngine::KBEngineApp::getSingleton().reset();

	Super::BeginPlay();

	LoginWidget = CreateWidget<UExLoginWidget>(GetWorld(), LoginWidgetClass);
	LoginWidget->AddToViewport();
	LoginWidget->LoginGameMode = this;
	LoginWidget->InitWidget();


	for (TActorIterator<AMetaKBEClient> ActorIt(GetWorld()); ActorIt; ++ActorIt)
	{
		KBEMain = (*ActorIt)->KBEMain;
	}

}

void AMetaLoginGameMode::OnCreateAccountResult(const UKBEventData* pEventData)
{

	const UKBEventData_onCreateAccountResult* ServerData = Cast<UKBEventData_onCreateAccountResult>(pEventData);
	DDH::Debug() << "OnCreateAccountResult, errorCode: " << ServerData->errorCode << " errorStr: " << ServerData->errorStr << DDH::Endl();

}

void AMetaLoginGameMode::OnLoginFailed(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginFailed* ServerData = Cast<UKBEventData_onLoginFailed>(pEventData);
	DDH::Debug() << "OnLoginFailed, failedcode: " << ServerData->failedcode << " errorStr: " << ServerData->errorStr << DDH::Endl();
}

void AMetaLoginGameMode::OnVersionNotMatch(const UKBEventData* pEventData)
{
	const UKBEventData_onVersionNotMatch* ServerData = Cast<UKBEventData_onVersionNotMatch>(pEventData);
	DDH::Debug() << "OnVersionNotMatch, clientVersion: " << ServerData->clientVersion << " serverVersion: " << ServerData->serverVersion << DDH::Endl();
}

void AMetaLoginGameMode::OnScriptVersionNotMatch(const UKBEventData* pEventData)
{
	const UKBEventData_onScriptVersionNotMatch* ServerData = Cast<UKBEventData_onScriptVersionNotMatch>(pEventData);
	DDH::Debug() << "OnScriptVersionNotMatch, clientScriptVersion: " << ServerData->clientScriptVersion << " serverScriptVersion: " << ServerData->serverScriptVersion << DDH::Endl();

}

void AMetaLoginGameMode::OnLoginBaseappFailed(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginBaseappFailed* ServerData = Cast<UKBEventData_onLoginBaseappFailed>(pEventData);
	DDH::Debug() << "OnLoginBaseappFailed, failedcode: " << ServerData->failedcode << " errorStr: " << ServerData->errorStr << DDH::Endl();
}

void AMetaLoginGameMode::OnLoginBaseapp(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginBaseapp* ServerData = Cast<UKBEventData_onLoginBaseapp>(pEventData);
	DDH::Debug() << "OnLoginBaseapp, eventName: " << ServerData->eventName << DDH::Endl();
}

void AMetaLoginGameMode::OnLoginSuccessfully(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginSuccessfully* ServerData = Cast<UKBEventData_onLoginSuccessfully>(pEventData);
	DDH::Debug() << "OnLoginBaseappFailed, entity_uuid: " << ServerData->entity_uuid << " entity_id: " << ServerData->entity_id << DDH::Endl();

	UGameplayStatics::OpenLevel(GetWorld(), FName("AvatarMap"));

}
