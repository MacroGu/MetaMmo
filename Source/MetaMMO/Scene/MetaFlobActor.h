// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/MetaActorEntity.h"
#include "MetaFlobActor.generated.h"

class UStaticMeshComponent;
class UTexture;
class UMaterialInterface;
class UMaterialInstanceDynamic;


/**
 * 
 */
UCLASS()
class METAMMO_API AMetaFlobActor : public AMetaActorEntity
{
	GENERATED_BODY()

public:

	AMetaFlobActor();

	virtual void Tick(float DeltaSeconds) override;

	virtual void Destroyed() override;
	
public:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* BaseMat;

	UPROPERTY()
		UMaterialInstanceDynamic* BaseMatInst;

	uint8 GoodId;

protected:

	virtual void BeginPlay() override;

};
