#pragma once
#include "Engine/KBECommon.h"
#include "Engine/ExSkillBase.h"

namespace KBEngine
{
	class ExSkill : public ExSkillBase
	{
	public:
		ExSkill();
		virtual ~ExSkill();

		virtual void __init__() override;
		virtual void onDestroy() override;

	};
}
