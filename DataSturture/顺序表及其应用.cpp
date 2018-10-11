//
//  顺序表及其应用.cpp
//  DataSturture
//
//  Created by 冯奕琦 on 2018/10/11.
//  Copyright © 2018年 冯奕琦. All rights reserved.
//
//
//实习目的：帮助学生熟练掌握顺序表的建立及基本操作
//问题描述：设计一个顺序表并实现对其进行基本操作。
//基本要求：建立一个顺序表：
//（1）输入数据；
//（2）实现数据的插入、删除、搜索、输出等基本操作；
//（3）实现集合的并、交和两个有序顺序表的合并。
//测试数据：
//5  //线性表A的长度
//1 3 5 7 9  //线性表A的数据
//2 10 //表示在第2个位置插入10
//10 //表示删除值=10的数据元素
//9 //查找元素9
//11/ 查找元素22
//6 //线性表B的长度
//1 2 3 4 5 6

#include <iostream>
#include <stdlib.h>

const int defaultSize = 100;
template <class T>
class SeqList {
    
protected:
    T *data;
    int maxSize;
    void reSize(int newSize);
    
public:
    int last;//最后一个数的位置
    SeqList(int sz = defaultSize);
    int FindValue(T value) const;
    bool insert(int at,T value);
    T remove(int at);
    T getData(int at);
    bool setData(int at,T value);
    bool findDelete(T value);
    
    bool isEmpty(){ if (last == -1) {return true;} else {return false;} ;} ;
    bool isFull(){ if (last == maxSize-1) {return true;} else {return false;} ;};
    
    void input();
    void outPut();
    void bubble();
};


    //MARK: - 线性表
template<class T>
SeqList<T>::SeqList(int sz){//构造新顺序表
    if (sz > 0) {
        last = -1;
        maxSize = sz;
        data = new T[maxSize];
    }
}

    //扩大数组
template<class T>
void SeqList<T>::reSize(int newSize){
        //检查合理性
    if (newSize < maxSize) { return; }
        //创建新数组
    T *newArray = new T[newSize];
    int n = last+1;
        //创建数组
    T *oldPointer = data;
    T *newPointer = newArray;
        //赋值
    while (n--) {
        *newPointer++ = *oldPointer++;
    }
    delete []data;
    data = newPointer;
    maxSize = newSize;
}

    //查找数组
template<class T>
int SeqList<T>::FindValue(T value)const{
    for (int i = 0; i <= last; i++ ) {
        if (data[i] == value){
            return i;
        }
    }
    
    return -1;
}

    //插入函数

template<class T>
bool SeqList<T>::insert(int at,T value){
    if (last == maxSize-1||at<0||at>last+1) return false;//检查输入
        //  if (at == last){last++;data[last] = value; return true;};
    for (int j = last; j>=at ; j--) {
            //    std::cout << last << std::endl;
        data[j+1] = data[j];
    }
    data[at] = value;
    last += 1;
    return true;
}


template <class T>
bool SeqList<T>::findDelete(T value){
    int indexOfValue = -1 ;
    indexOfValue = FindValue(value);
    if (indexOfValue != -1) {
        remove(indexOfValue);
        return true;
    }else{
        return false;
    }
    
}

    //删除函数
template<class T>
T SeqList<T>::remove(int at){
    if (at >= 0 && at <= last){
        T removeData;
        removeData = data[at];
            //删除数据
        for (int i = at; i < last; i++) {
            data[i] = data[i+1];
        }
        last--;
        return removeData;
    }else{
            //    std::cout << "删除顺序表超出范围" << std::endl;
        return T();
    }
}

    //获取函数
template<class T>
T SeqList<T>::getData(int at){
    if (at >= 0 && at <= last){
        return data[at];
    }else{
        std::cout << "获取顺序表超出范围" << std::endl;
        return T();
    }
}

    //更改函数
template<class T>
bool SeqList<T>::setData(int at,T value){
    if (at >= 0 && at <= last){
        data[at] = value;
        return true;
    }else{
        std::cout << "更改顺序表超出范围" << std::endl;
        return false;
    }
}

    //输入函数
template<class T>
void SeqList<T>::input(){
        //  std::cout << "输入表中最后一个元素的位置：";
    while (1) {
        int cout = -1;
        std::cin >> cout;
        last = cout - 1 ;
        if (last <= maxSize-1) break;
            //    std::cout << "超出最大范围";
    }
    for (int i = 0; i <= last; i++) {
        std::cin >> data[i];
    }
}

template<class T>
void SeqList<T>::outPut(){
    
    for (int i = 0; i <= last; i++) {
        std::cout << " " << data[i] ;
    }
}

    //MARK: 线性表的应用

void unionArrays(SeqList<int> &list1,SeqList<int> &list2){
    int list1Length = list1.last,list2Length = list2.last;
    
    for (int i = list2Length; i >= 0 ; i--) {
        int x = list2.getData(i);
        if (list1.FindValue(x) == -1){//没有找到一样的
            list1.insert(list1Length+1, x);
        };
        
    }
        //outPut
    std::cout << "A union B is";
    for (int i = 0; i <= list1.last; i++) {
        std::cout << " " << list1.getData(i) ;
    }
    std::cout << std::endl;
}

void crossArrays(SeqList<int> &list1,SeqList<int> &list2){
    int list2Length = list2.last;
    std::cout << "A cross B is";
    for (int i = 0; i <= list2Length ; i++) {
        int x = list2.getData(i);
        int index = -1;
        index = list1.FindValue(x);
        if (index != -1) {
            std::cout << " " << x ;
        }
    }
    std::cout << std::endl;
}

template <class T>
void SeqList<T>::bubble()
{
    int i,temp;
    for(int p=1;p<last+1;p++)
    {
        for(i=0;i<last+1-p;i++)
            if(data[i]>data[i+1])
            {
                temp=data[i];
                data[i]=data[i+1];
                data[i+1]=temp;
            }
    }
    
    
    std::cout << "A union B in sequence is";
    for(int i=0;i<=last;i++)std::cout<<" "<<data[i];
    std::cout<<std::endl;
}
int main(int argc, const char * argv[]) {
        // insert code here...
    SeqList<int> newArray1(200);
    SeqList<int> newArray2(200);
    newArray1.input();
    int insertAt,insertValue,deletValue,findValue1,findValue2;
    std::cin >> insertAt >> insertValue >> deletValue >> findValue1 >> findValue2;
    newArray2.input();
        //start to outPut
    std::cout << "A is created as:";
    newArray1.outPut();
    std::cout << std::endl;
        //insert
    newArray1.insert(insertAt-1,insertValue);
    std::cout << "After inserted A is" ;
    newArray1.outPut();
    std::cout << std::endl;
        //findandDelete
    newArray1.findDelete(deletValue);
        //output
    std::cout << "After deleted A is";
    newArray1.outPut();
    std::cout << std::endl;
        //findValue
    int findIndex1 = -1,findIndex2 = -1;
    findIndex1 = newArray1.FindValue(findValue1);
    if (findIndex1 == -1) {
        std::cout << findValue1 << " is not found" <<  std::endl;
    }else{
        std::cout << findValue1 << " is located at index of " << findIndex1+1 << std::endl;
    }
    findIndex2 = newArray1.FindValue(findValue2);
    if (findIndex2 == -1) {
        std::cout << findValue2 << " is not found" <<  std::endl;
    }else{
        std::cout << findValue2 << " is located at index of " << findIndex2+1 << std::endl;
    }
    std::cout << "B is created as:";
    newArray2.outPut();
    std::cout << std::endl;
    crossArrays(newArray1, newArray2);
    unionArrays(newArray1, newArray2);
    newArray1.bubble();
    return 0;
}
