#pragma once
#include "Queue.h"

typedef struct LogNode
{
 string _carNum;
 int _carType;
 Time _arrTime;
 Time _bgnTime;
 Time _lveTime;
 int _minute;
 int _fee;
 struct LogNode *_next;
}LogNode,*LogNodePtr;

 

class SystemLog
{
private:
 LogNodePtr _front;
 LogNodePtr _reer;
 int _recordSum;
public:
 SystemLog();
 ~SystemLog();
 bool Clear();
 bool Empty();
 bool SetPakLotFee();
 bool SetSideWayFee();
 LogNodePtr GetFront()const;//此处需修改，不能把头指针给出去
 LogNodePtr GetReer()const;//同上
 bool AddRecord(const CarNode& target,const Time& sysTime,int fee);
 friend ostream& operator<<(ostream& out,const SystemLog& log);
};
