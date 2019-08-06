#include "StdAfx.h"
#include "JceOutputStream.h"
#include"JCEBoolean.h"
#include"JCEChar.h"
#include"JCEShort.h"
#include"JCEInt.h"
#include"JCELong.h"
#include"JceStruct.h"
#include"JCEMap.h"


CJceOutputStream::CJceOutputStream(void)
{
}


CJceOutputStream::~CJceOutputStream(void)
{
}

ByteBuffer CJceOutputStream::getByteBuffer()
{
	return this->bs;
}

void CJceOutputStream::setServerEncoding(std::string paramString)
{
	this->sServerEncoding=paramString;
}

void CJceOutputStream::writeHead(char paramByte, int paramInt)
{
	 if (paramInt < 15)
    {
      char b2 = (char)(paramByte | paramInt << 4);
	  bs.append(b2);
      return;
    }
    if (paramInt < 256)
    {
      char b1 = (char)(paramByte | 0xF0);
	  bs.append(b1);
	  bs.append((char)paramInt);
      return;
    }
}

void CJceOutputStream::writeBool(bool paramBoolean, int paramInt)
{
	if(paramBoolean)
	{
		writeChar(1,paramInt);
	}else
	{
		writeChar(0,paramInt);
	}
}

void CJceOutputStream::writeChar(char paramByte, int paramInt)
{
    if (paramByte == 0)
    {
      writeHead((char)12, paramInt);
      return;
    }
    writeHead((char)0, paramInt);
	bs.append(paramByte);
}

void CJceOutputStream::writeShort(short paramShort, int paramInt)
{
    if ((paramShort >= char(-128)) && (paramShort <= char(127)))
    {
      writeChar((char)paramShort, paramInt);
      return;
    }
    writeHead((char)1, paramInt);
	bs.append(bs.reverse(paramShort));
}

void CJceOutputStream::writeInt(int paramInt1, int paramInt2)
{
    if ((paramInt1 >= short(-32768)) && (paramInt1 <= short(32767)))
    {
      writeShort((short)paramInt1, paramInt2);
      return;
    }
    writeHead((char)2, paramInt2);
	bs.append(bs.reverse(paramInt1));
}

void CJceOutputStream::writeLong(__int64 paramLong, int paramInt)
{
    if ((paramLong >= int(-2147483648)) && (paramLong <= int(2147483647)))
    {
      writeInt((int)paramLong, paramInt);
      return;
    }
    writeHead((char)3, paramInt);
	bs.append(bs.reverse(paramLong));
}

void CJceOutputStream::writeString(std::string paramString,int paramInt)
{
	if (paramString.size()> 255)
    {
      writeHead((char)7, paramInt);
	  bs.append<int>(bs.reverse(paramString.size()));
	  bs.append(paramString.c_str(),paramString.size());
      return;
    }
    writeHead((char)6, paramInt);
	bs.append((char)paramString.size());
	bs.append(paramString.c_str(),paramString.size());
}

void CJceOutputStream::writeStruct(JCE::IObject *paramJceStruct, int paramInt)
{
	JCE::CJceStruct *p=dynamic_cast<JCE::CJceStruct *>(paramJceStruct);
    writeHead((char)10, paramInt);
    p->writeTo(*this);
    writeHead((char)11, 0);
}

void CJceOutputStream::writeByteArray(JCE::JCEByteArray& paramArrayOfByte,int paramInt)
{
    writeHead((char)13, paramInt);
    writeHead((char)0, 0);
	writeShort(paramArrayOfByte.value().size(), 0);
	bs.append(paramArrayOfByte.value().contents(),paramArrayOfByte.value().size());
}

void CJceOutputStream::writeList(JCE::JCEListArray &paramList,unsigned int mType,int paramInt)
{
    writeHead((char)9, paramInt);
	writeChar(paramList._value.size(), 0);

	std::list<JCE::IObject*>::iterator iter;
	for(iter=paramList._value.begin();iter!=paramList._value.end();iter++)
	{
		write(*iter, 0);
	}
}

void CJceOutputStream::writeMap(JCE::JCEMap &mMap,unsigned int tVaule,int paramInt)
{
	writeHead((char)8, paramInt);
	writeChar((char)mMap._value.size(),0);

	std::map<JCE::IObject*,JCE::IObject*>::iterator iter;
	for(iter=mMap._value.begin();iter!=mMap._value.end();iter++)
	{
		write(iter->first,0);
		write(iter->second,1);
	}
}

void CJceOutputStream::write(JCE::IObject *object, int paramInt)
{
	switch(object->type())
	{
	case JCETypeJCEBoolean:
		{
			JCE::JCEBoolean *p=static_cast<JCE::JCEBoolean*>(object);
			writeBool(p->value(),paramInt);
		}break;
	case JCETypeJCEChar:
		{
			JCE::JCEChar *p=static_cast<JCE::JCEChar*>(object);
			writeChar(p->value(),paramInt);
		}break;
	case JCETypeJCEShort:
		{
			JCE::JCEShort *p=static_cast<JCE::JCEShort*>(object);
			writeShort(p->value(),paramInt);
		}break;
	case JCETypeJCEInt:
		{
			JCE::JCEInt *p=static_cast<JCE::JCEInt*>(object);
			writeInt(p->value(),paramInt);
		}break;
	case JCETypeJCELong:
		{
			JCE::JCELong *p=static_cast<JCE::JCELong*>(object);
			writeLong(p->value(),paramInt);
		}break;
	case JCETypeJCEByteArray:
		{
			JCE::JCEByteArray *p=static_cast<JCE::JCEByteArray*>(object);
			writeByteArray(*p,paramInt);
		}break;
	case JCETypeJCEString:
		{
			JCE::JCEString *p=static_cast<JCE::JCEString*>(object);
			writeString(p->value(),paramInt);
		}break;
	case JCETypeJCEStruct:
		{
			JCE::CJceStruct *p=static_cast<JCE::CJceStruct*>(object);
			writeStruct(p,paramInt);
		}break;
	case JCETypeJCEListArray:
		{
			JCE::JCEListArray *p=static_cast<JCE::JCEListArray*>(object);
			writeList(*p,0,paramInt);
		}break;
	case JCETypeJCEMap:
		{
			JCE::JCEMap *p=static_cast<JCE::JCEMap*>(object);
			writeMap(*p,0,paramInt);
		}break;
	default:
		{
			JCE::CJceStruct *p=static_cast<JCE::CJceStruct*>(object);
			writeStruct(p,paramInt);
		}
		break;
	}
}

JCE::IObject *CJceOutputStream::ObjectAlloc(unsigned int mType)
{
	JCE::IObject *object=NULL;
	switch(mType)
	{
	case JCETypeJCEChar:
		object=new JCE::JCEChar();
		break;
	case JCETypeJCEShort:
		object=new JCE::JCEShort();
		break;
	case JCETypeJCEInt:
		object=new JCE::JCEInt();
		break;
	case JCETypeJCELong:
		object=new JCE::JCELong();
		break;
	case JCETypeJCEByteArray:
		object=new JCE::JCEByteArray();
		break;
	case JCETypeJCEString:
		object=new JCE::JCEString();
		break;
	case JCETypeJCEMap:
		object=new JCE::JCEMap();
		break;
	case JCETypeJCEListArray:
		object=new JCE::JCEListArray();
		break;
	case JCETypeJCEStruct:
		object=NULL;
		break;
	}
	return object;
}