#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CJceStruct_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CJceStruct_API __declspec(dllimport)
#endif


#include"JceInputStream.h"
#include"JceOutputStream.h"
#include"JCEIObject.h"
#include "JCEType.h"

namespace JCE
{
	class DIPPEREXPORTS_CJceStruct_API  CJceStruct:public JCE::IObject
	{
	public:
		CJceStruct(void)
		{
		}
		virtual ~CJceStruct(void)
		{
		}
	public:
		virtual void readFrom(CJceInputStream &paramJceInputStream)=0;
		virtual void writeTo(CJceOutputStream &paramJceInputStream)=0;
	public:
		unsigned int type(){return JCETypeJCEStruct;};
	};
}

