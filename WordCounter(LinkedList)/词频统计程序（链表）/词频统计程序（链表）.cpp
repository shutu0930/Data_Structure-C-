// 词频统计程序（链表）.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<errno.h>
#include<ctype.h>
typedef struct word_tag{
    char *name;
    int count;
    struct word_tag *next;
}word;

word *head = NULL;
char *mycopy(char *name){
    char *new = (char *)malloc(strlen(name)+1);
    strcpy(new,name);
    return new;
}

word* create_word(char *name){
    word *new_word = (word*)malloc(sizeof(word));
    new_word->name = mycopy(name);
    new_word->count = 1;
    new_word->next = NULL;
    return new_word;
}

void word_push(char *name){
    word *current = NULL;
    word *previous = NULL;
    int is_count = 0;

    for(current = head; current; current= current->next){
        if( (is_count=strcmp(current->name, name)) >= 0){
            break;
        }
        previous = current;
    }

    if(head && !is_count){
        current->count++;
    }else{
        word* new_word = create_word(name);
        if(!previous){
            new_word->next = head;
            head = new_word;
        }else{
            previous->next = new_word;
            new_word->next = current;
        }
    }
}

void word_destory(){
    word *ptword;
    for(;head;head=head->next){
        ptword = head;
        free(ptword->name);
        free(ptword);
    }
}
void show(){
    word *pword;
    for(pword=head;pword;pword= pword->next){
        printf("%s,%d\n",pword->name, pword->count);
    }
}

int get_word( FILE *fp, char *buf, int size){
    int c = getc(fp);
    int i = 0;
    for(;c != EOF && isspace(c);c = getc(fp));
    for(;c != EOF && !isspace(c);c = getc(fp)){
        if( i < size - 1)
            buf[i++] = tolower(c);
    }
    if( i < size)
        buf[i] = '\0';
    if( c != EOF){
        ungetc(c, fp);
    }
    return buf[0] != '\0';
}
int main(int argc, char **argv){
    FILE *fp = NULL;
    char buffer[128] = {0};
    int i;
    for(i = 1; i < argc; i++){
        fp = fopen(argv[i], "r");
        if( !fp ){
            fprintf(stderr,"%s:can't open %s %s\n",
                    argv[0],argv[i],strerror(errno));
        }else{
            while(get_word(fp, buffer, sizeof(buffer))){
                word_push(buffer);
            }
            show();
            word_destory();
        }
        fclose(fp);
    }
    return 0;
}

