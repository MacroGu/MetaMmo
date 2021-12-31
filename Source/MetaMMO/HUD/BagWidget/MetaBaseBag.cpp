// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BagWidget/MetaBaseBag.h"
#include "MetaBagBlock.h"

void UExBaseBag::UpdateBlock(uint8 BlockId)
{
	BlockGroup[BlockId]->UpdateBlock();
}
