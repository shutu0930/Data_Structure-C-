#include "CarSystem.h"

#include "CarSystem.h"
#include <conio.h>
#include <iomanip>

CarSystem::CarSystem()
{
 _msgData=new MsgNode;
 _msgData->_next=NULL;
 _msg._orderType='E';
 _sysTime.SetTime(0,0);                 //设置停车场系统工作时间
 _pakLotFee=DEFAULT_PLOT_FEE;           //默认车场收费标准
 _sideWayFee=DEFAULT_SWAY_FEE;          //默认便道收费标准
 _readMsgFile="msg.txt";
 _saveLogFile="SystemLog.txt";
}


CarSystem::~CarSystem()
{
 delete _msgData;
 _msgData=NULL;
 _msg._orderType='E';
 _sysTime.SetTime(0,0);
 _pakLotFee=0;
 _sideWayFee=0;
}


bool CarSystem::SetPakLotFee(int feerate)
{
 if (feerate<0)
  return false;
 _pakLotFee=feerate;
 return true;
}


bool CarSystem::SetSideWayFee(int feerate)
{
 if (feerate<0)
  return false;
 _sideWayFee=feerate;
 return true;
}


bool CarSystem::PakLotTest()const
{
// system("cls");
 cout<<"=================================================="<<endl;
 cout<<_pakLot<<endl<<endl<<_tempLot<<endl<<endl<<_sideWay<<endl<<endl;
 system("pause");
 return true;
}


bool CarSystem::GetMsg()
{
 while (1)
 {
  cin>>_msg._orderType;
  if (_msg._orderType=='E'||_msg._orderType=='e')
  {
   getline(cin,string());
   return true;
  }//if
  else if (_msg._orderType=='A'||_msg._orderType=='D')
  {
   getchar();
   cin>>_msg.car;
   return true;
  }//else if
  else
  {
   cout<<"Wrong Message,Please input again!"<<endl;
   continue;
  }//else
 }//while
 return true;
}//GetMsg


bool CarSystem::LoadMsg()
{
 ifstream fin(_readMsgFile.c_str());
 if (fin.fail())
 {
  cout<<"Open File "<<_readMsgFile<<" Error!"<<endl;
  exit(1);
 }//if
 Msg msg;
 MsgNodePtr pLink=_msgData;
 int errors=0;//错误信息计数器
 int count=0;//消息计数器
 while (!fin.eof())
 {
  fin>>msg._orderType;
  //此处加入注释过滤功能
  if (msg._orderType=='A'||msg._orderType=='D')
  {
   pLink->_next=new MsgNode;
   pLink=pLink->_next;
   pLink->_msg._orderType=msg._orderType;
   fin.ignore();
   fin>>pLink->_msg.car;
   pLink->_next=NULL;
  }//if
  else if (msg._orderType=='E')
  {
   pLink->_next=new MsgNode;
   pLink=pLink->_next;
   pLink->_msg._orderType=msg._orderType;
   fin.ignore(1);
   fin>>pLink->_msg.car;
   pLink->_msg.car._timeArr--;
   pLink->_next=NULL;
  }//else if
  else
  {
   cout<<++errors<<" Error MessageDatas!"<<endl;
   getline(fin,string());//忽略一行
  }//else
  count++;//计数器+1
 }//while
 fin.close();
 cout<<_msgData;
 system("pause");
 if (errors)
 {
  cout<<"共读取"<<setw(3)<<count<<" 条消息。"<<"无效消息共"<<setw(3)<<errors<<"条！"<<endl;
  cout<<"此数据源可能导致程序异常终止，建议检查数据正确性再测试。是否继续(Y/N)？"<<endl;
  char ans;
  cin>>ans;
  if (ans=='N'||ans=='n')
  {
   exit(1);
  }//if
 }//if
 return true;
}//LoadMsg


bool CarSystem::ProcessMsgData()
{
 MsgNodePtr pFront=_msgData,pSet=pFront->_next,pLink=pSet->_next;
 while (pFront->_next->_next!=NULL)
 {
  while (pLink!=NULL)
  {
   if (pLink->_msg.car._timeArr<pFront->_next->_msg.car._timeArr)
   {
    pSet->_next=pLink->_next;
    pLink->_next=pFront->_next;
    pFront->_next=pLink;
    pLink=pSet->_next;
   }//if
   else
   {
    pSet=pLink;
    pLink=pLink->_next;
   }//else
  }//while
  pFront=pFront->_next;
  pSet=pFront->_next;
  pLink=pSet->_next;
 }//while
 return true;
}//ProcessMsgData

bool CarSystem::MsgDataEmpty() const
{
 return _msgData->_next==NULL;
}

 

bool CarSystem::PeekMsg()
{
 if (MsgDataEmpty())
  return false;
 MsgNodePtr pLink=_msgData->_next;
 _msg._orderType=pLink->_msg._orderType;
 _msg.car=pLink->_msg.car;
 _msgData->_next=pLink->_next;
 delete pLink;
 pLink=NULL;
 return true;
}


bool CarSystem::CheckMsg()
{
 if (_msg._orderType=='A'||_msg._orderType=='D'||_msg._orderType=='E')
 {//命令正确
  if (!_msg.car._carNum.empty()&&_msg.car._carType>=0)
  {//车牌号，车型正确，到达时间有效
   return true;
  }//if
 }//if
 return false;
}//CheckMsg


bool CarSystem::SetCar()
{
 if (!_pakLot.Full())
 {//车场没满
  _msg.car._timeBgn=_sysTime;
  _pakLot.Push(_msg.car); 
 }//if
 else if (!_sideWay.Full())
 {
  _sideWay.EnQueue(_msg.car);
 }//else if
 else
 {
  cout<<"没有更多的停车空间!"<<endl;
  system("pause");//此处加入系统暂停设置~
  return false;
 }//else
 return true;
}


bool CarSystem::GetCar(CarNode &carMove)
{
 if (_pakLot.Find(_msg.car))
 {//在车场
  CarNode carMove=_pakLot.Pop();
  while (carMove._carNum!=_msg.car._carNum)//优化此处，繁琐的string对象比较
  {//开始找车
   _tempLot.Push(carMove);
   carMove=_pakLot.Pop();
  }//for
  //carMove是应出库车辆
  int fee=(carMove._timeBgn-carMove._timeArr)*_sideWayFee+(_sysTime-carMove._timeBgn)*_pakLotFee;//入库汽车应缴停车费用
  fee*=carMove._carType;//汽车类型的倍数
  _carLog.AddRecord(carMove,_sysTime,fee);
  while (!_tempLot.Empty())
  {                                 //数据测试
   carMove=_tempLot.Pop(); 
   _pakLot.Push(carMove);
  }//while                                 //数据测试
  CheckPakLot();                             //检测车场                                //数据测试
 }//if
 else if (_sideWay.Find(_msg.car))
 {//在便道                                                                             此处仍存在问题
  CarNode carMove=_sideWay.DeQueue(),setBack=_sideWay.GetReer();//setBack-->便道的车出来后，其他的车还原
  while (carMove._carNum!=_msg.car._carNum)   //修改此处判断
  {//开始找车
   _sideWay.EnQueue(carMove);
   carMove=_sideWay.DeQueue();
  }//while
  //carMove是应出库车辆
  int fee=(_sysTime-carMove._timeArr)*_sideWayFee;//便道汽车应缴停车费用
  fee*=carMove._carType;//汽车类型的倍数
  _carLog.AddRecord(carMove,_sysTime,fee);//加入日志文件
  carMove=_sideWay.DeQueue();
  //第一辆就是要找的车 这里更改
  while (carMove._carNum!=setBack._carNum)
  {
   _sideWay.EnQueue(carMove);
   carMove=_sideWay.DeQueue();
  }//while
  _sideWay.EnQueue(carMove);//找到尾部车辆，入队列
 }//else if
 else
 {
  cout<<"找不到车辆 "<<_msg.car._carNum<<"!   请检查输入信息!"<<endl;
  PakLotTest();            //用户侦错功能
  cout<<_msg;
  system("pause");
  return false;
 }//else
 return true;
}//GetCar

 

bool CarSystem::ProcessMsg()
{
 if (!CheckMsg())
  return false;
 switch (_msg._orderType)
 {
 case 'A':
  {
   //此处加入系统暂停设置
   SetCar();//汽车入库
   break;
  }//case 'A'
 case 'D':
  {
   CarNode carMove;
   GetCar(carMove);//_msg暂存用，之后会读入
   break;
  }
 case'E':
  {
   int fee;//存储每辆车应缴的费用
   while (!_pakLot.Empty())
   {//先入库的先记录
    _msg.car=_pakLot.Pop();
    _tempLot.Push(_msg.car);
   }//while
   while (!_tempLot.Empty())
   {
    _msg.car=_tempLot.Pop();
    fee=(_msg.car._timeBgn-_msg.car._timeArr)*_sideWayFee+(_sysTime-_msg.car._timeBgn)*_pakLotFee;//入库汽车应缴停车费用
    fee*=_msg.car._carType;//汽车类型的倍数
    _carLog.AddRecord(_msg.car,_sysTime,fee);//车场的车清空，收费
   }//while
   while (!_sideWay.Empty())
   {
    _msg.car=_sideWay.DeQueue();
    fee=(_sysTime-_msg.car._timeArr)*_sideWayFee;//便道汽车应缴停车费用
    fee*=_msg.car._carType;//汽车类型的倍数
    _carLog.AddRecord(_msg.car,_sysTime,fee);//加入日志文件
   }//while
   break;
  }//case 'E'
 }//switch
 return true;
}//ProcessMsg


bool CarSystem::CheckPakLot()
{
 while (!_pakLot.Full()&&!_sideWay.Empty())
 {
  CarNode carMove=_sideWay.DeQueue();
  carMove._timeBgn=_sysTime;//入库时间
  _pakLot.Push(carMove);
 }//while
 return true;
}//CheckPakLot


bool CarSystem::AutoDriveEvent()
{
 bool finished=false;
 if (LoadMsg())
 {
  ProcessMsgData();      //处理消息区，按时间顺序排序
  if (!PeekMsg())
   return false;
  while (!finished)
  {
   _sysTime++;//系统总时间
   if (_msg.car._timeArr<=_sysTime||_msg._orderType=='E')
   {
    ProcessMsg();
    if (!PeekMsg())
     finished=true;
   }//if
   //删除了车场情况检测
   system("cls");
   cout<<"  ---------------------------------------------------------------------------- "<<endl;
   cout<<" |                · 停 · 车 · 场 · 管 · 理 · 系 · 统 ·                |"<<endl;
   cout<<"  ---------------------------------------------------------------------------- "<<endl;
   cout<<"                                           · 系 统 时 间 ·  "<<_sysTime<<"   "<<endl;
   cout<<_carLog;                           //自启动输出系统日志
  }//while
  SaveLogs();
  cout<<"     ◎◎"<<"车场容量："<<setw(3)<<_pakLot.StackCapacity()<<"       剩余容量："<<setw(3)
   <<_pakLot.StackCapacity()-_pakLot.StackSize()<<"       车辆数量："<<setw(3)<<_pakLot.StackSum()<<endl
   <<"     ◎◎便道容量："<<setw(3)<<_sideWay.QueueCapacity()<<"       剩余容量："<<setw(3)
   <<_sideWay.QueueCapacity()-_sideWay.QueueSize()<<"       车辆数量："<<setw(3)<<_sideWay.QueueSum()<<endl;
  //关闭系统;
  _sysTime.SetTime(0,0);
  _pakLot.Clear();
  _tempLot.Clear();
  _sideWay.Clear();
  _carLog.Clear();
  cout<<"     ◎◎"<<"系统已关闭！"
   <<"                       ◎";
  system("pause");
  return true;
 }
 cout<<"System Error!"<<endl;
 return false;
}

bool CarSystem::SaveLogs()
{//修改输出格式
 ofstream fout(_saveLogFile.c_str());
 if (fout.fail())
 {
  cout<<"Open File "<<_saveLogFile<<" Failed!"<<endl;
  exit(1);
 }
 fout<<endl<<"                                    -----停车场系统日志-----                 "<<endl<<endl;
 fout<<"  序号/t/t  车牌号/t/t/t       到达时间/t/t/t      离开时间/t/t    计费时间/t/t     费用 "<<endl;
 fout<<"-----------------------------------------------------------------------------------------"<<endl;
 LogNodePtr pLink=_carLog.GetFront()->_next;
 int count=0;
 while (pLink!=NULL)
 {
  fout<<"/t"<<setw(3)<<++count<<"/t      "<<setw(6)<<pLink->_carNum<<"/t        "<<setw(5)<<pLink->_arrTime
   <<"/t             "<<pLink->_lveTime<<"/t          "<<setw(4)<<pLink->_minute<<"/t         "<<setw(4)<<pLink->_fee<<endl;
  pLink=pLink->_next;
 }
 fout<<"-----------------------------------------------------------------------------------------"<<endl;
 fout<<endl<<"总运行时间：/t/t"<<_sysTime<<endl;
 fout.close();
 return true;
}

 

ostream& operator<<(ostream& out,Msg& msg)
{
 out<<msg._orderType<<"/t"<<msg.car;
 return out;
}


ostream& operator<<(ostream& out,MsgNodePtr msgData)
{
 int count=0;
 MsgNodePtr pLink=msgData->_next;
 while (pLink!=NULL)
 {
  ++count;
  out<<pLink->_msg<<endl;
  pLink=pLink->_next;
 }
 cout<<"Totally "<<count<<" Message!"<<endl;
 return out;
}

 


//////////////////////////////////////
//界面显示部分
//


bool CarSystem::PutPakLotInfo()const
{
 system("cls");
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<"        |          · 停 · 车 · 场 · 管 · 理 · 系 · 统 ·        |"<<endl;
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<"                                       · 系 统 时 间 ·  "<<_sysTime<<"   "<<endl;
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<"        |                   · 车 · 库 · 详 · 情 ·                 |"<<endl;
 cout<<"        | 序号      车牌号        到达时间       已停时间        费用  |"<<endl;
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<"        |                                                              |"<<endl;
 int count=0;
 CarNodePtr pBase=_pakLot.GetBase();
 int sum=_pakLot.StackSum();
 int minute=0;
 while (sum!=0)
 {
  minute=-(pBase->_timeArr-_sysTime);
  cout<<"        | "<<setw(3)<<++count<<"       "<<setw(6)<<pBase->_carNum<<"      "<<setw(5)<<pBase->_timeArr
   <<"           "<<setw(4)<<minute<<"          "<<setw(4)<<minute*_pakLotFee<<" |"<<endl;
  pBase++;
  sum--;
 }
 cout<<"        |                                                              |"<<endl;
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<endl;
 cout<<"          ◎共停车辆："<<setw(3)<<count<<"            ◎车场容量："<<setw(3)<<_pakLot.StackCapacity()<<endl<<endl;
 cout<<"        ◎◎";
 system("pause");
 return true;
}


bool CarSystem::PutSideWayInfo() const
{
 system("cls");
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<"        |          · 停 · 车 · 场 · 管 · 理 · 系 · 统 ·        |"<<endl;
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<"                                       · 系 统 时 间 ·  "<<_sysTime<<"   "<<endl;
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<"        |                   · 便 · 道 · 详 · 情 ·                 |"<<endl;
 cout<<"        | 序号      车牌号        到达时间       已停时间        费用  |"<<endl;
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<"        |                                                              |"<<endl;
 int count=0;
 CarNodePtr pBase=_sideWay.GetBase();
 int sum=_sideWay.QueueSum();
 int minute=0;
 while (sum!=0)
 {
  minute=-(pBase->_timeArr-_sysTime);           //掉转两个时间出现错误
  cout<<"        | "<<setw(3)<<++count<<"       "<<setw(6)<<pBase->_carNum<<"       "<<setw(5)<<pBase->_timeArr
   <<"           "<<setw(4)<<minute<<"         "<<setw(4)<<minute*_pakLotFee<<"  |"<<endl;
  pBase++;
  sum--;
 }
 cout<<"        |                                                              |"<<endl;
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<endl;
 cout<<"          ◎共停车辆："<<setw(3)<<count<<"            ◎便道容量："<<setw(3)<<_sideWay.QueueCapacity()<<endl<<endl;
 cout<<"        ◎◎";
 system("pause");
 return true;
}

 


bool CarSystem::StartSystem()
{
 int _exit=false;
 int number;
 while (!_exit)
 {
  system("cls");
  cout<<"      --------------------------------------------------------------------" <<endl;
  cout<<"     |             · 停 · 车 · 场 · 管 · 理 · 系 · 统 ·           |"<<endl;
  cout<<"      --------------------------------------------------------------------" <<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                       · 欢 · 迎 · 使 · 用 ·                   |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |            1.人 工 启 动                    2.自 动 测 试          |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |            3.参 数 设 置                    4.查 看 帮 助          |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                            0. 退 出 系 统                          |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                       · 暨 · 南 · 大 · 学 ·                   |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"      -------------------------------------------------------------------- "<<endl;
  cout<<endl;
  cout<<"          ◎请输入菜单选项-->";
  cin>>number;
  switch (number)
  {
  case 1:
   {
    DriveEvent();
    break;
   }
  case 2:
   {
    AutoDriveEvent();
    break;
   }
  case 3:
   {
    SetParametor();
    break;
   }
  case 4:
   {
    HelpFile();
    break;
   }
  case 0:
   {
    _exit=true;
    cout<<endl<<endl<<"        ◎◎感谢使用！";
    break;
   }
  default:
   {
    cout<<"输入有误，请重新输入!"<<endl;
    cin.ignore(100);
    system("pause");
    break;
   }
  }
 }
 return true;
}

 

bool CarSystem::DriveEvent()
{
 bool _exit=false,_useful=false;
 char order;
 while (!_exit)
 {
  system("cls");
  cout<<"      -------------------------------------------------------------------- "<<endl;
  cout<<"     |              · 停 · 车 · 场 · 管 · 理 · 系 · 统 ·          |"<<endl;
  cout<<"      -------------------------------------------------------------------- "<<endl;
  cout<<"                                         · 系 统 时 间 ·  "<<_sysTime<<endl;
  cout<<"      -------------------------------------------------------------------- "<<endl;
  cout<<"     |                       · 人 · 工 · 启 · 动 ·                   |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |            1.使 用 说 明                    2.查 看 车 库          |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |            3.查 看 便 道                    4.查 看 日 志          |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |            5.输 入 命 令                    6.关 闭 系 统          |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                              0.退 出 系 统                         |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                       · 暨 · 南 · 大 · 学 ·                   |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"      -------------------------------------------------------------------- "<<endl;
  cout<<endl;
  cout<<"          ◎请输入菜单选项-->";
  cin>>order;
  switch (order)
  {
  case '1':
   {//使用说明
    _useful=UseSystemHelp();
    break;
   }//case 1
  case '2':
   {//查看车场
    if (!_useful)
    {
     cout<<endl<<"        ◎◎"<<"请先阅读使用说明!"<<endl;
     system("pause");
     break;
    }//if
    PutPakLotInfo();
    break;
   }//case 2
  case '3':
   {//查看便道
    if (!_useful)
    {
     cout<<"请先阅读使用说明!"<<endl;
     system("pause");
     break;
    }//if
    PutSideWayInfo();
    break;
   }//case 3
  case '4':
   {//查看日志
    if (!_useful)
    {
     cout<<"请先阅读使用说明!"<<endl;
     system("pause");
     break;
    }//if
    system("cls");
    cout<<_carLog;
    system("pause");
    break;
   }//case 4
  case '5':
   {//输入命令
    cout<<endl<<"       ◎请输入控制命令：";
    GetMsg();
    while (_sysTime<_msg.car._timeArr)
    {
     CheckPakLot();
     _sysTime++;
    }//while
    ProcessMsg();
    break;
   }//case 5
  case '6':
   {//关闭系统   此处修改
    return true;
    break;
   }//case 6
  case '0':
   {//退出系统
    cout<<endl<<endl<<"        ◎◎感谢使用！";
    exit(1);
    break;
   }//case 0
  default:
   {//错误输入
    cout<<"       ◎输入有误，请重新输入!"<<endl;
    system("pause");
    break;
   }//default
  }//switch
 }//while
 return true;
}//DriveEvent


bool CarSystem::ParaHelp()
{
 system("cls");
 cout<<"      --------------------------------------------------------------------- "<<endl;
 cout<<"     |               · 停 · 车 · 场 · 管 · 理 · 系 · 统 ·          |"<<endl;
 cout<<"      --------------------------------------------------------------------- "<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |                       · 参 · 数 · 说 · 明 ·                    |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |      1. <系统初始时间>即系统启动时间，默认00：00启动。              |"<<endl;
 cout<<"     |      2. <收费标准>分为车场收费标准与便道收费标准，即停便道收费      |"<<endl;
 cout<<"     |         标准与车场不同，停在不同地方的总收费由两部分费用相加。      |"<<endl;
 cout<<"     |      3. <车场容量>即车场占地面积，与所能容纳车辆多少相关。          |"<<endl;
 cout<<"     |      4. <便道容量>即便道占地面积，车场停满之后会停在便道。          |"<<endl;
 cout<<"     |      5. <消息预存文档>自动启动系统时，需要先预读所有控制命令，      |"<<endl;
 cout<<"     |         这个是控制命令的存放位置，默认与程序路径相同，文件名为      |"<<endl;
 cout<<"     |         “msg.txt”(不包含引号)。命令存放一行一条，文件结尾以       |"<<endl; 
 cout<<"     |         <E,000000,0,00:00>结束。                                    |"<<endl;
 cout<<"     |      6. <日志保存文档>程序运行的所有数据将以系统日志方式保存，      |"<<endl;
 cout<<"     |         默认保存在与程序路径相同，文件名为”SystemLogs.txt“的      |"<<endl;
 cout<<"     |         文档中。(不包含引号)。                                      |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |                         · 按 任 意 键 返 回 ·                     |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |                       · 暨 · 南 · 大 · 学 ·                    |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"      --------------------------------------------------------------------- "<<endl;
 cout<<"/t◎";
 system("pause");
 return true;

}


bool CarSystem::SetParametor()
{
 bool _back=false;
 int number;
 while (!_back)
 {
  //系统时间，车场容量，便道容量，日志文档，消息数据区文档，收费标准
  system("cls");
  cout<<"      -------------------------------------------------------------------- "<<endl;
  cout<<"     |             · 停 · 车 · 场 · 管 · 理 · 系 · 统 ·           |"<<endl;
  cout<<"      -------------------------------------------------------------------- "<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                       · 参 · 数 · 设 · 置 ·                   |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                             1.参 数 说 明                          |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |        2.系 统 初 始 时 间                3.收 费 标 准            |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |        4.车 场 容 量                      5.便 道 容 量            |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |        6.消 息 预 存 文 档                7.日 志 保 存 文 档      |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                             0.返 回 上 层                          |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                       · 暨 · 南 · 大 · 学 ·                   |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"      -------------------------------------------------------------------- "<<endl;
  cout<<endl;
  cout<<"          ◎请输入菜单选项-->";
  cin>>number;
  cout<<endl;
  switch (number)
  {
  case 1:
   {//参数设置说明
    ParaHelp();
    break;
   }//case 1
  case 2:
   {//系统初始时间设置
    cout<<"        ◎◎请输入新系统时间-->";
    cin>>_sysTime;
    cout<<"        ◎◎新系统时间设置成功："<<_sysTime<<endl<<"/t◎";
    system("pause");
    break;
   }//case 2
  case 3:
   {//收费标准设置
    int pakLotFee=0,sideWayFee=0;
    cout<<"        ◎◎请输入新 停车场 收费标准-->";
    cin>>pakLotFee;
    cout<<"        ◎◎请输入新 便  道 收费标准-->";
    cin>>sideWayFee;
    if (SetPakLotFee(pakLotFee)&&SetSideWayFee(sideWayFee))
    {
     cout<<"        ◎◎新收费标准设置成功！停车场收费标准："<<setw(2)
      <<_pakLotFee<<"/t便道收费标准："<<setw(2)<<_sideWayFee<<endl<<"/t◎";
     system("pause");
    }//if
    else
    {
     cout<<"        ¤¤新收费标准设置失败！请重新设置。"<<endl<<"/t◎";
     system("pause");
     break;
    }//else
   }//case 3
  case 4:
   {//车场容量设置
    int capacity=0;
    cout<<"        ◎◎请输入新车场容量-->";
    cin>>capacity;
    if (capacity==0)
    {//车场容量不能设置为0
     cout<<"停车场容量不能设置为0！请重新设置！"<<endl;
     break;
    }//if
    if (_pakLot.ReSetStack(capacity)&&_tempLot.ReSetStack(capacity))
    {
     cout<<"        ◎◎新车场容量设置成功："<<capacity<<endl<<"/t◎";
     system("pause");
     break;
    }//if
    else
    {
     cout<<"        ¤¤新车场容量设置失败！请重新设置。"<<endl<<"/t◎";
     system("pause");
     break;
    }//else
   }//
  case 5:
   {//便道容量设置
    int capacity=0;
    cout<<"        ◎◎请输入新便道容量-->";
    cin>>capacity;
    if (_sideWay.ReSetQueue(capacity))
    {
     cout<<"        ◎◎新便道容量设置成功："<<capacity<<endl<<"/t◎";
     system("pause");
     break;
    }//if
    else
    {
     cout<<"        ¤¤新便道容量设置失败！请重新设置。"<<endl<<"/t◎";
     system("pause");
     break;
    }//else
   }// case 5
  case 6:
   {//消息命令文档路径设置
    cout<<"        ◎◎请输入新消息命令文档路径-->";
    cin>>_readMsgFile;
    if (_readMsgFile.empty())
    {
     cout<<"        ◎◎新消息命令文档路径设置成功："<<_readMsgFile<<endl<<"/t◎";
     system("pause");
     break;
    }//if
    else
    {
     cout<<"        ◎◎新消息命令文档路径设置失败！请重新设置。"<<endl<<"/t◎";
     system("pause");
     break;
    }//if
   }//case 6
  case 7:
   {//日志保存文档路径设置
    cout<<"        ◎◎请输入新消息命令文档路径-->";
    cin>>_saveLogFile;
    if (_saveLogFile.empty())
    {
     cout<<"        ◎◎新消息命令文档路径设置成功："<<_saveLogFile<<endl<<"/t◎";
     system("pause");
     break;
    }//if
    else
    {
     cout<<"        ◎◎新消息命令文档路径设置失败！请重新设置。"<<endl<<"/t◎";
     system("pause");
     break;
    }//else
   }//case 7
  case 0:
   {//返回上层
    _back=true;
    break;
   }//case 0
  default:
   {//输入错误
    cout<<"       ◎输入有误，请重新输入!";
    system("pause");
    break;
   }//default
  }//switch
 }//while
 return true;
}//SetParametor

 

bool CarSystem::UseSystemHelp()
{
 system("cls");
 cout<<"      --------------------------------------------------------------------- "<<endl;
 cout<<"     |              · 停 · 车 · 场 · 管 · 理 · 系 · 统 ·           |"<<endl;
 cout<<"      --------------------------------------------------------------------- "<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |                        · 使 · 用 · 说 · 明 ·                   |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |                  系统启动后，请按照如下格式输入系统命令             |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |      1. 命令类型，汽车车牌号，当前时间  例如：A,C07418,1,08:00      |"<<endl;
 cout<<"     |      2. 命令类型分三种-->   A-汽车到达，D-汽车离开，E-关闭系统      |"<<endl;
 cout<<"     |      3. 汽车车牌号应该是6位-->C07418,CT1259,80C57Z等均可。但是      |"<<endl;
 cout<<"     |         汽车离开的命令会检查是否存在汽车，若车牌号错误会导致系      |"<<endl;
 cout<<"     |         统中断，甚至出错(由于时间关系，未优化此处)。因此，键入      |"<<endl;
 cout<<"     |         命令时请慎重。                                              |"<<endl;
 cout<<"     |      4. 介于车牌与时间中的数字表示车辆类型，也相当于即车辆占地      |"<<endl;
 cout<<"     |         面积大小，1表示占一个车位大小，2表示两个车位大小，这与      |"<<endl;
 cout<<"     |         车场容量大小直接相关。                                      |"<<endl;
 cout<<"     |      5. 小时分钟均为两位中间以冒号相隔，且不能小于当前系统时间      |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |                          · 按 任 意 键 返 回 ·                    |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |                        · 暨 · 南 · 大 · 学 ·                   |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"      --------------------------------------------------------------------- "<<endl;
 cout<<"/t◎";
 system("pause");
 return true;
}


bool CarSystem::HelpFile()
{
 system("cls");
 cout<<"      -------------------------------------------------------------------- "<<endl;
 cout<<"     |             · 停 · 车 · 场 · 管 · 理 · 系 · 统 ·           |"<<endl;
 cout<<"      -------------------------------------------------------------------- "<<endl;
 cout<<"     |                                                                    |"<<endl;
 cout<<"     |                       · 说 · 明 · 文 · 档 ·                   |"<<endl;
 cout<<"     |                                                                    |"<<endl;
 cout<<"     |        本程序以两个栈结构(顺序栈)与一个队列(顺序队列)结构实现了停  |"<<endl;
 cout<<"     |    车场的管理问题，实现不够完美，有待改进。下是具体使用方法：      |"<<endl;
 cout<<"     |                                                                    |"<<endl;
 cout<<"     |   1. 人工启动-->用于人工输入命令控制停车场系统，详情见使用说明     |"<<endl;
 cout<<"     |   2. 自动启动-->用于处理预先保存的命令集文档，自动处理完成，并保存 |"<<endl;
 cout<<"     |      相应的日志文档，以供检测。                                    |"<<endl;
 cout<<"     |   3. 参数设置-->包含诸多程序参数的修改，详情见参数设置             |"<<endl;
 cout<<"     |   4. 程序使用C++，包含5个类[Time,Stack,Queue,SystemLog,CarSystem]  |"<<endl;
 cout<<"     |      均为简单类，实现单一。不包含虚函数，继承，多态。              |"<<endl;
 cout<<"     |                                                                    |"<<endl;
 cout<<"     |                         · 按 任 意 键 返 回 ·                    |"<<endl;
 cout<<"     |                                                                    |"<<endl;
 cout<<"     |                       · 暨 · 南 · 大 · 学 ·                   |"<<endl;
 cout<<"     |                                                                    |"<<endl;
 cout<<"      -------------------------------------------------------------------- "<<endl;
 cout<<"/t◎";
 system("pause");
 return true;
}
