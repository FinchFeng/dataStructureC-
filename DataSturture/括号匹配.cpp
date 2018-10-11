//
//  括号匹配.cpp
//  DataSturture
//
//  Created by 冯奕琦 on 2018/10/11.
//  Copyright © 2018年 冯奕琦. All rights reserved.
//

//用栈实现：输入一行符号,以#结束，判断其中的括号是否匹配。括号包括：
//{}  []  ()  <>

#include <iostream>
#include <stdlib.h>
const int maxSize = 50;
template <class T>

class Stack{//基类
public:
    Stack(){};
    virtual bool Push(const T x) = 0;//进栈
    virtual bool Pop(T& x) = 0;//出栈
    virtual bool getTop(T& x) = 0;//读取栈顶元素
    virtual bool isEmpty() const = 0 ;//判断是否为空
    virtual bool isFull() const = 0 ;//判断是否满
    virtual int getSize() const = 0 ;//获取元素个数
};
const int stackIncreament = 20; //溢出之前的增量
template <class T>
class SeqStack:public Stack<T>{
private:
    T *element; //数组指针
    int top; //栈顶指针
    int maxSize;//最大元素个数
    void overflowProcess();//溢出处理
public:
    SeqStack(int size);
    bool Push(const T x) ;//进栈
    bool Pop(T& x) ;//出栈
    bool getTop(T& x); //读取栈顶元素
    bool isEmpty() const { return top == -1 ; };//判断是否为空
    bool isFull() const { return top == maxSize-1 ; } ;//判断是否满
    int getSize() const { return top+1; } ;//获取元素个数
    void makeEmpty() {top = -1;};
};

template <class T>
SeqStack<T>::SeqStack(int size){
        //构造函数
    top = -1;
    maxSize = size;
    element = new T[maxSize];
};

template <class T>//栈溢出操作
void SeqStack<T>::overflowProcess(){
    T *newStack = new T[maxSize+stackIncreament] ;
    for (int i = 0; i<=top; i++) {
        newStack[i] = element[i];
    }
    maxSize = maxSize+stackIncreament;
    delete []element;
    element = newStack;
};

template <class T>
bool SeqStack<T>::Push(const T x){
    if (isFull()) {
        return false;
    }else{
        top++;
        element[top] = x;
            //    std::cout << x  << " " << top << std::endl;
        return true;
    }
};

template <class T>
bool SeqStack<T>::Pop(T &x){
    if (isEmpty()) {
        return false;
    }else{
        x = element[top];
        top--;
            //    std::cout << x  << " " << top << std::endl;
        return true;
    }
}

template <class T>
bool SeqStack<T>::getTop(T &x){
    if (isEmpty()) {
        return false;
    }else{
            //    int n = top;
            //    n--;
        x = element[top];
        return true;
    }
}

    // 栈的应用
bool isABracket(char c){
    if ((c == '(')||(c == '<')||(c == '{')||(c == '[')||(c == ')')||(c == ']')||(c == '}')||(c == '>')){
        return true;
    };
    return false;
}

bool isLeftSide(char c){
    if ((c == '(')||(c == '<')||(c == '{')||(c == '[')){
        return true;
    };
    return false;
}

bool isRightSide(char c){
    if ((c == ')')||(c == ']')||(c == '}')||(c == '>')){
        return true;
    };
    return false;
}

bool match(char left,char right){
    switch (left) {
        case '(':
            if (right == ')') {
                return true;
            }
            break;
        case '{':
            if (right == '}') {
                return true;
            }
            break;
        case '[':
            if (right == ']') {
                return true;
            }
            break;
        case '<':
            if (right == '>') {
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

char change(char left){
    switch (left) {
        case '(':
            return ')';
            break;
        case '{':
            return '}';
            break;
        case '[':
            return ']';
            break;
        case '<':
            return '>';
            break;
        default:
            break;
    }
    return ' ';
}

using namespace std;

    //MARK: - 主程序
int main(int argc, const char * argv[]) {
    
    SeqStack<char> stack(100);
    
        //循环输入
    int number = 0;
    char inPutChar = '~';
        //无左边括号
        //  int wrongCharNumber = -1 ;
        //  char wrongChar = ' ';
    while (inPutChar != '#') {
            //读入
        cin >> inPutChar ;
        number++;
        if (isABracket(inPutChar)) {
            if (isLeftSide(inPutChar)) {
                stack.Push(inPutChar);
            }
            if (isRightSide(inPutChar)) {
                    //检查是否配对
                char topTerm = ' ';
                if ((stack.getTop(topTerm))&&(match(topTerm, inPutChar))) {
                        //          cout << topTerm <<" match ? " << inPutChar << endl;
                        //          if (match(topTerm, inPutChar)) {
                    char popItem = ' ';
                    stack.Pop(popItem);
                        //          }else{
                        //无元素 或者不匹配 直接报错
                        //            cout << "The " << number << " character '" << inPutChar << "' is wrong."<< endl;
                        //            return 0;
                        //          }
                }else{
                        //无元素 或者不匹配 直接报错
                    cout << "The " << number << " character '" << inPutChar << "' is wrong."<< endl;
                    return 0;
                }
                
            }
        }
    }
    
        //进行栈检查
    if (stack.isEmpty()) {
        cout << "right." << endl;
    }else{
        cout << "loss of right character " ;
            //    char lossChar
        while (!stack.isEmpty()) {
            char popChar = ' ';
            stack.Pop(popChar);
            cout << change(popChar) ;
        }
        cout << ".";
        cout << endl;
    }
    
    return 0;
}

