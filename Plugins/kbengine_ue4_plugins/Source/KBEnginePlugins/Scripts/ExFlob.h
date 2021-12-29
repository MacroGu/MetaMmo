#pragma once
#include "Engine/KBECommon.h"
#include "Engine/ExFlobBase.h"

namespace KBEngine
{
	class ExFlob : public ExFlobBase
	{
	public:
		ExFlob();
		virtual ~ExFlob();

		virtual void __init__() override;
		virtual void onDestroy() override;

	};
}
