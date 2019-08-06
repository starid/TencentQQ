#pragma once
#include "JCEIObject.h"
namespace JCE
{
	class JCELong :
		public IObject
	{
	public:

		JCELong(void):_value(0)
		{
		}

		virtual ~JCELong(void)
		{
		}
	private:
		__int64	_value;
	public:
		__int64	value(){return _value;};
		__int64	&ref_value(){return _value;};
		void	value(__int64 l){_value=l;};
	public:
		unsigned int type(){return JCETypeJCELong;};
	};
}
