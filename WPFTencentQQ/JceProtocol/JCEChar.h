#pragma once
#include "JCEIObject.h"
namespace JCE
{
	class JCEChar :
		public IObject
	{
	public:

		JCEChar(void):_value(0)
		{
		}

		JCEChar(char c):_value(c)
		{
		}

		virtual ~JCEChar(void)
		{
		}
	private:
		char _value;
	public:
		char value(){return _value;};
		char &ref_value(){return _value;};
		void value(char c){_value=c;};
	public:
		unsigned int type(){return JCETypeJCEChar;};
	};
}

