//
//  链表及其应用.cpp
//  DataSturture
//
//  Created by 冯奕琦 on 2018/10/11.
//  Copyright © 2018年 冯奕琦. All rights reserved.
//

    //2
    //实习目的：熟练掌握链表的建立和基本操作。
    //问题描述：设计一个链表并实现对其进行基本操作。
    //基本要求：建立一个链表：
    //（1）输入数据；
    //（2）实现数据的插入、删除、搜索、输出等基本操作；
    //（3）实现集合的并、交和两个有序链表的合并。
    //测试数据：
    //0  //线性表输入结束标志
    //1 3 5 7 9 0  //线性表A的数据
    //2 10 //表示在第2个位置插入10
    //10 //表示删除值=10的数据元素
    //9 //查找元素9
    //22// 查找元素22
    //0  //线性表输入结束标志
    //1 2 3 4 5 6 0

#include <iostream>
#include <stdio.h>
#include<algorithm>
using namespace std;
class List; //前视定义,否则友元无法定义
class LinkNode
{
    friend  List; //链表结点类的定义
private:
    LinkNode *link;
    int data;
public:
    LinkNode (LinkNode *ptr = NULL)    {link=ptr;}
    LinkNode(const int & item, LinkNode *ptr = NULL){  data=item;link=ptr;}
    ~LinkNode(){};
};
class LinkList;
class Lists; //前视定义,否则友元无法定义
class LinkNodes
{
    friend LinkList;
    friend  Lists;//链表结点类的定义
public:
    LinkNodes *link;
    int data;
    LinkNodes (LinkNodes *ptr = NULL)    {link=ptr;}
    LinkNodes(const int & item, LinkNodes *ptr = NULL){  data=item;link=ptr;}
};

class Lists
{//单链表类的定义
public:
    LinkNodes *first; //指向首结点的指针
    Lists () { first = new LinkNodes();}   // 带头结点
    ~Lists (){ }         //析构函数
    void input(int  endTag);
    void output();
};

class LinkList:public Lists{
public:
    void insert(int at,int value);
    int locate(int value);
    void remove(int value);
    int length();
    void bubble();
};

    //输入函数
void Lists::input(int endTag){
        //定义last指针和current指针
    LinkNodes *last;
        //连接最后一个节点
    last = first;
        //获取值并且加入数组
    int value = 32498;
    while (value != endTag) {
        cin >> value;
        last->link = new LinkNodes(value);
        last = last->link;
    };
};

    //输出函数
void Lists::output(){
    LinkNodes *current;
    current = first->link;
    while (current->link != NULL) {
        cout << " " << current->data ;
        current = current->link;
    }
    cout << endl;
}

void LinkList::insert(int at, int value){
        //找到要插入的节点
    LinkNodes *current;
    current = first ;
    for (int i = 1; i < at; i++) {
        if (current->link == NULL) { break ;};
        current = current->link;
    }
        //插入值
    LinkNodes *newNode = new LinkNodes(value);
    newNode->link = current->link;
    current->link = newNode;
}

int LinkList::locate(int value){
    LinkNodes *current;
    current = first->link;
    int index = 1;
    while (current->link != NULL) {
        if (current->data == value) {
            return index;
        }
        index++;
        current = current->link;
    }
    return -999;
};

void LinkList::remove(int value){
    int removeIndex = 0;
    removeIndex = locate(value);
        //  cout << removeIndex << endl;
    if (removeIndex != -999){
            //找到要删除的节点
        LinkNodes *current;
        current = first ;
        for (int i = 1; i < removeIndex; i++) {
            if (current->link == NULL) { return ;};
            current = current->link;
        }
            //开始删除
        LinkNodes *deleteNode;
        deleteNode = current->link;
        current->link = deleteNode->link;
        delete deleteNode;
    }
}

    //MARK: - 链表的应用

int LinkList::length(){
    LinkNodes *current;
    current = first->link;
    int acout = 0;
    while (current->link != NULL) {
            //检查每一个元素
        current = current->link;
        acout++;
    }
    return acout;
};

void unionList(LinkList &list1,LinkList &list2){
    
    LinkNodes *current;
    current = list2.first->link;
    while (current->link != NULL) {
            //检查每一个元素
        int index = 0;
        index = list1.locate(current->data);
        if (index == -999){//如果没有出现
            int length = list1.length()+1;
            list1.insert(length, current->data);
        }
        current = current->link;
    }
    
    cout << "A union B is";
    list1.output();
    
};

void cross(LinkList &list1,LinkList &list2){
    cout << "A cross B is";
    LinkNodes *current;
    current = list2.first->link;
    while (current->link != NULL) {
            //检查每一个元素
        int index = 0;
        index = list1.locate(current->data);
        if (index != -999){//如果有出现
            cout << " " << current->data;
        }
        current = current->link;
    }
    cout << endl;
};

void LinkList::bubble(){
    int i = 0,temp;
    int data[length()+1];
        //创建数组
    LinkNodes *current;
    current = first->link;
    while (current->link != NULL) {
        data[i] = current->data;
            //    cout << data[i];
        i++;
        current = current->link;
    }
    for(int p=1;p<length();p++)
    {
        for(i=0;i<length()-p;i++)
            if(data[i]>data[i+1])
            {
                temp=data[i];
                data[i]=data[i+1];
                data[i+1]=temp;
            }
    }
    
    std::cout << "A union B in sequence is";
    for(int i=0;i<length();i++)std::cout<<" "<<data[i];
    std::cout<<std::endl;
}

    //MARK: - 主程序
int main(int argc, const char * argv[]) {
    LinkList newList,newList2;
    
    int endTag;
    cin >> endTag;
    newList.input(endTag);
    
    int at,value;
    cin >> at >> value;
    
    int removeValue;
    cin >> removeValue;
    
    int findValue1 = -1,findValue2 = -1;
    cin >> findValue1 >> findValue2;
    int findIndex1 = -1,findIndex2 = -1;
    
    cin >> endTag;
    newList2.input(endTag);
    
        //action
    
    cout << "A is created as:";
    newList.output();
        //  cout << endl;
    
    newList.insert(at, value);
    cout << "After inserted A is";
    newList.output();
        //  cout << endl;
    
    newList.remove(removeValue);
    cout << "After deleted A is";
    newList.output();
        //  cout << endl;
    
    findIndex1 = newList.locate(findValue1);
    findIndex2 = newList.locate(findValue2);
    if (findIndex1 != -999) {
        cout << findValue1 << " is located at index of " << findIndex1 << endl;
    }else{
        cout << findValue1 << " is not found" << endl;
    }
    if (findIndex2 != -999) {
        cout << findValue2 << " is located at index of " << findIndex2 << endl;
    } else {
        cout << findValue2 << " is not found " << endl;
    }
    
    cout << "B is created as:";
    newList2.output();
    
        //  cout << newList2.length() << " " << newList.length();
    cross(newList, newList2);
    unionList(newList, newList2);
    newList.bubble();
    
    return 0;
}

