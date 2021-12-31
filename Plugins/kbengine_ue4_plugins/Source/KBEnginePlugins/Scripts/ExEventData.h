// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/KBEvent.h"
#include "Engine/KBETypes.h"
#include "UObject/NoExportTypes.h"
#include "ExEventData.generated.h"

// 角色信息结构体
USTRUCT()
struct FROLE_INFO
{
	GENERATED_BODY()

public:

	UPROPERTY()
		uint64 Dbid;

	UPROPERTY()
		FString Name;

	UPROPERTY()
		uint8 RoleType;

	UPROPERTY()
		bool IsLastRole;

	void InitData(DBID InDbid, const FString& InName, uint8 InRoleType, bool InIsLastRole)
	{
		Dbid = InDbid;
		Name = InName;
		RoleType = InRoleType;
		IsLastRole = InIsLastRole;
	}

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqRoleList : public UKBEventData {
	GENERATED_BODY()

public:

	UPROPERTY()
		TArray<FROLE_INFO> RoleList;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnCreateRole : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		uint8 ErrorCode;

	UPROPERTY()
		FROLE_INFO RoleInfo;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnRemoveRole : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		FROLE_INFO RoleInfo;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnSelectRoleGame : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		uint64 Dbid;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqCreateRole : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		uint8 RoleType;

	UPROPERTY()
		FString Name;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqRemoveRole : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		FROLE_INFO RoleInfo;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqSelectRoleGame : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		FROLE_INFO RoleInfo;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqCreateRoom : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		FString RoomName;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SelectRoomGame : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		uint64 RoomId;
};

USTRUCT()
struct FROOM_INFO
{
	GENERATED_BODY()

public:

	UPROPERTY()
		uint64 RoomId;

	UPROPERTY()
		FString Name;

	void InitData(uint64 InRoomId, const FString & InName)
	{
		RoomId = InRoomId;
		Name = InName;
	}
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqRoomList : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		TArray<FROOM_INFO> RoomList;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnCreateRoom : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		FROOM_INFO RoomInfo;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnAnimUpdate : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		int32 EntityId;

	UPROPERTY()
		float Speed;

	UPROPERTY()
		float Direction;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_AnimUpdate : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		float Speed;

	UPROPERTY()
		float Direction;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SetBaseHP : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		int32 EntityId;

	UPROPERTY()
		bool IsPlayer;

	UPROPERTY()
		int32 BaseHP;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SetHP : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		int32 EntityId;

	UPROPERTY()
		bool IsPlayer;

	UPROPERTY()
		int32 HP;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SetDefense : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		int32 EntityId;

	UPROPERTY()
		int32 Defense;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SetPowerRatio : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		int32 EntityId;

	UPROPERTY()
		float PowerRatio;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SetSpeedRatio : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		int32 EntityId;

	UPROPERTY()
		float SpeedRatio;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnAttack : public UKBEventData {

	GENERATED_BODY()

public:

	UPROPERTY()
		int32 EntityId;

};

USTRUCT()
struct FGOOD_INFO
{
	GENERATED_BODY()

public:

	UPROPERTY()
		uint8 BlockId;

	UPROPERTY()
		uint8 GoodId;

	UPROPERTY()
		uint8 Number;

	void InitInfo(uint8 InBlockId, uint8 InGoodId, uint8 InNumber)
	{
		BlockId = InBlockId;
		GoodId = InGoodId;
		Number = InNumber;
	}

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqBagList : public UKBEventData
{
	GENERATED_BODY()

public:

	UPROPERTY()
		TArray<FGOOD_INFO> MainBag;

	UPROPERTY()
		TArray<FGOOD_INFO> SkillBag;

	UPROPERTY()
		TArray<FGOOD_INFO> BuffBag;

	UPROPERTY()
		TArray<FGOOD_INFO> EquipBag;
};


UCLASS()
class KBENGINEPLUGINS_API UKBEventData_PassGood : public UKBEventData
{
	GENERATED_BODY()

public:

	UPROPERTY()
		uint8 ArcBagType;

	UPROPERTY()
		uint8 ArcBlockId;

	UPROPERTY()
		uint8 DesBagType;

	UPROPERTY()
		uint8 DesBlockId;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnPassGood : public UKBEventData
{
	GENERATED_BODY()

public:

	UPROPERTY()
		uint8 ArcBagType;

	UPROPERTY()
		FGOOD_INFO ArcGoodInfo;

	UPROPERTY()
		uint8 DesBagType;

	UPROPERTY()
		FGOOD_INFO DesGoodInfo;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReduceGood : public UKBEventData
{
	GENERATED_BODY()

public:

	UPROPERTY()
		uint8 BagType;

	UPROPERTY()
		uint8 BlockId;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReduceGood : public UKBEventData
{
	GENERATED_BODY()

public:

	UPROPERTY()
		uint8 ReduceRes;

	UPROPERTY()
		uint8 BagType;

	UPROPERTY()
		FGOOD_INFO GoodInfo;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_Attack : public UKBEventData
{
	GENERATED_BODY()

public:

	UPROPERTY()
		uint8 SkillId;

	UPROPERTY()
		FVector SpawnPos;

	UPROPERTY()
		FVector TargetPos;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnIncreaseGood : public UKBEventData
{
	GENERATED_BODY()

public:

	UPROPERTY()
		uint8 BagType;

	UPROPERTY()
		FGOOD_INFO GoodInfo;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SendChatInfo : public UKBEventData
{
	GENERATED_BODY()

public:

	UPROPERTY()
		FString Message;

};

USTRUCT()
struct FCHAT_INFO
{
	GENERATED_BODY()

public:

	UPROPERTY()
		FString Name;

	UPROPERTY()
		FString Date;

	UPROPERTY()
		FString Message;

	void InitInfo(FString InName, FString InDate, FString InMessage)
	{
		Name = InName;
		Date = InDate;
		Message = InMessage;
	}
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_AcceptChatList : public UKBEventData
{
	GENERATED_BODY()

public:

	UPROPERTY()
		TArray<FCHAT_INFO> ChatList;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_UpdateCountDown : public UKBEventData
{
	GENERATED_BODY()

public:

	UPROPERTY()
		uint32 CountDown;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ShowResultList : public UKBEventData
{
	GENERATED_BODY()

public:

	UPROPERTY()
		FString NameOne;

	UPROPERTY()
		uint32 CountOne;

	UPROPERTY()
		FString NameTwo;

	UPROPERTY()
		uint32 CountTwo;

	UPROPERTY()
		FString NameThree;

	UPROPERTY()
		uint32 CountThree;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqTeleportRoom : public UKBEventData
{
	GENERATED_BODY()

public:

	UPROPERTY()
		uint64 DesRoomId;

};



// for meta mmo game new
// ----------------  req --------------------------------------------
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_reqAvatarList : public UKBEventData
{
	GENERATED_BODY()

public:

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_reqCreateAvatar : public UKBEventData
{
	GENERATED_BODY()

public:

	UPROPERTY()
	uint8 RoleType;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	TArray<uint8> Facade;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_reqEnterGame : public UKBEventData
{
	GENERATED_BODY()

public:

	UPROPERTY()
	uint64 DatabaseID;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_reqRemoveAvatar : public UKBEventData
{
	GENERATED_BODY()

public:

	UPROPERTY()
	uint64 dbid;

};

// ----------------  rsp --------------------------------------------
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_rspCreateAvatar : public UKBEventData {
	GENERATED_BODY()

public:

	uint32 ErrorCode;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_rspRemoveAvatar : public UKBEventData {
	GENERATED_BODY()

public:

	uint32 ErrorCode;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_rspEnterGame : public UKBEventData {
	GENERATED_BODY()

public:

		uint32 ErrorCode;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_rspAvatarList : public UKBEventData {
	GENERATED_BODY()

public:

	KBEngine::AVATAR_BRIEF_INFO_LIST AvatarList;

	uint64 dbid;

};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_rspSwitchAvatar : public UKBEventData {
	GENERATED_BODY()

public:

	uint32 ErrorCode;
};

/**
 * 
 */
UCLASS()
class KBENGINEPLUGINS_API UExEventData : public UObject
{
	GENERATED_BODY()
	
};
