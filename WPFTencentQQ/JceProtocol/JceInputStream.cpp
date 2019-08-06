#include "StdAfx.h"
#include "JceInputStream.h"
#include "JCEChar.h"
#include "JCEShort.h"
#include "JCEInt.h"
#include "JCELong.h"
#include "JCEByteArray.h"
#include "JCEString.h"
#include "JceStruct.h"
#include "JCEListArray.h"
#include "JCEBoolean.h"

CJceInputStream::CJceInputStream(void)
{
}

CJceInputStream::~CJceInputStream(void)
{
}

CJceInputStream::CJceInputStream(ByteBuffer paramByteBuffer)
{
	this->bs=paramByteBuffer;
}

CJceInputStream::CJceInputStream(JCE::JCEByteArray paramArrayOfByte)
{
	this->bs.clear();
	this->bs=paramArrayOfByte.value();
}

CJceInputStream::CJceInputStream(JCE::JCEByteArray paramArrayOfByte,int paramInt)
{
	this->bs.clear();
	this->bs=paramArrayOfByte.value();
	this->bs.rpos(paramInt);
}

unsigned int CJceInputStream::peakType()
{
	ByteBuffer bt=bs;
	CHeadData mHeadData;
	int i = bt.read<char>();
    mHeadData.type = ((char)(i & 0xF));
    mHeadData.tag = ((i & 0xF0) >> 4);
    if (mHeadData.tag == 15)
    {
		mHeadData.tag = (0xFF & bs.read<char>());
    }
	switch(mHeadData.type)
	{
	case 0:
		{
			return JCETypeJCEChar;
		}break;
	case 1:
		{
			return JCETypeJCEShort;
		}break;
	case 2:
		{
			return JCETypeJCEInt;
		}break;
	case 3:
		{
			return JCETypeJCELong;
		}break;
	case 4:
	case 5:
		{
			//float,double
		}break;
	case 6:
		{
			return JCETypeJCEString;
		}break;
	case 7:
		{
		}break;
	case 8:
		{
			return JCETypeJCEMap;
		}break;
	case 9:
		{
			return JCETypeJCEListArray;
		}break;
	case 10:
		{
			return JCETypeJCEStruct;
		}break;
	case 13:
		{
			return JCETypeJCEByteArray;
		}break;
	}
	return JCETypeJCEIObject;
}

int CJceInputStream::peakHead(CHeadData &paramHeadData)
{
	ByteBuffer bstmp=bs;
	return readHead(paramHeadData, bstmp);
}

void CJceInputStream::readHead(CHeadData &paramHeadData)
{
	readHead(paramHeadData, bs);
}

int CJceInputStream::readHead(CHeadData &paramHeadData, ByteBuffer &paramByteBuffer)
{
	int i = paramByteBuffer.read<char>();
    paramHeadData.type = ((char)(i & 0xF));
    paramHeadData.tag = ((i & 0xF0) >> 4);
    if (paramHeadData.tag == 15)
    {
		paramHeadData.tag = (0xFF & paramByteBuffer.read<char>());
      return 2;
    }
    return 1;
}

void CJceInputStream::skip(int paramInt)
{
	bs.mpos(paramInt);
}

void CJceInputStream::skipField()
{
	CHeadData localHeadData;
    readHead(localHeadData);
    skipField(localHeadData.type);
}

void CJceInputStream::skipToStructEnd()
{
	CHeadData localHeadData;
    do
    {
      readHead(localHeadData);
      skipField(localHeadData.type);
    }
    while (localHeadData.type != 11);
}

bool CJceInputStream::skipToTag(int paramInt)
{
	CHeadData localHeadData;
    while (true)
	{
		int i = peakHead(localHeadData);
        if (localHeadData.type == 11)
          return false;
        if (paramInt <= localHeadData.tag)
        {
          if (paramInt != localHeadData.tag)
            break;
          return true;
        }
        skip(i);
        skipField(localHeadData.type);
	}
    return false;
}

void CJceInputStream::skipField(char paramByte)
{
	switch(paramByte)
	{
	case 0:
		skip(1);
		break;
	case 1:
		skip(2);
		break;
	case 2:
		skip(4);
		break;
	case 3:
		skip(8);
		break;
	case 4:
		skip(4);
		break;
	case 5:
		skip(8);
		break;
	case 6:
		{
			int n = bs.read<char>();
			if (n < 0)
				n += 256;
			skip(n);
		}break;
	case 7:
		skip(bs.read<int>());
		break;
	case 8:
		{
			int k = readInt(0, true);
			int m=k * 2;
			if(m<0)
				return;
			skipField();
		}break;
	case 9:
		{
			int i = readInt(0, true);
			 if(i<0)
				 return;
			skipField();
		}break;
	case 10:
		{
			skipToStructEnd();
		}break;
	case 11:
	case 12:
		return;
	case 13:
		{
			CHeadData localHeadData;
			readHead(localHeadData);
			if (localHeadData.type != 0)
				return;
			skip(readInt(0, true));
		}break;
	}
}

void CJceInputStream::readByteArray(JCE::JCEByteArray &object, int paramInt, bool paramBoolean)
{
    if (skipToTag(paramInt))
    {
		CHeadData localHeadData;
		readHead(localHeadData);
		switch (localHeadData.type)
      {
      case 13:
		  {
			CHeadData localHeadData2;
			readHead(localHeadData2);
			if (localHeadData2.type != 0)
				return;
			JCE::JCEInt k(0);
			read(&k,0,true);
			if (k.value() < 0)
			  return;
			char *arrayOfByte = new char[k.value()];
			bs.read((uint8*)arrayOfByte,k.value());
			ByteBuffer buf;
			buf.append(arrayOfByte,k.value());
			object.value(buf);
			delete []arrayOfByte;
		  }break;
	  }
    }
}

std::string CJceInputStream::readString(int paramInt, bool paramBoolean)
{
	std::string paramString;
	char *arrayOfByte=NULL;
    if (skipToTag(paramInt))
    {
		CHeadData localHeadData;
		readHead(localHeadData);
		switch (localHeadData.type)
		{
		case 6:
			{
				int j = bs.read<char>();
				if (j < 0)
					j += 256;
			arrayOfByte = new char[j+1];
			bs.read((unsigned char*)arrayOfByte,j);
			arrayOfByte[j]=0;
			}break;
		case 7:
			{
				int j = bs.reverse(bs.read<int>());
				if (j < 0)
					j += 256;
			arrayOfByte = new char[j+1];
			bs.read((unsigned char*)arrayOfByte,j);
			arrayOfByte[j]=0;
			}break;
		}
	}
	if(arrayOfByte!=NULL)
		paramString=arrayOfByte;
	return paramString;
}

bool CJceInputStream::readBool(int paramInt, bool paramBoolean2)
{
	int i = readChar(paramInt, paramBoolean2);
    bool b = false;
    if (i != 0)
      b = true;
    return b;
}

short CJceInputStream::readShort(int paramInt, bool paramBoolean)
{
	short paramShort=0;
	if (skipToTag(paramInt))             //true表示存在此字段数据
    {
		CHeadData localHeadData;
		readHead(localHeadData);
		switch (localHeadData.type)
		{
		case 12:
			{
				paramShort=0;
			}break;
		case 0:
			{
				paramShort=(short)bs.reverse(bs.read<unsigned char>());
			}break;
		case 1:
			{
				paramShort=bs.reverse(bs.read<short>());
			 }break;
		 }
    }
	return paramShort;
}

int CJceInputStream::readInt(int paramInt2,bool paramBoolean)
{
	int paramInt1=0;
	if (skipToTag(paramInt2))             //true表示存在此字段数据
    {
		CHeadData localHeadData;
		readHead(localHeadData);
		switch (localHeadData.type)
      {
      case 12:
		  {
			paramInt1=0;
		  }break;
	  case 0:
		  {
			  paramInt1=(int)bs.reverse(bs.read<unsigned char>());
		  }break;
	  case 1:
		  {
			  paramInt1=(int)bs.reverse(bs.read<unsigned short>());
		  }break;
      case 2:
		  {
			  paramInt1=bs.reverse(bs.read<int>());
		  }break;
      }
    }
	return paramInt1;
}

__int64 CJceInputStream::readLong(int paramInt, bool paramBoolean2 )
{
	__int64 paramlong=0;
	if (skipToTag(paramInt))             //true表示存在此字段数据
    {
		CHeadData localHeadData;
		readHead(localHeadData);
		switch (localHeadData.type)
      {
      default:
		  break;
      case 12:
		  {
			paramlong=0;
		  }break;
	  case 0:
		  {
			  paramlong=(__int64)bs.reverse(bs.read<unsigned char>());
		  }break;
	  case 1:
		  {
			  paramlong=(__int64)bs.reverse(bs.read<unsigned short>());
		  }break;
      case 2:
		  {
			  paramlong=(__int64)bs.reverse(bs.read<unsigned int>());
		  }break;
      case 3:
		  {
			  paramlong=bs.reverse(bs.read<__int64>());
		  }break;
      }
    }
    return paramlong;
}

char CJceInputStream::readChar(int paramInt, bool paramBoolean)
{
	char paramByte=0;
	if (skipToTag(paramInt))             //true表示存在此字段数据
    {
		CHeadData localHeadData;
		readHead(localHeadData);
		switch (localHeadData.type)
     {
      case 12:
		  {
			  paramByte=0;
		  }break;
      case 0:
		  {
			  paramByte=bs.read<char>();
		  }break;
      }
    }
	return paramByte;
}

double CJceInputStream::readDouble(int paramInt, bool paramBoolean)
{
	double paramDouble=0;
	if (skipToTag(paramInt))
    {
      CHeadData localHeadData;
      readHead(localHeadData);
      switch (localHeadData.type)
      {
      default:
		break;
      case 12:
		  {
			  paramDouble = 0.0;
		  }break;
	  case 4:
		  {
			  paramDouble=(double)bs.read<float>();
		  }break;
      case 5:
		  {
			  paramDouble=bs.read<double>();
		  }break;
      }
    }
	return paramDouble;
}

float CJceInputStream::readFloat(int paramInt, bool paramBoolean)
{
	float paramFloat=0.0;
	if (skipToTag(paramInt))
    {
      CHeadData localHeadData;
      readHead(localHeadData);
      switch (localHeadData.type)
      {
      default:
		break;
      case 12:
		  {
			  paramFloat = 0.0;
		  }break;
      case 4:
		  {
			  paramFloat=bs.read<float>();
		  }break;
      }
    }
	return paramFloat;
}

void CJceInputStream::readStruct(JCE::IObject *paramJceStruct, int paramInt, bool paramBoolean)
{
	JCE::CJceStruct *p=dynamic_cast<JCE::CJceStruct *>(paramJceStruct);
	if (skipToTag(paramInt))             //true表示存在此字段数据
    {
		CHeadData localHeadData;
		readHead(localHeadData);
		if(localHeadData.type!=10)
		{
			return;
		}
		p->readFrom(*this);
		readHead(localHeadData);
		if(localHeadData.type!=11)
		{
			return;
		}
    }
}

ByteBuffer CJceInputStream::getBs()
{
	return bs;
}

void CJceInputStream::setServerEncoding(std::string paramString)
{
	sServerEncoding=paramString;
}

void CJceInputStream::wrap(unsigned char* paramArrayOfByte,unsigned int cnt)
{
	bs.clear();
	bs.append(paramArrayOfByte,cnt);
}

JCE::IObject *CJceInputStream::ObjectAlloc(unsigned int mType)
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
	case JCETypeJCEStruct:
		object=NULL;//问题
		break;
	case JCETypeJCEMap:
		object=new JCE::JCEMap();
		break;
	case JCETypeJCEListArray:
		object=new JCE::JCEListArray();
		break;
	}
	return object;
}

void CJceInputStream::read(JCE::IObject *object, int paramInt, bool paramBoolean)
{
	switch(object->type())
	{
	case JCETypeJCEBoolean:
		{
			JCE::JCEBoolean *p=static_cast<JCE::JCEBoolean*>(object);
			p->value(readBool(paramInt,paramBoolean));
		}break;
	case JCETypeJCEChar:
		{
			JCE::JCEChar *p=static_cast<JCE::JCEChar*>(object);
			p->value(readChar(paramInt,paramBoolean));
		}break;
	case JCETypeJCEShort:
		{
			JCE::JCEShort *p=static_cast<JCE::JCEShort*>(object);
			p->value(readShort(paramInt,paramBoolean));
		}break;
	case JCETypeJCEInt:
		{
			JCE::JCEInt *p=static_cast<JCE::JCEInt*>(object);
			p->value(readInt(paramInt,paramBoolean));
		}break;
	case JCETypeJCELong:
		{
			JCE::JCELong *p=static_cast<JCE::JCELong*>(object);
			p->value(readLong(paramInt,paramBoolean));
		}break;
	case JCETypeJCEByteArray:
		{
			JCE::JCEByteArray *p=static_cast<JCE::JCEByteArray*>(object);
			readByteArray(*p,paramInt,paramBoolean);
		}break;
	case JCETypeJCEString:
		{
			JCE::JCEString *p=static_cast<JCE::JCEString*>(object);
			p->value(readString(paramInt,paramBoolean));
		}break;
	case JCETypeJCEStruct:
		{
			readStruct(object,paramInt,paramBoolean);
		}break;
	case JCETypeJCEMap:
		{
			
			readMap(*static_cast<JCE::JCEMap*>(object),paramInt,paramBoolean);
		}break;
	case JCETypeJCEListArray:
		{
			readList(*static_cast<JCE::JCEListArray*>(object),paramInt,paramBoolean);
		}break;
	default:
		readStruct(object,paramInt,paramBoolean);
		break;
	}
}

void CJceInputStream::readList(JCE::JCEListArray &paramList,int paramInt,bool paramBoolean)
{
	//先取出数目
	JCE::JCEInt size=0;
	if (skipToTag(paramInt))
    {
      CHeadData localHeadData;
      readHead(localHeadData);
      switch (localHeadData.type)
	  {
	  case 9:
		  {
			  read(&size, 0, true);
			  if (size.value()< 0)
				  return;
			  unsigned int mValueType=0;
			  if(paramList._value.size()==1)
			  {
				  mValueType=(*paramList._value.begin())->type();
				  delete *paramList._value.begin();
				  paramList._value.clear();
			  }
			  for(int j=0;j<size.value();j++)
			 {
				JCE::IObject *mValue=ObjectAlloc(peakType());
				if(mValue==NULL)
				{
					//复合数据类型
					if(mValueType!=0)
					{
						mValue=ObjectAlloc(mValueType);
						if(mValue!=NULL)
						{
							read(mValue,0,true);
							paramList._value.push_back(mValue);
						}
					}else
					{
						MessageBox(NULL,"list error","jce error",MB_OK);
						return;
					}

				}else
				{
					read(mValue,0,true);
					paramList._value.push_back(mValue);
				}
			 }
		  }break;
	  }
	}

}

void CJceInputStream::readMap(JCE::JCEMap &mMap,int paramInt,bool paramBoolean)
{
	if(!skipToTag(paramInt))
		return;
	CHeadData localHeadData;
	readHead(localHeadData);
	switch(localHeadData.type)
	{
	case 8:
		{
			JCE::JCEInt i(0);
			read(&i,0,true);      //size
			if (i.value() < 0)
				return;
			for(int j=0;j<i.value();j++)
			{
				JCE::IObject *mKey=ObjectAlloc(peakType());;
				read(mKey,0,true);
				JCE::IObject *mValue=ObjectAlloc(peakType());
				read(mValue,1,true);
				mMap._value.insert(std::pair<JCE::IObject*,JCE::IObject*>(mKey,mValue));
			}
		}break;
	}
}