#include "MonsterBase.h"
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



void MonsterBase::onComponentsEnterworld()
{
}

void MonsterBase::onComponentsLeaveworld()
{
}

void MonsterBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_MonsterBase(id(), className());
}

void MonsterBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_MonsterBase(id(), className());
}

void MonsterBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* MonsterBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* MonsterBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void MonsterBase::onRemoteMethodCall(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("Monster");
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
		case 48:
		{
			ANIM_INFO OnAnimUpdate_arg1;
			((DATATYPE_ANIM_INFO*)pMethod->args[0])->createFromStreamEx(stream, OnAnimUpdate_arg1);
			OnAnimUpdate(OnAnimUpdate_arg1);
			break;
		}
		case 46:
		{
			SKILL_INFO OnAttack_arg1;
			((DATATYPE_SKILL_INFO*)pMethod->args[0])->createFromStreamEx(stream, OnAttack_arg1);
			OnAttack(OnAttack_arg1);
			break;
		}
		default:
			break;
	};
}

void MonsterBase::onUpdatePropertys(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("Monster");

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
			case 42:
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
			case 43:
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
			case 39:
			{
				uint32 oldval_MonsterID = MonsterID;
				MonsterID = stream.readUint32();

				if(pProp->isBase())
				{
					if(inited())
						onMonsterIDChanged(oldval_MonsterID);
				}
				else
				{
					if(inWorld())
						onMonsterIDChanged(oldval_MonsterID);
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
			case 41:
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

void MonsterBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs["Monster"];
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

	uint32 oldval_MonsterID = MonsterID;
	Property* pProp_MonsterID = pdatas[6];
	if(pProp_MonsterID->isBase())
	{
		if(inited() && !inWorld())
			onMonsterIDChanged(oldval_MonsterID);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_MonsterID->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onMonsterIDChanged(oldval_MonsterID);
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
	Property* pProp_enage = pdatas[7];
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

}

MonsterBase::MonsterBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL),
	BaseHP((int32)FCString::Atoi64(TEXT("500"))),
	HP((int32)FCString::Atoi64(TEXT("500"))),
	MonsterID((uint32)FCString::Atoi64(TEXT("0"))),
	enage((int32)FCString::Atoi64(TEXT("-1")))
{
}

MonsterBase::~MonsterBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;

}

void MonsterBase::attachComponents()
{
}

void MonsterBase::detachComponents()
{
}

}