// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MetaCharacterEntity.h"
#include "MetaMonsterCharacter.generated.h"


class UWidgetComponent;
class UMetaBloodBar;
/**
 * 
 */
UCLASS()
class METAMMO_API AMetaMonsterCharacter : public AMetaCharacterEntity
{
	GENERATED_BODY()
	
public:

	AMetaMonsterCharacter();

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetBaseHP(int32 InBaseHP) override;

	virtual void SetHP(int32 InHP) override;

	void PlayDeath();

public:

	UPROPERTY(EditAnywhere)
		UWidgetComponent* BloodBarComponent;

protected:

	virtual void BeginPlay() override;

	void MonsterDestroy();

protected:

	// UPROPERTY()
		UMetaBloodBar* BloodBar;

	FTimerHandle DestroyHandle;

};
