#include "SystemLog.h"
#include <iomanip>


SystemLog::SystemLog()
{
 _front=new LogNode;//头结点
 _reer=_front;
 _reer->_next=0;
 _recordSum=0;
}


SystemLog::~SystemLog()
{
 LogNodePtr pLog=_front;
 while(pLog!=NULL)
 {
  _front=_front->_next;
  delete pLog;
  pLog=_front;
 }
 _front=_reer=NULL;
 _recordSum=0;
}


bool SystemLog::Clear()
{
 LogNodePtr pDel=_front->_next,pLink=pDel;
 _front->_next=NULL;
 while (pLink!=NULL)
 {
  pLink=pLink->_next;
  delete pDel;
  pDel=pLink;
 }
 _reer=_front;
 _recordSum=0;
 return true;
}


bool SystemLog::Empty()
{
 return _recordSum==0;
}

LogNodePtr SystemLog::GetFront()const
{
 return _front->_next;//第一个元素(跳过头结点)
}

LogNodePtr SystemLog::GetReer()const
{
 return _reer;
}

 

bool SystemLog::AddRecord(const CarNode& target,const Time& sysTime,int fee)
{
 _reer->_next=new LogNode;
 _reer=_reer->_next;
 _reer->_carNum=target._carNum;
 _reer->_carType=target._carType;
 _reer->_arrTime=target._timeArr;
 _reer->_bgnTime=target._timeBgn;
 _reer->_lveTime=sysTime;
 _reer->_minute=_reer->_lveTime-_reer->_arrTime;
 _reer->_fee=fee;
 _reer->_next=NULL;
 return true;
}


ostream& operator<<(ostream& out,const SystemLog& log)
{
 out<<"  ----------------------------------------------------------------------------" <<endl;
 out<<" |                          · 系· 统 · 日 · 志 ·                         |"<<endl;
 out<<" | 序号      车牌号        到达时间       离开时间       计费时间       费用  |"<<endl;
 out<<"  ----------------------------------------------------------------------------"<<endl;
 LogNodePtr pLink=log._front->_next;
 int count=0;
 while (pLink!=NULL)
 {
  out<<" | "<<setw(3)<<++count<<"       "<<pLink->_carNum<<"         "<<pLink->_arrTime<<"           "<<pLink->_lveTime<<"           "<<setw(4)<<pLink->_minute<<"        "<<setw(4)<<pLink->_fee<<"  |"<<endl;
  pLink=pLink->_next;
 }
 out<<" |                                                       ◎共 "<<setw(3)<<count<<" 条日志记录  |"<<endl;
 out<<"  ----------------------------------------------------------------------------"<<endl;
 return out;
}
