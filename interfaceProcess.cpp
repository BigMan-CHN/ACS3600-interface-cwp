#include "interfaceProcess.h"
#include "interfaceDefines.h"
#include "interfaceParams.h"
#include "InterfaceResponse.h"

#include "method/CSetDecCtrl.h"
#include "method/CSetPutNoteFileCtrl.h"
#include "method/CSetOsdCtrl.h"
#include "method/CSetPowerCtrl.h"
#include "method/CStreamCtrl.h"
#include "method/CDisciplineCtrl.h"
#include "method/CSetRecCtrl.h"
#include "method/CGetHostDecInfo.h"
#include "method/CGetHostChnInfo.h"
#include "method/CGetHostStatus.h"
#include "method/GetTaskContent.h"
#include "method/CGetChannelContents.h"
#include "method/CGetHostConfig.h"
#include "method/CSetTaskDelete.h"
#include "method/CSendConsoleCmd.h"
#include "method/CSendSerialCmd.h"
#include "method/CHostControlDec.h"
#include "method/CHostControlDiscipline.h"
#include "method/CHostControl.h"
#include "method/CSetpoint.h"
#include "method/CSetWebNewWhine.h"
#include "method/CSetWebNewMosaic.h"
#include "method/CGetWebMosaicList.h"

InterfaceProcess::InterfaceProcess(string ip, int port, int timeOut)
    : _ip(ip), _port(port), _timeOut(timeOut), _client(new MPSClient(ip, port, timeOut)), _debugMode(false)
{
    mLogDebug("ip:" << this->_ip << ",port:" << this->_port << ",timeOut:" << this->_timeOut);
}

string InterfaceProcess::processRequest(string &requestStr)
{
    InterfaceResCode resCode = eInterfaceResCodeSuccess;
    InterfaceParams params;
    interfaceResponse response;
    do
    {
        //分析获取请求数据
        if (!params.analysisParams(requestStr))
        {
            mLogError("Failed to run params.analysisParams(requestStr)");
            resCode = eInterfaceResCodeRequErrorParam;
            break;
        }
        string sMethod;
        if (!params.getMethod(sMethod))
        {
            mLogError("get params error node:" << REQUEST_NODE_METHOD);
            resCode = eInterfaceResCodeRequErrorParam;
            break;
        }

        //printf("nethod.c_str %s\n", sMethod.c_str());
        mLogInfo("request method:" << sMethod);
        if (!strcmp(sMethod.c_str(), "_version"))
        {
            GetHostStatus status;
            string sResult;
            resCode = status.GetVersion(sResult);
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_HOST_INIT))
        {
            //hostInit 打开设备指定通道的视频流
            mLogInfo("hostInit 打开设备指定通道的视频流");
            int chNum;
            if (!params.getParamsNodeValueofInt(HOSTNIT_PARAMS_CHANNELNUM, chNum))
            {
                mLogError("get params error node:" << HOSTNIT_PARAMS_CHANNELNUM);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            string caseId;
            if (!params.getParamsNodeValueofStr(HOSTNIT_PARAMS_CASEID, caseId))
            {
                mLogError("get params error node:" << HOSTNIT_PARAMS_CASEID);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!checkCaseIdisEnable(caseId))
            {
                mLogError("Failed to run checkCaseIdisEnable(caseId)=(" << caseId << ")");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!checkChannelNumisEnable(chNum))
            {
                mLogError("Failed to run checkChannelNumisEnable(chNum)=(" << chNum << ")");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            CHostControl hostControl(this->_ip);
            resCode = hostControl.HostInit(chNum, caseId);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_HOST_START))
        {
            //hostStart 开始设备指定通道的视频录制
            mLogInfo("hostStart 开始设备指定通道的视频录制");
            int chNum;
            if (!params.getParamsNodeValueofInt(HOSTNIT_PARAMS_CHANNELNUM, chNum))
            {
                mLogError("get params error node:" << HOSTNIT_PARAMS_CHANNELNUM);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            string caseId;
            if (!params.getParamsNodeValueofStr(HOSTNIT_PARAMS_CASEID, caseId))
            {
                mLogError("get params error node:" << HOSTNIT_PARAMS_CASEID);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!checkCaseIdisEnable(caseId))
            {
                mLogError("Failed to run checkCaseIdisEnable(caseId)=(" << caseId << ")");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!checkChannelNumisEnable(chNum))
            {
                mLogError("Failed to run checkChannelNumisEnable(chNum)=(" << chNum << ")");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            CHostControl hostControl(this->_ip);
            resCode = hostControl.HostStart(chNum, caseId);
            //            resCode = this->HostStartMethod(caseId);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_HOST_STOP))
        {
            //hostStop 停止设备指定通道的视频录制
            mLogInfo("hostStop 停止设备指定通道的视频录制");
            int chNum;
            if (!params.getParamsNodeValueofInt(HOSTNIT_PARAMS_CHANNELNUM, chNum))
            {
                mLogError("get params error node:" << HOSTNIT_PARAMS_CHANNELNUM);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            if (!checkChannelNumisEnable(chNum))
            {
                mLogError("Failed to run checkChannelNumisEnable(chNum)=(" << chNum << ")");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            CHostControl hostControl(this->_ip);
            resCode = hostControl.HostStop(chNum);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_HOST_CLOSE))
        {
            //hostClose 关闭设备指定通道的视频流
            mLogInfo("hostClose 关闭设备指定通道的视频流");
            int chNum;
            if (!params.getParamsNodeValueofInt(HOSTNIT_PARAMS_CHANNELNUM, chNum))
            {
                mLogError("get params error node:" << HOSTNIT_PARAMS_CHANNELNUM);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            if (!checkChannelNumisEnable(chNum))
            {
                mLogError("Failed to run checkChannelNumisEnable(chNum)=(" << chNum << ")");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            CHostControl hostControl(this->_ip);
            resCode = hostControl.HostClose(chNum);
            //            resCode = this->HostCloseMethod();
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_HOST_STATUS))
        {
            //hostStatus 获取设备指定通道的直播状态
            mLogInfo("hostStatus 获取设备指定通道的直播状态");
            int chNum;
            if (!params.getParamsNodeValueofInt(HOSTNIT_PARAMS_CHANNELNUM, chNum))
            {
                mLogError("get params error node:" << HOSTNIT_PARAMS_CHANNELNUM);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            if (!checkChannelNumisEnable(chNum))
            {
                mLogError("Failed to run checkChannelNumisEnable(chNum)=(" << chNum << ")");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            GetHostStatus hostStatus;
            string sResult;
            resCode = hostStatus.GethostStatus(chNum, sResult);
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_HOST_SHUTDOWN))
        {
            //shutdown 关闭主机
            mLogError("没有此方法:" << sMethod);
            resCode = eInterfaceResCodeReqNoMethod;
            break;
            mLogInfo("shutdown 关闭主机");
            CHostControl hostControl(this->_ip);
            resCode = hostControl.HostShutdown();
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_HOST_REBOOT))
        {
            //reboot 重启主机
            mLogInfo("reboot 重启主机");
            CHostControl hostControl(this->_ip);
            resCode = hostControl.HostReboot();
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_HOST_SETPOINT))
        {
            //setpoint 视频打点
            mLogError("没有此方法:" << sMethod);
            resCode = eInterfaceResCodeReqNoMethod;
            break;
            //*
            mLogInfo("setpoint 视频打点");
            int chNum;
            if (!params.getParamsNodeValueofInt(HOSTNIT_PARAMS_CHANNELNUM, chNum))
            {
                mLogError("get params error node:" << HOSTNIT_PARAMS_CHANNELNUM);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            CSetpoint setPoint(this->_ip);
            string sResult;
            resCode = setPoint.Setpoint(sResult, chNum);
            response.setResponseResults(sResult);
            break;
            //*/
        }
        else if (!strcmp(sMethod.c_str(), METHOD_GET_CHANNEL_CONTENTS))
        {
            //getChannelContents 获取指定通道时间段内内容列表
            mLogInfo("getChannelContents 获取指定通道时间段内内容列表");

            string startTime, endTime;
            if (!params.getParamsNodeValueofStr(GET_CHANNEL_CONTENTS_PARAMS_START_DATE, startTime))
            {
                mLogError("get params error node:" << GET_CHANNEL_CONTENTS_PARAMS_START_DATE);
                startTime = "0000-01-01";
                //                resCode = eInterfaceResCodeRequErrorParam;
                //                break;
            }
            if (!params.getParamsNodeValueofStr(GET_CHANNEL_CONTENTS_PARAMS_END_DATE, endTime))
            {
                mLogError("get params error node:" << GET_CHANNEL_CONTENTS_PARAMS_END_DATE);
                //                resCode = eInterfaceResCodeRequErrorParam;
                //                break;
                endTime = "9999-12-31";
            }

            CGetChannelContents getChContents(this->_ip);
            string sResult;
            resCode = getChContents.GetChannelContents(startTime, endTime, sResult);
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_GET_TASK_CONTENTS))
        {
            //getTaskContents 获取指定任务的内容列表
            mLogInfo("getTaskContents 获取指定任务的内容列表");
            string caseId;
            if (!params.getParamsNodeValueofStr(GET_TESK_CONTENTS_PARAMS_CASEID, caseId))
            {
                mLogError("get params error node:" << GET_TESK_CONTENTS_PARAMS_CASEID);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            string sResult;
            resCode = this->GetTaskContentMethod(caseId, sResult);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_GET_HOST_CONFIG))
        {
            //getHostConfig
            mLogInfo("getHostConfig 获取主机网络配置和通道配置信息");
            CGetHostConfig getHostConfig(this->_ip);
            string sResult;
            resCode = getHostConfig.GetHostConfig(sResult);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_GET_HOST_DECINFO))
        {
            //getHostDecInfo
            int DecId;
            mLogInfo("getHostDecInfo 获取解码通道配置信息");
            if (!params.getParamsNodeValueofInt(HOST_DEC_INFO_PARAMS_RTSP_CHANNEL, DecId))
            {
                mLogError("get params error node:" << HOST_DEC_INFO_PARAMS_RTSP_CHANNEL);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            CGetHostDecInfo getHostDecInfo(this->_ip);
            string sResult;
            resCode = getHostDecInfo.GetHostDecInfo(sResult, DecId);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_GET_HOST_CHNINFO))
        {
            //getHostChnInfo
            int ChnNum;
            mLogInfo("getHostChnInfo");
            if (!params.getParamsNodeValueofInt(HOST_DEC_INFO_PARAMS_CHN_CHANNEL, ChnNum))
            {
                mLogError("get params error node:" << HOST_DEC_INFO_PARAMS_CHN_CHANNEL);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            CGetHostChnInfo getHostChnInfo(this->_ip);
            string sResult;
            resCode = getHostChnInfo.GetHostChnInfo(sResult, ChnNum);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_SET_START_DEC))
        {
            //setdecstart
            int Dectype, Channal, CacheTime;
            string sAddr;
            bool TcpMode;
            mLogInfo("SetStartDec");
            if (!params.getParamsNodeValueofInt(SET_START_DEC_PARAMS_DECTYPE, Dectype))
            {
                mLogError("set params error node:" << SET_START_DEC_PARAMS_DECTYPE);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt(SET_START_DEC_PARAMS_CHANNEL, Channal))
            {
                mLogError("set params error node:" << SET_START_DEC_PARAMS_CHANNEL);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofStr(SET_START_DEC_PARAMS_ADDR, sAddr))
            {
                mLogError("set params error node:" << SET_START_DEC_PARAMS_ADDR);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt(SET_START_DEC_PARAMS_CACHETIME, CacheTime))
            {
                mLogError("set params error node:" << SET_START_DEC_PARAMS_CACHETIME);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofBool(SET_START_DEC_PARAMS_TCPMODE, TcpMode))
            {
                mLogError("set params error node:" << SET_START_DEC_PARAMS_TCPMODE);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            CSetDecCtrl setDecCtrl(this->_ip);
            string sResult;
            resCode = setDecCtrl.SetDecCtrlStart(sResult, Dectype, Channal, CacheTime, sAddr, TcpMode);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_SET_STOP_DEC))
        {
            //setdecstop
            int Dectype, Channal;
            mLogInfo("setdecstop");
            if (!params.getParamsNodeValueofInt(SET_START_DEC_PARAMS_DECTYPE, Dectype))
            {
                mLogError("set params error node:" << SET_START_DEC_PARAMS_DECTYPE);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt(SET_START_DEC_PARAMS_CHANNEL, Channal))
            {
                mLogError("set params error node:" << SET_START_DEC_PARAMS_CHANNEL);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            CSetDecCtrl setDecCtrl(this->_ip);
            string sResult;
            resCode = setDecCtrl.SetDecCtrlStop(sResult, Dectype, Channal);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_SET_START_REC))
        {
            //StartRecord
            int RecMode;
            string TaskId, Title, ChannelID;
            mLogInfo("StartRecord");
            if (!params.getParamsNodeValueofInt(SET_START_REC_PARAMS_RECMODE, RecMode))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_RECMODE);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofStr(SET_START_REC_PARAMS_CHNAME, ChannelID))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_CHNAME);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofStr(SET_START_REC_PARAMS_TASKID, TaskId))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_TASKID);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofStr(SET_START_REC_PARAMS_DESRIPTOR, Title))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_DESRIPTOR);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
            CSetRecCtrl setRecCtrl(this->_ip);
            string sResult;
            resCode = setRecCtrl.SetRecCtrlStart(sResult, RecMode, ChannelID, TaskId, Title);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_SET_STOP_REC))
        {
            //setrecstop
            int RecMode;
            string TaskId,ChannelID;
            mLogInfo("StopRecord");
            if (!params.getParamsNodeValueofInt(SET_START_REC_PARAMS_RECMODE, RecMode))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_RECMODE);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
			if (!params.getParamsNodeValueofStr(SET_START_REC_PARAMS_CHNAME, ChannelID))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_CHNAME);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofStr(SET_START_REC_PARAMS_TASKID, TaskId))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_TASKID);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
            CSetRecCtrl setRecCtrl(this->_ip);
            string sResult;
            resCode = setRecCtrl.SetRecCtrlStop(sResult, RecMode, TaskId, ChannelID);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_GET_INFOLIST_REC))
        {
            
            int GetMode;
            string TaskId,StartTime,EndTime;
            mLogInfo("GetRecInfo");
            if (!params.getParamsNodeValueofInt(GET_INFOLIST_REC_PARAMS_GETMODE, GetMode))
            {
                mLogError("set params error node:" << GET_INFOLIST_REC_PARAMS_GETMODE);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofStr(GET_INFOLIST_REC_PARAMS_TASKID, TaskId))
            {
                mLogError("set params error node:" << GET_INFOLIST_REC_PARAMS_TASKID);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofStr(GET_INFOLIST_REC_PARAMS_STARTTIME, StartTime))
            {
                mLogError("set params error node:" << GET_INFOLIST_REC_PARAMS_STARTTIME);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofStr(GET_INFOLIST_REC_PARAMS_ENDTIME, EndTime))
            {
                mLogError("set params error node:" << GET_INFOLIST_REC_PARAMS_STARTTIME);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
            CSetRecCtrl setRecCtrl(this->_ip);
            string sResult;
            resCode = setRecCtrl.GetRecCtrlInfoList(sResult, GetMode, TaskId, StartTime, EndTime);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
/*        else if (!strcmp(sMethod.c_str(), METHOD_SET_TASKDEL_REC))
        {
            
            string TaskId;
            mLogInfo("SetTaskDelete");
            if (!params.getParamsNodeValueofStr(SET_START_REC_PARAMS_TASKID, TaskId))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_TASKID);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            CSetRecCtrl setRecCtrl(this->_ip);
            string sResult;
            resCode = setRecCtrl.SetRecCtrlTaskDel(sResult, TaskId);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
*/       
		else if (!strcmp(sMethod.c_str(), METHOD_SET_START_DISCIPLINE))
        {
            bool LoopFlag;
            int  PlayList;
            if (!params.getParamsNodeValueofBool(SET_START_DISCIPLINE_PARAMS_LOOPFLAG, LoopFlag))
            {
                mLogError("set params error node:" << SET_START_DISCIPLINE_PARAMS_LOOPFLAG);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt(SET_START_DISCIPLINE_PARAMS_PLAYLIST, PlayList))
            {
                mLogError("set params error node:" << SET_START_DISCIPLINE_PARAMS_PLAYLIST);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            //SetStartDiscipline
            mLogInfo("SetStartDiscipline 获取主机网络配置和通道配置信息");
            CDiscipLineCtrl DiscipLineCtrl(this->_ip);
            string sResult;
            resCode = DiscipLineCtrl.SetDiscipLineCtrlStart(sResult,LoopFlag,PlayList);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_SET_STOP_DISCIPLINE))
        {
            //SetStopDiscipline
            mLogInfo("SetStartDiscipline 获取主机网络配置和通道配置信息");
            CDiscipLineCtrl DiscipLineCtrl(this->_ip);
            string sResult;
            resCode = DiscipLineCtrl.SetDiscipLineCtrlStop(sResult);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_GET_STATUS_DISCIPLINE))
        {
            //DisciplineStatus
            mLogInfo("DisciplineStatus 获取主机网络配置和通道配置信息");
            CDiscipLineCtrl DiscipLineCtrl(this->_ip);
            string sResult;
            resCode = DiscipLineCtrl.GetDiscipLineCtrlStatus(sResult);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_SET_RTMPPUSH_STREAM))
        {
            //SetRtmpCliPush
            int RtmpID, Channel;
            string Addr;
            mLogInfo("SetRtmpCliPush");
            if (!params.getParamsNodeValueofInt(SET_START_REC_PARAMS_RTMPID, RtmpID))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_RTMPID);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            if (!params.getParamsNodeValueofStr(SET_START_REC_PARAMS_RTMPADDR, Addr))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_RTMPADDR);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            if (!params.getParamsNodeValueofInt(SET_START_REC_PARAMS_RTMPCHANNEL, Channel))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_RTMPCHANNEL);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            CStreamCtrl StreamCtrl(this->_ip);
            string sResult;
            resCode = StreamCtrl.SetStreamCtrlRtmpPush(sResult, RtmpID, Channel, Addr);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_SET_OPEN_STREAM))
        {
            //setrecstop
            bool AllFlag;
            int ChannelID;
            mLogInfo("setrecstop");
            if (!params.getParamsNodeValueofBool(SET_START_REC_PARAMS_OPENALLFLAG, AllFlag))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_OPENALLFLAG);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt(SET_START_REC_PARAMS_OPENCHANNELID, ChannelID))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_OPENCHANNELID);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            CStreamCtrl StreamCtrl(this->_ip);
            string sResult;
            resCode = StreamCtrl.SetStreamCtrlOpen(sResult, AllFlag, ChannelID);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_SET_CLOSE_STREAM))
        {
            //setrecstop
            bool AllFlag;
            int ChannelID;
            mLogInfo("setrecstop");
            if (!params.getParamsNodeValueofBool(SET_START_REC_PARAMS_CLOSEALLFLAG, AllFlag))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_CLOSEALLFLAG);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt(SET_START_REC_PARAMS_CLOSECHANNELID, ChannelID))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_CLOSECHANNELID);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            CStreamCtrl StreamCtrl(this->_ip);
            string sResult;
            resCode = StreamCtrl.SetStreamCtrlClose(sResult, AllFlag, ChannelID);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_SET_CONTROL_POWER))
        {
            //setrecstop
            int Cmd;
            mLogInfo("setrecstop");
            if (!params.getParamsNodeValueofInt(SET_START_POWER_PARAMS_CMD, Cmd))
            {
                mLogError("set params error node:" << SET_START_POWER_PARAMS_CMD);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            CSetPowerCtrl PowerCtrl(this->_ip);
            string sResult;
            resCode = PowerCtrl.SetPowerCtrlCmd(sResult, Cmd);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_SEND_CONSOLE_CMD))
        {
            //setrecstop
            string Cmd;
            mLogInfo("SetConsoleCmd");
            if (!params.getParamsNodeValueofStr(SEND_CONSOLE_PARAMS_CMD, Cmd))
            {
                mLogError("set params error node:" << SEND_CONSOLE_PARAMS_CMD);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            CSendConsoleCmd CSendConsoleCmd(this->_ip);
            string sResult;
            resCode = CSendConsoleCmd.SendConsoleCmd(sResult, Cmd);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_SEND_SERIAL_CMD))
        {
            //setrecstop
            int SerialID;
            string Cmd;
            mLogInfo("SetConsoleCmd");
            if (!params.getParamsNodeValueofInt(SEND_SERILAL_PARAMS_SERIALID, SerialID))
            {
                mLogError("set params error node:" << SEND_SERILAL_PARAMS_SERIALID);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofStr(SEND_SERILAL_PARAMS_CMD, Cmd))
            {
                mLogError("set params error node:" << SEND_SERILAL_PARAMS_CMD);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            CSendSerialCmd CSendSerialCmd(this->_ip);
            string sResult;
            resCode = CSendSerialCmd.SendSerialCmd(sResult, SerialID, Cmd);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_SET_START_OSD))
        {
            
            mLogInfo("METHOD_SET_START_OSD 标记caseid为可删除");

            string Title;
            int OsdMode, ChannelID,OsdType;
            mLogInfo("SetOsd");
            if (!params.getParamsNodeValueofInt(SET_CONFIG_ADD_OSD_OSDMODE, OsdMode))
            {
                mLogError("set params error node:" << SET_CONFIG_ADD_OSD_OSDMODE);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt(SET_CONFIG_ADD_OSD_CHANNELID, ChannelID))
            {
                mLogError("set params error node:" << SET_CONFIG_ADD_OSD_OSDMODE);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
			if (!params.getParamsNodeValueofInt("OsdType", OsdType))
            {
                mLogError("set params error node:" << "OsdType");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofStr(SET_CONFIG_ADD_OSD_TITLE, Title))
            {
                mLogError("get params error node:" << SET_CONFIG_ADD_OSD_TITLE);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            CSetOsdCtrl CSetOsdCtrl(this->_ip);
            string sResult;
            resCode = CSetOsdCtrl.SetOsdCtrlStart(sResult, OsdMode, ChannelID, Title, OsdType);
			//设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_SET_STOP_OSD))
        {
            
            mLogInfo("METHOD_SET_STOP_OSD 标记caseid为可删除");

            int OsdMode, ChannelID;
            mLogInfo("DelOsd");
            if (!params.getParamsNodeValueofInt(SET_CONFIG_DEL_OSD_OSDMODE, OsdMode))
            {
                mLogError("set params error node:" << SET_CONFIG_ADD_OSD_OSDMODE);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt(SET_CONFIG_DEL_OSD_CHANNELID, ChannelID))
            {
                mLogError("set params error node:" << SET_CONFIG_ADD_OSD_OSDMODE);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            CSetOsdCtrl CSetOsdCtrl(this->_ip);
            string sResult;
            resCode = CSetOsdCtrl.SetOsdCtrlStop(sResult, OsdMode, ChannelID);
			 //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "SetCwpOsdDel"))
        {
            
            mLogInfo("SetCwpOsdDel");
            int ChnID,OsdChnID;
            if (!params.getParamsNodeValueofInt("OverlayChn", ChnID))
            {
                mLogError("set params error node:" << "OverlayChn");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt("OverlayNum", OsdChnID))
            {
                mLogError("set params error node:" << "OverlayNum");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            CSetOsdCtrl SetCwpOsdDel(this->_ip);
            string sResult;
            resCode = SetCwpOsdDel.SetCwpOsdDel(sResult, ChnID, OsdChnID);
			 //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "SetCwpOsd"))
        {
            
            int Chn, Post, Num, Type, OverlayDisplay, FontSize, Color, SelectType, TimeORText;
            string Content;
            mLogInfo("SetCwpOsd");
            if (!params.getParamsNodeValueofInt("OverlayChn", Chn))
            {
                mLogError("set params error node:" << "OverlayChn");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
			if (!params.getParamsNodeValueofInt("OverlayDisplay", OverlayDisplay))
            {
                mLogError("set params error node:" << "OverlayDisplay");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt("OverlayPost", Post))
            {
                mLogError("set params error node:" << "OverlayPost");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt("OverlayNum", Num))
            {
                mLogError("set params error node:" << "OverlayNum");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt("OverlayType", Type))
            {
                mLogError("set params error node:" << "OverlayType");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt("Color", Color))
            {
                mLogError("set params error node:" << "Color");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt("FontSize", FontSize))
            {
                mLogError("set params error node:" << "FontSize");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

			if (!params.getParamsNodeValueofInt("TimeORText", TimeORText))
            {
                mLogError("set params error node:" << "TimeORText");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofStr("OverlayContent", Content))
            {
                mLogError("set params error node:" << "OverlayContent");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
            CSetOsdCtrl SetCwpOsd(this->_ip);
            string sResult;
            resCode = SetCwpOsd.SetCwpOsd(sResult, Chn, Post, Num, Type, Content, OverlayDisplay, Color, FontSize, TimeORText);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
        else if (!strcmp(sMethod.c_str(), METHOD_SET_PUTNOTEFILE))
        {
            mLogInfo("METHOD_SET_PUTNOTEFILE 标记caseid为可删除");

            string TrialId, Content,FileName;
            int FileSize;
            if (!params.getParamsNodeValueofStr(SET_CONFIG_PUTNOTEFILE_TRIALID, TrialId))
            {
                mLogError("get params error node:" << SET_CONFIG_PUTNOTEFILE_TRIALID);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofStr(SET_CONFIG_PUTNOTEFILE_CONTENT, Content))
            {
                mLogError("get params error node:" << SET_CONFIG_PUTNOTEFILE_CONTENT);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofStr(SET_CONFIG_PUTNOTEFILE_FILENAME, FileName))
            {
                mLogError("get params error node:" << SET_CONFIG_PUTNOTEFILE_FILENAME);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt(SET_CONFIG_PUTNOTEFILE_FILESIZE, FileSize))
            {
                mLogError("get params error node:" << SET_CONFIG_PUTNOTEFILE_FILESIZE);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            CSetPutNoteFileCtrl CSetPutNoteFileCtrl(this->_ip);
            string sResult;
            resCode = CSetPutNoteFileCtrl.SetPutNoteFileCtrlStart(sResult,TrialId,Content,FileName,FileSize);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "GetRecordState"))
        {
            mLogInfo("GetRecordState");

            //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
            CSetRecCtrl getRecordState(this->_ip);
            string sResult;
            resCode = getRecordState.GetRecordState(sResult);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "PauseRecord"))
        {
            
            int RecMode;
            string TaskId,ChannelID;
            mLogInfo("PauseRecord");
            if (!params.getParamsNodeValueofInt(SET_START_REC_PARAMS_RECMODE, RecMode))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_RECMODE);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
			if (!params.getParamsNodeValueofStr(SET_START_REC_PARAMS_CHNAME, ChannelID))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_CHNAME);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofStr(SET_START_REC_PARAMS_TASKID, TaskId))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_TASKID);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
            CSetRecCtrl PauseRecord(this->_ip);
            string sResult;
            resCode = PauseRecord.PauseRecord(sResult, RecMode, TaskId, ChannelID);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "ResumeRecord"))
        {
            
            int RecMode;
            string TaskId,Title,ChannelID;
            mLogInfo("ResumeRecord");
            if (!params.getParamsNodeValueofInt(SET_START_REC_PARAMS_RECMODE, RecMode))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_RECMODE);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
			if (!params.getParamsNodeValueofStr(SET_START_REC_PARAMS_CHNAME, ChannelID))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_CHNAME);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofStr(SET_START_REC_PARAMS_TASKID, TaskId))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_TASKID);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
			
            if (!params.getParamsNodeValueofStr(SET_START_REC_PARAMS_DESRIPTOR, Title))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_DESRIPTOR);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }


            //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
            CSetRecCtrl ResumeRecord(this->_ip);
            string sResult;
            resCode = ResumeRecord.ResumeRecord(sResult, RecMode, ChannelID, TaskId, Title);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "GetRecordTime"))
        {
            
            int RecMode,ChannelID;
            string TaskId;
            mLogInfo("GetRecordTime");
            if (!params.getParamsNodeValueofInt(SET_START_REC_PARAMS_RECMODE, RecMode))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_RECMODE);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
			if (!params.getParamsNodeValueofInt(SET_START_REC_PARAMS_CHNAME, ChannelID))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_CHNAME);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofStr(SET_START_REC_PARAMS_TASKID, TaskId))
            {
                mLogError("set params error node:" << SET_START_REC_PARAMS_TASKID);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
            CSetRecCtrl GetRecordTime(this->_ip);
            string sResult;
            resCode = GetRecordTime.GetRecordTime(sResult, RecMode, TaskId, ChannelID);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "SetRcrvRecord"))
        {
            
            mLogInfo("SetRcrvRecord");
			int RecOn;
            //获取params节点中DevID节点
            if (!params.getParamsNodeValueofInt("RecOn", RecOn))
            {
                mLogError("set params error node:" << "RecOn");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
            CSetRecCtrl setWebRcrvRecord(this->_ip);
            string sResult;
            resCode = setWebRcrvRecord.SetWebRcrvRecord(sResult,RecOn);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "GetRcrvRecord"))
        {
            
            mLogInfo("GetRcrvRecord");
            //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
            CSetRecCtrl getWebRcrvRecord(this->_ip);
            string sResult;
            resCode = getWebRcrvRecord.GetWebRcrvRecord(sResult);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "SetStartAutoRec"))
        {
		    mLogInfo("SetStartAutoRec");

			int StartRec;
            if (!params.getParamsNodeValueofInt("StartRec", StartRec))
            {
                mLogError("set params error node:" << "StartRec");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
		    //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
		    CSetRecCtrl setWebStartAutoRec(this->_ip);
		    string sResult;
		    resCode = setWebStartAutoRec.SetWebStartAutoRec(sResult, StartRec);
		    //设置返回信息 内容列表
		    response.setResponseResults(sResult);
		    break;
        }
		else if (!strcmp(sMethod.c_str(), "GetStartAutoRec"))
        {
		    mLogInfo("GetStartAutoRec");

		    //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
		    CSetRecCtrl getWebStartAutoRec(this->_ip);
		    string sResult;
		    resCode = getWebStartAutoRec.GetWebStartAutoRec(sResult);
		    //设置返回信息 内容列表
		    response.setResponseResults(sResult);
		    break;
        }
		else if (!strcmp(sMethod.c_str(), "GetHostRTSPDecInfo"))
        {
            //getHostDecInfo
            int DecId;
            mLogInfo("GetHostRTSPDecInfo");
            if (!params.getParamsNodeValueofInt(HOST_DEC_INFO_PARAMS_RTSP_CHANNEL, DecId))
            {
                mLogError("get params error node:" << HOST_DEC_INFO_PARAMS_RTSP_CHANNEL);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            CGetHostDecInfo GetHostRTSPDecInfo(this->_ip);
            string sResult;
            resCode = GetHostRTSPDecInfo.GetHostRTSPDecInfo(sResult, DecId);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "GetHostH323DecInfo"))
        {
            //getHostDecInfo
            int DecId;
            mLogInfo("GetHostH323DecInfo");
            if (!params.getParamsNodeValueofInt(HOST_DEC_INFO_PARAMS_RTSP_CHANNEL, DecId))
            {
                mLogError("get params error node:" << HOST_DEC_INFO_PARAMS_RTSP_CHANNEL);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            CGetHostDecInfo GetHostH323DecInfo(this->_ip);
            string sResult;
            resCode = GetHostH323DecInfo.GetHostH323DecInfo(sResult, DecId);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "GetHostSIPDecInfo"))
        {
            //getHostDecInfo
            int DecId;
            mLogInfo("GetHostSIPDecInfo");
            if (!params.getParamsNodeValueofInt(HOST_DEC_INFO_PARAMS_RTSP_CHANNEL, DecId))
            {
                mLogError("get params error node:" << HOST_DEC_INFO_PARAMS_RTSP_CHANNEL);
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            CGetHostDecInfo GetHostSIPDecInfo(this->_ip);
            string sResult;
            resCode = GetHostSIPDecInfo.GetHostSIPDecInfo(sResult, DecId);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "SetTaskDelete"))
        {
            
            string TaskID;
            mLogInfo("SetTaskDelete");
            if (!params.getParamsNodeValueofStr("TaskID", TaskID))
            {
                mLogError("get params error node:" << "TaskID");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            CSetRecCtrl SetRecUploadState(this->_ip);
            string sResult;
            resCode = SetRecUploadState.SetRecUploadState(sResult, TaskID);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "SetCwpNewWhine"))
        {
            int WhineChn, WhineType;
            mLogInfo("SetCwpNewWhine");
            //获取params节点中DevID节点
            if (!params.getParamsNodeValueofInt("WhineChn", WhineChn))
            {
                mLogError("set params error node:" << "WhineChn");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt("WhineType", WhineType))
            {
                mLogError("set params error node:" << "WhineType");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
            CSetWebNewWhine setWebNewWhine(this->_ip);
            string sResult;
            resCode = setWebNewWhine.SetWebNewWhine(sResult, WhineChn, WhineType);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "GetCwpNewWhine"))
        {
            int WhineChn, WhineType;
            mLogInfo("GetCwpNewWhine");
            //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
            CSetWebNewWhine getWebNewWhine(this->_ip);
            string sResult;
            resCode = getWebNewWhine.GetWebNewWhine(sResult);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "SetCwpNewWhineButton"))
        {
            int WhineChn, WhineButton;
            mLogInfo("SetCwpNewWhineButton");
            //获取params节点中DevID节点
            if (!params.getParamsNodeValueofInt("WhineChn", WhineChn))
            {
                mLogError("set params error node:" << "WhineChn");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt("WhineButton", WhineButton))
            {
                mLogError("set params error node:" << "WhineButton");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
            CSetWebNewWhine setWebNewWhineButton(this->_ip);
            string sResult;
            resCode = setWebNewWhineButton.SetWebNewWhineButton(sResult, WhineChn, WhineButton);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "SetDecAndMicWhine"))
        {
            int WhineChn, WhineType;
            mLogInfo("SetDecAndMicWhine");
            //获取params节点中DevID节点
            if (!params.getParamsNodeValueofInt("WhineChn", WhineChn))
            {
                mLogError("set params error node:" << "WhineChn");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            if (!params.getParamsNodeValueofInt("WhineType", WhineType))
            {
                mLogError("set params error node:" << "WhineType");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }

            //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
            CSetWebNewWhine SetDecAndMicWhine(this->_ip);
            string sResult;
            resCode = SetDecAndMicWhine.SetDecAndMicWhine(sResult, WhineChn, WhineType);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "GetDecAndMicWhine"))
        {
            int WhineChn, WhineType;
            mLogInfo("GetDecAndMicWhine");
			if (!params.getParamsNodeValueofInt("WhineChn", WhineChn))
            {
                mLogError("set params error node:" << "WhineChn");
                resCode = eInterfaceResCodeRequErrorParam;
                break;
            }
            //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
            CSetWebNewWhine GetDecAndMicWhine(this->_ip);
            string sResult;
            resCode = GetDecAndMicWhine.GetDecAndMicWhine(sResult, WhineChn);
            //设置返回信息 内容列表
            response.setResponseResults(sResult);
            break;
        }
		else if (!strcmp(sMethod.c_str(), "SetCwpMosaic"))
		{
			int ArryNums = 20;//JSON数组最大数量
			int MosaicDisplay[ArryNums],MosaicNum[ArryNums],MosaicType[ArryNums],ArryNumbers;
			string MosaicChn[ArryNums],MosaicWinX[ArryNums],MosaicWinY[ArryNums],MosaicWinH[ArryNums],MosaicWinW[ArryNums];
			cJSON* arrayItem[ArryNums];
			mLogInfo("SetWebMosaic");
			//取出JSON数组中ArryList数组的每一组数据,JSON数组数目保存在ArryNumbers中，每组数据保存在arrayItem数组中
			if (!params.getParamsNodeValueofArry("ArryList", ArryNumbers, arrayItem))
			{
				mLogError("set params error node:" << "ArryList");
				resCode = eInterfaceResCodeRequErrorParam;
				break;
			}
			//申请的数组小于实际的数组大小报错
			if(ArryNums < ArryNumbers)
			{
				mLogError("ArryNumbers is larger than requst arry,ArryNums:" << ArryNums<<"   ArryNumbers:"<<ArryNumbers);
				resCode = eInterfaceResCodeRequErrorParam;
				break;
			}
			//取出arrayItem数组中的数据
			for(int i = 0; i < ArryNumbers; i++)
			{
				if (!params.getNodeValueofStr(arrayItem[i],"MosaicChn", MosaicChn[i]))
				{
					mLogError("set params error node:" << "MosaicChn");
					resCode = eInterfaceResCodeRequErrorParam;
					break;
				}
				if (!params.getNodeValueofInt(arrayItem[i],"MosaicDisplay", MosaicDisplay[i]))
				{
					mLogError("set params error node:" << "MosaicDisplay");
					resCode = eInterfaceResCodeRequErrorParam;
					break;
				}
				if (!params.getNodeValueofInt(arrayItem[i],"MosaicNum", MosaicNum[i]))
				{
					mLogError("set params error node:" << "MosaicNum");
					resCode = eInterfaceResCodeRequErrorParam;
					break;
				}
				if (!params.getNodeValueofInt(arrayItem[i],"MosaicType", MosaicType[i]))
				{
					mLogError("set params error node:" << "MosaicType");
					resCode = eInterfaceResCodeRequErrorParam;
					break;
				}
				if (!params.getNodeValueofStr(arrayItem[i],"MosaicWinX", MosaicWinX[i]))
				{
					mLogError("set params error node:" << "MosaicWinX");
					resCode = eInterfaceResCodeRequErrorParam;
					break;
				}
				if (!params.getNodeValueofStr(arrayItem[i],"MosaicWinY", MosaicWinY[i]))
				{
					mLogError("set params error node:" << "MosaicWinY");
					resCode = eInterfaceResCodeRequErrorParam;
					break;
				}
				if (!params.getNodeValueofStr(arrayItem[i],"MosaicWinH", MosaicWinH[i]))
				{
					mLogError("set params error node:" << "MosaicWinH");
					resCode = eInterfaceResCodeRequErrorParam;
					break;
				}
				if (!params.getNodeValueofStr(arrayItem[i],"MosaicWinW", MosaicWinW[i]))
				{
					mLogError("set params error node:" << "MosaicWinW");
					resCode = eInterfaceResCodeRequErrorParam;
					break;
				}
				
			}
			
			 //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
			 CSetWebNewMosaic SetWebNewMosaic(this->_ip);
			 string sResult;
			 resCode = SetWebNewMosaic.SetWebNewMosaic(sResult, ArryNumbers, MosaicChn, MosaicDisplay, MosaicNum, MosaicType, MosaicWinX, MosaicWinY, MosaicWinH, MosaicWinW);
			 //设置返回信息 内容列表
			 response.setResponseResults(sResult);
			 //释放arrayItem申请的空间
//			 for(int i = 0; i < ArryNumbers; i++)
//			{
//				cJSON_Delete(arrayItem[i]);
//			}
			break;
		}
		else if (!strcmp(sMethod.c_str(), "GetCwpMosaicList"))
		{
		    mLogInfo("GetCwpMosaicList");
			int ChnnelID;
		    if (!params.getParamsNodeValueofInt("ChnnelID", ChnnelID))
		    {
			    mLogError("set params error node:" << "ChnnelID");
			    resCode = eInterfaceResCodeRequErrorParam;
			    break;
		    }
		    CGetWebMosaicList GetWebNewMosaicList(this->_ip);
		    string sResult;
		    resCode = GetWebNewMosaicList.GetWebNewMosaicList(sResult,ChnnelID);
		    //设置返回信息 内容列表
		    response.setResponseResults(sResult);
		    break;
		}
		else if (!strcmp(sMethod.c_str(), "GetHardDevsState"))
        {
		    mLogInfo("GetHardDevsState");

		    //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
		    CGetHostConfig GetHardDevsState(this->_ip);
		    string sResult;
		    resCode = GetHardDevsState.GetHardDevsState(sResult);
		    //设置返回信息 内容列表
		    response.setResponseResults(sResult);
		    break;
        }
        else
        {
            resCode = eInterfaceResCodeReqNoMethod;
            mLogError("没有此方法:" << sMethod);
            break;
        }

    } while (false);

    //生成返回信息
    string errorStr;
    string resStr;
    if (resCode != eInterfaceResCodeSuccess)
    {
        errorStr = GetInterfaceResError(resCode);
        //        response.clearAllMsg();
        //        resStr = response.simpleResponsePrintofFalied(errorStr);
        resStr = response.simpleResponsePrintofFalied(errorStr, resCode);
    }
    else
    {
        response.setResponseSuccessFlag();
        response.setResponseError("");
        resStr = response.responsePrint(_debugMode);
    }
    params.clearAll();
    response.clearAllMsg();
    mLogDebug("response str:" << resStr);
    return resStr;
}

void InterfaceProcess::debugMode()
{
    _debugMode = true;
}

InterfaceResCode InterfaceProcess::HostStatusMethod(CHStatus &chState)
{
    mLogInfo("获取设备指定通道的状态...");
    mLogDebug("run HostSTatusMethod(...)");
    //获取状态
    MPSMediaStatus state;
    MPSOperationRes opResCode = eMPSResultOK;
    ResponseCode resCode = _client->GetMediaState(opResCode, state);
    if (resCode != eResponseCodeSuccess)
    {
        mLogError("GetMediaState(...) error:" << resCode);
        return CovertResponseCode(resCode);
    }
    else if (opResCode != eMPSResultOK)
    {
        mLogError("mps response flag:" << opResCode << "," << getMPSOperationResStr(opResCode));
        return CovertMPSOperationCode(opResCode);
    }

    //转换状态值
    chState = CovertMediaStatus(state);
    if (chState >= eCHStatusSize)
    {
        //转换状态值失败
        mLogError("CovertMediadStatus(MPSMediaStatus)=(" << state << ") error. chState:" << chState);
        return eInterfaceResCodeErrorRecv;
    }
    return eInterfaceResCodeSuccess;
}

InterfaceResCode InterfaceProcess::HostStatusMethodV2(CHStatus &chState)
{
    GetHostStatus getStatus;
    int chNum;
    if (getStatus.GetStatus(chNum, chState) != true)
    {
        mLogError("Failed to run GetHostStatus::GetStatus(...)");
        return eInterfaceResCodeErrorLocalDataConvert;
    }

    //
    //
    if (chState >= eCHStatusSize)
    {
        //转换状态值失败
        mLogError("GetHostStatus::GetStatus(chState)=(" << chState << ") error. chState >= eCHStatusSize:" << eCHStatusSize);
        return eInterfaceResCodeErrorRecv;
    }
    return eInterfaceResCodeSuccess;
}
/*
InterfaceResCode InterfaceProcess::HostInitMethod(string caseId, string &resCaseId)
{
    mLogInfo("打开设备指定通道的视频流...");
    mLogInfo("caseID:"<<caseId);

    MPSOperationRes opResCode = eMPSResultOK;
    ResponseCode resCode = _client->MediaPrepare(caseId,opResCode,resCaseId);
    if(resCode != eResponseCodeSuccess){
        mLogError("MediaPrepare(caseId,...)=("<<caseId<<",...) error:"<<resCode);
        return CovertResponseCode(resCode);
    }else if(opResCode != eMPSResultOK){
        mLogError("mps response flag:"<<opResCode<<","<<getMPSOperationResStr(opResCode));
        return CovertMPSOperationCode(opResCode);
    }

    return eInterfaceResCodeSuccess;
}
//*/
/*
InterfaceResCode InterfaceProcess::HostStartMethod(string caseId)
{
    mLogInfo("开始设备指定通道的视频录制...");
    mLogInfo("caseID:"<<caseId);

    MPSOperationRes opResCode = eMPSResultOK;
    ResponseCode resCode = _client->MediaStart(caseId,opResCode);
    if(resCode != eResponseCodeSuccess){
        mLogError("MediaStart(caseId,...)=("<<caseId<<",...) error:"<<resCode);
        return CovertResponseCode(resCode);
    }else if(opResCode != eMPSResultOK){
        mLogError("mps response flag:"<<opResCode<<","<<getMPSOperationResStr(opResCode));
        return CovertMPSOperationCode(opResCode);
    }

#ifdef START_STOP_PROOF_ALONE_CONTROL
    resCode = _client->StartProofSave(opResCode);
    if(resCode != eResponseCodeSuccess){
        mLogError("StartProofSave(...) error:"<<resCode);
        return CovertResponseCode(resCode);
    }else if(opResCode != eMPSResultOK){
        mLogError("mps response flag:"<<opResCode<<","<<getMPSOperationResStr(opResCode));
        return CovertMPSOperationCode(opResCode);
    }
#endif
    return eInterfaceResCodeSuccess;
}
//*/
/*
InterfaceResCode InterfaceProcess::HostStopMethod(bool closeFlag)
{
    mLogInfo("停止设备指定通道的视频录制...");
    mLogInfo("closeFlag:"<<closeFlag);

    MPSOperationRes opResCode = eMPSResultOK;
    ResponseCode resCode;
#ifdef START_STOP_PROOF_ALONE_CONTROL
    resCode = _client->StopProofSave(opResCode);
    if(resCode != eResponseCodeSuccess){
        mLogError("StartProofSave(...) error:"<<resCode);
        return CovertResponseCode(resCode);
    }else if(opResCode != eMPSResultOK){
        mLogError("mps response flag:"<<opResCode<<","<<getMPSOperationResStr(opResCode));
        return CovertMPSOperationCode(opResCode);
    }
#endif

    resCode = _client->MediaStop(closeFlag,opResCode);
    if(resCode != eResponseCodeSuccess){
        mLogError("MediaStop(closeFlag,...)=("<<closeFlag<<",...) error:"<<resCode);
        return CovertResponseCode(resCode);
    }else if(opResCode != eMPSResultOK){
        mLogError("mps response flag:"<<opResCode<<","<<getMPSOperationResStr(opResCode));
        return CovertMPSOperationCode(opResCode);
    }
//    boost::thread::sleep(boost::get_system_time() + boost::posix_time::milliseconds(200));
    return eInterfaceResCodeSuccess;
}
//*/
/*
InterfaceResCode InterfaceProcess::HostCloseMethod()
{
    mLogInfo("关闭设备指定通道的视频流...");

    MPSOperationRes opResCode = eMPSResultOK;
    ResponseCode resCode = _client->MediaClose(true,opResCode);
    if(resCode != eResponseCodeSuccess){
        mLogError("MediaClose(...) error:"<<resCode);
        return CovertResponseCode(resCode);
    }else if(opResCode != eMPSResultOK){
        mLogError("mps response flag:"<<opResCode<<","<<getMPSOperationResStr(opResCode));
        return CovertMPSOperationCode(opResCode);
    }
    return eInterfaceResCodeSuccess;
}
//*/

InterfaceResCode InterfaceProcess::GetTaskContentMethod(string caseId, cJSON *result)
{
    CGetTaskContent getTaskContent(this->_ip);
    return getTaskContent.GetTaskContent(caseId, result);
}

InterfaceResCode InterfaceProcess::GetTaskContentMethod(string caseId, string &result)
{
    CGetTaskContent getTaskContent(this->_ip);
    return getTaskContent.GetTaskContent(caseId, result);
}

bool InterfaceProcess::checkCaseIdisEnable(string caseId)
{
    //TODO 检查caseid是否有效
    int len = caseId.length();
    if (len > REQUEST_PARAMS_NODE_CASEID_LEN)
    {
        mLogError("caseId.length():" << len << " > " << REQUEST_PARAMS_NODE_CASEID_LEN);
        return false;
    }
    if ((caseId[0] < 'A' || caseId[0] > 'Z') && (caseId[0] < 'a' || caseId[0] > 'z'))
    {
        mLogError("caseId[0]:" << caseId[0] << " scope[a,z][A,Z].");
        return false;
    }
    for (int i = 0; i < len; i++)
    {
        char c = caseId[i];
        if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && (c < '0' || c > '9'))
        {
            if (c == '-' || c == '_')
            {
                break;
            }
            mLogError("caseId.length():" << len << " caseId[" << i << "]:[" << caseId[i] << "], scope[a,z][A,Z][0,9]{-,_}.");
            return false;
        }
    }
    return true;
}

bool InterfaceProcess::checkChannelNumisEnable(int chNum)
{
    if (chNum < 1)
    {
        mLogError("chNum:" << chNum << " < 1 ,error!");
        return false;
    }
    else
    {
        return true;
    }
}
