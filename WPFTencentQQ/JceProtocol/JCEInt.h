#pragma once
#include "JCEIObject.h"
namespace JCE
{
	class JCEInt :
		public IObject
	{
	public:

		JCEInt(void):_value(0)
		{
		}

		JCEInt(int i):_value(i)
		{
		}

		virtual ~JCEInt(void)
		{
		}
	private:
		int	_value;
	public:
		int value(){return _value;};
		int &ref_value(){return _value;};
		void value(int v){_value=v;};
	public:
		unsigned int type(){return JCETypeJCEInt;};
	};
}

