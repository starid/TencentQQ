#pragma once
#include"JCEType.h"
namespace JCE
{
	class IObject
	{
	public:

		IObject(void)
		{
		}

		virtual ~IObject(void)
		{
		}
	public:
		virtual	unsigned int type(){return JCETypeJCEIObject;};
	};
}

