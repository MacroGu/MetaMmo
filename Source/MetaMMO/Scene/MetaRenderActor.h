// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MetaRenderActor.generated.h"

// 用来在场景里渲染RenderTexture 给界面使用
UCLASS()
class METAMMO_API AUMetaRenderActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUMetaRenderActor();


	UFUNCTION(BlueprintImplementableEvent)
		void SwitchRoleMesh(uint8 RoleType);



};
