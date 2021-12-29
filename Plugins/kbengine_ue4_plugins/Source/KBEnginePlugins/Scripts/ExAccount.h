#pragma once
#include "Engine/KBECommon.h"
#include "Engine/ExAccountBase.h"

namespace KBEngine
{
	class ExAccount : public ExAccountBase
	{
	public:
		ExAccount();
		virtual ~ExAccount();

		virtual void __init__() override;
		virtual void onDestroy() override;

		virtual void OnCreateRole(uint8 arg1, const ROLE_INFO& arg2) override;
		virtual void OnCreateRoom(uint8 arg1, const ROOM_INFO& arg2) override;
		virtual void OnRemoveRole(uint64 arg1) override;
		virtual void OnReqRoleList(const ROLE_LIST& arg1) override;
		virtual void OnReqRoomList(const ROOM_LIST& arg1) override;
		virtual void OnSelectRoleGame(uint8 arg1, uint64 arg2) override;

	public:

		// 保存角色列表到本地
		ROLE_LIST RoleList;

	};
}
