#pragma once
#include "JCEIObject.h"
namespace JCE
{
	class JCEShort :
		public IObject
	{
	public:

		JCEShort(void)
		{
		}

		virtual ~JCEShort(void)
		{
		}
	private:
		short	_value;
	public:
		short	value(){return _value;};
		short	&ref_value(){return _value;};
		void	value(short s){_value=s;};
	public:
		unsigned int type(){return JCETypeJCEShort;};
	};
}
