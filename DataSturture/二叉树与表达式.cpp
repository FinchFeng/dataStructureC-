//
//  二叉树与表达式.cpp
//  DataSturture
//
//  Created by 冯奕琦 on 2018/10/11.
//  Copyright © 2018年 冯奕琦. All rights reserved.
//

//将通过二叉链表实现的表达式二叉树进行输出，同时计算出结果。
//
//要求：
//
//1）二叉树建立时，使用先序建立；
//
//2）四个运算符包括：+, -, *, /;
//
//3 ) 在输出时，遇到优先级问题时，相应的括号也要输出。
//
//提示：
//
//1）递归执行下列步骤即可求值：先分别求出左子树和右子树表示的子表达式的值，最后根据根结点的运算符的要求，计算出表达式的最后结果。
//
//2）二叉树的中序遍历序列与原算术表达式基本相同，但是需要将中序序列加上括号，即当根结点运算符优先级高于左子树（或右子树）根结点运算符时，就需要加括号。

#include <iostream>
#include <string>


    //MARK: - 树

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
            //    cout << "Created success!" << endl;
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
            //    cout << "Inorder is:" ;
        inOrderTree(root,root);
            //    cout << "." << endl;
    }
    
    ;
    void inOrderTree(TreeNode *parent ,TreeNode *&subTree){
        if (subTree != NULL) {
                //set data
            bool printCol = false;
            char parentValue;
            char value = subTree->data;
                //查看是否需要加括号
            if ((parent != NULL)) {
                parentValue = parent->data;
                if (((parentValue=='*')||(parentValue=='/'))&&((value=='+')||(value=='-'))) {
                    printCol = true;
                    cout << "(";
                }
            }
                //赋值成为新的parent
            parent = subTree;
                //计算节点
            inOrderTree(parent,subTree->leftChild);
            cout << value ;
            inOrderTree(parent,subTree->rightChild);
            if (printCol) {
                cout << ")";
            }
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
    
    int operation(TreeNode *&currentNode){
        
        char leftValue = currentNode->leftChild->data;
        char rightValue = currentNode->rightChild->data;
        int leftInt,rightInt;
        
        char opationValue = currentNode->data;
        
            //    cout << leftValue << " " << opationValue << " " << rightValue << endl;
        
        
        if (isOperation(leftValue)) {
            leftInt = operation(currentNode->leftChild);
        }else{
            leftInt = int(leftValue)-48;
            
        }
        
        if (isOperation(rightValue)) {
            rightInt = operation(currentNode->rightChild);
        }else{
            rightInt = int(rightValue)-48;
        }
        
        int finalValue = 0;
        
        if (opationValue == '+') {
            finalValue = leftInt+rightInt;
        }
        if (opationValue == '-') {
            finalValue = leftInt-rightInt;
        }
        if (opationValue == '*') {
            finalValue = leftInt*rightInt;
        }
        if (opationValue == '/') {
            finalValue = leftInt/rightInt;
        }
        
            //    cout << leftInt << opationValue << rightInt << " = " << finalValue << endl;
        return finalValue;
        
    }
    
    bool isOperation(char n){
        if ((n == '+')||(n == '-')||(n == '*')||(n == '/')) {
            return true;
        }else{
            return false;
        }
    }
    
    int getFinalValue(){
        return operation(root);
    }
    
};




    //  MARK: - 主程序
int main(int argc, const char * argv[]) {
    
    Tree newTree('@');
    newTree.input();
    
    newTree.printInOrder();
    int value = newTree.getFinalValue();
    cout << "=" << value << endl ;
    
}





