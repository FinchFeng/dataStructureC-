//
//  稀疏矩阵的压缩存储.cpp
//  DataSturture
//
//  Created by 冯奕琦 on 2018/10/11.
//  Copyright © 2018年 冯奕琦. All rights reserved.
//

//稀疏矩阵的压缩存储：
//实现稀疏矩阵压缩存储，并实现矩阵转置和求和。
//输入矩阵时，首先需要输入非零元素的个数，然后分别输入矩阵的 行号，列号和值。
//输完2个矩阵后，自动进行计算第一个矩阵的转置以及两个矩阵的和。
//例如：输入如下：
//100 90 5 //矩阵的行数为100，列数为90，共5个非零元素。
//1 10 100 //a(1,10)=100
//50 60 200//a(50,60)=200
//50 80 100//a(50,80)=100
//60 60 200//a(60,60)=200
//99 89 10//a(99,89)=10
//100 90 2 //矩阵b的行数为100，列数为90，共2个非零元素。
//1 1 10 //b(1,1)=10
//50 60 -200//b(50,60)=-200


#include <iostream>

using namespace std;

struct Term{
    int row,col,value;
};

class Matrix {
public:
    int Mrow,Mcols,Mitems;
    const int maxItems = 100;
    Term *data ;
        //public:
        //构造函数
    Matrix(){
        data = new Term[maxItems];
    };
        //input
    void input(int row,int cols,int items){
            //赋值row cols item
        Mrow = row;
        Mcols = cols;
        Mitems = items;
        for (int i = 0;i < items;i++){
            int itemRow,itemCol,itemValue;
            cin >> itemRow >> itemCol >> itemValue;
            data[i].col = itemCol;
            data[i].row = itemRow;
            data[i].value = itemValue;
                //      cout << i << endl;
        }
            //    outPut();
        
    };
    
    void rotation(){
        int rowSize[Mcols+1];
        int rowStart[Mcols+1];
        for (int i = 0; i <= Mcols; i++) {
            rowSize[i] = 0;
            rowStart[i] = 0;
        }
        Matrix b;
        b.Mcols = Mrow;
        b.Mrow = Mcols;
        b.Mitems = Mitems;
        if (Mitems > 0) {
            for (int i = 0; i < Mitems; i++) {
                rowSize[data[i].col]++;
                
            }
                //      for (int i = 0; i <= Mcols; i++) {
                //        cout << "rowSize " <<  rowSize[i] << endl;
                //        cout << "rowStart " << rowStart[i] << endl;
                //      }
            for (int i = 1; i <= Mcols; i++) {
                rowStart[i] = rowSize[i-1]+rowStart[i-1];
            }
                //      cout << "Second" << endl;
                //
                //      for (int i = 0; i <= Mcols; i++) {
                //        cout << "rowSize " <<  rowSize[i] << endl;
                //        cout << "rowStart " << rowStart[i] << endl;
                //      }
            for (int i = 0; i < Mitems; i++) {
                int index = rowStart[data[i].col];
                b.data[index].col = data[i].row;
                b.data[index].row = data[i].col;
                b.data[index].value = data[i].value;
                rowStart[data[i].col]++;
            }
        }
        b.outPut();
    };
    
    void add(Matrix b){
        int items = Mitems;
        for (int i = 0; i < b.Mitems; i++) {
            bool haveSameItem = false;
            for (int j = 0; j < items; j++) {
                if ((b.data[i].row==data[j].row)&&(b.data[i].col==data[j].col)) {
                    data[j].value += b.data[i].value;
                        //          outPut();
                        //          cout << endl;
                    haveSameItem = true;
                    break;
                }
            }
                //添加新项
            if (!haveSameItem) {
                Mitems++;
                data[Mitems-1] = b.data[i];
                    //        cout << Mitems << endl;
            }
        }
            //排个序
        
        int i;
        Term temp;
        for(int p=1;p<Mitems;p++)
        {
            for(i=0;i<Mitems-p;i++)
                if(data[i].row>data[i+1].row||((data[i].row==data[i+1].row)&&data[i].col>data[i+1].col))
                {
                    temp=data[i];
                    data[i]=data[i+1];
                    data[i+1]=temp;
                }
        }
        
        
    };
        //outPut;
    void outPut(){
        for (int i = 0; i < Mitems; i++) {
            if (data[i].value != 0){
                cout << data[i].row << " " << data[i].col  << " " << data[i].value << endl;
            }
        };
    };
};

using namespace std;


    //  MARK: - 主程序
int main(int argc, const char * argv[]) {
    
    Matrix a,b;
    int aRow,aCols,aItem;
    cin >> aRow >> aCols >> aItem;
    a.input(aRow, aCols, aItem);
    int bRow,bCols,bItem;
    cin >> bRow >> bCols >> bItem;
    b.input(bRow, bCols, bItem);
    cout << "The transformed matrix is:" << endl;
    a.rotation();
    a.add(b);
    cout << "The added matrix is:" << endl;
    a.outPut();
    return 0;
}
