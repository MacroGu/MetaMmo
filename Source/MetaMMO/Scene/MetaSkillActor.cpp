// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/MetaSkillActor.h"
#include "Center/MetaMmoGameMode.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/World.h"
#include "Components/AudioComponent.h"



AMetaSkillActor::AMetaSkillActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));

	// 实例化开火粒子特效组件
	SkillParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SkillParticleComponent"));
	SkillParticleComponent->SetupAttachment(RootComponent);

	ShootAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ShootAudio"));
	ShootAudio->SetupAttachment(RootComponent);

	ExplodeAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ExplodeAudio"));
	ExplodeAudio->SetupAttachment(RootComponent);

}

void AMetaSkillActor::Destroyed()
{
	Super::Destroyed();

	if (MmoGameMode)
	{
		MmoGameMode->SkillMap.Remove(EntityId);
	}

}

void AMetaSkillActor::PlayExplode()
{
	// 播放爆炸特效
	SkillParticleComponent->SetTemplate(ExplodeParticle);

	// 播放爆炸音效
	ExplodeAudio->Play();

	// 延时 1.5 秒销毁
	GetWorld()->GetTimerManager().SetTimer(DestroyHandle, this, &AMetaSkillActor::DestroySkill, 1.5f);

}

void AMetaSkillActor::BeginPlay()
{
	Super::BeginPlay();

	if (MmoGameMode)
	{
		MmoGameMode->SkillMap.Add(EntityId, this);
	}

	// 一开始就播放技能特效
	SkillParticleComponent->SetTemplate(SkillParticle);

	// 播放声音
	ShootAudio->Play();

}

void AMetaSkillActor::DestroySkill()
{
	Destroy();
}
