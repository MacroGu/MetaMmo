// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Center/MetaKbeGameMode.h"
#include "MetaMmoGameMode.generated.h"

class AMetaCharacterEntity;
class AMetaPlayerCharacter;
class AMetaRemoteCharacter;
class AMetaMonsterCharacter;
class AMetaSkillActor;
class AMetaFlobActor;
class UMetaMmoWidget;


/**
 * 
 */
UCLASS()
class METAMMO_API AMetaMmoGameMode : public AMetaKbeGameMode
{
	GENERATED_BODY()


public:

	UPROPERTY()
		AMetaPlayerCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<AMetaPlayerCharacter>> PlayerClassList;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<AMetaRemoteCharacter>> RemoteClassList;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AMetaMonsterCharacter> MonsterClass;


	// 保持所有远程玩家和怪物
	UPROPERTY(EditAnywhere)
		TMap<int32, AMetaCharacterEntity*> CharacterMap;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UMetaMmoWidget> MmoWidgetClass;

	UPROPERTY(EditAnywhere)
		TMap<int32, AMetaSkillActor*> SkillMap;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<AMetaSkillActor>> SkillClassList;

	UPROPERTY(EditAnywhere)
		TMap<int32, AMetaFlobActor*> FlobMap;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AMetaFlobActor> FlobClass;

protected:

	virtual void InstallEvent() override;

	virtual void BeginPlay() override;

	void OnEnterWorld(const UKBEventData* EventData);

	void OnEnterSpace(const UKBEventData* EventData);

	void OnLeaveWorld(const UKBEventData* EventData);

	void OnLeaveSpace(const UKBEventData* EventData);

	void SetPosition(const UKBEventData* EventData);

	void SetDirection(const UKBEventData* EventData);

	void UpdatePosition(const UKBEventData* EventData);

	void OnAnimUpdate(const UKBEventData* EventData);

	void SetBaseHP(const UKBEventData* EventData);

	void SetHP(const UKBEventData* EventData);

	void SetDefense(const UKBEventData* EventData);

	void SetPowerRatio(const UKBEventData* EventData);

	void SetSpeedRatio(const UKBEventData* EventData);

	void OnAttack(const UKBEventData* EventData);

	// 离开房间返回大厅
	void OnLeaveRoom(const UKBEventData* EventData);

	// 玩家进入游戏场景
	void AddSpaceGeometryMapping(const UKBEventData* EventData);

protected:

	UMetaMmoWidget* MmoWidget;


public:

	virtual void UnInstallEvent() override;


};
