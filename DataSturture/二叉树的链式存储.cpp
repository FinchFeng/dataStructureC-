//
//  二叉树的链式存储.cpp
//  DataSturture
//
//  Created by 冯奕琦 on 2018/10/11.
//  Copyright © 2018年 冯奕琦. All rights reserved.
//

//实现二叉树的基本操作：建立、遍历、计算深度、结点数、叶子数等。
//
//输入C，先序创建二叉树，#表示空节点；
//
//输入H：计算二叉树的高度；
//
//输入L：计算二叉树的叶子个数；
//
//输入N：计算二叉树节点总个数；
//
//输入1：先序遍历二叉树；
//
//输入2：中序遍历二叉树；
//
//输入3：后续遍历二叉树；
//
//输入F：查找值=x的节点的个数；
//
//输入P：以缩格文本形式输出所有节点。



#include <iostream>
#include <string>

using namespace std;
struct TreeNode {//节点定义
    char data;
    TreeNode *leftChild,*rightChild;
    TreeNode(){
        leftChild = NULL;
        rightChild = NULL;
    };
    TreeNode(char value,TreeNode *l = NULL,TreeNode *r = NULL){
        data = value;
        leftChild = l;
        rightChild = r;
    };
};

class Tree{
public:
        //Value
    TreeNode *root;
    char stopValue;
    string treeInput;
    long lastIndex,inputIndex = 0;
    
    long height = 0,size = 0,leafSize = 0;
        //init
    Tree(){
        root = NULL;
    };
    Tree(char sValue){
        stopValue = sValue;
        root = NULL;
    }
        //method
    
    void input(){
        cin >> treeInput;
        lastIndex = treeInput.length()-1;
        creatNewTree(0, root);
        calculateTree(1, root);
        cout << "Created success!" << endl;
    }
    
    void creatNewTree(long index,TreeNode *&subTree){
        char value = treeInput[inputIndex];
            //    cout << index << " " << value << endl ;
        inputIndex++;
        if (index != lastIndex) {
            if (value != stopValue) {
                subTree = new TreeNode(value);
                creatNewTree(inputIndex, subTree->leftChild);
                creatNewTree(inputIndex, subTree->rightChild);
            }else{
                subTree = NULL;
            }
        }
    }
    
    void calculateTree(int level,TreeNode *&subTree){
        if (subTree != NULL) {
                //计算节点
            size++;
            if (level > height) {
                height = level;
            }
            if ((subTree->leftChild == NULL)&&(subTree->rightChild == NULL)) {
                leafSize++;
            }
                //      char value = subTree->data;
                //      cout << level << " " << value << endl;
            level++;
            calculateTree(level, subTree->leftChild);
            calculateTree(level, subTree->rightChild);
        }
    }
    
        //前序
    
    void printPreOrder(){
        cout << "Preorder is:" ;
        preOrderTree(root);
        cout << "." << endl;
    }
    
    void preOrderTree(TreeNode *&subTree){
        if (subTree != NULL) {
                //计算节点
            char value = subTree->data;
            cout << value << " " ;
            preOrderTree(subTree->leftChild);
            preOrderTree(subTree->rightChild);
        }
    }
    
        //中序
    
    void printInOrder(){
        cout << "Inorder is:" ;
        inOrderTree(root);
        cout << "." << endl;
    }
    
    void inOrderTree(TreeNode *&subTree){
        if (subTree != NULL) {
                //计算节点
            inOrderTree(subTree->leftChild);
            char value = subTree->data;
            cout << value << " " ;
            inOrderTree(subTree->rightChild);
        }
    }
    
        //后序
    
    void printTailOrder(){
        cout << "Postorder is:" ;
        tailOrderTree(root);
        cout << "." << endl;
    }
    
    void tailOrderTree(TreeNode *&subTree){
        if (subTree != NULL) {
                //计算节点
            tailOrderTree(subTree->leftChild);
            tailOrderTree(subTree->rightChild);
            char value = subTree->data;
            cout << value << " " ;
        }
    }
    
        //查找
    
    int findCount = 0;
    void findValue(char value){
        find(value, root);
        cout << "The count of "<< value <<" is " << findCount << "." << endl;
    }
    
    void find(char target,TreeNode *&subTree){
        if (subTree != NULL) {
                //计算节点
            char value = subTree->data;
            if (target == value) {
                findCount++;
            }
            find(target,subTree->leftChild);
            find(target,subTree->rightChild);
        }
    }
    
        //文本输出
    
    void printATree(){
        cout << "The tree is:" << endl;
        outputATree(0, root);
    }
    
    void outputATree(int level,TreeNode *&subTree){
        if (subTree != NULL) {
                //输出节点
            char value = subTree->data;
            for (int i = 0; i < level; i++) {
                cout << "  ";
            }
            cout << value << endl;
            level++;
            outputATree(level, subTree->leftChild);
            outputATree(level, subTree->rightChild);
        }
    }
    
};



    //  MARK: - 主程序
int main(int argc, const char * argv[]) {
    
    char inputChar,findValue;
    cin >> inputChar;
    Tree newTree('#');
    newTree.input();
    for (int i = 1; i<=7; i++) {
        cin >> inputChar;
    }
    cin >> findValue;
        //  cin >> inputChar;
    
    cout << "Height=" << newTree.height << "." << endl;
    cout << "Leaf=" << newTree.leafSize << "." << endl;
    cout << "Nodes=" << newTree.size << "." << endl;
    newTree.printPreOrder();
    newTree.printInOrder();
    newTree.printTailOrder();
    newTree.findValue(findValue);
    newTree.printATree();
}

