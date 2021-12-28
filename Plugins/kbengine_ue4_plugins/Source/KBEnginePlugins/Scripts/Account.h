#pragma once
#include "Engine/KBECommon.h"
#include "Engine/AccountBase.h"

namespace KBEngine
{
	class Account : public AccountBase
	{
	public:
		Account();
		virtual ~Account();

		virtual void __init__() override;
		virtual void onDestroy() override;

		virtual void rspAvatarList(const AVATAR_BRIEF_INFO_LIST& arg1, uint64 arg2) override;
		virtual void rspCreateAvatar(uint32 arg1) override;
		virtual void rspEnterGame(uint32 arg1) override;
		virtual void rspRemoveAvatar(uint32 arg1) override;
		virtual void rspSwitchAvatar(uint32 arg1) override;

	};
}
