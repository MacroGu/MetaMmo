#pragma once
#include "Engine/KBECommon.h"
#include "Engine/ExRoleBase.h"

namespace KBEngine
{
	class ExRole : public ExRoleBase
	{
	public:
		ExRole();
		virtual ~ExRole();

		virtual void __init__() override;
		virtual void onDestroy() override;

		virtual void OnAnimUpdate(const ANIM_INFO& arg1) override;

		virtual void onBaseHPChanged(int32 oldValue) override;

		virtual void onHPChanged(int32 oldValue) override;

		virtual void onDefenseChanged(int32 oldValue) override;

		virtual void onPowerRatioChanged(float oldValue) override;

		virtual void onSpeedRatioChanged(float oldValue) override;

		virtual void OnAttack() override;

		virtual void OnIncreaseGood(uint8 arg1, const GOOD_INFO& arg2) override;

		virtual void OnPassGood(uint8 arg1, const GOOD_INFO& arg2, uint8 arg3, const GOOD_INFO& arg4) override;

		virtual void OnReduceGood(uint8 arg1, uint8 arg2, const GOOD_INFO& arg3) override;

		virtual void OnReqBagList(const BAG_INFO& arg1, const BAG_INFO& arg2, const BAG_INFO& arg3, const BAG_INFO& arg4) override;

		virtual void AcceptChatList(const CHAT_LIST& arg1) override;

		virtual void UpdateCountDown(uint32 arg1) override;

		virtual void ShowResultList(const FString& arg1, uint32 arg2, const FString& arg3, uint32 arg4, const FString& arg5, uint32 arg6) override;

	};
}
