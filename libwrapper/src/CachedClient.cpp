#include "CachedClient.h"

//============================================================================
// [��  ��] ������memcached�������������Ӳ���ʼ����ز���dd
//----------------------------------------------------------------------------
// [��  ��] CCachedClient()
// [��  ��]
//         szSerOpts     :      ������ip���˿ں�(host1:port1,host2:port2)
// [����ֵ]
//         ��
//----------------------------------------------------------------------------
//============================================================================
CCachedClient::CCachedClient(const char *szSerOpts)
{  
    mcst = memcached_create(NULL);  
    if(!mcst){  
        exit(-1);
    }  
    
    memcached_server_st *mcServers = memcached_servers_parse(szSerOpts); 
    memcached_return_t   mcRet     = memcached_server_push(mcst,mcServers);  
    memcached_server_list_free(mcServers);  

    if(mcRet != MEMCACHED_SUCCESS){
        exit(-1);
    }   
    errorNo = 0;
}  


//============================================================================
// [��  ��] ���������Դ���ͷ�,����memcached��������������
//----------------------------------------------------------------------------
// [��  ��] ~CCachedClient()
// [��  ��]
//         �� 
// [����ֵ]
//         ��
//----------------------------------------------------------------------------
//============================================================================
CCachedClient::~CCachedClient()
{  
    memcached_free(this->mcst);  
}  


//============================================================================
// [��  ��] ����memcached������Գ�ʼ������
//----------------------------------------------------------------------------
// [��  ��] ~CCachedClient()
// [��  ��]
//        iSndTimeout  : д��ʱ
//        iRcvTimeout  : ����ʱ
//        iBlockFlag      : ������־
// [����ֵ]
//         ��
//----------------------------------------------------------------------------
//============================================================================
bool 
CCachedClient::InitCachedClient(const int iSndTimeout,const int iRcvTimeout, const int iBlockFlag)
{
    bool bRet = true;
    memcached_behavior_set(mcst,MEMCACHED_BEHAVIOR_NO_BLOCK,iBlockFlag);  
    memcached_behavior_set(mcst,MEMCACHED_BEHAVIOR_SND_TIMEOUT,iSndTimeout);  
    memcached_behavior_set(mcst,MEMCACHED_BEHAVIOR_RCV_TIMEOUT,iRcvTimeout);  
    return bRet;
}


//============================================================================
// [��  ��] ������memcached����������һ��Ԫ��,���keyֵ���ڣ��򸲸�ԭԪ��
//----------------------------------------------------------------------------
// [��  ��] SaveItem()
// [��  ��]
//         key     :      ����(sessionidֵ,32λ)
//         value   :      ��ֵ
//         validate:      ��Чʱ��(Ĭ��Ϊ300��,���Ϊ1800��)
// [����ֵ]
//         true    :      �ɹ�
//         false   :      ʧ��
//----------------------------------------------------------------------------
//============================================================================
bool 
CCachedClient::SaveItem(const string &key,const string &value,long validate=1800) 
{  
    bool bRet = true;
    memcached_return_t mcRet;  

    mcRet = memcached_set(mcst,key.c_str(),key.length(),value.c_str(),value.length(),validate,0);  
    if(MEMCACHED_SUCCESS != mcRet){  
        errorNo = MCCLIENT_SET_ERR;
        bRet = false; 
    }  
    return bRet;
}  

//============================================================================
// [��  ��] ��ѯָ�������������ֵ
//----------------------------------------------------------------------------
// [��  ��] QueryItemValue()
// [��  ��]
//         key     :      ����(sessionidֵ,32λ)
// [����ֵ]
//         value   :      ����ֵ
//----------------------------------------------------------------------------
//============================================================================
string 
CCachedClient::QueryItemValue(const string &key)
{  
    memcached_return_t mcRet;   
    string retValue("");  
    unsigned int flag;
    size_t outLen;

    char *result = memcached_get(mcst,key.c_str(),key.length(),&outLen,&flag,&mcRet);  
    if(mcRet == MEMCACHED_SUCCESS){          
        retValue = string(result);
        free(result);  
    }  
    else if(mcRet == MEMCACHED_NOTFOUND){  
        errorNo = MCCLIENT_NOT_FOUND_ERR;  
    }  
    else {  
        errorNo = MCCLIENT_GET_ERR;
    }
    return retValue;
}  

//============================================================================
// [��  ��] ˢ��key�Ĺ���ʱ��
//----------------------------------------------------------------------------
// [��  ��] FreshExpiration()
// [��  ��]
//         key           :      ����
//         expiration :      ��Чʱ��
// [����ֵ]
//         true          :      ˢ�³ɹ�
//         false         :      ʧ��
//----------------------------------------------------------------------------
//============================================================================
bool 
CCachedClient::FreshExpiration(const string &key,long expiration=300)
{  
    memcached_return_t mcRet; 

    bool bRet = true;
    
    mcRet = memcached_touch(mcst,key.c_str(),key.length(),expiration);  
    if(mcRet == MEMCACHED_SUCCESS){          
       
    }  
    else if(mcRet == MEMCACHED_NOTFOUND){ 
        bRet = false;
        errorNo = MCCLIENT_NOT_FOUND_ERR;   
    }  
    else {  
        bRet = false;        
        errorNo = MCCLIENT_FRESH_KEY_ERR;   
    }
    
    return bRet;
}  


//============================================================================
// [��  ��] ��memcached����������ɾ��ָ��keyԪ��
//----------------------------------------------------------------------------
// [��  ��] DeleteItem()
// [��  ��]
//         key     :      ����(sessionidֵ,32λ)
// [����ֵ]
//         true    :      �ɹ�
//         false   :      ʧ��
//----------------------------------------------------------------------------
//============================================================================
bool
CCachedClient::DeleteItem(const string &key)
{  
    bool bRet = true;
    memcached_return_t mcRet;  

    mcRet = memcached_delete(mcst,key.c_str(),key.length(),0);  
    if(mcRet != MEMCACHED_SUCCESS){
        bRet = false;
        errorNo = MCCLIENT_DEL_ERR;        
    } 
    return bRet;
}  

//============================================================================
// [��  ��] ��ȡ�������
//----------------------------------------------------------------------------
// [��  ��] GetErrorNo()
// [��  ��]
//         ��
// [����ֵ]
//         �������
//----------------------------------------------------------------------------
//============================================================================
int
CCachedClient::GetErrorNo()const
{
    return errorNo;
}


//============================================================================
// [��  ��] ��ȡ���������Ϣ
//----------------------------------------------------------------------------
// [��  ��] ErrorString()
// [��  ��]
//         ��
// [����ֵ]
//         ������Ϣ
//----------------------------------------------------------------------------
//============================================================================
string 
CCachedClient::ErrorString()
{
    string errorInfo;
    
    switch(errorNo){
    case 0:
        break;
    case MCCLIENT_CREATE_ERR:
        errorInfo = string("����MemCached����:����ʧ��!");
        break;
    case MCCLIENT_INIT_ERR:
        errorInfo = string("����MemCached����:��ʼ��ʧ��!");
        break;
    case MCCLIENT_SET_ERR:
        errorInfo = string("����MemCached����:����ʧ��!");
        break;
    case MCCLIENT_GET_ERR:
        errorInfo = string("����MemCached����:��ȡʧ��!");
        break;
    case MCCLIENT_DEL_ERR:
        errorInfo = string("����MemCached����:ɾ��ʧ��!");
        break;
    case MCCLIENT_NOT_FOUND_ERR:
        errorInfo = string("����MemCached����:����ʧ��!");
        break;
    case MCCLIENT_FRESH_KEY_ERR:
        errorInfo = string("����MemCached����:ˢ��Keyʧ��!");
        break;
    default:
        errorInfo = string("����MemCached����:δ֪��������!");
        break;
    }

    return errorInfo;
}

