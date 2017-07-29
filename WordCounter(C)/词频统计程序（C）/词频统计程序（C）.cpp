// ��Ƶͳ�Ƴ���C��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include <ctype.h>
#define MAX 32

typedef struct _TreeNode 
{ 
     int count; //���ֵĴ���  
     char* word;//���ʱ���   
     struct _TreeNode* left; 
     struct _TreeNode* right;   
         
}TreeNode; 
//��TreeNode�����ڴ�   
TreeNode* talloc(void) 
{ 
   return (TreeNode*)malloc(sizeof(TreeNode));         
} 
 
//��ӡtree   
void tprint(TreeNode* root) 
{ 
     //�������
     if(root!=NULL) 
     { 
         tprint(root->left); 
         printf("%-15s %d\n",root->word,root->count);   
         tprint(root->right);                 
     } 
} 
 
//�ѵ�����ӽڵ�ĺ���λ��   
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
//���ļ��ж�ȡ����
int getWord(FILE *fp,char *str)
{
    char c;
    int counter=0;
    while((c=fgetc(fp))!=EOF)
	{
        if( isNull(c)==1 &&(counter<= 0))
		{
            //��ȥ����ĸ�ַ�
            continue;
        }
        else if(isNull(c)==1&& (counter>0))
		{
            //һ�����ʶ�ȡ���
            break;
        }
        str[counter]=c;
		counter++;
    }
    str[counter]='\0';
    //�ɹ�����SUCCESS ���򷵻�FAIL
	
    if(counter> 0)
        return 1;
    else
        return 0;
}


//�Ƿ�treeռ�õ��ڴ�   
void treeFree(TreeNode* root) 
{ 
	TreeNode *temp=root;
	if(root!=NULL) 
   { 
      treeFree(root->left);             
      treeFree(root->right);      
	  free(root->word); //�ͷŽڵ��wordռ�õ��ڴ�   
      root=NULL;   //�Ƿ�ڵ�ռ�õ��ڴ�           
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


