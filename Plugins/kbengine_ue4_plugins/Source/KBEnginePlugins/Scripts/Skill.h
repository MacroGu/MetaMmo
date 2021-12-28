#pragma once
#include "Engine/SkillBase.h"

namespace KBEngine
{
	class Skill : public SkillBase
	{
	public:
		Skill();
		virtual ~Skill();

		virtual void __init__() override;
		virtual void onDestroy() override;


	};
}
