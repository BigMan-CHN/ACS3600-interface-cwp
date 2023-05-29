#ifndef CSETOSDCTRL_H
#define CSETOSDCTRL_H
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

class CSetOsdCtrl
{
public:
    CSetOsdCtrl(string ip=MPS_IP, int port=MPS_PORT, int timeOut=MPS_TIMEOUT);

    /**
     * @brief CSetOsdCtrlStart 获取主机的网络配置信息和通道配置信息
     * @param sResult
     * @return 0：成功，!0：失败.
     */
    InterfaceResCode SetOsdCtrlStart(string &sResult,int OsdMode,int ChannelID,string Title,int OsdType);

    /**
     * @brief CSetOsdCtrlStop 获取主机的网络配置信息和通道配置信息
     * @param sResult
     * @return 0：成功，!0：失败.
     */
    InterfaceResCode SetOsdCtrlStop(string &sResult,int OsdMode,int ChannelID);
	InterfaceResCode SetCwpOsd(string &sResult,int Chn, int Post,int Num, int Type, string Content, int OverlayDisplay, int Color, int FontSize, int TimeORText);
	InterfaceResCode SetCwpOsdDel(string &sResult, int ChannelID, int OsdChnID);

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
     * @brief SetOsdStart 获取主机配置信息
     * @param RtspNum
     * @param H323Num
     * @param oResult
     * @param cResult
     * @return true：成功，false：失败.
     */
    bool SetOsdStart(int OsdMode,int ChannelID,string Title,int OsdType, CData &oResult, char *cResult);

    /**
     * @brief SetOsdStop 获取主机配置信息
     * @param RtspNum
     * @param H323Num
     * @param oResult
     * @param cResult
     * @return true：成功，false：失败.
     */
    bool SetOsdStop(int OsdMode,int ChannelID, CData &oResult, char *cResult);
	bool SetCwpOsdInner( int OverlayDisplay, int Chn, int Post, int Num, int Type, string Content, int Color, int FontSize, int TimeORText, CData &oResult, char *cResult);
	bool SetCwpOsdDelInner(int ChannelID, int OsdChnID, CData &oResult, char *cResult);

private:
    //待控制设备ip,端口号,超时时间
    string _ip;
    int _port;
    int _timeOut;

    MPSClient *_client;
    CAnalyzeParaProc _AnalyParas;

    //用于存储结果
    cJSON *_result;
};

#endif // CSETOSDCTRL_H