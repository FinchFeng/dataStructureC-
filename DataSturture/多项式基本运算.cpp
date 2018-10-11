//
//  3.cpp
//  DataSturture
//
//  Created by 冯奕琦 on 2018/10/11.
//  Copyright © 2018年 冯奕琦. All rights reserved.
//

//实现多项式的输入、输出、加法、求导、求值。
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <math.h>


    //MARK: - 线性表

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
        //  if (at >= 0 && at <= last){
    return data[at];
        //  }else{
        //    std::cout << "获取顺序表超出范围" << std::endl;
        //    return T();
        //  }
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
        //  std::cout << last;
    for (int i = 0; i <= last; i++) {
        std::cout << " " << data[i] ;
    }
}


    //MARK: - 线性表的多项式应用

class Polynomial:public SeqList<int>{
public:
        //新的构造函数
    Polynomial(int size):SeqList(size){
    };
        //新的输入
    void input(){
            //将全部的数组元素设置为0
        for (int i = 0; i < maxSize; i++) {
            data[i] = 0;
        }
        int number,maxExp = 0;
        std::cin >> number ;
        for (int i = 1; i <= number; i++) {
            int exp,coaf;
                //输入一项
            std::cin >> coaf >> exp;
            if (exp >= 0) {
                data[exp] = coaf;
            }
                //判断是否最大
            if (maxExp < exp){
                maxExp = exp;
            }
        }
            //改变last
        last = maxExp;
    };
    
        //求导
    void derivative(){
        
        std::cout << "A'(x)=" ;
        
        for (int i = 1; i <= last; i++) {
            int coaf = getData(i);
            int exp = i-1 ;
            coaf = coaf*i;
            
            if (coaf != 0) {//有此项系数
                    //输出
                if (exp == 0) {
                    std::cout << coaf;
                }
                if (exp == 1) {
                    if (coaf == 1) {
                        std::cout << "x" ;
                    }else{
                        std::cout << coaf << "x" ;
                    }
                }
                if (exp > 1) {
                    if (coaf == 1) {
                        std::cout << "+" << "x^" << exp ;
                    }else{
                        std::cout << "+" << coaf << "x^" << exp ;
                    }
                }
            }
        }
        
        std::cout << std::endl;
    };
    
    void Evaluation(int value){
        
        std::cout << "A(" << value << ")=" ;
        
        int sum = getData(0) ;//常数项
        
        for (int i = 1; i <= last; i++) {
            int coaf = getData(i);
            sum += coaf*pow(value,i);
        }
        
        std::cout << sum ;
        
        std::cout << std::endl;
        
    };
    
};

    //MARK: - 主程序
int main(int argc, const char * argv[]) {
    
        //输入
    Polynomial newPolynomial(100),newPolynomial2(100);
    int value = 0;
    
    newPolynomial.input();
    newPolynomial2.input();
    std::cin >> value;
    
        //相加
    int maxLast = newPolynomial.last > newPolynomial2.last ? newPolynomial.last : newPolynomial2.last ;
    std::cout << "A(x)+B(x)=" ;
    for (int i = 0; i <= maxLast; i++) {
            //计算多项式系数
        int coaf = 0;
        coaf = newPolynomial.getData(i) + newPolynomial2.getData(i);
        
        if (coaf != 0) {//有此项系数
                //输出
            if (i == 0) {
                std::cout << coaf;
            }
            if (i == 1) {
                if (coaf == 1) {
                    std::cout << "x" ;
                }else{
                    std::cout << coaf << "x" ;
                }
            }
            if (i > 1) {
                if (coaf == 1) {
                    std::cout << "+" << "x^" << i ;
                }else{
                    std::cout << "+" << coaf << "x^" << i ;
                }
            }
        }
    }
    std::cout << std::endl;
    
    newPolynomial.derivative();
    newPolynomial.Evaluation(value);
    
    return 0;
}

