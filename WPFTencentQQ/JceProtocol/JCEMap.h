#pragma once
#include "jceiobject.h"
#include"JCEString.h"
#include<map>

//仅仅支持key为JCEString的map
namespace JCE
{
	class JCEMap :
		public IObject
	{
	public:

		JCEMap(void)
		{
		}

		virtual ~JCEMap(void)
		{
			std::map<JCE::IObject*,JCE::IObject*>::iterator iter = _value.begin();
			while(iter != _value.end()) //#1 
			{
			  //注意要先释放内存，在删除map元素，顺序不能颠倒。
			   //释放内存
			 delete iter->second;
			 iter->second = NULL;
			 //删除map元素
			 _value.erase(iter++); //#1
			}
		}
	public:
		std::map<JCE::IObject*,JCE::IObject*> _value;
	public:
		unsigned int type(){return JCETypeJCEMap;};
	};
}

