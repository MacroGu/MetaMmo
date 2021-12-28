#pragma once
#include "Engine/OreBase.h"

namespace KBEngine
{
	class Ore : public OreBase
	{
	public:
		Ore();
		virtual ~Ore();

		virtual void __init__() override;
		virtual void onDestroy() override;

	};
}
