#pragma once
#include "SystemLog.h"
#include <fstream>
#define DEFAULT_PLOT_FEE 8
#define DEFAULT_SWAY_FEE 5
typedef struct Message
{
 char _orderType;
 CarNode car;
}Msg,*MsgPtr;

typedef struct MsgNode
{
 Msg _msg;
 struct MsgNode *_next;
}MsgNode,*MsgNodePtr;

 

class CarSystem
{
private:
 Stack _pakLot;                     //停车场
 Stack _tempLot;                    //临时车场
 Queue _sideWay;                    //便道
 MsgNodePtr _msgData;               //消息数据区
 Msg _msg;                          //消息
 SystemLog _carLog;                 //系统数据库
 Time _sysTime;                     //系统时间
 int _pakLotFee;                    //车场收费标准
 int _sideWayFee;                   //便道收费标准
 string _readMsgFile;               //消息命令库文件
 string _saveLogFile;               //日志保存文件
 bool SetPakLotFee(int feerate);
 bool SetSideWayFee(int feerate);
 bool SetParametor();
 bool HelpFile();
 bool UseSystemHelp();
 bool ParaHelp();
 bool PutPakLotInfo()const;
 bool PutSideWayInfo()const;
public:
 CarSystem();
 ~CarSystem();
 bool GetMsg();
 bool LoadMsg();
 bool ProcessMsgData();
 bool MsgDataEmpty()const;
// int  MsgDataSum()const;
 bool PeekMsg();
 bool CheckMsg();
 bool SetCar();//从msg读取消息
 bool GetCar(CarNode& carMove);
 bool ProcessMsg();
 bool CheckPakLot();
 bool AutoDriveEvent();
 bool DriveEvent();
 bool PakLotTest()const;
 bool SaveLogs();
 friend ostream& operator<<(ostream& out,Msg& msg);
 friend ostream& operator<<(ostream& out,MsgNodePtr msgData);
 bool StartSystem();
};
