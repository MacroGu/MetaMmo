// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MetaKBEClient.generated.h"

class UKBEMain;


UCLASS()
class METAMMO_API AMetaKBEClient : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMetaKBEClient();

public:

	UPROPERTY(EditAnywhere)
	UKBEMain* KBEMain;


};
