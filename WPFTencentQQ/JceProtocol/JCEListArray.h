#pragma once
#include "jceiobject.h"
#include<list>
namespace JCE
{
	class JCEListArray :
		public IObject
	{
	public:

		JCEListArray(void)
		{
		}

		virtual ~JCEListArray(void)
		{
			std::list<JCE::IObject*>::iterator iter;
			for(iter=_value.begin();iter!=_value.end();iter++)
			{
				delete *iter;
			}
		}
	public:
		std::list<JCE::IObject*> _value;
	public:
		unsigned int type(){return JCETypeJCEListArray;};
	};
}

