#pragma once
#include "JCEIObject.h"
#include "../UtilLib/ByteBuffer.h"
namespace JCE
{
	class JCEByteArray :
		public IObject
	{
	public:

		JCEByteArray(void)
		{
		}

		JCEByteArray(char *p,size_t size)
		{
			_value.clear();
			_value.append(p,size);
		}

		virtual ~JCEByteArray(void)
		{
		}
	private:
		ByteBuffer _value;
	public:
		ByteBuffer	value(){return _value;};
		ByteBuffer	&ref_value(){return _value;};
		void		value(ByteBuffer	b){_value=b;};
	public:
		unsigned int type(){return JCETypeJCEByteArray;};
	};
}
