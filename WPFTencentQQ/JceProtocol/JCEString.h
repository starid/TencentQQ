#pragma once
#include "JCEIObject.h"
#include<string>
namespace JCE
{
	class JCEString :
		public IObject
	{
	public:

		JCEString(void)
		{
		}
		virtual ~JCEString(void)
		{
		}
	private:
		std::string _value;
	public:
		std::string value(){return _value;};
		std::string &ref_value(){return _value;};
		void		value(std::string s){_value=s;};
	public:
		unsigned int type(){return JCETypeJCEString;};

		bool operator <(const JCEString& _t) const
		{
			if(strcmp(_value.c_str(),_t._value.c_str())<0)
				return true;
			return false;
		}
	};
}

