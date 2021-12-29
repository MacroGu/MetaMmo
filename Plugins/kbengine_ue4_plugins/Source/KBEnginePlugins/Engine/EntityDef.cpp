#include "EntityDef.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "KBVar.h"
#include "Entity.h"

#include "Scripts/Account.h"
#include "Scripts/Avatar.h"
#include "Scripts/Skill.h"
#include "Scripts/Monster.h"
#include "Scripts/ItemDropPackage.h"
#include "Scripts/Ore.h"

namespace KBEngine
{

TMap<FString, uint16> EntityDef::datatype2id;
TMap<FString, DATATYPE_BASE*> EntityDef::datatypes;
TMap<uint16, DATATYPE_BASE*> EntityDef::id2datatypes;
TMap<FString, int32> EntityDef::entityclass;
TMap<FString, ScriptModule*> EntityDef::moduledefs;
TMap<uint16, ScriptModule*> EntityDef::idmoduledefs;

bool EntityDef::initialize()
{
	initDataTypes();
	initDefTypes();
	initScriptModules();
	return true;
}

bool EntityDef::reset()
{
	clear();
	return initialize();
}

void EntityDef::clear()
{
	TArray<DATATYPE_BASE*> deleted_datatypes;
	for (auto& item : EntityDef::datatypes)
	{
		int32 idx = deleted_datatypes.Find(item.Value);
		if (idx != INDEX_NONE)
			continue;

		deleted_datatypes.Add(item.Value);
		delete item.Value;
	}

	for (auto& item : EntityDef::moduledefs)
		delete item.Value;

	datatype2id.Empty();
	datatypes.Empty();
	id2datatypes.Empty();
	entityclass.Empty();
	moduledefs.Empty();
	idmoduledefs.Empty();
}

void EntityDef::initDataTypes()
{
	datatypes.Add(TEXT("UINT8"), new DATATYPE_UINT8());
	datatypes.Add(TEXT("UINT16"), new DATATYPE_UINT16());
	datatypes.Add(TEXT("UINT32"), new DATATYPE_UINT32());
	datatypes.Add(TEXT("UINT64"), new DATATYPE_UINT64());

	datatypes.Add(TEXT("INT8"), new DATATYPE_INT8());
	datatypes.Add(TEXT("INT16"), new DATATYPE_INT16());
	datatypes.Add(TEXT("INT32"), new DATATYPE_INT32());
	datatypes.Add(TEXT("INT64"), new DATATYPE_INT64());

	datatypes.Add(TEXT("FLOAT"), new DATATYPE_FLOAT());
	datatypes.Add(TEXT("DOUBLE"), new DATATYPE_DOUBLE());

	datatypes.Add(TEXT("STRING"), new DATATYPE_STRING());
	datatypes.Add(TEXT("VECTOR2"), new DATATYPE_VECTOR2());

	datatypes.Add(TEXT("VECTOR3"), new DATATYPE_VECTOR3());

	datatypes.Add(TEXT("VECTOR4"), new DATATYPE_VECTOR4());
	datatypes.Add(TEXT("PYTHON"), new DATATYPE_PYTHON());

	datatypes.Add(TEXT("UNICODE"), new DATATYPE_UNICODE());
	datatypes.Add(TEXT("ENTITYCALL"), new DATATYPE_ENTITYCALL());

	datatypes.Add(TEXT("BLOB"), new DATATYPE_BLOB());
}

Entity* EntityDef::createEntity(int utype)
{
	Entity* pEntity = NULL;

	switch(utype)
	{
		case 1:
			pEntity = new Account();
			break;
		case 2:
			pEntity = new Avatar();
			break;
		case 3:
			pEntity = new Skill();
			break;
		case 4:
			pEntity = new Monster();
			break;
		case 5:
			pEntity = new ItemDropPackage();
			break;
		case 6:
			pEntity = new Ore();
			break;
		default:
			SCREEN_ERROR_MSG("EntityDef::createEntity() : entity(%d) not found!", utype);
			break;
	};

	return pEntity;
}

void EntityDef::initScriptModules()
{
	ScriptModule* pAccountModule = new ScriptModule("Account", 1);
	EntityDef::moduledefs.Add(TEXT("Account"), pAccountModule);
	EntityDef::idmoduledefs.Add(1, pAccountModule);

	Property* pAccount_position = new Property();
	pAccount_position->name = TEXT("position");
	pAccount_position->properUtype = 40000;
	pAccount_position->properFlags = 4;
	pAccount_position->aliasID = 1;
	KBVar* pAccount_position_defval = new KBVar(FVector());
	pAccount_position->pDefaultVal = pAccount_position_defval;
	pAccountModule->propertys.Add(TEXT("position"), pAccount_position); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_position->aliasID, pAccount_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(position / 40000).");

	Property* pAccount_direction = new Property();
	pAccount_direction->name = TEXT("direction");
	pAccount_direction->properUtype = 40001;
	pAccount_direction->properFlags = 4;
	pAccount_direction->aliasID = 2;
	KBVar* pAccount_direction_defval = new KBVar(FVector());
	pAccount_direction->pDefaultVal = pAccount_direction_defval;
	pAccountModule->propertys.Add(TEXT("direction"), pAccount_direction); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_direction->aliasID, pAccount_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(direction / 40001).");

	Property* pAccount_spaceID = new Property();
	pAccount_spaceID->name = TEXT("spaceID");
	pAccount_spaceID->properUtype = 40002;
	pAccount_spaceID->properFlags = 16;
	pAccount_spaceID->aliasID = 3;
	KBVar* pAccount_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pAccount_spaceID->pDefaultVal = pAccount_spaceID_defval;
	pAccountModule->propertys.Add(TEXT("spaceID"), pAccount_spaceID); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_spaceID->aliasID, pAccount_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(spaceID / 40002).");

	TArray<DATATYPE_BASE*> Account_rspAvatarList_args;
	Account_rspAvatarList_args.Add(EntityDef::id2datatypes[31]);
	Account_rspAvatarList_args.Add(EntityDef::id2datatypes[5]);

	Method* pAccount_rspAvatarList = new Method();
	pAccount_rspAvatarList->name = TEXT("rspAvatarList");
	pAccount_rspAvatarList->methodUtype = 8;
	pAccount_rspAvatarList->aliasID = 1;
	pAccount_rspAvatarList->args = Account_rspAvatarList_args;

	pAccountModule->methods.Add(TEXT("rspAvatarList"), pAccount_rspAvatarList); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_rspAvatarList->aliasID, pAccount_rspAvatarList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(rspAvatarList / 8).");

	TArray<DATATYPE_BASE*> Account_rspCreateAvatar_args;
	Account_rspCreateAvatar_args.Add(EntityDef::id2datatypes[4]);

	Method* pAccount_rspCreateAvatar = new Method();
	pAccount_rspCreateAvatar->name = TEXT("rspCreateAvatar");
	pAccount_rspCreateAvatar->methodUtype = 5;
	pAccount_rspCreateAvatar->aliasID = 2;
	pAccount_rspCreateAvatar->args = Account_rspCreateAvatar_args;

	pAccountModule->methods.Add(TEXT("rspCreateAvatar"), pAccount_rspCreateAvatar); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_rspCreateAvatar->aliasID, pAccount_rspCreateAvatar);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(rspCreateAvatar / 5).");

	TArray<DATATYPE_BASE*> Account_rspEnterGame_args;
	Account_rspEnterGame_args.Add(EntityDef::id2datatypes[4]);

	Method* pAccount_rspEnterGame = new Method();
	pAccount_rspEnterGame->name = TEXT("rspEnterGame");
	pAccount_rspEnterGame->methodUtype = 7;
	pAccount_rspEnterGame->aliasID = 3;
	pAccount_rspEnterGame->args = Account_rspEnterGame_args;

	pAccountModule->methods.Add(TEXT("rspEnterGame"), pAccount_rspEnterGame); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_rspEnterGame->aliasID, pAccount_rspEnterGame);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(rspEnterGame / 7).");

	TArray<DATATYPE_BASE*> Account_rspRemoveAvatar_args;
	Account_rspRemoveAvatar_args.Add(EntityDef::id2datatypes[4]);

	Method* pAccount_rspRemoveAvatar = new Method();
	pAccount_rspRemoveAvatar->name = TEXT("rspRemoveAvatar");
	pAccount_rspRemoveAvatar->methodUtype = 6;
	pAccount_rspRemoveAvatar->aliasID = 4;
	pAccount_rspRemoveAvatar->args = Account_rspRemoveAvatar_args;

	pAccountModule->methods.Add(TEXT("rspRemoveAvatar"), pAccount_rspRemoveAvatar); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_rspRemoveAvatar->aliasID, pAccount_rspRemoveAvatar);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(rspRemoveAvatar / 6).");

	TArray<DATATYPE_BASE*> Account_rspSwitchAvatar_args;
	Account_rspSwitchAvatar_args.Add(EntityDef::id2datatypes[4]);

	Method* pAccount_rspSwitchAvatar = new Method();
	pAccount_rspSwitchAvatar->name = TEXT("rspSwitchAvatar");
	pAccount_rspSwitchAvatar->methodUtype = 9;
	pAccount_rspSwitchAvatar->aliasID = 5;
	pAccount_rspSwitchAvatar->args = Account_rspSwitchAvatar_args;

	pAccountModule->methods.Add(TEXT("rspSwitchAvatar"), pAccount_rspSwitchAvatar); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_rspSwitchAvatar->aliasID, pAccount_rspSwitchAvatar);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(rspSwitchAvatar / 9).");

	TArray<DATATYPE_BASE*> Account_reqAvatarList_args;

	Method* pAccount_reqAvatarList = new Method();
	pAccount_reqAvatarList->name = TEXT("reqAvatarList");
	pAccount_reqAvatarList->methodUtype = 1;
	pAccount_reqAvatarList->aliasID = -1;
	pAccount_reqAvatarList->args = Account_reqAvatarList_args;

	pAccountModule->methods.Add(TEXT("reqAvatarList"), pAccount_reqAvatarList); 
	pAccountModule->base_methods.Add(TEXT("reqAvatarList"), pAccount_reqAvatarList);

	pAccountModule->idbase_methods.Add(pAccount_reqAvatarList->methodUtype, pAccount_reqAvatarList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqAvatarList / 1).");

	TArray<DATATYPE_BASE*> Account_reqCreateAvatar_args;
	Account_reqCreateAvatar_args.Add(EntityDef::id2datatypes[2]);
	Account_reqCreateAvatar_args.Add(EntityDef::id2datatypes[12]);
	Account_reqCreateAvatar_args.Add(EntityDef::id2datatypes[11]);

	Method* pAccount_reqCreateAvatar = new Method();
	pAccount_reqCreateAvatar->name = TEXT("reqCreateAvatar");
	pAccount_reqCreateAvatar->methodUtype = 2;
	pAccount_reqCreateAvatar->aliasID = -1;
	pAccount_reqCreateAvatar->args = Account_reqCreateAvatar_args;

	pAccountModule->methods.Add(TEXT("reqCreateAvatar"), pAccount_reqCreateAvatar); 
	pAccountModule->base_methods.Add(TEXT("reqCreateAvatar"), pAccount_reqCreateAvatar);

	pAccountModule->idbase_methods.Add(pAccount_reqCreateAvatar->methodUtype, pAccount_reqCreateAvatar);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqCreateAvatar / 2).");

	TArray<DATATYPE_BASE*> Account_reqEnterGame_args;
	Account_reqEnterGame_args.Add(EntityDef::id2datatypes[5]);

	Method* pAccount_reqEnterGame = new Method();
	pAccount_reqEnterGame->name = TEXT("reqEnterGame");
	pAccount_reqEnterGame->methodUtype = 3;
	pAccount_reqEnterGame->aliasID = -1;
	pAccount_reqEnterGame->args = Account_reqEnterGame_args;

	pAccountModule->methods.Add(TEXT("reqEnterGame"), pAccount_reqEnterGame); 
	pAccountModule->base_methods.Add(TEXT("reqEnterGame"), pAccount_reqEnterGame);

	pAccountModule->idbase_methods.Add(pAccount_reqEnterGame->methodUtype, pAccount_reqEnterGame);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqEnterGame / 3).");

	TArray<DATATYPE_BASE*> Account_reqRemoveAvatar_args;
	Account_reqRemoveAvatar_args.Add(EntityDef::id2datatypes[5]);

	Method* pAccount_reqRemoveAvatar = new Method();
	pAccount_reqRemoveAvatar->name = TEXT("reqRemoveAvatar");
	pAccount_reqRemoveAvatar->methodUtype = 4;
	pAccount_reqRemoveAvatar->aliasID = -1;
	pAccount_reqRemoveAvatar->args = Account_reqRemoveAvatar_args;

	pAccountModule->methods.Add(TEXT("reqRemoveAvatar"), pAccount_reqRemoveAvatar); 
	pAccountModule->base_methods.Add(TEXT("reqRemoveAvatar"), pAccount_reqRemoveAvatar);

	pAccountModule->idbase_methods.Add(pAccount_reqRemoveAvatar->methodUtype, pAccount_reqRemoveAvatar);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqRemoveAvatar / 4).");

	ScriptModule* pAvatarModule = new ScriptModule("Avatar", 2);
	EntityDef::moduledefs.Add(TEXT("Avatar"), pAvatarModule);
	EntityDef::idmoduledefs.Add(2, pAvatarModule);

	Property* pAvatar_position = new Property();
	pAvatar_position->name = TEXT("position");
	pAvatar_position->properUtype = 40000;
	pAvatar_position->properFlags = 4;
	pAvatar_position->aliasID = 1;
	KBVar* pAvatar_position_defval = new KBVar(FVector());
	pAvatar_position->pDefaultVal = pAvatar_position_defval;
	pAvatarModule->propertys.Add(TEXT("position"), pAvatar_position); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_position->aliasID, pAvatar_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(position / 40000).");

	Property* pAvatar_direction = new Property();
	pAvatar_direction->name = TEXT("direction");
	pAvatar_direction->properUtype = 40001;
	pAvatar_direction->properFlags = 4;
	pAvatar_direction->aliasID = 2;
	KBVar* pAvatar_direction_defval = new KBVar(FVector());
	pAvatar_direction->pDefaultVal = pAvatar_direction_defval;
	pAvatarModule->propertys.Add(TEXT("direction"), pAvatar_direction); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_direction->aliasID, pAvatar_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(direction / 40001).");

	Property* pAvatar_spaceID = new Property();
	pAvatar_spaceID->name = TEXT("spaceID");
	pAvatar_spaceID->properUtype = 40002;
	pAvatar_spaceID->properFlags = 16;
	pAvatar_spaceID->aliasID = 3;
	KBVar* pAvatar_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pAvatar_spaceID->pDefaultVal = pAvatar_spaceID_defval;
	pAvatarModule->propertys.Add(TEXT("spaceID"), pAvatar_spaceID); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_spaceID->aliasID, pAvatar_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(spaceID / 40002).");

	Property* pAvatar_BaseHP = new Property();
	pAvatar_BaseHP->name = TEXT("BaseHP");
	pAvatar_BaseHP->properUtype = 28;
	pAvatar_BaseHP->properFlags = 4;
	pAvatar_BaseHP->aliasID = 4;
	KBVar* pAvatar_BaseHP_defval = new KBVar((int32)FCString::Atoi64(TEXT("500")));
	pAvatar_BaseHP->pDefaultVal = pAvatar_BaseHP_defval;
	pAvatarModule->propertys.Add(TEXT("BaseHP"), pAvatar_BaseHP); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_BaseHP->aliasID, pAvatar_BaseHP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(BaseHP / 28).");

	Property* pAvatar_HP = new Property();
	pAvatar_HP->name = TEXT("HP");
	pAvatar_HP->properUtype = 29;
	pAvatar_HP->properFlags = 4;
	pAvatar_HP->aliasID = 5;
	KBVar* pAvatar_HP_defval = new KBVar((int32)FCString::Atoi64(TEXT("500")));
	pAvatar_HP->pDefaultVal = pAvatar_HP_defval;
	pAvatarModule->propertys.Add(TEXT("HP"), pAvatar_HP); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_HP->aliasID, pAvatar_HP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(HP / 29).");

	Property* pAvatar_bagSize = new Property();
	pAvatar_bagSize->name = TEXT("bagSize");
	pAvatar_bagSize->properUtype = 21;
	pAvatar_bagSize->properFlags = 16;
	pAvatar_bagSize->aliasID = 6;
	KBVar* pAvatar_bagSize_defval = new KBVar((uint16)FCString::Atoi64(TEXT("30")));
	pAvatar_bagSize->pDefaultVal = pAvatar_bagSize_defval;
	pAvatarModule->propertys.Add(TEXT("bagSize"), pAvatar_bagSize); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_bagSize->aliasID, pAvatar_bagSize);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(bagSize / 21).");

	Property* pAvatar_dbid = new Property();
	pAvatar_dbid->name = TEXT("dbid");
	pAvatar_dbid->properUtype = 8;
	pAvatar_dbid->properFlags = 4;
	pAvatar_dbid->aliasID = 7;
	KBVar* pAvatar_dbid_defval = new KBVar((uint64)FCString::Atoi64(TEXT("0")));
	pAvatar_dbid->pDefaultVal = pAvatar_dbid_defval;
	pAvatarModule->propertys.Add(TEXT("dbid"), pAvatar_dbid); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_dbid->aliasID, pAvatar_dbid);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(dbid / 8).");

	Property* pAvatar_enage = new Property();
	pAvatar_enage->name = TEXT("enage");
	pAvatar_enage->properUtype = 27;
	pAvatar_enage->properFlags = 4;
	pAvatar_enage->aliasID = 8;
	KBVar* pAvatar_enage_defval = new KBVar((int32)FCString::Atoi64(TEXT("-1")));
	pAvatar_enage->pDefaultVal = pAvatar_enage_defval;
	pAvatarModule->propertys.Add(TEXT("enage"), pAvatar_enage); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_enage->aliasID, pAvatar_enage);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(enage / 27).");

	Property* pAvatar_facade = new Property();
	pAvatar_facade->name = TEXT("facade");
	pAvatar_facade->properUtype = 19;
	pAvatar_facade->properFlags = 4;
	pAvatar_facade->aliasID = 9;
	KBVar* pAvatar_facade_defval = new KBVar(TArray<uint8>());
	pAvatar_facade->pDefaultVal = pAvatar_facade_defval;
	pAvatarModule->propertys.Add(TEXT("facade"), pAvatar_facade); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_facade->aliasID, pAvatar_facade);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(facade / 19).");

	Property* pAvatar_isJump = new Property();
	pAvatar_isJump->name = TEXT("isJump");
	pAvatar_isJump->properUtype = 22;
	pAvatar_isJump->properFlags = 128;
	pAvatar_isJump->aliasID = 10;
	KBVar* pAvatar_isJump_defval = new KBVar((int8)FCString::Atoi64(TEXT("")));
	pAvatar_isJump->pDefaultVal = pAvatar_isJump_defval;
	pAvatarModule->propertys.Add(TEXT("isJump"), pAvatar_isJump); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_isJump->aliasID, pAvatar_isJump);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(isJump / 22).");

	Property* pAvatar_moveH = new Property();
	pAvatar_moveH->name = TEXT("moveH");
	pAvatar_moveH->properUtype = 24;
	pAvatar_moveH->properFlags = 128;
	pAvatar_moveH->aliasID = 11;
	KBVar* pAvatar_moveH_defval = new KBVar((int8)FCString::Atoi64(TEXT("")));
	pAvatar_moveH->pDefaultVal = pAvatar_moveH_defval;
	pAvatarModule->propertys.Add(TEXT("moveH"), pAvatar_moveH); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_moveH->aliasID, pAvatar_moveH);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(moveH / 24).");

	Property* pAvatar_moveLevel = new Property();
	pAvatar_moveLevel->name = TEXT("moveLevel");
	pAvatar_moveLevel->properUtype = 23;
	pAvatar_moveLevel->properFlags = 128;
	pAvatar_moveLevel->aliasID = 12;
	KBVar* pAvatar_moveLevel_defval = new KBVar((int8)FCString::Atoi64(TEXT("")));
	pAvatar_moveLevel->pDefaultVal = pAvatar_moveLevel_defval;
	pAvatarModule->propertys.Add(TEXT("moveLevel"), pAvatar_moveLevel); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_moveLevel->aliasID, pAvatar_moveLevel);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(moveLevel / 23).");

	Property* pAvatar_moveV = new Property();
	pAvatar_moveV->name = TEXT("moveV");
	pAvatar_moveV->properUtype = 25;
	pAvatar_moveV->properFlags = 128;
	pAvatar_moveV->aliasID = 13;
	KBVar* pAvatar_moveV_defval = new KBVar((int8)FCString::Atoi64(TEXT("")));
	pAvatar_moveV->pDefaultVal = pAvatar_moveV_defval;
	pAvatarModule->propertys.Add(TEXT("moveV"), pAvatar_moveV); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_moveV->aliasID, pAvatar_moveV);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(moveV / 25).");

	Property* pAvatar_name = new Property();
	pAvatar_name->name = TEXT("name");
	pAvatar_name->properUtype = 18;
	pAvatar_name->properFlags = 4;
	pAvatar_name->aliasID = 14;
	KBVar* pAvatar_name_defval = new KBVar(FString());
	pAvatar_name->pDefaultVal = pAvatar_name_defval;
	pAvatarModule->propertys.Add(TEXT("name"), pAvatar_name); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_name->aliasID, pAvatar_name);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(name / 18).");

	Property* pAvatar_netDelay = new Property();
	pAvatar_netDelay->name = TEXT("netDelay");
	pAvatar_netDelay->properUtype = 16;
	pAvatar_netDelay->properFlags = 32;
	pAvatar_netDelay->aliasID = 15;
	KBVar* pAvatar_netDelay_defval = new KBVar((uint16)FCString::Atoi64(TEXT("")));
	pAvatar_netDelay->pDefaultVal = pAvatar_netDelay_defval;
	pAvatarModule->propertys.Add(TEXT("netDelay"), pAvatar_netDelay); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_netDelay->aliasID, pAvatar_netDelay);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(netDelay / 16).");

	Property* pAvatar_serverTime = new Property();
	pAvatar_serverTime->name = TEXT("serverTime");
	pAvatar_serverTime->properUtype = 10;
	pAvatar_serverTime->properFlags = 32;
	pAvatar_serverTime->aliasID = 16;
	KBVar* pAvatar_serverTime_defval = new KBVar((uint32)FCString::Atoi64(TEXT("0")));
	pAvatar_serverTime->pDefaultVal = pAvatar_serverTime_defval;
	pAvatarModule->propertys.Add(TEXT("serverTime"), pAvatar_serverTime); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_serverTime->aliasID, pAvatar_serverTime);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(serverTime / 10).");

	Property* pAvatar_sex = new Property();
	pAvatar_sex->name = TEXT("sex");
	pAvatar_sex->properUtype = 17;
	pAvatar_sex->properFlags = 4;
	pAvatar_sex->aliasID = 17;
	KBVar* pAvatar_sex_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pAvatar_sex->pDefaultVal = pAvatar_sex_defval;
	pAvatarModule->propertys.Add(TEXT("sex"), pAvatar_sex); 

	pAvatarModule->usePropertyDescrAlias = true;
	pAvatarModule->idpropertys.Add((uint16)pAvatar_sex->aliasID, pAvatar_sex);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), property(sex / 17).");

	TArray<DATATYPE_BASE*> Avatar_OnAnimUpdate_args;
	Avatar_OnAnimUpdate_args.Add(EntityDef::id2datatypes[32]);

	Method* pAvatar_OnAnimUpdate = new Method();
	pAvatar_OnAnimUpdate->name = TEXT("OnAnimUpdate");
	pAvatar_OnAnimUpdate->methodUtype = 36;
	pAvatar_OnAnimUpdate->aliasID = 1;
	pAvatar_OnAnimUpdate->args = Avatar_OnAnimUpdate_args;

	pAvatarModule->methods.Add(TEXT("OnAnimUpdate"), pAvatar_OnAnimUpdate); 
	pAvatarModule->useMethodDescrAlias = true;
	pAvatarModule->idmethods.Add((uint16)pAvatar_OnAnimUpdate->aliasID, pAvatar_OnAnimUpdate);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(OnAnimUpdate / 36).");

	TArray<DATATYPE_BASE*> Avatar_OnAttack_args;
	Avatar_OnAttack_args.Add(EntityDef::id2datatypes[29]);

	Method* pAvatar_OnAttack = new Method();
	pAvatar_OnAttack->name = TEXT("OnAttack");
	pAvatar_OnAttack->methodUtype = 34;
	pAvatar_OnAttack->aliasID = 2;
	pAvatar_OnAttack->args = Avatar_OnAttack_args;

	pAvatarModule->methods.Add(TEXT("OnAttack"), pAvatar_OnAttack); 
	pAvatarModule->useMethodDescrAlias = true;
	pAvatarModule->idmethods.Add((uint16)pAvatar_OnAttack->aliasID, pAvatar_OnAttack);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(OnAttack / 34).");

	TArray<DATATYPE_BASE*> Avatar_ntfError_args;
	Avatar_ntfError_args.Add(EntityDef::id2datatypes[4]);

	Method* pAvatar_ntfError = new Method();
	pAvatar_ntfError->name = TEXT("ntfError");
	pAvatar_ntfError->methodUtype = 17;
	pAvatar_ntfError->aliasID = 3;
	pAvatar_ntfError->args = Avatar_ntfError_args;

	pAvatarModule->methods.Add(TEXT("ntfError"), pAvatar_ntfError); 
	pAvatarModule->useMethodDescrAlias = true;
	pAvatarModule->idmethods.Add((uint16)pAvatar_ntfError->aliasID, pAvatar_ntfError);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(ntfError / 17).");

	TArray<DATATYPE_BASE*> Avatar_ntfItemsChange_args;
	Avatar_ntfItemsChange_args.Add(EntityDef::id2datatypes[27]);
	Avatar_ntfItemsChange_args.Add(EntityDef::id2datatypes[23]);

	Method* pAvatar_ntfItemsChange = new Method();
	pAvatar_ntfItemsChange->name = TEXT("ntfItemsChange");
	pAvatar_ntfItemsChange->methodUtype = 22;
	pAvatar_ntfItemsChange->aliasID = 4;
	pAvatar_ntfItemsChange->args = Avatar_ntfItemsChange_args;

	pAvatarModule->methods.Add(TEXT("ntfItemsChange"), pAvatar_ntfItemsChange); 
	pAvatarModule->useMethodDescrAlias = true;
	pAvatarModule->idmethods.Add((uint16)pAvatar_ntfItemsChange->aliasID, pAvatar_ntfItemsChange);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(ntfItemsChange / 22).");

	TArray<DATATYPE_BASE*> Avatar_ntfReceiveChat_args;
	Avatar_ntfReceiveChat_args.Add(EntityDef::id2datatypes[28]);

	Method* pAvatar_ntfReceiveChat = new Method();
	pAvatar_ntfReceiveChat->name = TEXT("ntfReceiveChat");
	pAvatar_ntfReceiveChat->methodUtype = 29;
	pAvatar_ntfReceiveChat->aliasID = 5;
	pAvatar_ntfReceiveChat->args = Avatar_ntfReceiveChat_args;

	pAvatarModule->methods.Add(TEXT("ntfReceiveChat"), pAvatar_ntfReceiveChat); 
	pAvatarModule->useMethodDescrAlias = true;
	pAvatarModule->idmethods.Add((uint16)pAvatar_ntfReceiveChat->aliasID, pAvatar_ntfReceiveChat);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(ntfReceiveChat / 29).");

	TArray<DATATYPE_BASE*> Avatar_rspChangeName_args;
	Avatar_rspChangeName_args.Add(EntityDef::id2datatypes[4]);

	Method* pAvatar_rspChangeName = new Method();
	pAvatar_rspChangeName->name = TEXT("rspChangeName");
	pAvatar_rspChangeName->methodUtype = 18;
	pAvatar_rspChangeName->aliasID = 6;
	pAvatar_rspChangeName->args = Avatar_rspChangeName_args;

	pAvatarModule->methods.Add(TEXT("rspChangeName"), pAvatar_rspChangeName); 
	pAvatarModule->useMethodDescrAlias = true;
	pAvatarModule->idmethods.Add((uint16)pAvatar_rspChangeName->aliasID, pAvatar_rspChangeName);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(rspChangeName / 18).");

	TArray<DATATYPE_BASE*> Avatar_rspDigOre_args;

	Method* pAvatar_rspDigOre = new Method();
	pAvatar_rspDigOre->name = TEXT("rspDigOre");
	pAvatar_rspDigOre->methodUtype = 40;
	pAvatar_rspDigOre->aliasID = 7;
	pAvatar_rspDigOre->args = Avatar_rspDigOre_args;

	pAvatarModule->methods.Add(TEXT("rspDigOre"), pAvatar_rspDigOre); 
	pAvatarModule->useMethodDescrAlias = true;
	pAvatarModule->idmethods.Add((uint16)pAvatar_rspDigOre->aliasID, pAvatar_rspDigOre);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(rspDigOre / 40).");

	TArray<DATATYPE_BASE*> Avatar_rspStopDigOre_args;

	Method* pAvatar_rspStopDigOre = new Method();
	pAvatar_rspStopDigOre->name = TEXT("rspStopDigOre");
	pAvatar_rspStopDigOre->methodUtype = 41;
	pAvatar_rspStopDigOre->aliasID = 8;
	pAvatar_rspStopDigOre->args = Avatar_rspStopDigOre_args;

	pAvatarModule->methods.Add(TEXT("rspStopDigOre"), pAvatar_rspStopDigOre); 
	pAvatarModule->useMethodDescrAlias = true;
	pAvatarModule->idmethods.Add((uint16)pAvatar_rspStopDigOre->aliasID, pAvatar_rspStopDigOre);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(rspStopDigOre / 41).");

	TArray<DATATYPE_BASE*> Avatar_rspSwitchAvatar_args;
	Avatar_rspSwitchAvatar_args.Add(EntityDef::id2datatypes[4]);

	Method* pAvatar_rspSwitchAvatar = new Method();
	pAvatar_rspSwitchAvatar->name = TEXT("rspSwitchAvatar");
	pAvatar_rspSwitchAvatar->methodUtype = 19;
	pAvatar_rspSwitchAvatar->aliasID = 9;
	pAvatar_rspSwitchAvatar->args = Avatar_rspSwitchAvatar_args;

	pAvatarModule->methods.Add(TEXT("rspSwitchAvatar"), pAvatar_rspSwitchAvatar); 
	pAvatarModule->useMethodDescrAlias = true;
	pAvatarModule->idmethods.Add((uint16)pAvatar_rspSwitchAvatar->aliasID, pAvatar_rspSwitchAvatar);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(rspSwitchAvatar / 19).");

	TArray<DATATYPE_BASE*> Avatar_reqSwitchAvatar_args;

	Method* pAvatar_reqSwitchAvatar = new Method();
	pAvatar_reqSwitchAvatar->name = TEXT("reqSwitchAvatar");
	pAvatar_reqSwitchAvatar->methodUtype = 16;
	pAvatar_reqSwitchAvatar->aliasID = -1;
	pAvatar_reqSwitchAvatar->args = Avatar_reqSwitchAvatar_args;

	pAvatarModule->methods.Add(TEXT("reqSwitchAvatar"), pAvatar_reqSwitchAvatar); 
	pAvatarModule->base_methods.Add(TEXT("reqSwitchAvatar"), pAvatar_reqSwitchAvatar);

	pAvatarModule->idbase_methods.Add(pAvatar_reqSwitchAvatar->methodUtype, pAvatar_reqSwitchAvatar);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(reqSwitchAvatar / 16).");

	TArray<DATATYPE_BASE*> Avatar_AnimUpdate_args;
	Avatar_AnimUpdate_args.Add(EntityDef::id2datatypes[32]);

	Method* pAvatar_AnimUpdate = new Method();
	pAvatar_AnimUpdate->name = TEXT("AnimUpdate");
	pAvatar_AnimUpdate->methodUtype = 35;
	pAvatar_AnimUpdate->aliasID = -1;
	pAvatar_AnimUpdate->args = Avatar_AnimUpdate_args;

	pAvatarModule->methods.Add(TEXT("AnimUpdate"), pAvatar_AnimUpdate); 
	pAvatarModule->cell_methods.Add(TEXT("AnimUpdate"), pAvatar_AnimUpdate);

	pAvatarModule->idcell_methods.Add(pAvatar_AnimUpdate->methodUtype, pAvatar_AnimUpdate);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(AnimUpdate / 35).");

	TArray<DATATYPE_BASE*> Avatar_Attack_args;
	Avatar_Attack_args.Add(EntityDef::id2datatypes[29]);

	Method* pAvatar_Attack = new Method();
	pAvatar_Attack->name = TEXT("Attack");
	pAvatar_Attack->methodUtype = 30;
	pAvatar_Attack->aliasID = -1;
	pAvatar_Attack->args = Avatar_Attack_args;

	pAvatarModule->methods.Add(TEXT("Attack"), pAvatar_Attack); 
	pAvatarModule->cell_methods.Add(TEXT("Attack"), pAvatar_Attack);

	pAvatarModule->idcell_methods.Add(pAvatar_Attack->methodUtype, pAvatar_Attack);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(Attack / 30).");

	TArray<DATATYPE_BASE*> Avatar_Relive_args;

	Method* pAvatar_Relive = new Method();
	pAvatar_Relive->name = TEXT("Relive");
	pAvatar_Relive->methodUtype = 31;
	pAvatar_Relive->aliasID = -1;
	pAvatar_Relive->args = Avatar_Relive_args;

	pAvatarModule->methods.Add(TEXT("Relive"), pAvatar_Relive); 
	pAvatarModule->cell_methods.Add(TEXT("Relive"), pAvatar_Relive);

	pAvatarModule->idcell_methods.Add(pAvatar_Relive->methodUtype, pAvatar_Relive);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(Relive / 31).");

	TArray<DATATYPE_BASE*> Avatar_ReqChangeEnage_args;
	Avatar_ReqChangeEnage_args.Add(EntityDef::id2datatypes[8]);

	Method* pAvatar_ReqChangeEnage = new Method();
	pAvatar_ReqChangeEnage->name = TEXT("ReqChangeEnage");
	pAvatar_ReqChangeEnage->methodUtype = 33;
	pAvatar_ReqChangeEnage->aliasID = -1;
	pAvatar_ReqChangeEnage->args = Avatar_ReqChangeEnage_args;

	pAvatarModule->methods.Add(TEXT("ReqChangeEnage"), pAvatar_ReqChangeEnage); 
	pAvatarModule->cell_methods.Add(TEXT("ReqChangeEnage"), pAvatar_ReqChangeEnage);

	pAvatarModule->idcell_methods.Add(pAvatar_ReqChangeEnage->methodUtype, pAvatar_ReqChangeEnage);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(ReqChangeEnage / 33).");

	TArray<DATATYPE_BASE*> Avatar_ReqStartDamage_args;
	Avatar_ReqStartDamage_args.Add(EntityDef::id2datatypes[29]);
	Avatar_ReqStartDamage_args.Add(EntityDef::id2datatypes[25]);

	Method* pAvatar_ReqStartDamage = new Method();
	pAvatar_ReqStartDamage->name = TEXT("ReqStartDamage");
	pAvatar_ReqStartDamage->methodUtype = 32;
	pAvatar_ReqStartDamage->aliasID = -1;
	pAvatar_ReqStartDamage->args = Avatar_ReqStartDamage_args;

	pAvatarModule->methods.Add(TEXT("ReqStartDamage"), pAvatar_ReqStartDamage); 
	pAvatarModule->cell_methods.Add(TEXT("ReqStartDamage"), pAvatar_ReqStartDamage);

	pAvatarModule->idcell_methods.Add(pAvatar_ReqStartDamage->methodUtype, pAvatar_ReqStartDamage);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(ReqStartDamage / 32).");

	TArray<DATATYPE_BASE*> Avatar_reqChangeJump_args;
	Avatar_reqChangeJump_args.Add(EntityDef::id2datatypes[6]);

	Method* pAvatar_reqChangeJump = new Method();
	pAvatar_reqChangeJump->name = TEXT("reqChangeJump");
	pAvatar_reqChangeJump->methodUtype = 23;
	pAvatar_reqChangeJump->aliasID = -1;
	pAvatar_reqChangeJump->args = Avatar_reqChangeJump_args;

	pAvatarModule->methods.Add(TEXT("reqChangeJump"), pAvatar_reqChangeJump); 
	pAvatarModule->cell_methods.Add(TEXT("reqChangeJump"), pAvatar_reqChangeJump);

	pAvatarModule->idcell_methods.Add(pAvatar_reqChangeJump->methodUtype, pAvatar_reqChangeJump);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(reqChangeJump / 23).");

	TArray<DATATYPE_BASE*> Avatar_reqChangeMoveH_args;
	Avatar_reqChangeMoveH_args.Add(EntityDef::id2datatypes[6]);

	Method* pAvatar_reqChangeMoveH = new Method();
	pAvatar_reqChangeMoveH->name = TEXT("reqChangeMoveH");
	pAvatar_reqChangeMoveH->methodUtype = 25;
	pAvatar_reqChangeMoveH->aliasID = -1;
	pAvatar_reqChangeMoveH->args = Avatar_reqChangeMoveH_args;

	pAvatarModule->methods.Add(TEXT("reqChangeMoveH"), pAvatar_reqChangeMoveH); 
	pAvatarModule->cell_methods.Add(TEXT("reqChangeMoveH"), pAvatar_reqChangeMoveH);

	pAvatarModule->idcell_methods.Add(pAvatar_reqChangeMoveH->methodUtype, pAvatar_reqChangeMoveH);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(reqChangeMoveH / 25).");

	TArray<DATATYPE_BASE*> Avatar_reqChangeMoveLevel_args;
	Avatar_reqChangeMoveLevel_args.Add(EntityDef::id2datatypes[6]);

	Method* pAvatar_reqChangeMoveLevel = new Method();
	pAvatar_reqChangeMoveLevel->name = TEXT("reqChangeMoveLevel");
	pAvatar_reqChangeMoveLevel->methodUtype = 24;
	pAvatar_reqChangeMoveLevel->aliasID = -1;
	pAvatar_reqChangeMoveLevel->args = Avatar_reqChangeMoveLevel_args;

	pAvatarModule->methods.Add(TEXT("reqChangeMoveLevel"), pAvatar_reqChangeMoveLevel); 
	pAvatarModule->cell_methods.Add(TEXT("reqChangeMoveLevel"), pAvatar_reqChangeMoveLevel);

	pAvatarModule->idcell_methods.Add(pAvatar_reqChangeMoveLevel->methodUtype, pAvatar_reqChangeMoveLevel);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(reqChangeMoveLevel / 24).");

	TArray<DATATYPE_BASE*> Avatar_reqChangeMoveV_args;
	Avatar_reqChangeMoveV_args.Add(EntityDef::id2datatypes[6]);

	Method* pAvatar_reqChangeMoveV = new Method();
	pAvatar_reqChangeMoveV->name = TEXT("reqChangeMoveV");
	pAvatar_reqChangeMoveV->methodUtype = 26;
	pAvatar_reqChangeMoveV->aliasID = -1;
	pAvatar_reqChangeMoveV->args = Avatar_reqChangeMoveV_args;

	pAvatarModule->methods.Add(TEXT("reqChangeMoveV"), pAvatar_reqChangeMoveV); 
	pAvatarModule->cell_methods.Add(TEXT("reqChangeMoveV"), pAvatar_reqChangeMoveV);

	pAvatarModule->idcell_methods.Add(pAvatar_reqChangeMoveV->methodUtype, pAvatar_reqChangeMoveV);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(reqChangeMoveV / 26).");

	TArray<DATATYPE_BASE*> Avatar_reqChangeName_args;
	Avatar_reqChangeName_args.Add(EntityDef::id2datatypes[12]);

	Method* pAvatar_reqChangeName = new Method();
	pAvatar_reqChangeName->name = TEXT("reqChangeName");
	pAvatar_reqChangeName->methodUtype = 12;
	pAvatar_reqChangeName->aliasID = -1;
	pAvatar_reqChangeName->args = Avatar_reqChangeName_args;

	pAvatarModule->methods.Add(TEXT("reqChangeName"), pAvatar_reqChangeName); 
	pAvatarModule->cell_methods.Add(TEXT("reqChangeName"), pAvatar_reqChangeName);

	pAvatarModule->idcell_methods.Add(pAvatar_reqChangeName->methodUtype, pAvatar_reqChangeName);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(reqChangeName / 12).");

	TArray<DATATYPE_BASE*> Avatar_reqDigOre_args;
	Avatar_reqDigOre_args.Add(EntityDef::id2datatypes[8]);

	Method* pAvatar_reqDigOre = new Method();
	pAvatar_reqDigOre->name = TEXT("reqDigOre");
	pAvatar_reqDigOre->methodUtype = 38;
	pAvatar_reqDigOre->aliasID = -1;
	pAvatar_reqDigOre->args = Avatar_reqDigOre_args;

	pAvatarModule->methods.Add(TEXT("reqDigOre"), pAvatar_reqDigOre); 
	pAvatarModule->cell_methods.Add(TEXT("reqDigOre"), pAvatar_reqDigOre);

	pAvatarModule->idcell_methods.Add(pAvatar_reqDigOre->methodUtype, pAvatar_reqDigOre);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(reqDigOre / 38).");

	TArray<DATATYPE_BASE*> Avatar_reqExecInnerFunc_args;
	Avatar_reqExecInnerFunc_args.Add(EntityDef::id2datatypes[1]);
	Avatar_reqExecInnerFunc_args.Add(EntityDef::id2datatypes[1]);

	Method* pAvatar_reqExecInnerFunc = new Method();
	pAvatar_reqExecInnerFunc->name = TEXT("reqExecInnerFunc");
	pAvatar_reqExecInnerFunc->methodUtype = 14;
	pAvatar_reqExecInnerFunc->aliasID = -1;
	pAvatar_reqExecInnerFunc->args = Avatar_reqExecInnerFunc_args;

	pAvatarModule->methods.Add(TEXT("reqExecInnerFunc"), pAvatar_reqExecInnerFunc); 
	pAvatarModule->cell_methods.Add(TEXT("reqExecInnerFunc"), pAvatar_reqExecInnerFunc);

	pAvatarModule->idcell_methods.Add(pAvatar_reqExecInnerFunc->methodUtype, pAvatar_reqExecInnerFunc);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(reqExecInnerFunc / 14).");

	TArray<DATATYPE_BASE*> Avatar_reqMoveItem_args;
	Avatar_reqMoveItem_args.Add(EntityDef::id2datatypes[3]);
	Avatar_reqMoveItem_args.Add(EntityDef::id2datatypes[3]);

	Method* pAvatar_reqMoveItem = new Method();
	pAvatar_reqMoveItem->name = TEXT("reqMoveItem");
	pAvatar_reqMoveItem->methodUtype = 20;
	pAvatar_reqMoveItem->aliasID = -1;
	pAvatar_reqMoveItem->args = Avatar_reqMoveItem_args;

	pAvatarModule->methods.Add(TEXT("reqMoveItem"), pAvatar_reqMoveItem); 
	pAvatarModule->cell_methods.Add(TEXT("reqMoveItem"), pAvatar_reqMoveItem);

	pAvatarModule->idcell_methods.Add(pAvatar_reqMoveItem->methodUtype, pAvatar_reqMoveItem);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(reqMoveItem / 20).");

	TArray<DATATYPE_BASE*> Avatar_reqPickupItem_args;
	Avatar_reqPickupItem_args.Add(EntityDef::id2datatypes[8]);
	Avatar_reqPickupItem_args.Add(EntityDef::id2datatypes[24]);

	Method* pAvatar_reqPickupItem = new Method();
	pAvatar_reqPickupItem->name = TEXT("reqPickupItem");
	pAvatar_reqPickupItem->methodUtype = 37;
	pAvatar_reqPickupItem->aliasID = -1;
	pAvatar_reqPickupItem->args = Avatar_reqPickupItem_args;

	pAvatarModule->methods.Add(TEXT("reqPickupItem"), pAvatar_reqPickupItem); 
	pAvatarModule->cell_methods.Add(TEXT("reqPickupItem"), pAvatar_reqPickupItem);

	pAvatarModule->idcell_methods.Add(pAvatar_reqPickupItem->methodUtype, pAvatar_reqPickupItem);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(reqPickupItem / 37).");

	TArray<DATATYPE_BASE*> Avatar_reqSendChatMessage_args;
	Avatar_reqSendChatMessage_args.Add(EntityDef::id2datatypes[5]);
	Avatar_reqSendChatMessage_args.Add(EntityDef::id2datatypes[2]);
	Avatar_reqSendChatMessage_args.Add(EntityDef::id2datatypes[12]);

	Method* pAvatar_reqSendChatMessage = new Method();
	pAvatar_reqSendChatMessage->name = TEXT("reqSendChatMessage");
	pAvatar_reqSendChatMessage->methodUtype = 27;
	pAvatar_reqSendChatMessage->aliasID = -1;
	pAvatar_reqSendChatMessage->args = Avatar_reqSendChatMessage_args;

	pAvatarModule->methods.Add(TEXT("reqSendChatMessage"), pAvatar_reqSendChatMessage); 
	pAvatarModule->cell_methods.Add(TEXT("reqSendChatMessage"), pAvatar_reqSendChatMessage);

	pAvatarModule->idcell_methods.Add(pAvatar_reqSendChatMessage->methodUtype, pAvatar_reqSendChatMessage);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(reqSendChatMessage / 27).");

	TArray<DATATYPE_BASE*> Avatar_reqSetupInnerProp_args;
	Avatar_reqSetupInnerProp_args.Add(EntityDef::id2datatypes[1]);
	Avatar_reqSetupInnerProp_args.Add(EntityDef::id2datatypes[1]);

	Method* pAvatar_reqSetupInnerProp = new Method();
	pAvatar_reqSetupInnerProp->name = TEXT("reqSetupInnerProp");
	pAvatar_reqSetupInnerProp->methodUtype = 13;
	pAvatar_reqSetupInnerProp->aliasID = -1;
	pAvatar_reqSetupInnerProp->args = Avatar_reqSetupInnerProp_args;

	pAvatarModule->methods.Add(TEXT("reqSetupInnerProp"), pAvatar_reqSetupInnerProp); 
	pAvatarModule->cell_methods.Add(TEXT("reqSetupInnerProp"), pAvatar_reqSetupInnerProp);

	pAvatarModule->idcell_methods.Add(pAvatar_reqSetupInnerProp->methodUtype, pAvatar_reqSetupInnerProp);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(reqSetupInnerProp / 13).");

	TArray<DATATYPE_BASE*> Avatar_reqSplitItemNum_args;
	Avatar_reqSplitItemNum_args.Add(EntityDef::id2datatypes[3]);
	Avatar_reqSplitItemNum_args.Add(EntityDef::id2datatypes[4]);
	Avatar_reqSplitItemNum_args.Add(EntityDef::id2datatypes[3]);

	Method* pAvatar_reqSplitItemNum = new Method();
	pAvatar_reqSplitItemNum->name = TEXT("reqSplitItemNum");
	pAvatar_reqSplitItemNum->methodUtype = 21;
	pAvatar_reqSplitItemNum->aliasID = -1;
	pAvatar_reqSplitItemNum->args = Avatar_reqSplitItemNum_args;

	pAvatarModule->methods.Add(TEXT("reqSplitItemNum"), pAvatar_reqSplitItemNum); 
	pAvatarModule->cell_methods.Add(TEXT("reqSplitItemNum"), pAvatar_reqSplitItemNum);

	pAvatarModule->idcell_methods.Add(pAvatar_reqSplitItemNum->methodUtype, pAvatar_reqSplitItemNum);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(reqSplitItemNum / 21).");

	TArray<DATATYPE_BASE*> Avatar_reqStopDigOre_args;

	Method* pAvatar_reqStopDigOre = new Method();
	pAvatar_reqStopDigOre->name = TEXT("reqStopDigOre");
	pAvatar_reqStopDigOre->methodUtype = 39;
	pAvatar_reqStopDigOre->aliasID = -1;
	pAvatar_reqStopDigOre->args = Avatar_reqStopDigOre_args;

	pAvatarModule->methods.Add(TEXT("reqStopDigOre"), pAvatar_reqStopDigOre); 
	pAvatarModule->cell_methods.Add(TEXT("reqStopDigOre"), pAvatar_reqStopDigOre);

	pAvatarModule->idcell_methods.Add(pAvatar_reqStopDigOre->methodUtype, pAvatar_reqStopDigOre);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Avatar), method(reqStopDigOre / 39).");

	ScriptModule* pSkillModule = new ScriptModule("Skill", 3);
	EntityDef::moduledefs.Add(TEXT("Skill"), pSkillModule);
	EntityDef::idmoduledefs.Add(3, pSkillModule);

	Property* pSkill_position = new Property();
	pSkill_position->name = TEXT("position");
	pSkill_position->properUtype = 40000;
	pSkill_position->properFlags = 4;
	pSkill_position->aliasID = 1;
	KBVar* pSkill_position_defval = new KBVar(FVector());
	pSkill_position->pDefaultVal = pSkill_position_defval;
	pSkillModule->propertys.Add(TEXT("position"), pSkill_position); 

	pSkillModule->usePropertyDescrAlias = true;
	pSkillModule->idpropertys.Add((uint16)pSkill_position->aliasID, pSkill_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Skill), property(position / 40000).");

	Property* pSkill_direction = new Property();
	pSkill_direction->name = TEXT("direction");
	pSkill_direction->properUtype = 40001;
	pSkill_direction->properFlags = 4;
	pSkill_direction->aliasID = 2;
	KBVar* pSkill_direction_defval = new KBVar(FVector());
	pSkill_direction->pDefaultVal = pSkill_direction_defval;
	pSkillModule->propertys.Add(TEXT("direction"), pSkill_direction); 

	pSkillModule->usePropertyDescrAlias = true;
	pSkillModule->idpropertys.Add((uint16)pSkill_direction->aliasID, pSkill_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Skill), property(direction / 40001).");

	Property* pSkill_spaceID = new Property();
	pSkill_spaceID->name = TEXT("spaceID");
	pSkill_spaceID->properUtype = 40002;
	pSkill_spaceID->properFlags = 16;
	pSkill_spaceID->aliasID = 3;
	KBVar* pSkill_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pSkill_spaceID->pDefaultVal = pSkill_spaceID_defval;
	pSkillModule->propertys.Add(TEXT("spaceID"), pSkill_spaceID); 

	pSkillModule->usePropertyDescrAlias = true;
	pSkillModule->idpropertys.Add((uint16)pSkill_spaceID->aliasID, pSkill_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Skill), property(spaceID / 40002).");

	Property* pSkill_skillId = new Property();
	pSkill_skillId->name = TEXT("skillId");
	pSkill_skillId->properUtype = 35;
	pSkill_skillId->properFlags = 4;
	pSkill_skillId->aliasID = 4;
	KBVar* pSkill_skillId_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pSkill_skillId->pDefaultVal = pSkill_skillId_defval;
	pSkillModule->propertys.Add(TEXT("skillId"), pSkill_skillId); 

	pSkillModule->usePropertyDescrAlias = true;
	pSkillModule->idpropertys.Add((uint16)pSkill_skillId->aliasID, pSkill_skillId);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Skill), property(skillId / 35).");

	pSkillModule->useMethodDescrAlias = true;
	ScriptModule* pMonsterModule = new ScriptModule("Monster", 4);
	EntityDef::moduledefs.Add(TEXT("Monster"), pMonsterModule);
	EntityDef::idmoduledefs.Add(4, pMonsterModule);

	Property* pMonster_position = new Property();
	pMonster_position->name = TEXT("position");
	pMonster_position->properUtype = 40000;
	pMonster_position->properFlags = 4;
	pMonster_position->aliasID = 1;
	KBVar* pMonster_position_defval = new KBVar(FVector());
	pMonster_position->pDefaultVal = pMonster_position_defval;
	pMonsterModule->propertys.Add(TEXT("position"), pMonster_position); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_position->aliasID, pMonster_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(position / 40000).");

	Property* pMonster_direction = new Property();
	pMonster_direction->name = TEXT("direction");
	pMonster_direction->properUtype = 40001;
	pMonster_direction->properFlags = 4;
	pMonster_direction->aliasID = 2;
	KBVar* pMonster_direction_defval = new KBVar(FVector());
	pMonster_direction->pDefaultVal = pMonster_direction_defval;
	pMonsterModule->propertys.Add(TEXT("direction"), pMonster_direction); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_direction->aliasID, pMonster_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(direction / 40001).");

	Property* pMonster_spaceID = new Property();
	pMonster_spaceID->name = TEXT("spaceID");
	pMonster_spaceID->properUtype = 40002;
	pMonster_spaceID->properFlags = 16;
	pMonster_spaceID->aliasID = 3;
	KBVar* pMonster_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pMonster_spaceID->pDefaultVal = pMonster_spaceID_defval;
	pMonsterModule->propertys.Add(TEXT("spaceID"), pMonster_spaceID); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_spaceID->aliasID, pMonster_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(spaceID / 40002).");

	Property* pMonster_BaseHP = new Property();
	pMonster_BaseHP->name = TEXT("BaseHP");
	pMonster_BaseHP->properUtype = 42;
	pMonster_BaseHP->properFlags = 4;
	pMonster_BaseHP->aliasID = 4;
	KBVar* pMonster_BaseHP_defval = new KBVar((int32)FCString::Atoi64(TEXT("500")));
	pMonster_BaseHP->pDefaultVal = pMonster_BaseHP_defval;
	pMonsterModule->propertys.Add(TEXT("BaseHP"), pMonster_BaseHP); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_BaseHP->aliasID, pMonster_BaseHP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(BaseHP / 42).");

	Property* pMonster_HP = new Property();
	pMonster_HP->name = TEXT("HP");
	pMonster_HP->properUtype = 43;
	pMonster_HP->properFlags = 4;
	pMonster_HP->aliasID = 5;
	KBVar* pMonster_HP_defval = new KBVar((int32)FCString::Atoi64(TEXT("500")));
	pMonster_HP->pDefaultVal = pMonster_HP_defval;
	pMonsterModule->propertys.Add(TEXT("HP"), pMonster_HP); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_HP->aliasID, pMonster_HP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(HP / 43).");

	Property* pMonster_MonsterID = new Property();
	pMonster_MonsterID->name = TEXT("MonsterID");
	pMonster_MonsterID->properUtype = 39;
	pMonster_MonsterID->properFlags = 128;
	pMonster_MonsterID->aliasID = 6;
	KBVar* pMonster_MonsterID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pMonster_MonsterID->pDefaultVal = pMonster_MonsterID_defval;
	pMonsterModule->propertys.Add(TEXT("MonsterID"), pMonster_MonsterID); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_MonsterID->aliasID, pMonster_MonsterID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(MonsterID / 39).");

	Property* pMonster_enage = new Property();
	pMonster_enage->name = TEXT("enage");
	pMonster_enage->properUtype = 41;
	pMonster_enage->properFlags = 4;
	pMonster_enage->aliasID = 7;
	KBVar* pMonster_enage_defval = new KBVar((int32)FCString::Atoi64(TEXT("-1")));
	pMonster_enage->pDefaultVal = pMonster_enage_defval;
	pMonsterModule->propertys.Add(TEXT("enage"), pMonster_enage); 

	pMonsterModule->usePropertyDescrAlias = true;
	pMonsterModule->idpropertys.Add((uint16)pMonster_enage->aliasID, pMonster_enage);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), property(enage / 41).");

	TArray<DATATYPE_BASE*> Monster_OnAnimUpdate_args;
	Monster_OnAnimUpdate_args.Add(EntityDef::id2datatypes[32]);

	Method* pMonster_OnAnimUpdate = new Method();
	pMonster_OnAnimUpdate->name = TEXT("OnAnimUpdate");
	pMonster_OnAnimUpdate->methodUtype = 48;
	pMonster_OnAnimUpdate->aliasID = 1;
	pMonster_OnAnimUpdate->args = Monster_OnAnimUpdate_args;

	pMonsterModule->methods.Add(TEXT("OnAnimUpdate"), pMonster_OnAnimUpdate); 
	pMonsterModule->useMethodDescrAlias = true;
	pMonsterModule->idmethods.Add((uint16)pMonster_OnAnimUpdate->aliasID, pMonster_OnAnimUpdate);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), method(OnAnimUpdate / 48).");

	TArray<DATATYPE_BASE*> Monster_OnAttack_args;
	Monster_OnAttack_args.Add(EntityDef::id2datatypes[29]);

	Method* pMonster_OnAttack = new Method();
	pMonster_OnAttack->name = TEXT("OnAttack");
	pMonster_OnAttack->methodUtype = 46;
	pMonster_OnAttack->aliasID = 2;
	pMonster_OnAttack->args = Monster_OnAttack_args;

	pMonsterModule->methods.Add(TEXT("OnAttack"), pMonster_OnAttack); 
	pMonsterModule->useMethodDescrAlias = true;
	pMonsterModule->idmethods.Add((uint16)pMonster_OnAttack->aliasID, pMonster_OnAttack);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), method(OnAttack / 46).");

	TArray<DATATYPE_BASE*> Monster_AnimUpdate_args;
	Monster_AnimUpdate_args.Add(EntityDef::id2datatypes[32]);

	Method* pMonster_AnimUpdate = new Method();
	pMonster_AnimUpdate->name = TEXT("AnimUpdate");
	pMonster_AnimUpdate->methodUtype = 47;
	pMonster_AnimUpdate->aliasID = -1;
	pMonster_AnimUpdate->args = Monster_AnimUpdate_args;

	pMonsterModule->methods.Add(TEXT("AnimUpdate"), pMonster_AnimUpdate); 
	pMonsterModule->cell_methods.Add(TEXT("AnimUpdate"), pMonster_AnimUpdate);

	pMonsterModule->idcell_methods.Add(pMonster_AnimUpdate->methodUtype, pMonster_AnimUpdate);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), method(AnimUpdate / 47).");

	TArray<DATATYPE_BASE*> Monster_Attack_args;
	Monster_Attack_args.Add(EntityDef::id2datatypes[29]);

	Method* pMonster_Attack = new Method();
	pMonster_Attack->name = TEXT("Attack");
	pMonster_Attack->methodUtype = 42;
	pMonster_Attack->aliasID = -1;
	pMonster_Attack->args = Monster_Attack_args;

	pMonsterModule->methods.Add(TEXT("Attack"), pMonster_Attack); 
	pMonsterModule->cell_methods.Add(TEXT("Attack"), pMonster_Attack);

	pMonsterModule->idcell_methods.Add(pMonster_Attack->methodUtype, pMonster_Attack);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), method(Attack / 42).");

	TArray<DATATYPE_BASE*> Monster_Relive_args;

	Method* pMonster_Relive = new Method();
	pMonster_Relive->name = TEXT("Relive");
	pMonster_Relive->methodUtype = 43;
	pMonster_Relive->aliasID = -1;
	pMonster_Relive->args = Monster_Relive_args;

	pMonsterModule->methods.Add(TEXT("Relive"), pMonster_Relive); 
	pMonsterModule->cell_methods.Add(TEXT("Relive"), pMonster_Relive);

	pMonsterModule->idcell_methods.Add(pMonster_Relive->methodUtype, pMonster_Relive);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), method(Relive / 43).");

	TArray<DATATYPE_BASE*> Monster_ReqChangeEnage_args;
	Monster_ReqChangeEnage_args.Add(EntityDef::id2datatypes[8]);

	Method* pMonster_ReqChangeEnage = new Method();
	pMonster_ReqChangeEnage->name = TEXT("ReqChangeEnage");
	pMonster_ReqChangeEnage->methodUtype = 45;
	pMonster_ReqChangeEnage->aliasID = -1;
	pMonster_ReqChangeEnage->args = Monster_ReqChangeEnage_args;

	pMonsterModule->methods.Add(TEXT("ReqChangeEnage"), pMonster_ReqChangeEnage); 
	pMonsterModule->cell_methods.Add(TEXT("ReqChangeEnage"), pMonster_ReqChangeEnage);

	pMonsterModule->idcell_methods.Add(pMonster_ReqChangeEnage->methodUtype, pMonster_ReqChangeEnage);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), method(ReqChangeEnage / 45).");

	TArray<DATATYPE_BASE*> Monster_ReqStartDamage_args;
	Monster_ReqStartDamage_args.Add(EntityDef::id2datatypes[29]);
	Monster_ReqStartDamage_args.Add(EntityDef::id2datatypes[25]);

	Method* pMonster_ReqStartDamage = new Method();
	pMonster_ReqStartDamage->name = TEXT("ReqStartDamage");
	pMonster_ReqStartDamage->methodUtype = 44;
	pMonster_ReqStartDamage->aliasID = -1;
	pMonster_ReqStartDamage->args = Monster_ReqStartDamage_args;

	pMonsterModule->methods.Add(TEXT("ReqStartDamage"), pMonster_ReqStartDamage); 
	pMonsterModule->cell_methods.Add(TEXT("ReqStartDamage"), pMonster_ReqStartDamage);

	pMonsterModule->idcell_methods.Add(pMonster_ReqStartDamage->methodUtype, pMonster_ReqStartDamage);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Monster), method(ReqStartDamage / 44).");

	ScriptModule* pItemDropPackageModule = new ScriptModule("ItemDropPackage", 5);
	EntityDef::moduledefs.Add(TEXT("ItemDropPackage"), pItemDropPackageModule);
	EntityDef::idmoduledefs.Add(5, pItemDropPackageModule);

	Property* pItemDropPackage_position = new Property();
	pItemDropPackage_position->name = TEXT("position");
	pItemDropPackage_position->properUtype = 40000;
	pItemDropPackage_position->properFlags = 4;
	pItemDropPackage_position->aliasID = 1;
	KBVar* pItemDropPackage_position_defval = new KBVar(FVector());
	pItemDropPackage_position->pDefaultVal = pItemDropPackage_position_defval;
	pItemDropPackageModule->propertys.Add(TEXT("position"), pItemDropPackage_position); 

	pItemDropPackageModule->usePropertyDescrAlias = true;
	pItemDropPackageModule->idpropertys.Add((uint16)pItemDropPackage_position->aliasID, pItemDropPackage_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ItemDropPackage), property(position / 40000).");

	Property* pItemDropPackage_direction = new Property();
	pItemDropPackage_direction->name = TEXT("direction");
	pItemDropPackage_direction->properUtype = 40001;
	pItemDropPackage_direction->properFlags = 4;
	pItemDropPackage_direction->aliasID = 2;
	KBVar* pItemDropPackage_direction_defval = new KBVar(FVector());
	pItemDropPackage_direction->pDefaultVal = pItemDropPackage_direction_defval;
	pItemDropPackageModule->propertys.Add(TEXT("direction"), pItemDropPackage_direction); 

	pItemDropPackageModule->usePropertyDescrAlias = true;
	pItemDropPackageModule->idpropertys.Add((uint16)pItemDropPackage_direction->aliasID, pItemDropPackage_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ItemDropPackage), property(direction / 40001).");

	Property* pItemDropPackage_spaceID = new Property();
	pItemDropPackage_spaceID->name = TEXT("spaceID");
	pItemDropPackage_spaceID->properUtype = 40002;
	pItemDropPackage_spaceID->properFlags = 16;
	pItemDropPackage_spaceID->aliasID = 3;
	KBVar* pItemDropPackage_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pItemDropPackage_spaceID->pDefaultVal = pItemDropPackage_spaceID_defval;
	pItemDropPackageModule->propertys.Add(TEXT("spaceID"), pItemDropPackage_spaceID); 

	pItemDropPackageModule->usePropertyDescrAlias = true;
	pItemDropPackageModule->idpropertys.Add((uint16)pItemDropPackage_spaceID->aliasID, pItemDropPackage_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ItemDropPackage), property(spaceID / 40002).");

	Property* pItemDropPackage_dropItems = new Property();
	pItemDropPackage_dropItems->name = TEXT("dropItems");
	pItemDropPackage_dropItems->properUtype = 55;
	pItemDropPackage_dropItems->properFlags = 4;
	pItemDropPackage_dropItems->aliasID = 4;
	pItemDropPackage_dropItems->pDefaultVal = EntityDef::id2datatypes[27]->parseDefaultValStr("");
	pItemDropPackageModule->propertys.Add(TEXT("dropItems"), pItemDropPackage_dropItems); 

	pItemDropPackageModule->usePropertyDescrAlias = true;
	pItemDropPackageModule->idpropertys.Add((uint16)pItemDropPackage_dropItems->aliasID, pItemDropPackage_dropItems);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ItemDropPackage), property(dropItems / 55).");

	Property* pItemDropPackage_ownerDBID = new Property();
	pItemDropPackage_ownerDBID->name = TEXT("ownerDBID");
	pItemDropPackage_ownerDBID->properUtype = 52;
	pItemDropPackage_ownerDBID->properFlags = 4;
	pItemDropPackage_ownerDBID->aliasID = 5;
	KBVar* pItemDropPackage_ownerDBID_defval = new KBVar((uint64)FCString::Atoi64(TEXT("")));
	pItemDropPackage_ownerDBID->pDefaultVal = pItemDropPackage_ownerDBID_defval;
	pItemDropPackageModule->propertys.Add(TEXT("ownerDBID"), pItemDropPackage_ownerDBID); 

	pItemDropPackageModule->usePropertyDescrAlias = true;
	pItemDropPackageModule->idpropertys.Add((uint16)pItemDropPackage_ownerDBID->aliasID, pItemDropPackage_ownerDBID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ItemDropPackage), property(ownerDBID / 52).");

	pItemDropPackageModule->useMethodDescrAlias = true;
	ScriptModule* pOreModule = new ScriptModule("Ore", 6);
	EntityDef::moduledefs.Add(TEXT("Ore"), pOreModule);
	EntityDef::idmoduledefs.Add(6, pOreModule);

	Property* pOre_position = new Property();
	pOre_position->name = TEXT("position");
	pOre_position->properUtype = 40000;
	pOre_position->properFlags = 4;
	pOre_position->aliasID = 1;
	KBVar* pOre_position_defval = new KBVar(FVector());
	pOre_position->pDefaultVal = pOre_position_defval;
	pOreModule->propertys.Add(TEXT("position"), pOre_position); 

	pOreModule->usePropertyDescrAlias = true;
	pOreModule->idpropertys.Add((uint16)pOre_position->aliasID, pOre_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Ore), property(position / 40000).");

	Property* pOre_direction = new Property();
	pOre_direction->name = TEXT("direction");
	pOre_direction->properUtype = 40001;
	pOre_direction->properFlags = 4;
	pOre_direction->aliasID = 2;
	KBVar* pOre_direction_defval = new KBVar(FVector());
	pOre_direction->pDefaultVal = pOre_direction_defval;
	pOreModule->propertys.Add(TEXT("direction"), pOre_direction); 

	pOreModule->usePropertyDescrAlias = true;
	pOreModule->idpropertys.Add((uint16)pOre_direction->aliasID, pOre_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Ore), property(direction / 40001).");

	Property* pOre_spaceID = new Property();
	pOre_spaceID->name = TEXT("spaceID");
	pOre_spaceID->properUtype = 40002;
	pOre_spaceID->properFlags = 16;
	pOre_spaceID->aliasID = 3;
	KBVar* pOre_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pOre_spaceID->pDefaultVal = pOre_spaceID_defval;
	pOreModule->propertys.Add(TEXT("spaceID"), pOre_spaceID); 

	pOreModule->usePropertyDescrAlias = true;
	pOreModule->idpropertys.Add((uint16)pOre_spaceID->aliasID, pOre_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Ore), property(spaceID / 40002).");

	Property* pOre_digCount = new Property();
	pOre_digCount->name = TEXT("digCount");
	pOre_digCount->properUtype = 58;
	pOre_digCount->properFlags = 4;
	pOre_digCount->aliasID = 4;
	KBVar* pOre_digCount_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pOre_digCount->pDefaultVal = pOre_digCount_defval;
	pOreModule->propertys.Add(TEXT("digCount"), pOre_digCount); 

	pOreModule->usePropertyDescrAlias = true;
	pOreModule->idpropertys.Add((uint16)pOre_digCount->aliasID, pOre_digCount);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Ore), property(digCount / 58).");

	Property* pOre_oreID = new Property();
	pOre_oreID->name = TEXT("oreID");
	pOre_oreID->properUtype = 57;
	pOre_oreID->properFlags = 4;
	pOre_oreID->aliasID = 5;
	KBVar* pOre_oreID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pOre_oreID->pDefaultVal = pOre_oreID_defval;
	pOreModule->propertys.Add(TEXT("oreID"), pOre_oreID); 

	pOreModule->usePropertyDescrAlias = true;
	pOreModule->idpropertys.Add((uint16)pOre_oreID->aliasID, pOre_oreID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Ore), property(oreID / 57).");

	pOreModule->useMethodDescrAlias = true;
}

void EntityDef::initDefTypes()
{
	{
		uint16 utype = 2;
		FString typeName = TEXT("BOOL");
		FString name = TEXT("UINT8");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 3;
		FString typeName = TEXT("UINT16");
		FString name = TEXT("UINT16");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 5;
		FString typeName = TEXT("UINT64");
		FString name = TEXT("UINT64");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 4;
		FString typeName = TEXT("UINT32");
		FString name = TEXT("UINT32");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 6;
		FString typeName = TEXT("INT8");
		FString name = TEXT("INT8");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 7;
		FString typeName = TEXT("INT16");
		FString name = TEXT("INT16");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 8;
		FString typeName = TEXT("ENTITY_ID");
		FString name = TEXT("INT32");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 9;
		FString typeName = TEXT("INT64");
		FString name = TEXT("INT64");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 1;
		FString typeName = TEXT("STRING");
		FString name = TEXT("STRING");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 12;
		FString typeName = TEXT("UNICODE");
		FString name = TEXT("UNICODE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 13;
		FString typeName = TEXT("FLOAT");
		FString name = TEXT("FLOAT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 14;
		FString typeName = TEXT("DOUBLE");
		FString name = TEXT("DOUBLE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PYTHON");
		FString name = TEXT("PYTHON");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_DICT");
		FString name = TEXT("PY_DICT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_TUPLE");
		FString name = TEXT("PY_TUPLE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_LIST");
		FString name = TEXT("PY_LIST");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 20;
		FString typeName = TEXT("ENTITYCALL");
		FString name = TEXT("ENTITYCALL");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 11;
		FString typeName = TEXT("BLOB");
		FString name = TEXT("BLOB");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 15;
		FString typeName = TEXT("VECTOR2");
		FString name = TEXT("VECTOR2");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 16;
		FString typeName = TEXT("VECTOR3");
		FString name = TEXT("VECTOR3");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 17;
		FString typeName = TEXT("VECTOR4");
		FString name = TEXT("VECTOR4");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 22;
		FString typeName = TEXT("STRING_LIST");
		DATATYPE_STRING_LIST* pDatatype = new DATATYPE_STRING_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 23;
		FString typeName = TEXT("UINT16_LIST");
		DATATYPE_UINT16_LIST* pDatatype = new DATATYPE_UINT16_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 24;
		FString typeName = TEXT("UINT64_LIST");
		DATATYPE_UINT64_LIST* pDatatype = new DATATYPE_UINT64_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 25;
		FString typeName = TEXT("ENTITY_LIST");
		DATATYPE_ENTITY_LIST* pDatatype = new DATATYPE_ENTITY_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 26;
		FString typeName = TEXT("ITEM");
		DATATYPE_ITEM* pDatatype = new DATATYPE_ITEM();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 27;
		FString typeName = TEXT("ITEM_LIST");
		DATATYPE_ITEM_LIST* pDatatype = new DATATYPE_ITEM_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 28;
		FString typeName = TEXT("CHAT_INFO");
		DATATYPE_CHAT_INFO* pDatatype = new DATATYPE_CHAT_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 29;
		FString typeName = TEXT("SKILL_INFO");
		DATATYPE_SKILL_INFO* pDatatype = new DATATYPE_SKILL_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 30;
		FString typeName = TEXT("AVATAR_BRIEF_INFO");
		DATATYPE_AVATAR_BRIEF_INFO* pDatatype = new DATATYPE_AVATAR_BRIEF_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 31;
		FString typeName = TEXT("AVATAR_BRIEF_INFO_LIST");
		DATATYPE_AVATAR_BRIEF_INFO_LIST* pDatatype = new DATATYPE_AVATAR_BRIEF_INFO_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 32;
		FString typeName = TEXT("ANIM_INFO");
		DATATYPE_ANIM_INFO* pDatatype = new DATATYPE_ANIM_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	for(auto& Elem : EntityDef::datatypes)
	{
		if(Elem.Value)
		{
			Elem.Value->bind();
		}
	}
}


}