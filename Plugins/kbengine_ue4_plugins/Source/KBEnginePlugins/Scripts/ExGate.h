#pragma once
#include "Engine/KBECommon.h"
#include "Engine/ExGateBase.h"


namespace KBEngine
{
	class ExGate : public ExGateBase
	{
	public:
		ExGate();
		virtual ~ExGate();

		virtual void __init__() override;
		virtual void onDestroy() override;

	};
}
