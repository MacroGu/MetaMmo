// Fill out your copyright notice in the Description page of Project Settings.


#include "Center/MetaKBEClient.h"
#include "Engine/KBEMain.h"


// Sets default values
AMetaKBEClient::AMetaKBEClient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));

	KBEMain = CreateDefaultSubobject<UKBEMain>(TEXT("KBEMain"));

}


