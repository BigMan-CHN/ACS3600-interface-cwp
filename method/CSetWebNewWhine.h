#ifndef SetWebNewWhine_H
#define SetWebNewWhine_H
/********************************************************
 * public c/c++ standard headers
 *******************************************************/
#include <stdio.h>
#include <iostream>
#include <string.h>

/********************************************************
 * boost usart headers
 *******************************************************/
#include <boost/asio.hpp>
#include <boost/bind.hpp>

/********************************************************
 * lib headers
 *******************************************************/
#include <log.h>
#include <TransmitClient.h>
#include <xmlParser.h>
#include <LibXML.h>
#include <Server.h>
#include <cJSON.h>
#include <ctime>

#include "interfaceDefines.h"
#include "MPSClient.h"
#include "CAnalyzeParaProc.h"
#include "stu_sqlite.h"
#include "sqlite3.h"

class CSetWebNewWhine
{
public:
    CSetWebNewWhine(string ip=MPS_IP, int port=MPS_PORT, int timeOut=MPS_TIMEOUT);

    /**
     * @brief GetHostDecInfo 获取主机的网络配置信息和通道配置信息
     * @param sResult
     * @return 0：成功，!0：失败.
     */
    InterfaceResCode GetWebNewWhine(string &sResult);
	
    InterfaceResCode SetWebNewWhine(string &sResult,int WhineChn,int WhineType);
	
	InterfaceResCode GetWebNewWhineButton(string &sResult);
	
	InterfaceResCode SetWebNewWhineButton(string &sResult,int WhineChn,int WhineButton);
	
	InterfaceResCode GetDecAndMicWhine(string &sResult, int WhineChn);
	
    InterfaceResCode SetDecAndMicWhine(string &sResult,int WhineChn,int WhineType);

private:
    /**
     * @brief ComposeResult 合并结果
     * @param result
     * @return true：成功，false：失败.
     */
    bool ComposeResult(cJSON * result);
    /**
     * @brief ComposeResult 合并结果
     */
    string ComposeResult();
	
    bool SetWebNewWhineINner(int WhineChn,int WhineType, CData &oResult, char *cResult);
	
	bool GetWebNewWhineINner( CData &oResult, char *cResult);
	
	bool SetWebNewWhineButtonINner(int WhineChn,int WhineButton, CData &oResult, char *cResult);
	
	bool GetWebNewWhineButtonINner( CData &oResult, char *cResult);
	
	bool SetDecAndMicWhineINner(int WhineChn,int WhineType, CData &oResult, char *cResult);

	bool GetDecAndMicWhineINner( CData &oResult, char *cResult, int WhineChn);

	bool SetWebMICGainInner(CData& oResult, char* cResult,int MicVal, int ChnNam);

	bool SetWebMICWhineButtonInner(CData& oResult, char* cResult,int ButtonVal, int ChnNam);

	bool GetWebMICWhineButtonInner(CData& oResult, char* cResult, int ChnNam, int &ButtonVal);

	bool GetWebMICGainInner(CData& oResult, char* cResult, int ChnNam, int &MicVal);

private:
    //待控制设备ip,端口号,超时时间
    string _ip;
    int _port;
    int _timeOut;

    MPSClient *_client;
    CAnalyzeParaProc _AnalyParas;

    //用于存储结果
    cJSON *_result;
    cJSON *_total;
    cJSON *_addressList;
};

#endif // CGETHOSTCHNINFO_H
