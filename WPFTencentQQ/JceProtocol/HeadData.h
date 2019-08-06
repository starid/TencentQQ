#pragma once
class CHeadData
{
public:
	CHeadData(void)
	{
	}

	virtual ~CHeadData(void)
	{
	}
public:
	int tag;
    char type;
public:
	void clear()
    {
      type = 0;
      tag = 0;
    }
};

