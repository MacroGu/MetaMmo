// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MetaActorEntity.generated.h"

class AMetaMmoGameMode;

UCLASS()
class METAMMO_API AMetaActorEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMetaActorEntity();

	virtual void Tick(float DeltaSeconds) override;

	void SetTargetPosition(FVector InPos);

public:

	int32 EntityId;

	AMetaMmoGameMode* MmoGameMode;

protected:

	virtual void BeginPlay() override;

protected:

	// 将要移动到的位置
	FVector TargetPosition;

	// 上一次时间
	float LastUpdatePositionTIme;

	float MoveSpeed;


};
