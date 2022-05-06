#include "jinzhi.h"
#include "ui_jinzhi.h"
#include<iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;
typedef int ElemType;
struct Stack{
    ElemType *stack;
    int top;
    int MaxSize;
};
//1初始化栈S为空
void InitStack(Stack& S){
    S.MaxSize=10;
    S.stack=new ElemType[S.MaxSize];
    if(!S.stack){
        cerr<<"动态存储空间分配失败！"<<endl;
        exit(1);
    }
    S.top=-1;
}
//元素item入栈，插入到栈顶
void Push(Stack& S,ElemType item){
    if(S.top==S.MaxSize-1){
        int k=sizeof(ElemType);
        S.stack=(ElemType*)realloc(S.stack,2*S.MaxSize*k);
        S.MaxSize=2*S.MaxSize;
    }
    //栈顶指针后移一个位置
    S.top++;
    //将新元素插入到栈顶
    S.stack[S.top]=item;
}

//2删除栈顶元素并返回
ElemType Pop(Stack& S){\
// 若栈顶为空，则退出运行
     if(S.top==-1){
        cerr<<"Stack is empty!"<<endl;
        exit(1);
     }
     S.top--;
     return S.stack[S.top+1];
}

//4、读取栈顶元素的值
ElemType Peek(Stack& S){
    if(S.top==-1){
        cerr<<"Stack is empty!"<<endl;
        exit(1);
     }

     return S.stack[S.top];
}

//5、判断S是否为空，若是返回true
bool EmptyStack(Stack& S){
    return S.top==-1;
}

//6、清除栈中所有的元素，释放动态存贮空间
void ClearStack(Stack& S){
    if(S.stack){
        delete []S.stack;
        S.stack=0;
    }
    S.top=-1;
    S.MaxSize=0;
}
jinzhi::jinzhi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::jinzhi)
{
    ui->setupUi(this);
    this->setWindowTitle("进制转换器");
    this->setMinimumSize(420,560);
    this->setMaximumSize(420,560);
    QFont f("仿宋",20);
    ui->lineEdit->setFont(f);
}

jinzhi::~jinzhi()
{
    delete ui;
}

void jinzhi::on_pushButton_clicked()
{
    Qsjinzhi += "0";
    ui->lineEdit->setText(Qsjinzhi);
}
void jinzhi::on_pushButton_1_clicked()
{
    Qsjinzhi += "1";
    ui->lineEdit->setText(Qsjinzhi);
}
void jinzhi::on_pushButton_2_clicked()
{
    Qsjinzhi += "2";
    ui->lineEdit->setText(Qsjinzhi);
}
void jinzhi::on_pushButton_3_clicked()
{
    Qsjinzhi += "3";
    ui->lineEdit->setText(Qsjinzhi);
}
void jinzhi::on_pushButton_4_clicked()
{
    Qsjinzhi += "4";
    ui->lineEdit->setText(Qsjinzhi);
}
void jinzhi::on_pushButton_5_clicked()
{
    Qsjinzhi += "5";
    ui->lineEdit->setText(Qsjinzhi);
}
void jinzhi::on_pushButton_6_clicked()
{
    Qsjinzhi += "6";
    ui->lineEdit->setText(Qsjinzhi);
}
void jinzhi::on_pushButton_7_clicked()
{
    Qsjinzhi += "7";
    ui->lineEdit->setText(Qsjinzhi);
}
void jinzhi::on_pushButton_8_clicked()
{
    Qsjinzhi += "8";
    ui->lineEdit->setText(Qsjinzhi);
}
void jinzhi::on_pushButton_9_clicked()
{
    Qsjinzhi += "9";
    ui->lineEdit->setText(Qsjinzhi);
}
void jinzhi::on_pushButton_11_clicked()
{
    Qsjinzhi.clear();
    ui->lineEdit->clear();
}
void jinzhi::on_pushButton_delete_clicked()
{
    Qsjinzhi.chop(1);
    ui->lineEdit->setText(Qsjinzhi);
}

void jinzhi::on_pushButton_back_clicked()
{
    this->hide();
    MainWindow *main = new MainWindow;
    main->show();
}
void jinzhi::on_pushButton_zhuan_clicked()
{
    int num = ui->spinNum->value();
    Stack s;
    InitStack(s);
    int n = Qsjinzhi.toInt();
    while(n){
        int i=n%num;
        Push(s,i);
        n=n/num;
    }
    Qsjinzhi.clear();
    ui->lineEdit->clear();
    while(!EmptyStack(s)){
        Qsjinzhi += QString::number(Pop(s));
     }
    ui->lineEdit->setText(Qsjinzhi);
}
