#pragma once
#include "JCEIObject.h"
namespace JCE
{
	class JCEBoolean :
		public IObject
	{
	public:

		JCEBoolean(void):_value(0)
		{
		}

		JCEBoolean(bool c):_value(c)
		{
		}

		virtual ~JCEBoolean(void)
		{
		}
	private:
		bool _value;
	public:
		bool value(){return _value;};
		bool &ref_value(){return _value;};
		void value(bool c){_value=c;};
	public:
		unsigned int type(){return JCETypeJCEBoolean;};
	};
}