#include <iostream>
#include "jsoncpp/json.h"

using namespace std;
using namespace Json;

int main()
{
	string str ="{\"SERVICE\":{\"SERVICE_HEADER\":{\"SERVICE_ID\":\"TFNCustSetup\",\"ORG\":\"000000000001\",\"CHANNEL_ID\":\"BANK\",\"SUB_TERMINAL_TYPE\":\"APP\",\"OP_ID\":\"0000\",\"REQUEST_TIME\":\"20160405101435\",\"VERSION_ID\":\"01\",\"MAC\":\"0000\",\"SERV_RESPONSE\":{\"STATUS\":\"F\",\"CODE\":\"1101\",\"DESC\":\"重复建立客户\"}},\"SERVICE_BODY\":{\"RESPONSE\":{}}}}"; 
	
	Reader reader;
	Value root;
	if(reader.parse(str,root))
	{
		Value service_val = root["SERVICE"];   //SERVICE 's value
		if(service_val.isObject())
		{
			cout<<"...."<<endl;
			Value ser_header_val = service_val["SERVICE_HEADER"];  //SERVICE_HEADER 's value
			if(ser_header_val.isObject())
			{
				cout<<"...parse header..."<<endl;
				Value ser_response = ser_header_val["SERV_RESPONSE"];
				if(ser_response.isObject())
				{
					string m_res_status = ser_response["STATUS"].asString();
					string m_res_code = ser_response["CODE"].asString();
					string m_res_desc = ser_response["DESC"].asString();
					cout<<"m_res_status="<<m_res_status<<",m_res_code="<<m_res_code<<",m_res_desc="<<m_res_desc<<endl;
				}
			}
			
			Value ser_body_val = service_val["SERVICE_BODY"];    //SERVICE_BODY 's value
			if(ser_body_val.isObject())
			{
				cout<<"parse body...."<<endl;
				Value ser_body_resp_val = ser_body_val["RESPONSE"];   //RESPONSE 's value
				if(ser_body_resp_val.isObject())
				{
					cout<<"parse body response...."<<endl;
					if(ser_body_resp_val.isNull())
					{
						cout<<"NULL response ..."<<endl;
					}
					else
					{
						cout<<"response string :"<<ser_body_resp_val.toStyledString().c_str()<<endl;
				  }
					/*
					string  curnbr = ser_body_resp_val["CONTR_NBR"].asString();
					cout<<"CONTR_NBR="<<curnbr<<endl;
					
					cout<<"parse desc..."<<endl;
					string desc = ser_body_resp_val["DESC"].asString();
					cout<<"DESC ="<<desc<<endl;
					
					//parse MULCT_RULES_LIST
					Value load_list = ser_body_resp_val["MULCT_RULES_LIST"];
					int list_size = load_list.size();
					cout<<"list_size = "<<list_size<<endl;
					for(int j = 0;j <  list_size;j++)
					{
						int  day_past_due = load_list[j]["DAY_PAST_DUE"].asInt();
						cout<<"DAY_PAST_DUE="<<day_past_due<<endl;
					}
					
					
					//SUB_TERMINAL_LIST
					Value sub_value = ser_body_resp_val["SUB_TERMINAL_LIST"];
					int list_sub_size = sub_value.size();
					cout<<"list_sub_size= "<<list_sub_size<<endl;
					for(int j = 0;j < list_sub_size;j++)
					{
						cout<<"SUB_TERMINAL_LIST ="<<sub_value[j]<<endl;
					}
					*/
					
				}
			}
		}	
		
	}
	return 0;
}
