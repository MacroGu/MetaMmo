// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MetaRoomWidget.generated.h"


class AMetaRoomGameMode;
class UScrollBox;
class UEditableTextBox;
class UMetaRoomItem;
struct FROOM_INFO;


/**
 * 
 */
UCLASS()
class METAMMO_API UMetaRoomWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	AMetaRoomGameMode* RoomGameMode;

	UPROPERTY(Meta = (BindWidget))
		UScrollBox* RoomListScroll;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* RoomNameTextBox;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UMetaRoomItem> RoomItemClass;

	UPROPERTY()
		TArray<UMetaRoomItem*> RoomItemGroup;

public:

	void OnReqRoomList(TArray<FROOM_INFO> RoomList);

	void OnCreateRoom(FROOM_INFO RoomInfo);


	UFUNCTION(BlueprintCallable)
		void RefreshEvent();

	UFUNCTION(BlueprintCallable)
		void CreateRoomEvent();

	UFUNCTION(BlueprintCallable)
		void EnterGameEvent();

protected:

	void RoomItemSelect(uint64 RoomId);

};
