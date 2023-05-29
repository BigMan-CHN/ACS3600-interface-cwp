#include "CSetWebNewWhine.h"
#include <boost/lexical_cast.hpp>

CSetWebNewWhine::CSetWebNewWhine(string ip, int port, int timeOut)
    :_result(cJSON_CreateObject())
    ,_total(cJSON_CreateObject())
    ,_addressList(cJSON_CreateArray())
    ,_ip(ip)
    ,_port(port)
    ,_timeOut(timeOut)
    ,_client(new MPSClient(ip,port,timeOut))
    ,_AnalyParas()
{

}

bool CSetWebNewWhine::ComposeResult(cJSON *result)
{
    if(_result == NULL || result == NULL){
        mLogError("cJSON result == NULL.");
        result = NULL;
        return false;
    }

    if(_addressList == NULL){
        mLogWarn("cJSON _addressList == NULL.");
        return false;
    }
    if(_total == NULL){
        mLogWarn("cJSON _total == NULL.");
        return false;
    }

    //result中添加节点
	//cJSON_AddItemToObject(_result,"Total",_total);
    //cJSON_AddItemToObject(_result,"AddressList",_addressList);	
    return true;
}

string CSetWebNewWhine::ComposeResult()
{
    cJSON * result = cJSON_CreateObject();
    if(ComposeResult(result) == false){
        cJSON_Delete(result);
        return "";
    }else{
        char *cRes = cJSON_Print(_result);
        string res = cRes;
        cJSON_Delete(result);
        return res;
    }
}
bool CSetWebNewWhine::SetWebNewWhineINner(int WhineChn,int WhineType, CData &oResult, char *cResult)
{
	mLogDebug("run SetWebNewWhineINner(...)");
	
	//1. 封装业务请求
	char szReqBody[REQ_BODY_MAXLEN] = { 0 };
	int num;
	switch(WhineChn)
	{
		case 1:
			 num = 1;
			 break;
		case 2:
			 num = 2;
			 break;
		case 3:
			 num = 5;
			 break;
		case 4:
			 num = 6;
			 break;
		default:
			 mLogError("SetWebNewWhineINner WhineChn error !!!\n"<<WhineChn);
			 return false;
	 }
						
	sprintf(szReqBody, INTERFACE_SET_AUDIO_WHINE_CONF_SENDCMD, num, WhineType);
	int realBodySize = strlen(szReqBody);
					
	char szReqCmd[REQ_CMD_MAXLEN] = { 0 };
	szReqCmd[0] = 0;  //不加密
	szReqCmd[1] = 3;  //2Get请求, 3是SET, 4是SYS
	szReqCmd[2] = realBodySize >> 8;
	szReqCmd[3] = realBodySize;
	memcpy(&szReqCmd[4], szReqBody, realBodySize);
					
	//2. 发送socket请求
	MPSOperationRes opResCode = eMPSResultOK; //??
	ResponseCode resCode = _client->GetConfigNew(szReqCmd, 4 + realBodySize, opResCode, oResult, cResult);
	if (resCode != eResponseCodeSuccess) {
		mLogError("GetConfig(...) error:" << resCode);
		return false;
	}

	return true;

}
bool CSetWebNewWhine::GetWebNewWhineINner( CData &oResult, char *cResult)
{
	mLogDebug("run SetWebNewWhineINner(...)");
	
	//1. 封装业务请求
	char *ReqBody;
	int num;
	char szReqBody[REQ_BODY_MAXLEN] = { 0 };
	memset(szReqBody,0,REQ_BODY_MAXLEN);
	for(int WhineChn = 1; WhineChn <= 4; WhineChn++)
	{
		switch(WhineChn)
	    {
			case 1:
				 num = 1;
				 break;
			case 2:
				 num = 2;
				 break;
			case 3:
				 num = 5;
				 break;
			case 4:
				 num = 6;
				 break;
			default:
				 mLogError("GetWebNewWhineINner WhineChn error !!!\n"<<WhineChn);
				 return false;
		 }

		ReqBody = szReqBody + strlen(szReqBody);
		sprintf(ReqBody, INTERFACE_GET_AUDIO_WHINE_CONF_SENDCMD, num,num);
	}	
	
	//sprintf(szReqBody, "aud_out1.ch1.audio_crack_mode\n");
	mLogDebug("szReqBody = "<<szReqBody);
	int realBodySize = strlen(szReqBody);
					
	char szReqCmd[REQ_CMD_MAXLEN] = { 0 };
	szReqCmd[0] = 0;  //不加密
	szReqCmd[1] = 2;  //2Get请求, 3是SET, 4是SYS
	szReqCmd[2] = realBodySize >> 8;
	szReqCmd[3] = realBodySize;
	memcpy(&szReqCmd[4], szReqBody, realBodySize);
					
	//2. 发送socket请求
	MPSOperationRes opResCode = eMPSResultOK; //??
	ResponseCode resCode = _client->GetConfigNew(szReqCmd, 4 + realBodySize, opResCode, oResult, cResult);
	if (resCode != eResponseCodeSuccess) {
		mLogError("GetConfig(...) error:" << resCode);
		return false;
	}

	return true;

}
bool CSetWebNewWhine::SetWebNewWhineButtonINner(int WhineChn,int WhineButton, CData &oResult, char *cResult)
{
	mLogDebug("run SetWebNewWhineButtonINner(...)");
	
	//1. 封装业务请求
	char szReqBody[REQ_BODY_MAXLEN] = { 0 };
	int num;
	switch(WhineChn)
    {
		case 1:
			 num = 1;
			 break;
		case 2:
			 num = 2;
			 break;
		case 3:
			 num = 5;
			 break;
		case 4:
			 num= 6;
			 break;
		default:
			 mLogError("SetWebNewWhineButtonINner WhineChn error !!!\n"<<WhineChn);
			 return false;
	 }					
	sprintf(szReqBody, INTERFACE_SET_AUDIO_WHINE_BUTTON_SENDCMD, num, WhineButton);
	int realBodySize = strlen(szReqBody);
					
	char szReqCmd[REQ_CMD_MAXLEN] = { 0 };
	szReqCmd[0] = 0;  //不加密
	szReqCmd[1] = 3;  //2Get请求, 3是SET, 4是SYS
	szReqCmd[2] = realBodySize >> 8;
	szReqCmd[3] = realBodySize;
	memcpy(&szReqCmd[4], szReqBody, realBodySize);
					
	//2. 发送socket请求
	MPSOperationRes opResCode = eMPSResultOK; //??
	ResponseCode resCode = _client->GetConfigNew(szReqCmd, 4 + realBodySize, opResCode, oResult, cResult);
	if (resCode != eResponseCodeSuccess) {
		mLogError("GetConfig(...) error:" << resCode);
		return false;
	}

	return true;

}
bool CSetWebNewWhine::GetWebNewWhineButtonINner( CData &oResult, char *cResult)
{
	mLogDebug("run GetWebNewWhineButtonINner(...)");
	
	//1. 封装业务请求
	char *ReqBody;
	int num;
	char szReqBody[REQ_BODY_MAXLEN] = { 0 };
	memset(szReqBody,0,REQ_BODY_MAXLEN);
	for(int WhineChn = 1; WhineChn <= 4; WhineChn++)
	{
		switch(WhineChn)
	    {
			case 1:
				 num = 1;
				 break;
			case 2:
				 num = 2;
				 break;
			case 3:
				 num = 5;
				 break;
			case 4:
				 num= 6;
				 break;
			default:
				 mLogError("GetWebNewWhineButtonINner WhineChn error !!!\n"<<WhineChn);
				 return false;
		 }
		ReqBody = szReqBody + strlen(szReqBody);
		//sprintf(ReqBody, INTERFACE_SET_AUDIO_WHINE_BUTTON_SENDCMD, num);
		sprintf(ReqBody, INTERFACE_GET_AUDIO_WHINE_CONF_SENDCMD, num,num);
	}					
	//mLogDebug("szReqBody = "<<szReqBody);
	int realBodySize = strlen(szReqBody);
					
	char szReqCmd[REQ_CMD_MAXLEN] = { 0 };
	szReqCmd[0] = 0;  //不加密
	szReqCmd[1] = 2;  //2Get请求, 3是SET, 4是SYS
	szReqCmd[2] = realBodySize >> 8;
	szReqCmd[3] = realBodySize;
	memcpy(&szReqCmd[4], szReqBody, realBodySize);
					
	//2. 发送socket请求
	MPSOperationRes opResCode = eMPSResultOK; //??
	ResponseCode resCode = _client->GetConfigNew(szReqCmd, 4 + realBodySize, opResCode, oResult, cResult);
	if (resCode != eResponseCodeSuccess) {
		mLogError("GetConfig(...) error:" << resCode);
		return false;
	}

	return true;

}

InterfaceResCode CSetWebNewWhine::SetWebNewWhine(string &sResult,int WhineChn,int WhineType)
{
		mLogInfo("SetWebNewWhine...");
		CData oResult = SVSMAP();
		char cResult[8192] = {0};
#if 1
		if(SetWebNewWhineINner(WhineChn, WhineType, oResult, cResult) == false){
			mLogError("Failed to run  GetConsoleConfig(...)");
			return eInterfaceResCodeError;
		}
#endif 
	
#if 0	
		if (!_AnalyParas.ConvertSTRING2CJSONParseSerialCmdParam(oResult, cResult, _result, _addressList))
		{
			mLogError("Failed to run  ConvertSTRING2CJSONParseSerialCmdParam(...)");
			return eInterfaceResCodeError;
		}
#endif		
#if 0
		int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
		printf("SendConsoleCmd\n");
		for (int i = 0; i < iRecvLength; i++)
		{
			if (i < 4)
			{
				printf("%d", cResult[i]);
			}
			else 
			{
				printf("%c", cResult[i]);
			}
		}
	
		if( _AnalyParas.ConvertSTRING2CJSONSendConsoleCmd(oResult, cResult) == false){
			mLogError("Failed to run  ConvertSTRING2CJSONSendConsoleCmd(...)");
			return eInterfaceResCodeError;
		}
#endif 
	
		sResult = ComposeResult();
		cJSON_Delete(_result);

		return eInterfaceResCodeSuccess;

}


InterfaceResCode CSetWebNewWhine::GetWebNewWhine(string &sResult)
{
		mLogInfo("GetWebNewWhine...");
		CData oResult = SVSMAP();
		char cResult[8192] = {0};
		int ParamNumber = 4;
		cJSON *tmplist[20];
		string Method = "GetWebNewWhine";
#if 1
		if(GetWebNewWhineINner(oResult, cResult) == false){
			mLogError("Failed to run  GetConsoleConfig(...)");
			return eInterfaceResCodeError;
		}
#endif 	
	
#if 0
		int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
		printf("SendConsoleCmd\n");
		for (int i = 0; i < iRecvLength; i++)
		{
			if (i < 4)
			{
				printf("%d", cResult[i]);
			}
			else 
			{
				printf("%c", cResult[i]);
			}
		}
#endif
		//mLogDebug("GetWebNewWhineINner ");
		for(int i = 1; i <= ParamNumber; i++)
		{
			tmplist[i] = cJSON_CreateObject();
		}
		if( _AnalyParas.ConvertSTRING2CJSONGetWebNewWhine(oResult, cResult, Method,_result, _addressList, tmplist,  ParamNumber) == false){
			mLogError("Failed to run  ConvertSTRING2CJSONSendConsoleCmd(...)");
			return eInterfaceResCodeError;
		}
 
		cJSON_AddItemToObject(_result, "WhineList", _addressList);
		sResult = ComposeResult();
		cJSON_Delete(_result);

		return eInterfaceResCodeSuccess;

}
InterfaceResCode CSetWebNewWhine::SetWebNewWhineButton(string &sResult,int WhineChn,int WhineButton)
{
		mLogInfo("SetWebNewWhineButton...");
		CData oResult = SVSMAP();
		char cResult[8192] = {0};
#if 1
		if(SetWebNewWhineButtonINner(WhineChn, WhineButton, oResult, cResult) == false){
			mLogError("Failed to run  GetConsoleConfig(...)");
			return eInterfaceResCodeError;
		}
#endif 
	
#if 0	
		if (!_AnalyParas.ConvertSTRING2CJSONParseSerialCmdParam(oResult, cResult, _result, _addressList))
		{
			mLogError("Failed to run  ConvertSTRING2CJSONParseSerialCmdParam(...)");
			return eInterfaceResCodeError;
		}
#endif		
#if 0
		int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
		printf("SendConsoleCmd\n");
		for (int i = 0; i < iRecvLength; i++)
		{
			if (i < 4)
			{
				printf("%d", cResult[i]);
			}
			else 
			{
				printf("%c", cResult[i]);
			}
		}
	
		if( _AnalyParas.ConvertSTRING2CJSONSendConsoleCmd(oResult, cResult) == false){
			mLogError("Failed to run  ConvertSTRING2CJSONSendConsoleCmd(...)");
			return eInterfaceResCodeError;
		}
#endif 
	
		sResult = ComposeResult();
		cJSON_Delete(_result);

		return eInterfaceResCodeSuccess;

}

InterfaceResCode CSetWebNewWhine::GetWebNewWhineButton(string &sResult)
{
		mLogInfo("GetWebNewWhineButton...");
		CData oResult = SVSMAP();
		char cResult[8192] = {0};
		int ParamNumber = 4;
		cJSON *tmplist[20];
		string Method = "GetWebNewWhineButton";
#if 1
		if(GetWebNewWhineButtonINner(oResult, cResult) == false){
			mLogError("Failed to run  GetConsoleConfig(...)");
			return eInterfaceResCodeError;
		}
#endif 	
	
#if 0
		int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
		printf("SendConsoleCmd\n");
		for (int i = 0; i < iRecvLength; i++)
		{
			if (i < 4)
			{
				printf("%d", cResult[i]);
			}
			else 
			{
				printf("%c", cResult[i]);
			}
		}
#endif	
		for(int i = 1; i <= ParamNumber; i++)
		{
			tmplist[i] = cJSON_CreateObject();
			//mLogDebug("2222222222");
		}
		if( _AnalyParas.ConvertSTRING2CJSONGetWebNewWhine(oResult, cResult, Method,_result, _addressList, tmplist,  ParamNumber) == false){
			mLogError("Failed to run  ConvertSTRING2CJSONSendConsoleCmd(...)");
			return eInterfaceResCodeError;
		}
 
		cJSON_AddItemToObject(_result, "WhineList", _addressList);
		sResult = ComposeResult();
		cJSON_Delete(_result);

		return eInterfaceResCodeSuccess;

}
bool CSetWebNewWhine::SetDecAndMicWhineINner(int WhineChn,int WhineType, CData &oResult, char *cResult)
{
	mLogDebug("run SetWebNewWhineINner(...)");
	
	//1. 封装业务请求
	char szReqBody[REQ_BODY_MAXLEN] = { 0 };
	int num;
	switch(WhineChn)
	{
		case 15:
			 num = 1;
			 break;
		case 16:
			 num = 2;
			 break;
		case 17:
			 num = 5;
			 break;
		case 18:
			 num = 6;
			 break;
		default:
			 mLogError("SetWebNewWhineINner WhineChn error !!!\n"<<WhineChn);
			 return false;
	 }
	
	switch(WhineType)
	{
		case 1:
			 sprintf(szReqBody, "aud_out1.ch%d.audio_crack_mode=%d\naud_out1.ch%d.audio_crack=1\n", num, WhineType, num);
			 break;
		case 2:
			 sprintf(szReqBody, "aud_out1.ch%d.audio_crack_mode=%d\naud_out1.ch%d.audio_crack=1\n", num, WhineType, num);
			 break;
		case 3:
			 sprintf(szReqBody, "aud_out1.ch%d.audio_crack=0\n", num);
			 break;
	 }					
	
	int realBodySize = strlen(szReqBody);
					
	char szReqCmd[REQ_CMD_MAXLEN] = { 0 };
	szReqCmd[0] = 0;  //不加密
	szReqCmd[1] = 3;  //2Get请求, 3是SET, 4是SYS
	szReqCmd[2] = realBodySize >> 8;
	szReqCmd[3] = realBodySize;
	memcpy(&szReqCmd[4], szReqBody, realBodySize);
					
	//2. 发送socket请求
	MPSOperationRes opResCode = eMPSResultOK; //??
	ResponseCode resCode = _client->GetConfigNew(szReqCmd, 4 + realBodySize, opResCode, oResult, cResult);
	if (resCode != eResponseCodeSuccess) {
		mLogError("GetConfig(...) error:" << resCode);
		return false;
	}

	return true;

}
bool CSetWebNewWhine::GetDecAndMicWhineINner( CData &oResult, char *cResult, int WhineChn)
{
	mLogDebug("run SetWebNewWhineINner(...)");
	
	//1. 封装业务请求
	char *ReqBody;
	int num;
	char szReqBody[REQ_BODY_MAXLEN] = { 0 };
	memset(szReqBody,0,REQ_BODY_MAXLEN);
//	for(int WhineChn = 1; WhineChn <= 4; WhineChn++)
	{
		switch(WhineChn)
	    {
			case 15:
				 num = 1;
				 break;
			case 16:
				 num = 2;
				 break;
			case 17:
				 num = 5;
				 break;
			case 18:
				 num = 6;
				 break;
			default:
				 mLogError("GetDecAndMicWhineINner WhineChn error !!!\n"<<WhineChn);
				 return false;
		 }

		ReqBody = szReqBody + strlen(szReqBody);
		sprintf(ReqBody, "aud_out1.ch%d.audio_crack_mode\naud_out1.ch%d.audio_crack\n", num,num);
	}	
	
	//sprintf(szReqBody, "aud_out1.ch1.audio_crack_mode\n");
	mLogDebug("szReqBody = "<<szReqBody);
	int realBodySize = strlen(szReqBody);
					
	char szReqCmd[REQ_CMD_MAXLEN] = { 0 };
	szReqCmd[0] = 0;  //不加密
	szReqCmd[1] = 2;  //2Get请求, 3是SET, 4是SYS
	szReqCmd[2] = realBodySize >> 8;
	szReqCmd[3] = realBodySize;
	memcpy(&szReqCmd[4], szReqBody, realBodySize);
					
	//2. 发送socket请求
	MPSOperationRes opResCode = eMPSResultOK; //??
	ResponseCode resCode = _client->GetConfigNew(szReqCmd, 4 + realBodySize, opResCode, oResult, cResult);
	if (resCode != eResponseCodeSuccess) {
		mLogError("GetConfig(...) error:" << resCode);
		return false;
	}

	return true;

}
bool CSetWebNewWhine::SetWebMICGainInner(CData& oResult, char* cResult,int MicVal, int ChnNam)
{
	mLogDebug("run SetWebAudioConfInner(...)");

	 int SerialID = 1;//串口透传，串口1
	 int  cCmdLength   = 0;
	 char cCmdSend[1024]   = {0};
	 
	sqlite3 *reg_db = NULL;
	char DataBuf[1024];
	char *buf;
	char *register_db = "Audio_manage.db";
	
	STU stu;
	time_t cur_time = time(NULL);
	struct tm *tm_ptr;
	tm_ptr = localtime(&cur_time);
	reg_db = (sqlite3 *)create_db(register_db); //创建数据库
	create_db_table(reg_db);  //创建注册表
	memset(DataBuf, 0, 1024);
	 //string Cmd[8] = {"<1,2,2,0,0>","<2,2,2,0,0>","<3,2,2,0,0>","<4,2,2,0,0>","<5,2,2,0,0>","<6,2,2,0,0>","<7,2,2,0,0>"};
	 //cCmdLength = strlen(Cmd.c_str());
	 //memcpy(cCmdSend, Cmd.c_str(), strlen(Cmd.c_str()));
	 float Valtmp = MicVal;
	 float GainVal = Valtmp/10;
	 //<指令类型,操作类型,输入/输出,通道,值>
	 sprintf(cCmdSend,"<8,1,2,%d,%.1f>", ChnNam, GainVal); 
	 cCmdLength = strlen(cCmdSend);
	 
	 MPSOperationRes opResCode = eMPSResultOK;
	 ResponseCode resCode = _client->GetSerialNew(SerialID, cCmdSend, cCmdLength, opResCode, oResult,cResult);
	 if(resCode != eResponseCodeSuccess){
		 mLogError("GetSerialNew(...) error:"<<resCode);
		 return false;
	 }
	//判断是否设置变声调节成功
	 char *arg[MAX_ARG_NUM] = {};
	 for (int i = 0; i < MAX_ARG_NUM; i ++)
	 {
		 arg[i] = (char *)calloc(1, strlen(cResult)+1);
		 if(NULL == arg[i]) 
		 {
		   mLogError("calloc is error\n");
		   return false;
		  }
	  }
	 sscanf(cResult, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s", arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9]);
	 if (strcmp("ok>", arg[5]))
	 {
		 mLogError("SetWebMICGainInner failed");
		 return false;
	 }
//	 sprintf(DataBuf,"<8,2,2,%d,%d,ok>",ChnNam-1, MicVal);
//	 stu.id = 25 + ChnNam;
//	 sprintf(stu.val,DataBuf);
//	 sprintf(stu.name,"Audio_MICWhineGain%d",ChnNam);
//	 sprintf(stu.time, "%04d/%02d/%02d-%02d:%02d:%02d", tm_ptr->tm_year+1900, tm_ptr->tm_mon+1, tm_ptr->tm_mday, tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);
//	 update_stu_db(reg_db, &stu); //add 到数据库 
	 
	 sprintf(stu.name,"Audio_MICWhineGain0");
	 find_stu_db(reg_db, &stu, DataBuf);
	 //解析
	 char *carg[40] = {};
	 for (int i = 0; i < 40; i ++)
	 {
		  carg[i] = (char *)calloc(1, strlen(DataBuf)+1);
		  if(NULL == carg[i]) 
		  {
		   mLogError("calloc is error\n");
		   return eInterfaceResCodeError;
		 }
	  }
	 sscanf(DataBuf, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",\
	 carg[0], carg[1], carg[2], carg[3], carg[4], carg[5], carg[6], carg[7], carg[8], carg[9],\
	 carg[10], carg[11], carg[12], carg[13], carg[14], carg[15], carg[16], carg[17], carg[18], carg[19],\
	 carg[20], carg[21], carg[22], carg[23], carg[24], carg[25], carg[26], carg[27], carg[28], carg[29], \
	 carg[30], carg[31], carg[32], carg[33], carg[34], carg[35], carg[36], carg[37], carg[38], carg[39]);
	 //修改相应通道的值
	 int chn = atoi(arg[3]) + 3;
	 carg[chn] = arg[4];
	 //36个
	 sprintf(DataBuf,"%s", carg[0]);
	 for(int i = 1; i <= 27; i++)
	 {					 
		 buf = DataBuf + strlen(DataBuf);
	 
		 sprintf(buf,",%s", carg[i]);
		 
	 }
	 mLogDebug("DataBuf = "<<DataBuf);
	 //更新数据
	 stu.id = 11;
	 sprintf(stu.val,DataBuf);
	 sprintf(stu.name,"Audio_MICWhineGain0");
	 sprintf(stu.time, "%04d/%02d/%02d-%02d:%02d:%02d", tm_ptr->tm_year+1900, tm_ptr->tm_mon+1, tm_ptr->tm_mday, tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);
	 update_stu_db(reg_db, &stu); //add 到数据库 

	 return true;


}
bool CSetWebNewWhine::SetWebMICWhineButtonInner(CData& oResult, char* cResult,int ButtonVal, int ChnNam)
{
	mLogDebug("run SetWebMICWhineButtonInner(...)");

	 //获取状态
	 int SerialID = 1;//串口透传，串口1
	 int  cCmdLength   = 0;
	 char cCmdSend[1024]   = {0};
	 
	sqlite3 *reg_db = NULL;
	char DataBuf[1024];
	char *buf;
	char *register_db = "Audio_manage.db";
	
	STU stu;
	time_t cur_time = time(NULL);
	struct tm *tm_ptr;
	tm_ptr = localtime(&cur_time);
	reg_db = (sqlite3 *)create_db(register_db); //创建数据库
	create_db_table(reg_db);  //创建注册表
	memset(DataBuf, 0, 1024);
	 //string Cmd[8] = {"<1,2,2,0,0>","<2,2,2,0,0>","<3,2,2,0,0>","<4,2,2,0,0>","<5,2,2,0,0>","<6,2,2,0,0>","<7,2,2,0,0>"};

	 //<指令类型,操作类型,输入/输出,通道,值>
	 //开启变声开关
	 char Mute[10];
	if(ButtonVal == 0)
	{
		sprintf(Mute,"true"); 

	}else{
		sprintf(Mute,"false"); 

	}
	 sprintf(cCmdSend,"<7,1,2,%d,%s>",ChnNam, Mute); 
	 mLogDebug("cCmdSend:"<<cCmdSend);
	 
	 cCmdLength = strlen(cCmdSend);
	 
	 MPSOperationRes opResCode = eMPSResultOK;
	 //发送cCmdSend信息给服务器
	 ResponseCode resCode = _client->GetSerialNew(SerialID, cCmdSend, cCmdLength, opResCode, oResult, cResult);
	 if(resCode != eResponseCodeSuccess){
		 mLogError("GetSerialNew1(...) error:"<<resCode);
		 return false;
	 }
	 //判断是否开启开关成功
	 char *arg[MAX_ARG_NUM] = {};
	 for (int i = 0; i < MAX_ARG_NUM; i ++)
	 {
		 arg[i] = (char *)calloc(1, strlen(cResult)+1);
		 if(NULL == arg[i]) 
		 {
		   mLogError("calloc is error\n");
		   return false;
		  }
	  }
	 sscanf(cResult, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s", arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9]);
	 if (strcmp("ok>", arg[5]))
	 {
		 mLogDebug("cResult:"<<cResult);
		 mLogError("open or off button failed");
		 return false;
	 }
//	 sprintf(DataBuf,"<7,2,2,%d,%d,ok>",ChnNam-1, ButtonVal);
//	 stu.id = 11 + ChnNam;
//	 sprintf(stu.val,DataBuf);
//	 sprintf(stu.name,"Audio_MICWhineButton%d",ChnNam);
//	 sprintf(stu.time, "%04d/%02d/%02d-%02d:%02d:%02d", tm_ptr->tm_year+1900, tm_ptr->tm_mon+1, tm_ptr->tm_mday, tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);
//	 update_stu_db(reg_db, &stu); //add 到数据库 
	 
	 sprintf(stu.name,"Audio_MICWhineButton0");
	 find_stu_db(reg_db, &stu, DataBuf);
	 //解析
	 char *carg[40] = {};
	 for (int i = 0; i < 40; i ++)
	 {
		  carg[i] = (char *)calloc(1, strlen(DataBuf)+1);
		  if(NULL == carg[i]) 
		  {
		   mLogError("calloc is error\n");
		   return eInterfaceResCodeError;
		 }
	  }
	 sscanf(DataBuf, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",\
	 carg[0], carg[1], carg[2], carg[3], carg[4], carg[5], carg[6], carg[7], carg[8], carg[9],\
	 carg[10], carg[11], carg[12], carg[13], carg[14], carg[15], carg[16], carg[17], carg[18], carg[19],\
	 carg[20], carg[21], carg[22], carg[23], carg[24], carg[25], carg[26], carg[27], carg[28], carg[29], \
	 carg[30], carg[31], carg[32], carg[33], carg[34], carg[35], carg[36], carg[37], carg[38], carg[39]);
	 int chn = atoi(arg[3]) + 3;//找到 <，，>数据中对应通道的数据的位置
	 carg[chn] = arg[4];//修改数据
	 //36个字符“，”除外
	 sprintf(DataBuf,"%s", carg[0]);
	 for(int i = 1; i <= 27; i++)
	 {					 
		 buf = DataBuf + strlen(DataBuf);
	 
		 sprintf(buf,",%s", carg[i]);
		 
	 }
	 mLogDebug("DataBuf = "<<DataBuf);
	 //更新数据
	 stu.id = 10;
	 sprintf(stu.val,DataBuf);
	 sprintf(stu.name,"Audio_MICWhineButton0");
	 sprintf(stu.time, "%04d/%02d/%02d-%02d:%02d:%02d", tm_ptr->tm_year+1900, tm_ptr->tm_mon+1, tm_ptr->tm_mday, tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);
	 update_stu_db(reg_db, &stu); //add 到数据库 

	 return true;

}

InterfaceResCode CSetWebNewWhine::SetDecAndMicWhine(string &sResult,int WhineChn,int WhineType)
{
		mLogInfo("SetDecAndMicWhine...");
		CData oResult = SVSMAP();
		char cResult[8192] = {0};
		char Result[8192] = {0};
		int MicVal;
		
#if 1
		if(WhineChn <= 14)
		{
			switch(WhineType)
			{
				case 1:
					 MicVal = 10;//大叔音
					if (!SetWebMICWhineButtonInner(oResult, cResult, 1, WhineChn))
					{
						mLogError("Failed to run  SetWebMICWhineButtonInner(...)");
						return eInterfaceResCodeError;
					}
					//MIC通道：1-14
					 if (!SetWebMICGainInner(oResult, Result, MicVal, WhineChn))
					 {
						 mLogError("Failed to run  SetWebMICGainInner(...)");
						 return eInterfaceResCodeError;
					 }
					 
					 break;
				case 2:
					 MicVal = 25;//萝莉音
					if (!SetWebMICWhineButtonInner(oResult, cResult, 1, WhineChn))
					{
						mLogError("Failed to run  SetWebMICWhineButtonInner(...)");
						return eInterfaceResCodeError;
					}
					//MIC通道：1-14
					if (!SetWebMICGainInner(oResult, Result, MicVal, WhineChn))
					{
						mLogError("Failed to run  SetWebMICGainInner(...)");
						return eInterfaceResCodeError;
					}
					 break;
				case 3:
					//关闭变声
				 	if (!SetWebMICWhineButtonInner(oResult, cResult, 0, WhineChn))
					{
						mLogError("Failed to run  SetWebMICWhineButtonInner(...)");
						return eInterfaceResCodeError;
					}
					break;
			 }
			
		}
		else
		{
			//音频解码通道：15、16、17、18
			if(SetDecAndMicWhineINner(WhineChn, WhineType, oResult, cResult) == false)
			{
				mLogError("Failed to run  SetDecAndMicWhineINner(...)");
				return eInterfaceResCodeError;
			}
		}

#endif 
	
#if 0	
		if (!_AnalyParas.ConvertSTRING2CJSONParseSerialCmdParam(oResult, cResult, _result, _addressList))
		{
			mLogError("Failed to run  ConvertSTRING2CJSONParseSerialCmdParam(...)");
			return eInterfaceResCodeError;
		}
#endif		
#if 0
		int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
		printf("SendConsoleCmd\n");
		for (int i = 0; i < iRecvLength; i++)
		{
			if (i < 4)
			{
				printf("%d", cResult[i]);
			}
			else 
			{
				printf("%c", cResult[i]);
			}
		}
	
		if( _AnalyParas.ConvertSTRING2CJSONSendConsoleCmd(oResult, cResult) == false){
			mLogError("Failed to run  ConvertSTRING2CJSONSendConsoleCmd(...)");
			return eInterfaceResCodeError;
		}
#endif 
	
		sResult = ComposeResult();
		cJSON_Delete(_result);

		return eInterfaceResCodeSuccess;

}

bool CSetWebNewWhine::GetWebMICWhineButtonInner(CData& oResult, char* cResult, int ChnNam, int &ButtonVal)
{
	mLogDebug("run GetWebMICWhineButtonInner(...)");
#if 0
	 //获取状态
	 int SerialID = 1;//串口透传，串口1
	 int  cCmdLength   = 0;
	 char cCmdSend[1024]   = {0};
	 //string Cmd[8] = {"<1,2,2,0,0>","<2,2,2,0,0>","<3,2,2,0,0>","<4,2,2,0,0>","<5,2,2,0,0>","<6,2,2,0,0>","<7,2,2,0,0>"};
	 //cCmdLength = strlen(Cmd.c_str());
	 //memcpy(cCmdSend, Cmd.c_str(), strlen(Cmd.c_str()));

	 //<指令类型,操作类型,输入/输出,通道,值>
	 //开启变声开关
	 sprintf(cCmdSend,INTERFACE_GETWEB_WHINE_OPEN_SENDCMD,ChnNam-1); 
	 cCmdLength = strlen(cCmdSend);
	 
	 MPSOperationRes opResCode = eMPSResultOK;
	 //发送cCmdSend信息给服务器
	 ResponseCode resCode = _client->GetSerialNew(SerialID, cCmdSend, cCmdLength, opResCode, oResult, cResult);
	 if(resCode != eResponseCodeSuccess){
		 mLogError("GetSerialNew1(...) error:"<<resCode);
		 return false;
	 }
 		 //判断开关状态
	 char *arg[MAX_ARG_NUM] = {};
	 for (int i = 0; i < MAX_ARG_NUM; i ++)
	 {
		 arg[i] = (char *)calloc(1, strlen(cResult)+1);
		 if(NULL == arg[i]) 
		 {
		   mLogError("calloc is error\n");
		   return false;
		  }
	  }
	 sscanf(cResult, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s", arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9]);
	 if (strcmp("ok>", arg[5]))
	 {
		 mLogError("GET MIC button failed");
		 return false;
	 }
	 if (!strcmp("1", arg[4]))
	 {
		 cJSON_AddItemToObject(_result, "ButtonVal", cJSON_CreateNumber(1));
		 cJSON_AddItemToObject(_result, "ChnName", cJSON_CreateNumber(ChnNam));
	 }
	 else if(!strcmp("0", arg[4]))
	 {
	 	cJSON_AddItemToObject(_result, "ButtonVal", cJSON_CreateNumber(0));
	 	cJSON_AddItemToObject(_result, "ChnName", cJSON_CreateNumber(ChnNam));
	 }else{
	 	mLogError("GET MIC button failed!!!");
	 	return false;
	 }
#else
	 sqlite3 *reg_db = NULL;
	 char DataBuf[1024]={0};
	 char *buf;
	 char *register_db = "Audio_manage.db";
	
	 STU stu;
	 time_t cur_time = time(NULL);
	 struct tm *tm_ptr;
	 tm_ptr = localtime(&cur_time);
	 reg_db = (sqlite3 *)create_db(register_db); //创建数据库
	 create_db_table(reg_db);  //创建注册表
	 
 	memset(cResult, 0, RES_BUF_MAXLEN);
	sprintf(stu.name,"Audio_MICWhineButton0");	 
 	find_stu_db(reg_db, &stu, DataBuf);
	
	 char *arg[40] = {};
	 for (int i = 0; i < 40; i ++)
	 {
		 arg[i] = (char *)calloc(1, strlen(DataBuf)+1);
		 if(NULL == arg[i]) 
		 {
			mLogError("calloc is error\n");
			return false;
		 }
	 }
	 
	 //mLogDebug("cResult:"<<cResult);
	 
	 //命令格式cResult: "<9（指令类型）,2（操作类型，1:SET，2:GET）,2（输入2/输出1）,1（通道0~31）,80（值）,ok（状态）>"
	 sscanf(DataBuf, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",\
	 arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9],\
	 arg[10], arg[11], arg[12], arg[13], arg[14], arg[15], arg[16], arg[17], arg[18], arg[19],\
	 arg[20], arg[21], arg[22], arg[23], arg[24], arg[25], arg[26], arg[27], arg[28], arg[29], \
	 arg[30], arg[31], arg[32], arg[33], arg[34], arg[35], arg[36], arg[37], arg[38], arg[39]);
 
//	 int chn = ChnNam + 3;
//	 int Mute;
//	 if(!strcmp(arg[chn],"true"))
//	 {
//		 Mute = 1; 
//	 
//	 }
//	 else if(!strcmp(arg[chn],"false"))
//	 {
//		 Mute = 0;
//	 }
//	 else{
//	 
//		 mLogError("GetWebMICWhineButtonInner arg[chn] err");
//		 return false;
//	 }
	 mLogDebug("DataBuf:"<<DataBuf<<"   arg[27]:"<<arg[27]);

	 if (strcmp("ok>", arg[27]))
	 {
		 mLogError("GET MIC button failed");
		 return false;
	 }
	 
	 //获取对应通道开关状态
	 int chn = ChnNam + 3;
	 
	 if(!strcmp(arg[chn],"true"))
	 {
		 ButtonVal = 0; 
	 
	 }
	 else if(!strcmp(arg[chn],"false"))
	 {
		 ButtonVal = 1;
	 }
	 
//	for(int i = 1; i <= 14; i++)
//	{
//		 if(!strcmp(arg[chn],"true"))
//		 {
//			 Mute = 0; 
//		 
//		 }
//		 else if(!strcmp(arg[chn],"false"))
//		 {
//			 Mute = 1;
//		 }
//		 else{
//		 
//			 mLogError("GetWebMICWhineButtonInner arg[chn] err");
//			 return false;
//		 }
//		 
//		cJSON * tmp = cJSON_CreateObject();
//		cJSON_AddItemToObject(tmp, "ButtonVal", cJSON_CreateNumber(Mute));
//		cJSON_AddItemToObject(tmp, "ChnName", cJSON_CreateNumber(i));
//		cJSON_AddItemToArray(_addressList, tmp);
//	 }
#endif
//	 cJSON_AddItemToObject(_result, "AudioList", _addressList);

	 return true;

}
bool CSetWebNewWhine::GetWebMICGainInner(CData& oResult, char* cResult, int ChnNam, int &MicVal)
{
	mLogDebug("run GetWebMICGainInner(...)");
#if 0

	 int SerialID = 1;//串口透传，串口1
	 int  cCmdLength   = 0;
	 char cCmdSend[1024]   = {0};
	 //string Cmd[8] = {"<1,2,2,0,0>","<2,2,2,0,0>","<3,2,2,0,0>","<4,2,2,0,0>","<5,2,2,0,0>","<6,2,2,0,0>","<7,2,2,0,0>"};
	 //cCmdLength = strlen(Cmd.c_str());
	 //memcpy(cCmdSend, Cmd.c_str(), strlen(Cmd.c_str()));

	 //<指令类型,操作类型,输入/输出,通道,值>
	 sprintf(cCmdSend,INTERFACE_GETWEB_MIC_GAIN_SENDCMD, ChnNam-1); 
	 cCmdLength = strlen(cCmdSend);
	 
	 MPSOperationRes opResCode = eMPSResultOK;
	 ResponseCode resCode = _client->GetSerialNew(SerialID, cCmdSend, cCmdLength, opResCode, oResult,cResult);
	 if(resCode != eResponseCodeSuccess){
		 mLogError("GetSerialNew(...) error:"<<resCode);
		 return false;
	 }
#else
	sqlite3 *reg_db = NULL;
	char DataBuf[1024];
	char *buf;
	char *register_db = "Audio_manage.db";
//	int ChnNum[5] = {1,16,28,1,4};
	
	STU stu;
	time_t cur_time = time(NULL);
	struct tm *tm_ptr;
	tm_ptr = localtime(&cur_time);
	reg_db = (sqlite3 *)create_db(register_db); //创建数据库
	create_db_table(reg_db);  //创建注册表

	sprintf(stu.name,"Audio_MICWhineGain0");

	find_stu_db(reg_db, &stu, DataBuf);
	
#endif
	//判断是否获取变声调节成功
//	 char *arg[MAX_ARG_NUM] = {};
//	 for (int i = 0; i < MAX_ARG_NUM; i ++)
//	 {
//		 arg[i] = (char *)calloc(1, strlen(cResult)+1);
//		 if(NULL == arg[i]) 
//		 {
//		   mLogError("calloc is error\n");
//		   return false;
//		  }
//	  }
//	 sscanf(cResult, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s", arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9]);
//	 if (strcmp("ok>", arg[5]))
//	 {
//		 mLogError("GetWebMICGainInner failed");
//		 return false;
//	 }
	 
	 char *arg[40] = {};
	 for (int i = 0; i < 40; i ++)
	 {
		 arg[i] = (char *)calloc(1, strlen(DataBuf)+1);
		 if(NULL == arg[i]) 
		 {
			mLogError("calloc is error\n");
			return false;
		 }
	 }
	 
	 //mLogDebug("cResult:"<<cResult);
	 
	 //命令格式cResult: "<9（指令类型）,2（操作类型，1:SET，2:GET）,2（输入2/输出1）,1（通道0~31）,80（值）,ok（状态）>"
	 sscanf(DataBuf, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",\
	 arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9],\
	 arg[10], arg[11], arg[12], arg[13], arg[14], arg[15], arg[16], arg[17], arg[18], arg[19],\
	 arg[20], arg[21], arg[22], arg[23], arg[24], arg[25], arg[26], arg[27], arg[28], arg[29], \
	 arg[30], arg[31], arg[32], arg[33], arg[34], arg[35], arg[36], arg[37], arg[38], arg[39]);
 

	 
	 int chn = ChnNam + 3;

	 char tmp[10];
	 float Valtmp;
	 sprintf(tmp,"%s",arg[chn]);
	
	 sscanf(tmp,"%f",&Valtmp);
//	 mLogDebug("Valtmp:"<<Valtmp);
	 int Val = Valtmp*10;//转换为web音量取值范围-720-120

	 MicVal = Val;
	 sprintf(cResult,"<8,2,2,%d,%d,ok>", ChnNam, Val);
	 
	 mLogDebug("cResult = "<<cResult);
 	 mLogDebug("arg[chn] = "<<arg[chn]);

//	 cJSON_AddNumberToObject(_result, "MicVal", Val);

	 return true;

}

InterfaceResCode CSetWebNewWhine::GetDecAndMicWhine(string &sResult, int WhineChn)
{
		mLogInfo("GetDecAndMicWhine...");
		CData oResult = SVSMAP();
		char cResult[8192] = {0};
		int ParamNumber = 4;
		cJSON *tmplist[20];
		string Method = "GetDecAndMicWhine";
		int ButtonVal,MicVal;
#if 1		
		if(WhineChn <= 14)
		{
			if (!GetWebMICWhineButtonInner(oResult, cResult, WhineChn, ButtonVal))
			{
				mLogError("Failed to run  GetWebMICWhineButtonInner(...)");
				return eInterfaceResCodeError;
			}
			if(ButtonVal == 1)
			{
				if(GetWebMICGainInner( oResult, cResult, WhineChn, MicVal) == false)
				{
					mLogError("Failed to run  GetWebMICGainInner(...)");
					return eInterfaceResCodeError;
				}
				cJSON_AddItemToObject(_result, "WhineChn", cJSON_CreateNumber(WhineChn));
				if(MicVal > 20)
				{
					cJSON_AddItemToObject(_result,"WhineType",cJSON_CreateNumber(2));

				}else{
					cJSON_AddItemToObject(_result,"WhineType",cJSON_CreateNumber(1));
				}
				
			}
			else
			{
				cJSON_AddItemToObject(_result, "WhineChn", cJSON_CreateNumber(WhineChn));
				cJSON_AddItemToObject(_result,"WhineType",cJSON_CreateNumber(3));
			}

		}
		else if(WhineChn > 14 && WhineChn <= 18)
		{
			//音频解码通道：15、16、17、18
			if(GetDecAndMicWhineINner(oResult, cResult, WhineChn) == false)
			{
				mLogError("Failed to run  GetDecAndMicWhineINner(...)");
				return eInterfaceResCodeError;
			}
			
			tmplist[0] = cJSON_CreateObject();
			
			if( _AnalyParas.ConvertSTRING2CJSONGetWebNewWhine(oResult, cResult, Method,_result, _addressList, tmplist,  ParamNumber) == false)
			{
				mLogError("Failed to run  ConvertSTRING2CJSONSendConsoleCmd(...)");
				return eInterfaceResCodeError;
			}

			cJSON *WhineButton = cJSON_GetObjectItem(tmplist[0],"WhineButton");
//			cJSON *WhineChn = cJSON_GetObjectItem(tmplist[0],"WhineChn");
			cJSON *WhineType = cJSON_GetObjectItem(tmplist[0],"WhineType");
			if(WhineButton->valueint == 0)
			{
				cJSON_AddItemToObject(_result,"WhineType",cJSON_CreateNumber(3));
				cJSON_AddItemToObject(_result,"WhineChn",cJSON_CreateNumber(WhineChn));
			}
			else
			{
				cJSON_AddItemToObject(_result,"WhineType",cJSON_CreateNumber(WhineType->valueint));
				cJSON_AddItemToObject(_result,"WhineChn",cJSON_CreateNumber(WhineChn));
			}
		}
		else
		{
			mLogError("WhineChn is Error !!!");
			return eInterfaceResCodeError;
		}
#endif 	
	
#if 0
		int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
		printf("SendConsoleCmd\n");
		for (int i = 0; i < iRecvLength; i++)
		{
			if (i < 4)
			{
				printf("%d", cResult[i]);
			}
			else 
			{
				printf("%c", cResult[i]);
			}
		}
#endif
		//mLogDebug("GetWebNewWhineINner ");

//		if( _AnalyParas.ConvertSTRING2CJSONGetWebNewWhine(oResult, cResult, Method,_result, _addressList, tmplist,  ParamNumber) == false){
//			mLogError("Failed to run  ConvertSTRING2CJSONSendConsoleCmd(...)");
//			return eInterfaceResCodeError;
//		}
// 
//		cJSON_AddItemToObject(_result, "WhineList", _addressList);

		sResult = ComposeResult();
		cJSON_Delete(_result);

		return eInterfaceResCodeSuccess;

}



