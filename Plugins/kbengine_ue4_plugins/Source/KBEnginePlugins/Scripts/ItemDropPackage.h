#pragma once
#include "Engine/ItemDropPackageBase.h"

namespace KBEngine
{
	class ItemDropPackage : public ItemDropPackageBase
	{
	public:
		ItemDropPackage();
		virtual ~ItemDropPackage();

		virtual void __init__() override;
		virtual void onDestroy() override;

	};
}
