// 词频统计程序（C）.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include <ctype.h>
#define MAX 32

typedef struct _TreeNode 
{ 
     int count; //出现的次数  
     char* word;//单词本身   
     struct _TreeNode* left; 
     struct _TreeNode* right;   
         
}TreeNode; 
//给TreeNode分配内存   
TreeNode* talloc(void) 
{ 
   return (TreeNode*)malloc(sizeof(TreeNode));         
} 
 
//打印tree   
void tprint(TreeNode* root) 
{ 
     //中序遍历
     if(root!=NULL) 
     { 
         tprint(root->left); 
         printf("%-15s %d\n",root->word,root->count);   
         tprint(root->right);                 
     } 
} 
 
//把单词添加节点的合适位置   
TreeNode* addNode(TreeNode* node,const char* word) 
{ 
    int con;       
    TreeNode* temp=NULL;   
    if(node==NULL) 
    { 
        node=talloc(); 
        node->count=1;   
		node->word=(char *) malloc(50*sizeof (char));
        strcpy(node->word,word); 
        node->left=node->right=NULL; 
    }else if((con=strcmp(word,node->word))<0) 
    { 
       temp=addNode(node->left,word); 
       node->left=temp;     
    }else if(con=strcmp(word,node->word)>0) 
    { 
       temp=addNode(node->right,word);   
       node->right=temp;     
    }else
	{ 
       (node->count)++;     
    }     
    return node; 
} 

int isNull(char c)
{
      return !(((c>='a'&&c<='z')||(c>='A'&&c<='Z')));
}
//从文件中读取单词
int getWord(FILE *fp,char *str)
{
    char c;
    int counter=0;
    while((c=fgetc(fp))!=EOF)
	{
        if( isNull(c)==1 &&(counter<= 0))
		{
            //消去非字母字符
            continue;
        }
        else if(isNull(c)==1&& (counter>0))
		{
            //一个单词读取完毕
            break;
        }
        str[counter]=c;
		counter++;
    }
    str[counter]='\0';
    //成功返回SUCCESS 否则返回FAIL
	
    if(counter> 0)
        return 1;
    else
        return 0;
}


//是否tree占用的内存   
void treeFree(TreeNode* root) 
{ 
	TreeNode *temp=root;
	if(root!=NULL) 
   { 
      treeFree(root->left);             
      treeFree(root->right);      
	  free(root->word); //释放节点的word占用的内存   
      root=NULL;   //是否节点占用的内存           
      free(temp);       
   }   
} 
  
void main() 
{ 
	FILE *fp;
	fp=fopen("a.txt","r");
	char *str;
	str=(char *) malloc(50*sizeof (char));
	 TreeNode* root=NULL; 
	
  if(fp!=NULL) 
  { 
	  
    while((getWord(fp,str)==1)) 
     { 
        root=addNode(root,str);                         
     } 
    tprint(root);   
    treeFree(root);                             
    fclose(fp);                                     
  }else
  { 
         printf("open error\n");   
 } 
  
} 


