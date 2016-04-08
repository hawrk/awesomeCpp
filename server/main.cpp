/*
 * main.cpp
 *
 *  Created on: 2016年3月16日
 *      Author: Administrator
 */

#include "config.hpp"
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>

const static char* config_name = "../config/memcached.config";
const static char* log_path = "../log";

using namespace hawrk;
using namespace google;
using namespace std;

int main(int argc,char* argv[])
{
	//init log
	InitGoogleLogging(argv[0]);
	FLAGS_log_dir = "../log";
	if(access(log_path,F_OK) < 0)
	{
		if(mkdir(log_path,0755) < 0)
		{
			cout<<"create log dir fail."<<endl;
			exit(0);
		}
	}
	FLAGS_logbufsecs  = 0;  //日志实时输出
	FLAGS_max_log_size = 1024; // max log size is 1024M
	LOG(INFO)<<"main start ..."<<endl;

	CConfig config;
	if(!config.FileExist(config_name))
	{
		LOG(ERROR)<<"config file:["<<config_name<<"] not exist!!"<<endl;
		exit(0);
	}

	//get all value
	StrStrMap mmap;
	config.ReadConf(config_name,mmap);
	LOG(ERROR)<<"get config file key :[TIMEOUT]"<<mmap["TIMEOUT"]<<endl;

	//get value
	char szserver_ip[16] ={0};
	char szserver_port[5] = {0};
	if(!config.ReadConfByKey(config_name,"MCSERVER_IP",szserver_ip))
	{
		LOG(ERROR)<<"get config file key :[MCSERVER_IP] error!!"<<endl;
		exit(0);
	}
	if(!config.ReadConfByKey(config_name,"MCSERVER_PORT",szserver_port))
	{
		LOG(ERROR)<<"get config file key :[MCSERVER_PORT] error!!"<<endl;
		exit(0);
	}

	//printf result
	LOG(INFO)<<"memcached ip:["<<szserver_ip<<"]"<<endl;
	LOG(INFO)<<"memcached port:["<<szserver_port<<"]"<<endl;

	return 0;

}

