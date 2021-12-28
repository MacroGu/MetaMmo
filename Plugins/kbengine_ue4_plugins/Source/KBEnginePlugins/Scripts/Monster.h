#pragma once
#include "Engine/MonsterBase.h"

namespace KBEngine
{
	class Monster : public MonsterBase
	{
	public:
		Monster();
		virtual ~Monster();

		virtual void __init__() override;
		virtual void onDestroy() override;


		virtual void OnAnimUpdate(const ANIM_INFO& arg1) override;
		virtual void OnAttack(const SKILL_INFO& arg1) override;

	};
}
