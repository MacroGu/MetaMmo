// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Center/MetaKbeGameMode.h"
#include "MetaLoginGameMode.generated.h"

class UKBEMain;
class UMetaLoginWidget;
class UKBEventData;

/**
 * 
 */
UCLASS()
class METAMMO_API AMetaLoginGameMode : public AMetaKbeGameMode
{
	GENERATED_BODY()

public:

	virtual void InstallEvent() override;

public:

	UKBEMain* KBEMain;


protected:

	virtual void BeginPlay() override;

	/* KBE事件
	*/
	void OnCreateAccountResult(const UKBEventData* pEventData);

	/* KBE事件
	*/
	void OnLoginFailed(const UKBEventData* pEventData);

	/* KBE事件
	*/
	void OnVersionNotMatch(const UKBEventData* pEventData);

	/* KBE事件
	*/
	void OnScriptVersionNotMatch(const UKBEventData* pEventData);

	/* KBE事件
	*/
	void OnLoginBaseappFailed(const UKBEventData* pEventData);

	/* KBE事件
	*/
	void OnLoginBaseapp(const UKBEventData* pEventData);

	/* KBE事件
	*/
	void OnLoginSuccessfully(const UKBEventData* pEventData);

protected:

	UMetaLoginWidget* LoginWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMetaLoginWidget> LoginWidgetClass;


};

