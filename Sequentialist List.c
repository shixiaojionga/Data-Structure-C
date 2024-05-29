#include <stdio.h>
#include <stdlib.h>

#define Eletype int

typedef struct{
    Eletype *elements;
                                                                                                                         //size_t是无符号整数类型
    size_t size;                                                                                                         //顺序表的长度
    size_t capacity;                                                                                                     //顺序表的容量
}SequentialList;

void SequentialListInit(SequentialList *list, int capacity){                                                             //创建顺序表
    list->elements = (Eletype *)malloc(sizeof(Eletype)*capacity);                                                        //申请空间
    list->size = 0;                                                                                                      //顺序表的初始长度为0
    list->capacity = capacity;                                                                                           //顺序表的容量直接等于指定参数
}

void SequentialListDestory(SequentialList *list){                                                                        //销毁顺序表
    if(list->elements){                                                                                                  //如果顺序表中有数据则执行
        free(list->elements);                                                                                            //释放顺序表中元素的空间
        list->elements = NULL;                                                                                           //将顺序表中的数据赋值为空
    }
}
size_t SequentialListSize(const SequentialList *list){                                                                   //返回顺序表的大小
    return list->size;
}

void SequentialListInsert(SequentialList *list, int index, int element){                                                 //在顺序表中插入元素
    if(index < 0 || index > list->size){                                                                                 //先确定索引是否合法
        printf("Invalid index\n");
        return;
    }
    if(list->size == list->capacity){                                                                                    //如果顺序表长度等于容量则将容量翻倍
        int *Newelements = (Eletype *)realloc(list->elements, sizeof(Eletype) * list->capacity * 2);
        if(Newelements == NULL){
            printf("Failed to allocate memory\n");
            return;
        }
        list->elements = Newelements;
        list->capacity *= 2;
    }
    for (size_t i = list->size;i > index; i--){                                                                          //将索引index后的每一个数据都向后移动一位
        list->elements[i] = list->elements[i - 1];
    }
    list->elements[index] = element;                                                                                     //将索引index的值替换为想要添加的值
    list->size ++;
}

void SequentialListDelete(SequentialList *list, int index){
    if(index < 0 || index >= list->size){                                                                                //先确定索引是否合法
        printf("Invalid index\n");
        return;
    }
    for(size_t i = index; i < list->size; i++){                                                                          //将从指定索引开始向后的每一个数据都向前移动一位
        list->elements[i] = list->elements[i+1];
    }
    list->size --;
}

int SequentialListFind(const SequentialList *list, Eletype element){                                                     //查找顺序表中某元素对应的索引
    for(size_t i = 0; i < list->size; i++){
        if(list->elements[i] == element){
            return i;
        }
    }
    return -1;
}

Eletype SequentialListIndex(const SequentialList *list, int index){                                                     //查找顺序表中某索引对应的元素
    if(index < 0 || index >= list->size){
        printf("Invalid index\n");
        return -1;
    }
    return list->elements[index];
}
void SequentialListSet(SequentialList *list, int index, Eletype element){
    if(index < 0 || index >= list->size){                                                                               //先确定索引是否合法
        printf("Invalid index\n");
        return;
    }
    list->elements[index] = element;
}

int main(){
    SequentialList list;
    SequentialListInit(&list, 1);
    for(int i = 0; i < 10; i++){
        SequentialListInsert(&list, i, i*10);
    }
    printf("Size:%d\n",SequentialListSize(&list));
    return 0;
}
