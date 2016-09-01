#include "CachedClient.h"

//============================================================================
// [描  述] 负责与memcached服务器建立连接并初始化相关参数dd
//----------------------------------------------------------------------------
// [函  数] CCachedClient()
// [参  数]
//         szSerOpts     :      服务器ip及端口号(host1:port1,host2:port2)
// [返回值]
//         无
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
// [描  述] 负责相关资源的释放,如与memcached建立的网络连接
//----------------------------------------------------------------------------
// [函  数] ~CCachedClient()
// [参  数]
//         无 
// [返回值]
//         无
//----------------------------------------------------------------------------
//============================================================================
CCachedClient::~CCachedClient()
{  
    memcached_free(this->mcst);  
}  


//============================================================================
// [描  述] 负责memcached相关属性初始化操作
//----------------------------------------------------------------------------
// [函  数] ~CCachedClient()
// [参  数]
//        iSndTimeout  : 写超时
//        iRcvTimeout  : 读超时
//        iBlockFlag      : 阻塞标志
// [返回值]
//         无
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
// [描  述] 负责向memcached服务器插入一个元素,如果key值存在，则覆盖原元素
//----------------------------------------------------------------------------
// [函  数] SaveItem()
// [参  数]
//         key     :      键名(sessionid值,32位)
//         value   :      键值
//         validate:      有效时间(默认为300秒,最大为1800秒)
// [返回值]
//         true    :      成功
//         false   :      失败
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
// [描  述] 查询指定键名相关属性值
//----------------------------------------------------------------------------
// [函  数] QueryItemValue()
// [参  数]
//         key     :      键名(sessionid值,32位)
// [返回值]
//         value   :      属性值
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
// [描  述] 刷新key的过期时间
//----------------------------------------------------------------------------
// [函  数] FreshExpiration()
// [参  数]
//         key           :      键名
//         expiration :      有效时间
// [返回值]
//         true          :      刷新成功
//         false         :      失败
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
// [描  述] 向memcached服务器发送删除指定key元素
//----------------------------------------------------------------------------
// [函  数] DeleteItem()
// [参  数]
//         key     :      键名(sessionid值,32位)
// [返回值]
//         true    :      成功
//         false   :      失败
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
// [描  述] 获取错误代号
//----------------------------------------------------------------------------
// [函  数] GetErrorNo()
// [参  数]
//         无
// [返回值]
//         错误代号
//----------------------------------------------------------------------------
//============================================================================
int
CCachedClient::GetErrorNo()const
{
    return errorNo;
}


//============================================================================
// [描  述] 获取具体错误信息
//----------------------------------------------------------------------------
// [函  数] ErrorString()
// [参  数]
//         无
// [返回值]
//         错误信息
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
        errorInfo = string("操作MemCached错误:连接失败!");
        break;
    case MCCLIENT_INIT_ERR:
        errorInfo = string("操作MemCached错误:初始化失败!");
        break;
    case MCCLIENT_SET_ERR:
        errorInfo = string("操作MemCached错误:保存失败!");
        break;
    case MCCLIENT_GET_ERR:
        errorInfo = string("操作MemCached错误:获取失败!");
        break;
    case MCCLIENT_DEL_ERR:
        errorInfo = string("操作MemCached错误:删除失败!");
        break;
    case MCCLIENT_NOT_FOUND_ERR:
        errorInfo = string("操作MemCached错误:查找失败!");
        break;
    case MCCLIENT_FRESH_KEY_ERR:
        errorInfo = string("操作MemCached错误:刷新Key失败!");
        break;
    default:
        errorInfo = string("操作MemCached错误:未知请求类型!");
        break;
    }

    return errorInfo;
}

