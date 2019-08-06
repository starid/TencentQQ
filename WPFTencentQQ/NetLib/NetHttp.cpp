#include "StdAfx.h"
#include "NetHttp.h"
#include<curl.h>

#pragma comment(lib,"libcurl.lib")

CURL *curl=NULL;

CNetHttp::CNetHttp(void)
{
	curl_global_init(CURL_GLOBAL_ALL);
}


CNetHttp::~CNetHttp(void)
{
	curl_global_cleanup();
}

bool CNetHttp::CoInitialize()
{
	if(curl)
	{
		curl_easy_cleanup(curl);
		curl=NULL;
	}
	curl = curl_easy_init();
	if(curl)
	{	
		return true;
	}
	return false;
}

void CNetHttp::UnInitialize()
{
	if(curl)
	{
		curl_easy_cleanup(curl);
		curl=NULL;
	}
}

bool CNetHttp::perform(HTTP_TYPE nType,std::string strUrl,unsigned int dwPort,ByteBuffer *pBuffer)
{
	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL,strUrl.c_str());
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		if(nType==TYPE_POST)
			curl_easy_setopt(curl, CURLOPT_POST,1L);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);  //设置访问的超时
		curl_easy_setopt(curl, CURLOPT_PORT, dwPort);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &process_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, pBuffer);      //可以给回调函数提供一个自定义参数，libcurl不处理该参数，只是简单的传递

					
		//增加header字段
		struct curl_slist *chunk = NULL;
		//chunk = curl_slist_append(chunk, "Accept-Encoding: gzip, deflate");
		chunk = curl_slist_append(chunk, "Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, application/x-ms-application, application/x-ms-xbap, application/vnd.ms-xpsdocument, application/xaml+xml, */*");
		chunk = curl_slist_append(chunk, "Accept-Language: zh-cn");
		chunk = curl_slist_append(chunk, "User-Agent: Mozilla/5.0");
		chunk = curl_slist_append(chunk, "Connection: Keep-Alive");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

		unsigned char buf[]="num=20&page=0&sessionid=0&keyword=surreal&agerg=0&sex=0&firston=0&video=0&country=0&province=0&city=0&district=0&hcountry=0&hprovince=0&hcity=0&hdistrict=0&online=0&ldw=404133171";
		curl_easy_setopt(curl,  CURLOPT_POSTFIELDS,buf);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, sizeof(buf));

		CURLcode res = curl_easy_perform(curl);
		if(res != CURLE_OK)
		{
			return false;
		}
		long retcode = 0;
		res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE , &retcode); 
		if ( (res == CURLE_OK) && retcode == 200 )
		{
			double length = 0;
			res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD , &length);
			//处理接收到的数据
			return true;
		}
		return false;
	}else
		return false;
}


/**  *	@brief libcurl接收到数据时的回调函数  *  
*	将接收到的数据保存到本地文件中，同时显示在控制台上。  * 
*	@param [in] buffer 接收到的数据所在缓冲区 
*	@param [in] size 数据长度 
*	@param [in] nmemb 数据片数量 
*	@param [in/out] 用户自定义指针 
*	@return 获取的数据长度 */ 
size_t process_data(void *buffer, size_t size, size_t nmemb, void *user_p)
{
	ByteBuffer *p=static_cast<ByteBuffer *>(user_p);
	p->append((char *)buffer,nmemb);
	return nmemb;     //返回处理的大小
}
