/*
	Generated by KBEngine!
	Please do not modify this file!
	Please inherit this module, such as: (class Skill : public SkillBase)
	tools = kbcmd
*/

#pragma once
#include "KBECommon.h"
#include "Entity.h"
#include "KBETypes.h"
#include "EntityCallSkillBase.h"

namespace KBEngine
{

class Method;
class Property;
class MemoryStream;

// defined in */scripts/entity_defs/Skill.def
	// Please inherit and implement "class Skill : public SkillBase"
class KBENGINEPLUGINS_API SkillBase : public Entity
{
public:
	EntityBaseEntityCall_SkillBase* pBaseEntityCall;
	EntityCellEntityCall_SkillBase* pCellEntityCall;

	uint8 skillId;
	virtual void onSkillIdChanged(uint8 oldValue) {}


	void onComponentsEnterworld() override;
	void onComponentsLeaveworld() override;

	void onGetBase() override;
	void onGetCell() override;
	void onLoseCell() override;

	EntityCall* getBaseEntityCall() override;
	EntityCall* getCellEntityCall() override;


	void onRemoteMethodCall(MemoryStream& stream) override;
	void onUpdatePropertys(MemoryStream& stream) override;
	void callPropertysSetMethods() override;

	SkillBase();
	virtual ~SkillBase();

	void attachComponents() override;
	void detachComponents() override;

};

}