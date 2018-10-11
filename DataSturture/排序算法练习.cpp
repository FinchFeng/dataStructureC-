//
//  排序算法练习.cpp
//  DataSturture
//
//  Created by 冯奕琦 on 2018/10/11.
//  Copyright © 2018年 冯奕琦. All rights reserved.
//

//设有顺序放置的n个桶，每个桶中装有一粒砾石，每粒砾石的颜色是红,白,蓝之一。要求重新安排这些砾石，使得所有红色砾石在前，所有白色砾石居中，所有蓝色砾石居后，重新安排时对每粒砾石的颜色只能看一次，并且只允许交换操作来调整砾石的位置。
//提示：
//
//
//利用快速排序思想解决。由于要求“对每粒砾石的颜色只能看一次”，设3个指针i，j和k，若将j看作工作指针，将r[1..j-1]作为红色，r[j..k-1]为白色，r[k..n]为兰色。从j=1开始查看，若r[j]为白色，则j=j+1；若r[j]为红色，则交换r[j]与r[i]，且j=j+1，i=i+1；若r[j]为兰色，则交换r[j]与r[k];k=k-1。算法进行到j>k为止。
//
//为方便处理，将三种砾石的颜色用整数1、2和3表示。

/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include "assert.h"
#include <iostream>
using namespace std;

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */


bool switchValue(int &n1,int &n2){
    if (n1 != n2){
        int temp = n1;
        n1 = n2;
        n2 = temp;
        return true;
    }else{
        return false;
    }
}

void Sort(int *a, int n){
    int i = 0,j = 0 ,k = n-1;
    while (j<=k) {
        int value = a[j];
        if (value == 1) {
            switchValue(a[i], a[j]);
            if (i != j) {
                cout << i << "<--->" << j << endl;
            }
            j++;
            i++;
        }
        if (value == 2) {
            j++;
        }
        if (value == 3) {
            switchValue(a[j], a[k]);
            if (j != k){
                cout << j << "<--->" << k << endl;
            }
            k--;
        }
    }
    for (int i = 0; i<n; i++) {
        cout << a[i] ;
    }
    cout << endl;
};

/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

int main() {
    int n;
    cin >> n;
    int * a= new int[n];
    for (int i=0;i<n;i++)
        cin>>a[i];
    Sort(a,n);
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */
