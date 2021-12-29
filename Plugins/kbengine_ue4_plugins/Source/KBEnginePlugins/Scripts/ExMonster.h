#pragma once
#include "Engine/KBECommon.h"
#include "Engine/ExMonsterBase.h"

namespace KBEngine
{
	class ExMonster : public ExMonsterBase
	{
	public:
		ExMonster();
		virtual ~ExMonster();

		virtual void __init__() override;
		virtual void onDestroy() override;

		virtual void OnAnimUpdate(const ANIM_INFO& arg1) override;

		virtual void onBaseHPChanged(int32 oldValue) override;

		virtual void onHPChanged(int32 oldValue) override;

		virtual void OnAttack() override;

	};
}
