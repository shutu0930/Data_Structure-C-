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
 Stack _pakLot;                     //ͣ����
 Stack _tempLot;                    //��ʱ����
 Queue _sideWay;                    //���
 MsgNodePtr _msgData;               //��Ϣ������
 Msg _msg;                          //��Ϣ
 SystemLog _carLog;                 //ϵͳ���ݿ�
 Time _sysTime;                     //ϵͳʱ��
 int _pakLotFee;                    //�����շѱ�׼
 int _sideWayFee;                   //����շѱ�׼
 string _readMsgFile;               //��Ϣ������ļ�
 string _saveLogFile;               //��־�����ļ�
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
 bool SetCar();//��msg��ȡ��Ϣ
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
