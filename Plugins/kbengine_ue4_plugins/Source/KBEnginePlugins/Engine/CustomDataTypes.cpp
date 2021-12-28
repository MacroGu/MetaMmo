#include "CustomDataTypes.h"
#include "EntityDef.h"
#include "KBDebug.h"
#include "DataTypes.h"
#include "Runtime/Core/Public/Misc/Variant.h"

namespace KBEngine
{

void DATATYPE_STRING_LIST::createFromStreamEx(MemoryStream& stream, STRING_LIST& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		datas.Add(stream.readUint16());
	};

}

void DATATYPE_STRING_LIST::addToStreamEx(Bundle& stream, const STRING_LIST& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		stream.writeUint16(v[i]);
	};
}

void DATATYPE_UINT16_LIST::createFromStreamEx(MemoryStream& stream, UINT16_LIST& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		datas.Add(stream.readUint16());
	};

}

void DATATYPE_UINT16_LIST::addToStreamEx(Bundle& stream, const UINT16_LIST& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		stream.writeUint16(v[i]);
	};
}

void DATATYPE_UINT64_LIST::createFromStreamEx(MemoryStream& stream, UINT64_LIST& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		datas.Add(stream.readUint64());
	};

}

void DATATYPE_UINT64_LIST::addToStreamEx(Bundle& stream, const UINT64_LIST& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		stream.writeUint64(v[i]);
	};
}

void DATATYPE_ENTITY_LIST::createFromStreamEx(MemoryStream& stream, ENTITY_LIST& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		datas.Add(stream.readInt32());
	};

}

void DATATYPE_ENTITY_LIST::addToStreamEx(Bundle& stream, const ENTITY_LIST& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		stream.writeInt32(v[i]);
	};
}

void DATATYPE_ITEM::createFromStreamEx(MemoryStream& stream, ITEM& datas)
{
	datas.uid = stream.readUint64();
	datas.id = stream.readUint32();
	datas.num = stream.readUint32();
	datas.bagIndex = stream.readUint16();
}

void DATATYPE_ITEM::addToStreamEx(Bundle& stream, const ITEM& v)
{
	stream.writeUint64(v.uid);
	stream.writeUint32(v.id);
	stream.writeUint32(v.num);
	stream.writeUint16(v.bagIndex);
}

void DATATYPE_ITEM_LIST::createFromStreamEx(MemoryStream& stream, ITEM_LIST& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		ITEM childDatas;
		itemType.createFromStreamEx(stream, childDatas);
		datas.Add(childDatas);
	};

}

void DATATYPE_ITEM_LIST::addToStreamEx(Bundle& stream, const ITEM_LIST& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		itemType.addToStreamEx(stream, v[i]);
	};
}

void DATATYPE_CHAT_INFO::createFromStreamEx(MemoryStream& stream, CHAT_INFO& datas)
{
	datas.dbid = stream.readUint64();
	datas.targetDBID = stream.readUint64();
	datas.chatType = stream.readUint8();
	datas.sceneID = stream.readUint32();
	datas.name = stream.readUnicode();
	datas.chatContent = stream.readUnicode();
}

void DATATYPE_CHAT_INFO::addToStreamEx(Bundle& stream, const CHAT_INFO& v)
{
	stream.writeUint64(v.dbid);
	stream.writeUint64(v.targetDBID);
	stream.writeUint8(v.chatType);
	stream.writeUint32(v.sceneID);
	stream.writeUnicode(v.name);
	stream.writeUnicode(v.chatContent);
}

void DATATYPE_SKILL_INFO::createFromStreamEx(MemoryStream& stream, SKILL_INFO& datas)
{
	datas.skillId = stream.readUint8();
	datas.spawnPos = stream.readVector3();
	datas.targetPos = stream.readVector3();
}

void DATATYPE_SKILL_INFO::addToStreamEx(Bundle& stream, const SKILL_INFO& v)
{
	stream.writeUint8(v.skillId);
	stream.writeVector3(v.spawnPos);
	stream.writeVector3(v.targetPos);
}

void DATATYPE_AVATAR_BRIEF_INFO::createFromStreamEx(MemoryStream& stream, AVATAR_BRIEF_INFO& datas)
{
	datas.dbid = stream.readUint64();
	datas.sex = stream.readUint8();
	datas.name = stream.readUnicode();
	datas.facade = stream.readBlob();
}

void DATATYPE_AVATAR_BRIEF_INFO::addToStreamEx(Bundle& stream, const AVATAR_BRIEF_INFO& v)
{
	stream.writeUint64(v.dbid);
	stream.writeUint8(v.sex);
	stream.writeUnicode(v.name);
	stream.writeBlob(v.facade);
}

void DATATYPE_AVATAR_BRIEF_INFO_LIST::createFromStreamEx(MemoryStream& stream, AVATAR_BRIEF_INFO_LIST& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		AVATAR_BRIEF_INFO childDatas;
		itemType.createFromStreamEx(stream, childDatas);
		datas.Add(childDatas);
	};

}

void DATATYPE_AVATAR_BRIEF_INFO_LIST::addToStreamEx(Bundle& stream, const AVATAR_BRIEF_INFO_LIST& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		itemType.addToStreamEx(stream, v[i]);
	};
}

void DATATYPE_ANIM_INFO::createFromStreamEx(MemoryStream& stream, ANIM_INFO& datas)
{
	datas.Speed = stream.readFloat();
	datas.Direction = stream.readFloat();
}

void DATATYPE_ANIM_INFO::addToStreamEx(Bundle& stream, const ANIM_INFO& v)
{
	stream.writeFloat(v.Speed);
	stream.writeFloat(v.Direction);
}


}