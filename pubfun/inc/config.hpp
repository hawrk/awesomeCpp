/*
 * config.hpp
 *
 *  Created on: 2016年3月16日
 *  Author: Hawrk
 *  Version:1.0
 *     Desc:对配置文件的相关操作
 */

#ifndef INCLUDE_CONFIG_HPP_
#define INCLUDE_CONFIG_HPP_

#include <map>
#include <string>
#include "pubfun.hpp"
#include "glog/logging.h"
#include "macro.hpp"

using namespace std;

namespace hawrk
{

	class CConfig
	{
	public:
		CConfig() = default;
		CConfig(const char* filepath):filename(filepath){}   //没有分号!
		~CConfig(){};

	public:
		//判断配置文件是否存在
		bool FileExist(const char* filename);

		//读取所有配置信息
		bool ReadConf(const char* filename,StrStrMap& outmap);

		//根据key 值读取 配置文件值
		bool ReadConfByKey(const char* filename,const char* key,char* value);

	private:
		const char* filename;
		StrStrMap strmap;
	};
}



#endif /* INCLUDE_CONFIG_HPP_ */
