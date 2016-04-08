#ifndef __CACHED_CLIENT_H
#define __CACHED_CLIENT_H

#include <string>
#include <stdio.h>
#include <libmemcached/memcached.h> 

using namespace std;

/* 错误代号 */
#define MCCLIENT_CREATE_ERR    1
#define MCCLIENT_INIT_ERR      2  
#define MCCLIENT_SET_ERR       3
#define MCCLIENT_GET_ERR       4
#define MCCLIENT_DEL_ERR       5
#define MCCLIENT_NOT_FOUND_ERR 6
#define MCCLIENT_FRESH_KEY_ERR 7 

class CCachedClient
{
public:
	/* 构造函数*/
	CCachedClient(const char *szSerOpts);

	/* 析构造函数*/
	~CCachedClient();

	/* 初始化函数*/
	bool InitCachedClient(const int iSndTimeout,const int iRcvTimeout, const int iBlockFlag);
	
	/* 添加一个元素*/
	bool SaveItem(const string &key,const string &value,long validate);

	/* 删除指定key的元素*/
	bool DeleteItem(const string &key);

	/* 获取指定key元素的值*/
	string QueryItemValue(const string &key);
	
	bool FreshExpiration(const string &key,long expiration);

	/* 获取具体错误信息*/
	string ErrorString();

	/* 获取错误代号*/
	int GetErrorNo()const;
private:
	int  errorNo;             //错误代号
	memcached_st *mcst;       //保存与memcached框架连接服务列表          
};

#endif // #ifndef __CACHED_CLIENT_H
