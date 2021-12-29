#include "AvatarBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"
#include "EntityComponent.h"

namespace KBEngine
{



void AvatarBase::onComponentsEnterworld()
{
}

void AvatarBase::onComponentsLeaveworld()
{
}

void AvatarBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_AvatarBase(id(), className());
}

void AvatarBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_AvatarBase(id(), className());
}

void AvatarBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* AvatarBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* AvatarBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void AvatarBase::onRemoteMethodCall(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("Avatar");
	uint16 methodUtype = 0;
	uint16 componentPropertyUType = 0;

	if (sm->usePropertyDescrAlias)
	{
		componentPropertyUType = stream.readUint8();
	}
	else
	{
		componentPropertyUType = stream.readUint16();
	}

	if (sm->useMethodDescrAlias)
	{
		methodUtype = stream.read<uint8>();
	}
	else
	{
		methodUtype = stream.read<uint16>();
	}

	if(componentPropertyUType > 0)
	{
		KBE_ASSERT(false);

		return;
	}

	Method* pMethod = sm->idmethods[methodUtype];

	switch(pMethod->methodUtype)
	{
		case 36:
		{
			ANIM_INFO OnAnimUpdate_arg1;
			((DATATYPE_ANIM_INFO*)pMethod->args[0])->createFromStreamEx(stream, OnAnimUpdate_arg1);
			OnAnimUpdate(OnAnimUpdate_arg1);
			break;
		}
		case 34:
		{
			SKILL_INFO OnAttack_arg1;
			((DATATYPE_SKILL_INFO*)pMethod->args[0])->createFromStreamEx(stream, OnAttack_arg1);
			OnAttack(OnAttack_arg1);
			break;
		}
		case 17:
		{
			uint32 ntfError_arg1 = stream.readUint32();
			ntfError(ntfError_arg1);
			break;
		}
		case 22:
		{
			ITEM_LIST ntfItemsChange_arg1;
			((DATATYPE_ITEM_LIST*)pMethod->args[0])->createFromStreamEx(stream, ntfItemsChange_arg1);
			UINT16_LIST ntfItemsChange_arg2;
			((DATATYPE_UINT16_LIST*)pMethod->args[1])->createFromStreamEx(stream, ntfItemsChange_arg2);
			ntfItemsChange(ntfItemsChange_arg1, ntfItemsChange_arg2);
			break;
		}
		case 29:
		{
			CHAT_INFO ntfReceiveChat_arg1;
			((DATATYPE_CHAT_INFO*)pMethod->args[0])->createFromStreamEx(stream, ntfReceiveChat_arg1);
			ntfReceiveChat(ntfReceiveChat_arg1);
			break;
		}
		case 18:
		{
			uint32 rspChangeName_arg1 = stream.readUint32();
			rspChangeName(rspChangeName_arg1);
			break;
		}
		case 40:
		{
			rspDigOre();
			break;
		}
		case 41:
		{
			rspStopDigOre();
			break;
		}
		case 19:
		{
			uint32 rspSwitchAvatar_arg1 = stream.readUint32();
			rspSwitchAvatar(rspSwitchAvatar_arg1);
			break;
		}
		default:
			break;
	};
}

void AvatarBase::onUpdatePropertys(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("Avatar");

	while(stream.length() > 0)
	{
		uint16 componentPropertyUType = 0;
		uint16 properUtype = 0;

		if (sm->usePropertyDescrAlias)
		{
			componentPropertyUType = stream.readUint8();
			properUtype = stream.read<uint8>();
		}
		else
		{
			componentPropertyUType = stream.readUint16();
			properUtype = stream.read<uint16>();
		}

		if(componentPropertyUType > 0)
		{
			KBE_ASSERT(false);

			return;
		}

		Property* pProp = sm->idpropertys[properUtype];

		switch(pProp->properUtype)
		{
			case 28:
			{
				int32 oldval_BaseHP = BaseHP;
				BaseHP = stream.readInt32();

				if(pProp->isBase())
				{
					if(inited())
						onBaseHPChanged(oldval_BaseHP);
				}
				else
				{
					if(inWorld())
						onBaseHPChanged(oldval_BaseHP);
				}

				break;
			}
			case 29:
			{
				int32 oldval_HP = HP;
				HP = stream.readInt32();

				if(pProp->isBase())
				{
					if(inited())
						onHPChanged(oldval_HP);
				}
				else
				{
					if(inWorld())
						onHPChanged(oldval_HP);
				}

				break;
			}
			case 21:
			{
				uint16 oldval_bagSize = bagSize;
				bagSize = stream.readUint16();

				if(pProp->isBase())
				{
					if(inited())
						onBagSizeChanged(oldval_bagSize);
				}
				else
				{
					if(inWorld())
						onBagSizeChanged(oldval_bagSize);
				}

				break;
			}
			case 8:
			{
				uint64 oldval_dbid = dbid;
				dbid = stream.readUint64();

				if(pProp->isBase())
				{
					if(inited())
						onDbidChanged(oldval_dbid);
				}
				else
				{
					if(inWorld())
						onDbidChanged(oldval_dbid);
				}

				break;
			}
			case 40001:
			{
				FVector oldval_direction = direction;
				direction = stream.readVector3();

				if(pProp->isBase())
				{
					if(inited())
						onDirectionChanged(oldval_direction);
				}
				else
				{
					if(inWorld())
						onDirectionChanged(oldval_direction);
				}

				break;
			}
			case 27:
			{
				int32 oldval_enage = enage;
				enage = stream.readInt32();

				if(pProp->isBase())
				{
					if(inited())
						onEnageChanged(oldval_enage);
				}
				else
				{
					if(inWorld())
						onEnageChanged(oldval_enage);
				}

				break;
			}
			case 19:
			{
				TArray<uint8> oldval_facade = facade;
				facade = stream.readBlob();

				if(pProp->isBase())
				{
					if(inited())
						onFacadeChanged(oldval_facade);
				}
				else
				{
					if(inWorld())
						onFacadeChanged(oldval_facade);
				}

				break;
			}
			case 22:
			{
				int8 oldval_isJump = isJump;
				isJump = stream.readInt8();

				if(pProp->isBase())
				{
					if(inited())
						onIsJumpChanged(oldval_isJump);
				}
				else
				{
					if(inWorld())
						onIsJumpChanged(oldval_isJump);
				}

				break;
			}
			case 24:
			{
				int8 oldval_moveH = moveH;
				moveH = stream.readInt8();

				if(pProp->isBase())
				{
					if(inited())
						onMoveHChanged(oldval_moveH);
				}
				else
				{
					if(inWorld())
						onMoveHChanged(oldval_moveH);
				}

				break;
			}
			case 23:
			{
				int8 oldval_moveLevel = moveLevel;
				moveLevel = stream.readInt8();

				if(pProp->isBase())
				{
					if(inited())
						onMoveLevelChanged(oldval_moveLevel);
				}
				else
				{
					if(inWorld())
						onMoveLevelChanged(oldval_moveLevel);
				}

				break;
			}
			case 25:
			{
				int8 oldval_moveV = moveV;
				moveV = stream.readInt8();

				if(pProp->isBase())
				{
					if(inited())
						onMoveVChanged(oldval_moveV);
				}
				else
				{
					if(inWorld())
						onMoveVChanged(oldval_moveV);
				}

				break;
			}
			case 18:
			{
				FString oldval_name = name;
				name = stream.readUnicode();

				if(pProp->isBase())
				{
					if(inited())
						onNameChanged(oldval_name);
				}
				else
				{
					if(inWorld())
						onNameChanged(oldval_name);
				}

				break;
			}
			case 16:
			{
				uint16 oldval_netDelay = netDelay;
				netDelay = stream.readUint16();

				if(pProp->isBase())
				{
					if(inited())
						onNetDelayChanged(oldval_netDelay);
				}
				else
				{
					if(inWorld())
						onNetDelayChanged(oldval_netDelay);
				}

				break;
			}
			case 40000:
			{
				FVector oldval_position = position;
				position = stream.readVector3();

				if(pProp->isBase())
				{
					if(inited())
						onPositionChanged(oldval_position);
				}
				else
				{
					if(inWorld())
						onPositionChanged(oldval_position);
				}

				break;
			}
			case 10:
			{
				uint32 oldval_serverTime = serverTime;
				serverTime = stream.readUint32();

				if(pProp->isBase())
				{
					if(inited())
						onServerTimeChanged(oldval_serverTime);
				}
				else
				{
					if(inWorld())
						onServerTimeChanged(oldval_serverTime);
				}

				break;
			}
			case 17:
			{
				uint8 oldval_sex = sex;
				sex = stream.readUint8();

				if(pProp->isBase())
				{
					if(inited())
						onSexChanged(oldval_sex);
				}
				else
				{
					if(inWorld())
						onSexChanged(oldval_sex);
				}

				break;
			}
			case 40002:
			{
				stream.readUint32();
				break;
			}
			default:
				break;
		};
	}
}

void AvatarBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs["Avatar"];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

	int32 oldval_BaseHP = BaseHP;
	Property* pProp_BaseHP = pdatas[4];
	if(pProp_BaseHP->isBase())
	{
		if(inited() && !inWorld())
			onBaseHPChanged(oldval_BaseHP);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_BaseHP->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onBaseHPChanged(oldval_BaseHP);
			}
		}
	}

	int32 oldval_HP = HP;
	Property* pProp_HP = pdatas[5];
	if(pProp_HP->isBase())
	{
		if(inited() && !inWorld())
			onHPChanged(oldval_HP);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_HP->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onHPChanged(oldval_HP);
			}
		}
	}

	uint16 oldval_bagSize = bagSize;
	Property* pProp_bagSize = pdatas[6];
	if(pProp_bagSize->isBase())
	{
		if(inited() && !inWorld())
			onBagSizeChanged(oldval_bagSize);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_bagSize->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onBagSizeChanged(oldval_bagSize);
			}
		}
	}

	uint64 oldval_dbid = dbid;
	Property* pProp_dbid = pdatas[7];
	if(pProp_dbid->isBase())
	{
		if(inited() && !inWorld())
			onDbidChanged(oldval_dbid);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_dbid->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onDbidChanged(oldval_dbid);
			}
		}
	}

	FVector oldval_direction = direction;
	Property* pProp_direction = pdatas[2];
	if(pProp_direction->isBase())
	{
		if(inited() && !inWorld())
			onDirectionChanged(oldval_direction);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_direction->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onDirectionChanged(oldval_direction);
			}
		}
	}

	int32 oldval_enage = enage;
	Property* pProp_enage = pdatas[8];
	if(pProp_enage->isBase())
	{
		if(inited() && !inWorld())
			onEnageChanged(oldval_enage);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_enage->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onEnageChanged(oldval_enage);
			}
		}
	}

	TArray<uint8> oldval_facade = facade;
	Property* pProp_facade = pdatas[9];
	if(pProp_facade->isBase())
	{
		if(inited() && !inWorld())
			onFacadeChanged(oldval_facade);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_facade->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onFacadeChanged(oldval_facade);
			}
		}
	}

	int8 oldval_isJump = isJump;
	Property* pProp_isJump = pdatas[10];
	if(pProp_isJump->isBase())
	{
		if(inited() && !inWorld())
			onIsJumpChanged(oldval_isJump);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_isJump->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onIsJumpChanged(oldval_isJump);
			}
		}
	}

	int8 oldval_moveH = moveH;
	Property* pProp_moveH = pdatas[11];
	if(pProp_moveH->isBase())
	{
		if(inited() && !inWorld())
			onMoveHChanged(oldval_moveH);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_moveH->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onMoveHChanged(oldval_moveH);
			}
		}
	}

	int8 oldval_moveLevel = moveLevel;
	Property* pProp_moveLevel = pdatas[12];
	if(pProp_moveLevel->isBase())
	{
		if(inited() && !inWorld())
			onMoveLevelChanged(oldval_moveLevel);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_moveLevel->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onMoveLevelChanged(oldval_moveLevel);
			}
		}
	}

	int8 oldval_moveV = moveV;
	Property* pProp_moveV = pdatas[13];
	if(pProp_moveV->isBase())
	{
		if(inited() && !inWorld())
			onMoveVChanged(oldval_moveV);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_moveV->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onMoveVChanged(oldval_moveV);
			}
		}
	}

	FString oldval_name = name;
	Property* pProp_name = pdatas[14];
	if(pProp_name->isBase())
	{
		if(inited() && !inWorld())
			onNameChanged(oldval_name);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_name->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onNameChanged(oldval_name);
			}
		}
	}

	uint16 oldval_netDelay = netDelay;
	Property* pProp_netDelay = pdatas[15];
	if(pProp_netDelay->isBase())
	{
		if(inited() && !inWorld())
			onNetDelayChanged(oldval_netDelay);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_netDelay->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onNetDelayChanged(oldval_netDelay);
			}
		}
	}

	FVector oldval_position = position;
	Property* pProp_position = pdatas[1];
	if(pProp_position->isBase())
	{
		if(inited() && !inWorld())
			onPositionChanged(oldval_position);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_position->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onPositionChanged(oldval_position);
			}
		}
	}

	uint32 oldval_serverTime = serverTime;
	Property* pProp_serverTime = pdatas[16];
	if(pProp_serverTime->isBase())
	{
		if(inited() && !inWorld())
			onServerTimeChanged(oldval_serverTime);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_serverTime->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onServerTimeChanged(oldval_serverTime);
			}
		}
	}

	uint8 oldval_sex = sex;
	Property* pProp_sex = pdatas[17];
	if(pProp_sex->isBase())
	{
		if(inited() && !inWorld())
			onSexChanged(oldval_sex);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_sex->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onSexChanged(oldval_sex);
			}
		}
	}

}

AvatarBase::AvatarBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL),
	BaseHP((int32)FCString::Atoi64(TEXT("500"))),
	HP((int32)FCString::Atoi64(TEXT("500"))),
	bagSize((uint16)FCString::Atoi64(TEXT("30"))),
	dbid((uint64)FCString::Atoi64(TEXT("0"))),
	enage((int32)FCString::Atoi64(TEXT("-1"))),
	facade(),
	isJump((int8)FCString::Atoi64(TEXT("0"))),
	moveH((int8)FCString::Atoi64(TEXT("0"))),
	moveLevel((int8)FCString::Atoi64(TEXT("0"))),
	moveV((int8)FCString::Atoi64(TEXT("0"))),
	name(TEXT("")),
	netDelay((uint16)FCString::Atoi64(TEXT("0"))),
	serverTime((uint32)FCString::Atoi64(TEXT("0"))),
	sex((uint8)FCString::Atoi64(TEXT("0")))
{
}

AvatarBase::~AvatarBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;

}

void AvatarBase::attachComponents()
{
}

void AvatarBase::detachComponents()
{
}

}