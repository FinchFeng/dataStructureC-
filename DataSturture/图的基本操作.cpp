//
//  图的基本操作.cpp
//  DataSturture
//
//  Created by 冯奕琦 on 2018/10/11.
//  Copyright © 2018年 冯奕琦. All rights reserved.
//

//建立图(邻接矩阵、邻近表任选其一)的存储结构、实现图的深度优先遍历和广度优先遍历。

    //MARK:图的操作
#include <iostream>
#include <string>
using namespace std;

class Queue {
public:
    int array[100];
    int rear = 0;
    Queue(){
        for (int i = 0; i<100; i++) {
            array[i] = 0;
        }
    }
    
    bool isEmpty(){
        return rear==0;
    }
    
    int outOfQueue(){
        if (!isEmpty()) {
            rear--;
            int answer = array[0];
            for (int i=0; i<=rear; i++) {
                array[i] = array[i+1];
            }
            return answer;
        }
        abort();
    }
    
    void inQueue(int value){
        array[rear] = value;
        rear++;
    }
    
};

class Graphmtx{
public:
    int pointCount,edgeArray[100][100];
    char pointName[100];
    
    Graphmtx(int numberOfPoint){
        pointCount = numberOfPoint;
        for (int i = 0; i<numberOfPoint; i++) {
            for (int j = 0; j<numberOfPoint; j++) {
                edgeArray[i][j] = 0;
            }
        }
            //    memset(edgeArray,0, sizeof(edgeArray));
    }
    
        //把char转化为int
    int getPointPosition(char name){
        for (int i = 0; i<pointCount; i++) {
            if (name == pointName[i]) {
                return i;
            }
        }
        return -1;
    }
    
    void creatAEdge(int point1,int point2,int weight){
        if (point1<pointCount&&point2<pointCount) {
            edgeArray[point1][point2] = weight;
            edgeArray[point2][point1] = weight;
        }
    }
    
    void outPut(){
        cout << "edges are:" <<endl;
        for (int i = 0; i<pointCount; i++) {
            for (int j = i+1; j<pointCount; j++) {
                if (edgeArray[i][j] != 0) {
                    cout << pointName[i] << "-" << pointName[j] << ":" << edgeArray[i][j] <<endl ;
                }
            }
        }
    }
    void inputPointName(){
        for (int i=0; i<pointCount ; i++) {
            cin >> pointName[i];
        }
    }
    
        //深度搜索
    
    int getNextPointOf(int point,int after){
        for (int i = after; i<pointCount; i++) {
            if (edgeArray[point][i] != 0) {
                return i;
            }
        }
        return -1;
    }
    
    void startDFS(){
        int startPoint = 0;
        bool boolArray[pointCount];
        for (int i = 0; i < pointCount ; i++) {
            boolArray[i] = false;
        }
            //    memset(boolArray, false, sizeof(boolArray));
        cout << "DFS:" ;
        DFS(startPoint, boolArray);
        cout << endl;
    }
    
    void DFS(int point,bool idArray[]){
            //访问这个节点
            //    bool newIdArray = idArray;
        idArray[point] = true;
        cout << pointName[point] << " ";
            //获取下一个节点
        int nextPoint = -1;
        int tryingPoint = 0;
        nextPoint = getNextPointOf(point, tryingPoint);
        while (nextPoint != -1) {
            if (!idArray[nextPoint]) { DFS(nextPoint,idArray); }
            nextPoint = getNextPointOf(point, nextPoint+1);
        }
        
    }
    
    void startBFS(){
        int startPoint = 0;
        bool idArray[pointCount];
            //    memset(idArray, false, sizeof(idArray));
        for (int i = 0; i<pointCount; i++) {
            idArray[i] = false;
        }
            //创建队列
        Queue pointQueue;
            //访问头节点
        idArray[startPoint] = true;
        cout << "BFS:" << pointName[startPoint] << " ";
        pointQueue.inQueue(startPoint);
        while (!pointQueue.isEmpty()) {
                //推出一个节点
            int rearPoint = pointQueue.outOfQueue();
            int nextPoint = getNextPointOf(rearPoint, 0);
            while (nextPoint != -1) {
                if (!idArray[nextPoint]) {
                        //访问这个节点并且加入队列
                    idArray[nextPoint] = true;
                    cout << pointName[nextPoint] << " ";
                    pointQueue.inQueue(nextPoint);
                }
                nextPoint = getNextPointOf(rearPoint, nextPoint+1);
            }
                //      cout << " rearPoint " << pointName[rearPoint]  << endl;
        }
        cout << endl;
    }
    
};



    //  MARK: - 主程序
int main(int argc, const char * argv[]) {
    int pointNumber;
    cin >> pointNumber;
    Graphmtx newGrap(pointNumber);
    newGrap.inputPointName();
    int edgeCount;
    cin >> edgeCount;
    for (int i = 0; i<edgeCount; i++) {
        int point1,point2,weight;
        cin >> point1 >> point2 >> weight;
        newGrap.creatAEdge(point1, point2, weight);
    }
    newGrap.startDFS();
    newGrap.startBFS();
    newGrap.outPut();
    return 0;
}


