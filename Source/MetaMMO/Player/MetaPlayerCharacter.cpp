﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MetaPlayerCharacter.h"
#include "MetaMmoController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/Matrix.h"
#include "Engine/KBEngine.h"
#include "Scripts/ExEventData.h"
#include "TimerManager.h"
#include "UObject/NoExportTypes.h"
#include "Math/RotationMatrix.h"
#include "Scripts/ExCommon.h"
#include "HUD/MetaMmoWidget.h"



AMetaPlayerCharacter::AMetaPlayerCharacter()
{
	TurnRate = 30.f;
	LookUpRate = 3.f;

	// 跟随控制器移动旋转的设置
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.f;		// The Camera follows at this distance behind the character 
	CameraBoom->bUsePawnControlRotation = true;	// Rotate the arm based on the controller
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 120.f));
	// 取消手臂遮挡
	CameraBoom->bDoCollisionTest = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);	// Attach the camera to the end of the boom and let the boom adjust to match the controller roientation
	FollowCamera->bUsePawnControlRotation = false;

	// 技能射出点
	SkillPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SkillPoint"));
	SkillPoint->SetupAttachment(RootComponent);

}

void AMetaPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMetaPlayerCharacter::DoJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMetaPlayerCharacter::DoStopJump);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMetaPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMetaPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AMetaPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMetaPlayerCharacter::LookUp);

	PlayerInputComponent->BindAction("OperateBag", IE_Pressed, this, &AMetaPlayerCharacter::OperateBag);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMetaPlayerCharacter::RequestAttack);

	PlayerInputComponent->BindAction("ScrollUp", IE_Pressed, this, &AMetaPlayerCharacter::ScrollUp);
	PlayerInputComponent->BindAction("ScrollDown", IE_Pressed, this, &AMetaPlayerCharacter::ScrollDown);

	PlayerInputComponent->BindAction("BuffOne", IE_Pressed, this, &AMetaPlayerCharacter::BuffOne);
	PlayerInputComponent->BindAction("BuffTwo", IE_Pressed, this, &AMetaPlayerCharacter::BuffTwo);
	PlayerInputComponent->BindAction("BuffThree", IE_Pressed, this, &AMetaPlayerCharacter::BuffThree);

}

void AMetaPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// 同步位置到公共类
	UExCommon::Get()->SetPlayerPos(GetActorLocation());
	UExCommon::Get()->SetCameraPos(FollowCamera->GetComponentLocation());

	// 获取动作蓝图参数
	AnimSpeed = GetVelocity().Size();
	AnimIsInAir = GetMovementComponent()->IsFalling();

	// 获取移动角度
	float PreDir = GetVelocity().ToOrientationRotator().Yaw - GetActorRotation().Yaw;

	if (PreDir > 180.f)
	{
		PreDir -= 360.f;
	}
	if (PreDir < -180.f)
	{
		PreDir += 360.f;
	}

	// 速度太小， 移动角度为0
	if (AnimSpeed < 5.f)
	{
		AnimDirection = 0.f;
	}
	else
	{
		AnimDirection = PreDir;
	}

}

void AMetaPlayerCharacter::Destroyed()
{
	Super::Destroy();

	// 停止定时器
	GetWorld()->GetTimerManager().ClearTimer(AnimUpdateHandle);

}

void AMetaPlayerCharacter::SetBaseHP(int32 InBaseHP)
{
	if (InBaseHP < BaseHP)
	{
		// 判断是否当前血值比新的血值小
		if (HP < InBaseHP)
		{
			HP = InBaseHP;
		}
	}
	BaseHP = InBaseHP;
}

void AMetaPlayerCharacter::SetHP(int32 InHP)
{
	// 如果新的HP 为0， 旧的HP 不为0， 说明死亡
	if (InHP == 0 && HP > 0)
	{
		// 切换输入模式UI
		MmoController->SwitchInputMode(true);
	}

	// 如果旧的HP 为0， 新的HP 大于0， 说明复活
	if (InHP > 0 && HP == 0)
	{
		// 切换输入模式为 Game
		MmoController->SwitchInputMode(false);
	}

	// 新的HP 不为0， 并且比旧的HP 小， 并且两者不相等  说明受伤
	if (InHP > 0 && InHP < HP && InHP != BaseHP)
	{
		// 播放受伤动画
		float ret = CharacterAnim->Montage_Play(HurtMontage);

		DDH::Debug() << "guhong SetHP --> " << ret << DDH::Endl();

	}

	// 保存HP
	HP = InHP;

}

void AMetaPlayerCharacter::SetSpeedRatio(float InSpeedRatio)
{
	// 修改速度
	GetCharacterMovement()->MaxWalkSpeed = 600 * InSpeedRatio;
}

void AMetaPlayerCharacter::Attack(uint8 SkillId)
{
	if (HP <= 0)
	{
		return;
	}

	// 如果正在跳跃，返回
	if (AnimIsInAir)
	{
		return;
	}

	if (MmoController)
	{
		FVector2D ScreenSize = GEngine->GameViewport->Viewport->GetSizeXY();

		// 获取射线起点和方向
		FVector RayStartPos;
		FVector RayDirection;
		MmoController->DeprojectScreenPositionToWorld(ScreenSize.X * 0.5f, ScreenSize.Y * 0.5f, RayStartPos, RayDirection);

		// 进行射线检测
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.bReturnPhysicalMaterial = false;
		TraceParams.bTraceComplex = true;

		FVector TargetPos;

		// 进行射线检测
		FHitResult HitResult(ForceInit);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, RayStartPos, RayStartPos + RayDirection * 1000.f, ECollisionChannel::ECC_GameTraceChannel1, TraceParams))
		{
			TargetPos = HitResult.Location;
		}
		else
		{
			TargetPos = RayStartPos + RayDirection * 5000.f;
		}

		// 向服务器请求发射技能
		UKBEventData_Attack* EventData = NewObject<UKBEventData_Attack>();
		EventData->SkillId = SkillId;
		EventData->SpawnPos = SkillPoint->GetComponentLocation();
		EventData->TargetPos = TargetPos;
		KBENGINE_EVENT_FIRE("Attack", EventData);
	}

}

void AMetaPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 默认不显示背包
	IsShowBag = false;

	// 修改输入模式
	MmoController->SwitchInputMode(false);

	// 启动更新动作定时器
	GetWorld()->GetTimerManager().SetTimer(AnimUpdateHandle, this, &AMetaPlayerCharacter::AnimUpdate, 0.5f, true, 0.5f);
}

void AMetaPlayerCharacter::DoJump()
{
	Jump();
}

void AMetaPlayerCharacter::DoStopJump()
{
	StopJumping();
}

void AMetaPlayerCharacter::MoveForward(float Value)
{
	if (Controller != NULL && Value != 0.f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMetaPlayerCharacter::MoveRight(float Value)
{
	if (Controller != NULL && Value != 0.f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMetaPlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value * TurnRate * GetWorld()->GetDeltaSeconds());
}

void AMetaPlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value * LookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMetaPlayerCharacter::AnimUpdate()
{
	UKBEventData_AnimUpdate* EventData = NewObject<UKBEventData_AnimUpdate>();
	EventData->Speed = AnimSpeed;
	EventData->Direction = AnimDirection;
	KBENGINE_EVENT_FIRE("AnimUpdate", EventData);

}

void AMetaPlayerCharacter::OperateBag()
{
	// 如果血值 为0
	if (HP == 0)
	{
		return;
	}

	IsShowBag = !IsShowBag;
	
	if (MmoController)
	{
		MmoController->SwitchInputMode(IsShowBag);
	}

	if (MmoWidget)
	{
		MmoWidget->OpenOrCloseBag(IsShowBag);
	}

}

void AMetaPlayerCharacter::RequestAttack()
{
	// 如果正在显示背包或者已经死亡， 不处理
	if (IsShowBag || HP == 0)
		return;

	// 如果当前被选中的技能框不存在，直接返回
	if (!UMetaDataMgr::Get()->IsGoodExist(EBagType::SkillBag, UMetaDataMgr::Get()->CurrentOnSkill))
		return;

	// 请求服务器使用（减少）物品
	UKBEventData_ReduceGood* EventData = NewObject<UKBEventData_ReduceGood>();
	EventData->BagType = (uint8)EBagType::SkillBag;
	// 这里的 CurrentOnSkill就是对于技能背包的BlockId
	EventData->BlockId = UMetaDataMgr::Get()->CurrentOnSkill;
	KBENGINE_EVENT_FIRE("ReduceGood", EventData);

}

void AMetaPlayerCharacter::ScrollUp()
{
	// 修改数据
	if (UMetaDataMgr::Get()->CurrentOnSkill == 0)
	{
		UMetaDataMgr::Get()->CurrentOnSkill = 2;
	}
	else
	{
		UMetaDataMgr::Get()->CurrentOnSkill -= 1;
	}

	// 通知UI 更新
	if (MmoWidget)
	{
		MmoWidget->UpdateSkillOn();
	}
}

void AMetaPlayerCharacter::ScrollDown()
{
	// 修改数据
	if (UMetaDataMgr::Get()->CurrentOnSkill == 2)
	{
		UMetaDataMgr::Get()->CurrentOnSkill = 0;
	}
	else
	{
		UMetaDataMgr::Get()->CurrentOnSkill += 1;
	}

	// 通知UI 更新
	if (MmoWidget)
	{
		MmoWidget->UpdateSkillOn();
	}
}

void AMetaPlayerCharacter::BuffOne()
{
	RequestBuff(0);
}

void AMetaPlayerCharacter::BuffTwo()
{
	RequestBuff(1);
}

void AMetaPlayerCharacter::BuffThree()
{
	RequestBuff(2);
}

void AMetaPlayerCharacter::RequestBuff(uint8 BlockId)
{
	// 先判断是否有物品
	if (!UMetaDataMgr::Get()->IsGoodExist(EBagType::BuffBag, BlockId))
	{
		return;
	}

	// 先告诉服务器减少物品
	UKBEventData_ReduceGood* EventData = NewObject<UKBEventData_ReduceGood>();
	EventData->BagType = (uint8)EBagType::BuffBag;
	EventData->BlockId = BlockId;
	KBENGINE_EVENT_FIRE("ReduceGood", EventData);
}
