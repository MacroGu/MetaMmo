#pragma once
#include "Engine/AvatarBase.h"

namespace KBEngine
{
	class Avatar : public AvatarBase
	{
	public:
		Avatar();
		virtual ~Avatar();

		virtual void __init__() override;
		virtual void onDestroy() override;


		virtual void OnAnimUpdate(const ANIM_INFO& arg1) override;
		virtual void OnAttack(const SKILL_INFO& arg1) override;
		virtual void ntfError(uint32 arg1) override;
		virtual void ntfItemsChange(const ITEM_LIST& arg1, const UINT16_LIST& arg2) override;
		virtual void ntfReceiveChat(const CHAT_INFO& arg1) override;
		virtual void rspChangeName(uint32 arg1) override;
		virtual void rspDigOre() override;
		virtual void rspStopDigOre() override;
		virtual void rspSwitchAvatar(uint32 arg1) override;

	};
}
