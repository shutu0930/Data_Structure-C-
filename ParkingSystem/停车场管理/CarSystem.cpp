#include "CarSystem.h"

#include "CarSystem.h"
#include <conio.h>
#include <iomanip>

CarSystem::CarSystem()
{
 _msgData=new MsgNode;
 _msgData->_next=NULL;
 _msg._orderType='E';
 _sysTime.SetTime(0,0);                 //����ͣ����ϵͳ����ʱ��
 _pakLotFee=DEFAULT_PLOT_FEE;           //Ĭ�ϳ����շѱ�׼
 _sideWayFee=DEFAULT_SWAY_FEE;          //Ĭ�ϱ���շѱ�׼
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
 int errors=0;//������Ϣ������
 int count=0;//��Ϣ������
 while (!fin.eof())
 {
  fin>>msg._orderType;
  //�˴�����ע�͹��˹���
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
   getline(fin,string());//����һ��
  }//else
  count++;//������+1
 }//while
 fin.close();
 cout<<_msgData;
 system("pause");
 if (errors)
 {
  cout<<"����ȡ"<<setw(3)<<count<<" ����Ϣ��"<<"��Ч��Ϣ��"<<setw(3)<<errors<<"����"<<endl;
  cout<<"������Դ���ܵ��³����쳣��ֹ��������������ȷ���ٲ��ԡ��Ƿ����(Y/N)��"<<endl;
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
 {//������ȷ
  if (!_msg.car._carNum.empty()&&_msg.car._carType>=0)
  {//���ƺţ�������ȷ������ʱ����Ч
   return true;
  }//if
 }//if
 return false;
}//CheckMsg


bool CarSystem::SetCar()
{
 if (!_pakLot.Full())
 {//����û��
  _msg.car._timeBgn=_sysTime;
  _pakLot.Push(_msg.car); 
 }//if
 else if (!_sideWay.Full())
 {
  _sideWay.EnQueue(_msg.car);
 }//else if
 else
 {
  cout<<"û�и����ͣ���ռ�!"<<endl;
  system("pause");//�˴�����ϵͳ��ͣ����~
  return false;
 }//else
 return true;
}


bool CarSystem::GetCar(CarNode &carMove)
{
 if (_pakLot.Find(_msg.car))
 {//�ڳ���
  CarNode carMove=_pakLot.Pop();
  while (carMove._carNum!=_msg.car._carNum)//�Ż��˴���������string����Ƚ�
  {//��ʼ�ҳ�
   _tempLot.Push(carMove);
   carMove=_pakLot.Pop();
  }//for
  //carMove��Ӧ���⳵��
  int fee=(carMove._timeBgn-carMove._timeArr)*_sideWayFee+(_sysTime-carMove._timeBgn)*_pakLotFee;//�������Ӧ��ͣ������
  fee*=carMove._carType;//�������͵ı���
  _carLog.AddRecord(carMove,_sysTime,fee);
  while (!_tempLot.Empty())
  {                                 //���ݲ���
   carMove=_tempLot.Pop(); 
   _pakLot.Push(carMove);
  }//while                                 //���ݲ���
  CheckPakLot();                             //��⳵��                                //���ݲ���
 }//if
 else if (_sideWay.Find(_msg.car))
 {//�ڱ��                                                                             �˴��Դ�������
  CarNode carMove=_sideWay.DeQueue(),setBack=_sideWay.GetReer();//setBack-->����ĳ������������ĳ���ԭ
  while (carMove._carNum!=_msg.car._carNum)   //�޸Ĵ˴��ж�
  {//��ʼ�ҳ�
   _sideWay.EnQueue(carMove);
   carMove=_sideWay.DeQueue();
  }//while
  //carMove��Ӧ���⳵��
  int fee=(_sysTime-carMove._timeArr)*_sideWayFee;//�������Ӧ��ͣ������
  fee*=carMove._carType;//�������͵ı���
  _carLog.AddRecord(carMove,_sysTime,fee);//������־�ļ�
  carMove=_sideWay.DeQueue();
  //��һ������Ҫ�ҵĳ� �������
  while (carMove._carNum!=setBack._carNum)
  {
   _sideWay.EnQueue(carMove);
   carMove=_sideWay.DeQueue();
  }//while
  _sideWay.EnQueue(carMove);//�ҵ�β�������������
 }//else if
 else
 {
  cout<<"�Ҳ������� "<<_msg.car._carNum<<"!   ����������Ϣ!"<<endl;
  PakLotTest();            //�û������
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
   //�˴�����ϵͳ��ͣ����
   SetCar();//�������
   break;
  }//case 'A'
 case 'D':
  {
   CarNode carMove;
   GetCar(carMove);//_msg�ݴ��ã�֮������
   break;
  }
 case'E':
  {
   int fee;//�洢ÿ����Ӧ�ɵķ���
   while (!_pakLot.Empty())
   {//�������ȼ�¼
    _msg.car=_pakLot.Pop();
    _tempLot.Push(_msg.car);
   }//while
   while (!_tempLot.Empty())
   {
    _msg.car=_tempLot.Pop();
    fee=(_msg.car._timeBgn-_msg.car._timeArr)*_sideWayFee+(_sysTime-_msg.car._timeBgn)*_pakLotFee;//�������Ӧ��ͣ������
    fee*=_msg.car._carType;//�������͵ı���
    _carLog.AddRecord(_msg.car,_sysTime,fee);//�����ĳ���գ��շ�
   }//while
   while (!_sideWay.Empty())
   {
    _msg.car=_sideWay.DeQueue();
    fee=(_sysTime-_msg.car._timeArr)*_sideWayFee;//�������Ӧ��ͣ������
    fee*=_msg.car._carType;//�������͵ı���
    _carLog.AddRecord(_msg.car,_sysTime,fee);//������־�ļ�
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
  carMove._timeBgn=_sysTime;//���ʱ��
  _pakLot.Push(carMove);
 }//while
 return true;
}//CheckPakLot


bool CarSystem::AutoDriveEvent()
{
 bool finished=false;
 if (LoadMsg())
 {
  ProcessMsgData();      //������Ϣ������ʱ��˳������
  if (!PeekMsg())
   return false;
  while (!finished)
  {
   _sysTime++;//ϵͳ��ʱ��
   if (_msg.car._timeArr<=_sysTime||_msg._orderType=='E')
   {
    ProcessMsg();
    if (!PeekMsg())
     finished=true;
   }//if
   //ɾ���˳���������
   system("cls");
   cout<<"  ---------------------------------------------------------------------------- "<<endl;
   cout<<" |                �� ͣ �� �� �� �� �� �� �� �� �� ϵ �� ͳ ��                |"<<endl;
   cout<<"  ---------------------------------------------------------------------------- "<<endl;
   cout<<"                                           �� ϵ ͳ ʱ �� ��  "<<_sysTime<<"   "<<endl;
   cout<<_carLog;                           //���������ϵͳ��־
  }//while
  SaveLogs();
  cout<<"     ���"<<"����������"<<setw(3)<<_pakLot.StackCapacity()<<"       ʣ��������"<<setw(3)
   <<_pakLot.StackCapacity()-_pakLot.StackSize()<<"       ����������"<<setw(3)<<_pakLot.StackSum()<<endl
   <<"     �����������"<<setw(3)<<_sideWay.QueueCapacity()<<"       ʣ��������"<<setw(3)
   <<_sideWay.QueueCapacity()-_sideWay.QueueSize()<<"       ����������"<<setw(3)<<_sideWay.QueueSum()<<endl;
  //�ر�ϵͳ;
  _sysTime.SetTime(0,0);
  _pakLot.Clear();
  _tempLot.Clear();
  _sideWay.Clear();
  _carLog.Clear();
  cout<<"     ���"<<"ϵͳ�ѹرգ�"
   <<"                       ��";
  system("pause");
  return true;
 }
 cout<<"System Error!"<<endl;
 return false;
}

bool CarSystem::SaveLogs()
{//�޸������ʽ
 ofstream fout(_saveLogFile.c_str());
 if (fout.fail())
 {
  cout<<"Open File "<<_saveLogFile<<" Failed!"<<endl;
  exit(1);
 }
 fout<<endl<<"                                    -----ͣ����ϵͳ��־-----                 "<<endl<<endl;
 fout<<"  ���/t/t  ���ƺ�/t/t/t       ����ʱ��/t/t/t      �뿪ʱ��/t/t    �Ʒ�ʱ��/t/t     ���� "<<endl;
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
 fout<<endl<<"������ʱ�䣺/t/t"<<_sysTime<<endl;
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
//������ʾ����
//


bool CarSystem::PutPakLotInfo()const
{
 system("cls");
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<"        |          �� ͣ �� �� �� �� �� �� �� �� �� ϵ �� ͳ ��        |"<<endl;
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<"                                       �� ϵ ͳ ʱ �� ��  "<<_sysTime<<"   "<<endl;
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<"        |                   �� �� �� �� �� �� �� �� ��                 |"<<endl;
 cout<<"        | ���      ���ƺ�        ����ʱ��       ��ͣʱ��        ����  |"<<endl;
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
 cout<<"          ��ͣ������"<<setw(3)<<count<<"            �򳵳�������"<<setw(3)<<_pakLot.StackCapacity()<<endl<<endl;
 cout<<"        ���";
 system("pause");
 return true;
}


bool CarSystem::PutSideWayInfo() const
{
 system("cls");
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<"        |          �� ͣ �� �� �� �� �� �� �� �� �� ϵ �� ͳ ��        |"<<endl;
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<"                                       �� ϵ ͳ ʱ �� ��  "<<_sysTime<<"   "<<endl;
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<"        |                   �� �� �� �� �� �� �� �� ��                 |"<<endl;
 cout<<"        | ���      ���ƺ�        ����ʱ��       ��ͣʱ��        ����  |"<<endl;
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<"        |                                                              |"<<endl;
 int count=0;
 CarNodePtr pBase=_sideWay.GetBase();
 int sum=_sideWay.QueueSum();
 int minute=0;
 while (sum!=0)
 {
  minute=-(pBase->_timeArr-_sysTime);           //��ת����ʱ����ִ���
  cout<<"        | "<<setw(3)<<++count<<"       "<<setw(6)<<pBase->_carNum<<"       "<<setw(5)<<pBase->_timeArr
   <<"           "<<setw(4)<<minute<<"         "<<setw(4)<<minute*_pakLotFee<<"  |"<<endl;
  pBase++;
  sum--;
 }
 cout<<"        |                                                              |"<<endl;
 cout<<"         -------------------------------------------------------------- "<<endl;
 cout<<endl;
 cout<<"          ��ͣ������"<<setw(3)<<count<<"            ����������"<<setw(3)<<_sideWay.QueueCapacity()<<endl<<endl;
 cout<<"        ���";
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
  cout<<"     |             �� ͣ �� �� �� �� �� �� �� �� �� ϵ �� ͳ ��           |"<<endl;
  cout<<"      --------------------------------------------------------------------" <<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                       �� �� �� ӭ �� ʹ �� �� ��                   |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |            1.�� �� �� ��                    2.�� �� �� ��          |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |            3.�� �� �� ��                    4.�� �� �� ��          |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                            0. �� �� ϵ ͳ                          |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                       �� �� �� �� �� �� �� ѧ ��                   |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"      -------------------------------------------------------------------- "<<endl;
  cout<<endl;
  cout<<"          ��������˵�ѡ��-->";
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
    cout<<endl<<endl<<"        ����лʹ�ã�";
    break;
   }
  default:
   {
    cout<<"������������������!"<<endl;
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
  cout<<"     |              �� ͣ �� �� �� �� �� �� �� �� �� ϵ �� ͳ ��          |"<<endl;
  cout<<"      -------------------------------------------------------------------- "<<endl;
  cout<<"                                         �� ϵ ͳ ʱ �� ��  "<<_sysTime<<endl;
  cout<<"      -------------------------------------------------------------------- "<<endl;
  cout<<"     |                       �� �� �� �� �� �� �� �� ��                   |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |            1.ʹ �� ˵ ��                    2.�� �� �� ��          |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |            3.�� �� �� ��                    4.�� �� �� ־          |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |            5.�� �� �� ��                    6.�� �� ϵ ͳ          |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                              0.�� �� ϵ ͳ                         |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                       �� �� �� �� �� �� �� ѧ ��                   |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"      -------------------------------------------------------------------- "<<endl;
  cout<<endl;
  cout<<"          ��������˵�ѡ��-->";
  cin>>order;
  switch (order)
  {
  case '1':
   {//ʹ��˵��
    _useful=UseSystemHelp();
    break;
   }//case 1
  case '2':
   {//�鿴����
    if (!_useful)
    {
     cout<<endl<<"        ���"<<"�����Ķ�ʹ��˵��!"<<endl;
     system("pause");
     break;
    }//if
    PutPakLotInfo();
    break;
   }//case 2
  case '3':
   {//�鿴���
    if (!_useful)
    {
     cout<<"�����Ķ�ʹ��˵��!"<<endl;
     system("pause");
     break;
    }//if
    PutSideWayInfo();
    break;
   }//case 3
  case '4':
   {//�鿴��־
    if (!_useful)
    {
     cout<<"�����Ķ�ʹ��˵��!"<<endl;
     system("pause");
     break;
    }//if
    system("cls");
    cout<<_carLog;
    system("pause");
    break;
   }//case 4
  case '5':
   {//��������
    cout<<endl<<"       ��������������";
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
   {//�ر�ϵͳ   �˴��޸�
    return true;
    break;
   }//case 6
  case '0':
   {//�˳�ϵͳ
    cout<<endl<<endl<<"        ����лʹ�ã�";
    exit(1);
    break;
   }//case 0
  default:
   {//��������
    cout<<"       ��������������������!"<<endl;
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
 cout<<"     |               �� ͣ �� �� �� �� �� �� �� �� �� ϵ �� ͳ ��          |"<<endl;
 cout<<"      --------------------------------------------------------------------- "<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |                       �� �� �� �� �� ˵ �� �� ��                    |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |      1. <ϵͳ��ʼʱ��>��ϵͳ����ʱ�䣬Ĭ��00��00������              |"<<endl;
 cout<<"     |      2. <�շѱ�׼>��Ϊ�����շѱ�׼�����շѱ�׼����ͣ����շ�      |"<<endl;
 cout<<"     |         ��׼�복����ͬ��ͣ�ڲ�ͬ�ط������շ��������ַ�����ӡ�      |"<<endl;
 cout<<"     |      3. <��������>������ռ����������������ɳ���������ء�          |"<<endl;
 cout<<"     |      4. <�������>�����ռ�����������ͣ��֮���ͣ�ڱ����          |"<<endl;
 cout<<"     |      5. <��ϢԤ���ĵ�>�Զ�����ϵͳʱ����Ҫ��Ԥ�����п������      |"<<endl;
 cout<<"     |         ����ǿ�������Ĵ��λ�ã�Ĭ�������·����ͬ���ļ���Ϊ      |"<<endl;
 cout<<"     |         ��msg.txt��(����������)��������һ��һ�����ļ���β��       |"<<endl; 
 cout<<"     |         <E,000000,0,00:00>������                                    |"<<endl;
 cout<<"     |      6. <��־�����ĵ�>�������е��������ݽ���ϵͳ��־��ʽ���棬      |"<<endl;
 cout<<"     |         Ĭ�ϱ����������·����ͬ���ļ���Ϊ��SystemLogs.txt����      |"<<endl;
 cout<<"     |         �ĵ��С�(����������)��                                      |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |                         �� �� �� �� �� �� �� ��                     |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |                       �� �� �� �� �� �� �� ѧ ��                    |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"      --------------------------------------------------------------------- "<<endl;
 cout<<"/t��";
 system("pause");
 return true;

}


bool CarSystem::SetParametor()
{
 bool _back=false;
 int number;
 while (!_back)
 {
  //ϵͳʱ�䣬���������������������־�ĵ�����Ϣ�������ĵ����շѱ�׼
  system("cls");
  cout<<"      -------------------------------------------------------------------- "<<endl;
  cout<<"     |             �� ͣ �� �� �� �� �� �� �� �� �� ϵ �� ͳ ��           |"<<endl;
  cout<<"      -------------------------------------------------------------------- "<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                       �� �� �� �� �� �� �� �� ��                   |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                             1.�� �� ˵ ��                          |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |        2.ϵ ͳ �� ʼ ʱ ��                3.�� �� �� ׼            |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |        4.�� �� �� ��                      5.�� �� �� ��            |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |        6.�� Ϣ Ԥ �� �� ��                7.�� ־ �� �� �� ��      |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                             0.�� �� �� ��                          |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"     |                       �� �� �� �� �� �� �� ѧ ��                   |"<<endl;
  cout<<"     |                                                                    |"<<endl;
  cout<<"      -------------------------------------------------------------------- "<<endl;
  cout<<endl;
  cout<<"          ��������˵�ѡ��-->";
  cin>>number;
  cout<<endl;
  switch (number)
  {
  case 1:
   {//��������˵��
    ParaHelp();
    break;
   }//case 1
  case 2:
   {//ϵͳ��ʼʱ������
    cout<<"        �����������ϵͳʱ��-->";
    cin>>_sysTime;
    cout<<"        �����ϵͳʱ�����óɹ���"<<_sysTime<<endl<<"/t��";
    system("pause");
    break;
   }//case 2
  case 3:
   {//�շѱ�׼����
    int pakLotFee=0,sideWayFee=0;
    cout<<"        ����������� ͣ���� �շѱ�׼-->";
    cin>>pakLotFee;
    cout<<"        ����������� ��  �� �շѱ�׼-->";
    cin>>sideWayFee;
    if (SetPakLotFee(pakLotFee)&&SetSideWayFee(sideWayFee))
    {
     cout<<"        ������շѱ�׼���óɹ���ͣ�����շѱ�׼��"<<setw(2)
      <<_pakLotFee<<"/t����շѱ�׼��"<<setw(2)<<_sideWayFee<<endl<<"/t��";
     system("pause");
    }//if
    else
    {
     cout<<"        ������շѱ�׼����ʧ�ܣ����������á�"<<endl<<"/t��";
     system("pause");
     break;
    }//else
   }//case 3
  case 4:
   {//������������
    int capacity=0;
    cout<<"        ����������³�������-->";
    cin>>capacity;
    if (capacity==0)
    {//����������������Ϊ0
     cout<<"ͣ����������������Ϊ0�����������ã�"<<endl;
     break;
    }//if
    if (_pakLot.ReSetStack(capacity)&&_tempLot.ReSetStack(capacity))
    {
     cout<<"        ����³����������óɹ���"<<capacity<<endl<<"/t��";
     system("pause");
     break;
    }//if
    else
    {
     cout<<"        ����³�����������ʧ�ܣ����������á�"<<endl<<"/t��";
     system("pause");
     break;
    }//else
   }//
  case 5:
   {//�����������
    int capacity=0;
    cout<<"        ����������±������-->";
    cin>>capacity;
    if (_sideWay.ReSetQueue(capacity))
    {
     cout<<"        ����±���������óɹ���"<<capacity<<endl<<"/t��";
     system("pause");
     break;
    }//if
    else
    {
     cout<<"        ����±����������ʧ�ܣ����������á�"<<endl<<"/t��";
     system("pause");
     break;
    }//else
   }// case 5
  case 6:
   {//��Ϣ�����ĵ�·������
    cout<<"        �������������Ϣ�����ĵ�·��-->";
    cin>>_readMsgFile;
    if (_readMsgFile.empty())
    {
     cout<<"        �������Ϣ�����ĵ�·�����óɹ���"<<_readMsgFile<<endl<<"/t��";
     system("pause");
     break;
    }//if
    else
    {
     cout<<"        �������Ϣ�����ĵ�·������ʧ�ܣ����������á�"<<endl<<"/t��";
     system("pause");
     break;
    }//if
   }//case 6
  case 7:
   {//��־�����ĵ�·������
    cout<<"        �������������Ϣ�����ĵ�·��-->";
    cin>>_saveLogFile;
    if (_saveLogFile.empty())
    {
     cout<<"        �������Ϣ�����ĵ�·�����óɹ���"<<_saveLogFile<<endl<<"/t��";
     system("pause");
     break;
    }//if
    else
    {
     cout<<"        �������Ϣ�����ĵ�·������ʧ�ܣ����������á�"<<endl<<"/t��";
     system("pause");
     break;
    }//else
   }//case 7
  case 0:
   {//�����ϲ�
    _back=true;
    break;
   }//case 0
  default:
   {//�������
    cout<<"       ��������������������!";
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
 cout<<"     |              �� ͣ �� �� �� �� �� �� �� �� �� ϵ �� ͳ ��           |"<<endl;
 cout<<"      --------------------------------------------------------------------- "<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |                        �� ʹ �� �� �� ˵ �� �� ��                   |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |                  ϵͳ�������밴�����¸�ʽ����ϵͳ����             |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |      1. �������ͣ��������ƺţ���ǰʱ��  ���磺A,C07418,1,08:00      |"<<endl;
 cout<<"     |      2. �������ͷ�����-->   A-�������D-�����뿪��E-�ر�ϵͳ      |"<<endl;
 cout<<"     |      3. �������ƺ�Ӧ����6λ-->C07418,CT1259,80C57Z�Ⱦ��ɡ�����      |"<<endl;
 cout<<"     |         �����뿪����������Ƿ���������������ƺŴ���ᵼ��ϵ      |"<<endl;
 cout<<"     |         ͳ�жϣ���������(����ʱ���ϵ��δ�Ż��˴�)����ˣ�����      |"<<endl;
 cout<<"     |         ����ʱ�����ء�                                              |"<<endl;
 cout<<"     |      4. ���ڳ�����ʱ���е����ֱ�ʾ�������ͣ�Ҳ�൱�ڼ�����ռ��      |"<<endl;
 cout<<"     |         �����С��1��ʾռһ����λ��С��2��ʾ������λ��С������      |"<<endl;
 cout<<"     |         ����������Сֱ����ء�                                      |"<<endl;
 cout<<"     |      5. Сʱ���Ӿ�Ϊ��λ�м���ð��������Ҳ���С�ڵ�ǰϵͳʱ��      |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |                          �� �� �� �� �� �� �� ��                    |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"     |                        �� �� �� �� �� �� �� ѧ ��                   |"<<endl;
 cout<<"     |                                                                     |"<<endl;
 cout<<"      --------------------------------------------------------------------- "<<endl;
 cout<<"/t��";
 system("pause");
 return true;
}


bool CarSystem::HelpFile()
{
 system("cls");
 cout<<"      -------------------------------------------------------------------- "<<endl;
 cout<<"     |             �� ͣ �� �� �� �� �� �� �� �� �� ϵ �� ͳ ��           |"<<endl;
 cout<<"      -------------------------------------------------------------------- "<<endl;
 cout<<"     |                                                                    |"<<endl;
 cout<<"     |                       �� ˵ �� �� �� �� �� �� ��                   |"<<endl;
 cout<<"     |                                                                    |"<<endl;
 cout<<"     |        ������������ջ�ṹ(˳��ջ)��һ������(˳�����)�ṹʵ����ͣ  |"<<endl;
 cout<<"     |    �����Ĺ������⣬ʵ�ֲ����������д��Ľ������Ǿ���ʹ�÷�����      |"<<endl;
 cout<<"     |                                                                    |"<<endl;
 cout<<"     |   1. �˹�����-->�����˹������������ͣ����ϵͳ�������ʹ��˵��     |"<<endl;
 cout<<"     |   2. �Զ�����-->���ڴ���Ԥ�ȱ��������ĵ����Զ�������ɣ������� |"<<endl;
 cout<<"     |      ��Ӧ����־�ĵ����Թ���⡣                                    |"<<endl;
 cout<<"     |   3. ��������-->����������������޸ģ��������������             |"<<endl;
 cout<<"     |   4. ����ʹ��C++������5����[Time,Stack,Queue,SystemLog,CarSystem]  |"<<endl;
 cout<<"     |      ��Ϊ���࣬ʵ�ֵ�һ���������麯�����̳У���̬��              |"<<endl;
 cout<<"     |                                                                    |"<<endl;
 cout<<"     |                         �� �� �� �� �� �� �� ��                    |"<<endl;
 cout<<"     |                                                                    |"<<endl;
 cout<<"     |                       �� �� �� �� �� �� �� ѧ ��                   |"<<endl;
 cout<<"     |                                                                    |"<<endl;
 cout<<"      -------------------------------------------------------------------- "<<endl;
 cout<<"/t��";
 system("pause");
 return true;
}
