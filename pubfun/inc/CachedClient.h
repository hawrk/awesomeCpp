#ifndef __CACHED_CLIENT_H
#define __CACHED_CLIENT_H

#include <string>
#include <stdio.h>
#include <libmemcached/memcached.h> 

using namespace std;

/* ������� */
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
	/* ���캯��*/
	CCachedClient(const char *szSerOpts);

	/* �����캯��*/
	~CCachedClient();

	/* ��ʼ������*/
	bool InitCachedClient(const int iSndTimeout,const int iRcvTimeout, const int iBlockFlag);
	
	/* ���һ��Ԫ��*/
	bool SaveItem(const string &key,const string &value,long validate);

	/* ɾ��ָ��key��Ԫ��*/
	bool DeleteItem(const string &key);

	/* ��ȡָ��keyԪ�ص�ֵ*/
	string QueryItemValue(const string &key);
	
	bool FreshExpiration(const string &key,long expiration);

	/* ��ȡ���������Ϣ*/
	string ErrorString();

	/* ��ȡ�������*/
	int GetErrorNo()const;
private:
	int  errorNo;             //�������
	memcached_st *mcst;       //������memcached������ӷ����б�          
};

#endif // #ifndef __CACHED_CLIENT_H
