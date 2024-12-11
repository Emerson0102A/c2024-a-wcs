#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50
#define MAX_NUMBER 10

typedef struct{
    int quantity;
    char name[MAX_SIZE];
}inventory;

int count=0;
inventory item[MAX_NUMBER];
//不能在文件作用域声明可变数组长度（文件作用域是file scope）
//因此只能用一个确定的宏定义来初始化数组的长度
void load(){
    FILE*file=fopen("inventory.txt","r");
    if(file==NULL) {
        printf("The inventory is empty!\n");
        return;
    }
    //只能用数组，不能用指针的原因：调用结构体里面成员的方式有两种：
    //一种是使用定义的成员来点取调用
    //一种是定义指针来用箭头调用
    else {
        while (fscanf(file, "%s %d", item[count].name, &item[count].quantity) == 2) {
            count++;
        }
    }
    //scanf读取完的数据都通过变量的地址储存在变量了，而这个原理跟scanf是完全相同的
    //只是前者从文档流中获取数据，而后者从键盘流中获取数据
    fclose(file);
}

void display(){
    printf("Now the inventory has goods as follows:\n");
    for(int i=0;i<count;i++){
        printf("%s %d\n",item[i].name,item[i].quantity);
    }
}

void save(){
    FILE*file=fopen("inventory.txt","w");
    for(int i=0;i<count;i++){
        fprintf(file,"%s %d",item[i].name,item[i].quantity);
    }
    fclose(file);
}

void import(){
    FILE*file=fopen("inventory.txt","a");
    if(count==MAX_NUMBER){
        printf("The inventory is already full!");
        return;
    }
    count++;
    printf("请输入你想添加的货物：");
    scanf("%s",item[count].name);
    printf("请输入你想添加的数量：");
    scanf_s("%d",&item[count].quantity);
    for(int i=0;i<MAX_NUMBER;i++){
        if(strcmp(item[i].name,item[count].name)==0){
            item[i].quantity=item[i].quantity+item[count].quantity;
            count--;
        }
    }
    fprintf(file,"%s %d\n",item[count].name,item[count].quantity);
    fclose(file);
    save();
}
void export(){
    if(count==0){
        printf("The inventory is already empty!");
        return;
    }
    char *title=NULL;
    int value=0,i=0;
    title=(char*)malloc(sizeof(char)*MAX_SIZE);
    printf("请输入你想移除的货物：");
    scanf("%s",title);
    printf("请输入你想移除的数量：");
    scanf_s("%d",&value);
    while(item[i].name!=NULL) {
        if (strcmp(item[i].name, title) == 0) {
            item[i].quantity = item[i].quantity - value;
            return;
        }
    }
    free(title);
    save();
}

int main(){
    int choice=0;
    printf("请输入你想进行的操作：");
    scanf_s("%d",&choice);
    load();
    display();
    switch(choice){
        case 1:display();break;
        case 2:import();break;
        case 3:export();break;
        case 4:save();break;
    }
}
