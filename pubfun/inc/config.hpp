/*
 * config.hpp
 *
 *  Created on: 2016��3��16��
 *  Author: Hawrk
 *  Version:1.0
 *     Desc:�������ļ�����ز���
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
		CConfig(const char* filepath):filename(filepath){}   //û�зֺ�!
		~CConfig(){};

	public:
		//�ж������ļ��Ƿ����
		bool FileExist(const char* filename);

		//��ȡ����������Ϣ
		bool ReadConf(const char* filename,StrStrMap& outmap);

		//����key ֵ��ȡ �����ļ�ֵ
		bool ReadConfByKey(const char* filename,const char* key,char* value);

	private:
		const char* filename;
		StrStrMap strmap;
	};
}



#endif /* INCLUDE_CONFIG_HPP_ */
