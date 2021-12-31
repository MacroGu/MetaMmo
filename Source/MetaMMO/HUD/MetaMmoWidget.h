// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Data/MetaDataMgr.h"
#include "MetaMmoWidget.generated.h"

class UProgressBar;
class UTextBlock;
class UOverlay;
class UKBEventData;
class UMetaMainBag;
class UMetaEquipBag;
class UMetaSkillBag;
class UMetaBuffBag;
class UMetaChatRoom;
class AMetaPlayerCharacter;

/**
 * 
 */
UCLASS()
class METAMMO_API UMetaMmoWidget : public UUserWidget
{
	GENERATED_BODY()
	


public:

	void InstallEvents(FText RoomName);

	void UnInstallEvents();

	void SetName(FString InName);

	void SetHpPercent(float InPercent);

	UFUNCTION(BlueprintCallable)
	void ReliveEvent();

	UFUNCTION(BlueprintCallable)
		void LeaveRoom();

	// 显示与关闭背包
	void OpenOrCloseBag(bool IsOpen);

	// 接受Drop事件后还原物品
	UFUNCTION(BlueprintCallable)
		void ReviseDragGood();

	void SetBaseHp(int32 InBaseHp);

	void SetDefense(int32 InDefense);

	void SetPowerRatio(float InPowerRatio);

	void SetSpeedRatio(float InSpeedRatio);

	// 检查一次哪个技能被激活
	void UpdateSkillOn();

public:

	// 添加倒计时
	UPROPERTY(Meta = (BindWidget))
	UOverlay* Countdown;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* TimeCountdown;

	// 排行榜 显示前三名
	UPROPERTY(Meta = (BindWidget))
	UOverlay* RankList;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* RankOne;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* RankTwo;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* RankThree;


	UPROPERTY(Meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* RoomText;

	UPROPERTY(Meta = (BindWidget))
	UProgressBar* BloodProgress;

	UPROPERTY(Meta = (BindWidget))
	UOverlay* ReliveBox;

	UPROPERTY(Meta = (BindWidget))
	UMetaMainBag* MainBag;

	UPROPERTY(Meta = (BindWidget))
	UMetaEquipBag* EquipBag;

	UPROPERTY(Meta = (BindWidget))
	UMetaSkillBag* SkillBag;

	UPROPERTY(Meta = (BindWidget))
	UMetaBuffBag* BuffBag;

	UPROPERTY(Meta = (BindWidget))
	UMetaChatRoom* ChatRoom;

	UPROPERTY()
	AMetaPlayerCharacter* PlayerCharacter;

protected: 

	void OnReqBagList(const UKBEventData* EventData);

	void UpdateBagBlock(EBagType BagType, uint8 BlockId);

	void OnPassGood(const UKBEventData* EventData);

	void OnReduceGood(const UKBEventData* EventData);

	void OnIncreaseGood(const UKBEventData* EventData);

	void UpdateCountDown(const UKBEventData* EventData);

	void ShowResultList(const UKBEventData* EventData);

};
