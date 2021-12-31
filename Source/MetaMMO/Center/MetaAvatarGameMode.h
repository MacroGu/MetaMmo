// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Center/MetaKbeGameMode.h"
#include "MetaAvatarGameMode.generated.h"

class UMetaAvatarWidget;
class AUMetaRenderActor;

/**
 * 
 */
UCLASS()
class METAMMO_API AMetaAvatarGameMode : public AMetaKbeGameMode
{
	GENERATED_BODY()
	

public:
	virtual void InstallEvent() override;


public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UMetaAvatarWidget> RoleWidgetClass;

	UMetaAvatarWidget* RoleWidget;

	AUMetaRenderActor* RenderActor;


protected:

	virtual void BeginPlay() override;

	void OnReqRoleList(const UKBEventData* EventData);

	void OnCreateRole(const UKBEventData* EventData);

	void OnRemoveRole(const UKBEventData* EventData);

	void OnSelectRoleGame(const UKBEventData* EventData);


};
