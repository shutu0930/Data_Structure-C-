// 查找算法的实现与比较2.cpp : 定义控制台应用程序的入口点。
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
	cout<<"请选择以下功能："<<endl
		<<"1.比较在有序表和无序表下进行顺序查找时的效率"<<endl
		<<"2.比较在同一有序表下进行顺序查找和二分查找的效率"<<endl
		<<"3.退出"<<endl;	
	int select;
    bool outcome=true;
	cin>>select;
	switch(select){
	case 1 :
		{
			cout<<"比较在有序表和无序表下进行顺序查找时的效率。"<<endl;
			cout<<"表中的奇数从1开始一共n个，要查找searches次。"<<endl;
	        int n,searches,i,j;
	        Ordered_list a;
			List<Record> b;
			Random Numbers;
			while(outcome)
			{
				cout<<"请选择以下功能："<<endl
			        <<"1.生成新的有序表       2.生成新的无序表"<<endl
			        <<"3.测试查找有序表的效率 4.测试查找无序表的效率"<<endl
			        <<"5.退出"<<endl;
				cin>>select;
				switch(select)
				{
				case 1:
					cout<<"请输入n和searches的值："<<flush;
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
					cout<<"请输入n和searches的值："<<flush;
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
			cout<<"比较在同一有序表下进行顺序查找和二分查找的效率"<<endl;
	        cout<<"表中的奇数从1开始一共n个，要查找searches次。"<<endl;
			int n,searches,i;
			Ordered_list a;
			while(outcome)
			{
				cout<<"请选择以下功能："<<endl
			        <<"1.生成新的有序表                2.测试顺序查找的效率"<<endl
			        <<"3.测试binary-search1查找效率    4.测试binary-search2查找效率"<<endl
			        <<"5.退出"<<endl;
				cin>>select;
				switch(select)
				{
				case 1:
					cout<<"请输入n和searches的值："<<flush;
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
