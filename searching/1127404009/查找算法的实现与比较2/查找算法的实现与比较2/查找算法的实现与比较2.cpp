// �����㷨��ʵ����Ƚ�2.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include"utility.h"
#include"Random.h"
#include"Timer.h"
#include"Key.h"
typedef Key Record;
#include"List.h"
#include"Ordered_list.h"
#include"search.h"

void main()
{
	cout<<"��ѡ�����¹��ܣ�"<<endl
		<<"1.�Ƚ���������������½���˳�����ʱ��Ч��"<<endl
		<<"2.�Ƚ���ͬһ������½���˳����ҺͶ��ֲ��ҵ�Ч��"<<endl
		<<"3.�˳�"<<endl;	
	int select;
    bool outcome=true;
	cin>>select;
	switch(select){
	case 1 :
		{
			cout<<"�Ƚ���������������½���˳�����ʱ��Ч�ʡ�"<<endl;
			cout<<"���е�������1��ʼһ��n����Ҫ����searches�Ρ�"<<endl;
	        int n,searches,i,j;
	        Ordered_list a;
			List<Record> b;
			Random Numbers;
			while(outcome)
			{
				cout<<"��ѡ�����¹��ܣ�"<<endl
			        <<"1.�����µ������       2.�����µ������"<<endl
			        <<"3.���Բ���������Ч�� 4.���Բ���������Ч��"<<endl
			        <<"5.�˳�"<<endl;
				cin>>select;
				switch(select)
				{
				case 1:
					cout<<"������n��searches��ֵ��"<<flush;
					cin>>n>>searches;
					a.clear();
					j=1;
					for(i=1;i<=n;i++)
					{
						if (a.insert(a.size(), j) !=success)
						{
							cout << " Overflow in filling list." << endl;
							
						}
						cout<<j<<endl;
						j+=2;
					}
					break;
				case 2:
					cout<<"������n��searches��ֵ��"<<flush;
					cin>>n>>searches;
					b.clear();
					for(i=1;i<=n;i++)
					{
						if (b.nonorderinsert(b.size(),2 * Numbers.random_integer(0, n-1)+1,n-1) != success)
							cout << " Overflow in filling list." << endl;
						cout<<(2*Numbers.random_integer(0, n-1)+1)<<endl;
					
					}
						
						break;
				case 3:
					test_search(searches,a);
					break;
				case 4:
					test_search(searches,b);
					break;
				case 5:
					outcome=false;
				}
			}
		}
			break;
		case 2:
			{
			cout<<"�Ƚ���ͬһ������½���˳����ҺͶ��ֲ��ҵ�Ч��"<<endl;
	        cout<<"���е�������1��ʼһ��n����Ҫ����searches�Ρ�"<<endl;
			int n,searches,i;
			Ordered_list a;
			while(outcome)
			{
				cout<<"��ѡ�����¹��ܣ�"<<endl
			        <<"1.�����µ������                2.����˳����ҵ�Ч��"<<endl
			        <<"3.����binary-search1����Ч��    4.����binary-search2����Ч��"<<endl
			        <<"5.�˳�"<<endl;
				cin>>select;
				switch(select)
				{
				case 1:
					cout<<"������n��searches��ֵ��"<<flush;
					cin>>n>>searches;
					a.clear();
					for(i=1;i<=n;i++)
					{
						if (a.insert(a.size(), 2*i-1) != success)
							cout << " Overflow in filling list." << endl;
					}
					break;
				case 2:
					test_search(searches,a);
					break;
				case 3:
					test_b1_search(searches,a);
					break;
				case 4:
					test_b2_search(searches,a);
					break;
				case 5:
					outcome=false;
				}
			   }
			}	
			break;
		case 3:
			outcome=false;
		}
}
