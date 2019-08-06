#pragma once
class CCpuId
{
public:
	CCpuId(void);
	~CCpuId(void);
private:
	void cpuid(unsigned int);
	void LeftMove(unsigned int var);
	void LM(unsigned int var);
public:
	bool isSupport();
	void getCpuName(unsigned char*,unsigned int);
	void getCpuBrand();
	void getCpuFeature();
	void getCpuSeris();
private:
	unsigned int veax;
	unsigned int vebx;
	unsigned int vedx;
	unsigned int vecx;
};

