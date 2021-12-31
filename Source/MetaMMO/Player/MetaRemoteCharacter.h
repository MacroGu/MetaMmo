// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MetaCharacterEntity.h"
#include "MetaRemoteCharacter.generated.h"


class UBoxComponent;
class UWidgetComponent;
class UMetaBloodBar;

/**
 * 
 */
UCLASS()
class METAMMO_API AMetaRemoteCharacter : public AMetaCharacterEntity
{
	GENERATED_BODY()
	
public:

	AMetaRemoteCharacter();

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetBaseHP(int32 InBaseHP) override;

	virtual void SetHP(int32 InHP) override;

public:

	// �ж��Ƿ��ŵ���ײ��
	UPROPERTY(EditAnywhere)
		UBoxComponent* GroundBox;

	UPROPERTY(EditAnywhere)
		UWidgetComponent* BloodBarComponent;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverLapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	UMetaBloodBar* BloodBar;

	static FName GroundName;

};
