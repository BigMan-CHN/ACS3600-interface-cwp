#ifndef CGETHOSTDECINFO_H
#define CGETHOSTDECINFO_H
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

class CGetHostDecInfo
{
public:
    CGetHostDecInfo(string ip=MPS_IP, int port=MPS_PORT, int timeOut=MPS_TIMEOUT);

    /**
     * @brief GetHostDecInfo 获取主机的网络配置信息和通道配置信息
     * @param sResult
     * @return 0：成功，!0：失败.
     */
    InterfaceResCode GetHostDecInfo(string &sResult,int DecId);
	InterfaceResCode GetHostRTSPDecInfo(string &sResult,int DECID);
	InterfaceResCode GetHostH323DecInfo(string &sResult,int DECID);
	InterfaceResCode GetHostSIPDecInfo(string &sResult,int DECID);



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
    /**
     * @brief getDecConfig 获取主机配置信息
     * @param RtspNum
     * @param H323Num
     * @param oResult
     * @param cResult
     * @return true：成功，false：失败.
     */
    bool getDecConfig(int DecId,CData &oResult, char *cResult);
	bool getH323DecConfig(int DecId,CData &oResult, char *cResult);
	bool getSIPDecConfig(int DecId,CData &oResult, char *cResult);
	

private:
    //待控制设备ip,端口号,超时时间
    string _ip;
    int _port;
    int _timeOut;

    MPSClient *_client;
    CAnalyzeParaProc _AnalyParas;

    //用于存储结果
    cJSON *_result;
    cJSON *_rtspdec;
    cJSON *_h323dec;
	cJSON *_sipdec;
	
};

#endif // CGETHOSTDECINFO_H
