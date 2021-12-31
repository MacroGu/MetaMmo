// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BagWidget/MetaSkillBag.h"
#include "TextBlock.h"
#include "Data/MetaDataMgr.h"


void UMetaSkillBag::UpdateSkillOn()
{
	for (int i = 0; i < OnTextGroup.Num(); ++i)
	{
		if (i == UMetaDataMgr::Get()->CurrentOnSkill)
		{
			OnTextGroup[i]->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			OnTextGroup[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
