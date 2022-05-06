#include "juzhen.h"
#include "ui_juzhen.h"
#include  <stdlib.h>
#include  <string.h>
#include   <stdio.h>

#define INFEASIBLE -1
#define MAXSIZE 99 // 非零元个数的最大值
juzhen::~juzhen()
{
    delete ui;
}
typedef struct {
    int i, j; // 行下标,列下标
    int e; // 非零元素值
}Triple;

typedef struct {
    Triple data[MAXSIZE + 1]; // 非零元三元组表,从data[1]开始使用
    int mu, nu, tu; // 矩阵的行数、列数和非零元个数
}TSMatrix;

void AtoT(int num[][MAXSIZE],TSMatrix *T)//二维数组转三元组
{
    T->tu = 1;
    for(int i=1;i<=T->mu;i++)
    {
        for(int j=1;j<=T->nu;j++)
        {
            if(num[i][j]!=0)
            {
                T->data[T->tu].i = i;
                T->data[T->tu].j = j;
                T->data[T->tu].e = num[i][j];
                T->tu++;
            }
        }
    }
    T->tu--;
}

void TtoA(TSMatrix T,int num[][MAXSIZE])//三元组转二维数组
{
    for(int i=1;i<=T.tu;i++)
    {
        num[T.data[i].i][T.data[i].j] = T.data[i].e;
    }
}

void Create_Matrix(TSMatrix *T,int m,int n,int x[])
{
    int l = 0;
    int num[MAXSIZE][MAXSIZE]={0};
    T->mu = m;
    T->nu = n;
    printf("请输入稀疏矩阵的元素\n");
    for (int i = 1; i <= T->mu; i++)
    {
        for (int j = 1; j <= T->nu; j++)
        {
            num[i][j] = x[l];
            l++;
        }
    }
    AtoT(num, T);//数组转三元组
}
// 三元组表示的稀疏矩阵加法: C=A+B
int Matrix_Addition(TSMatrix A, TSMatrix B, TSMatrix *C)
{
    int row_a, row_b,col_a, col_b, index_a, index_b, index_c;
    //A元素的行号，B元素的行号，A元素的列号，B元素的列号，ABC矩阵三元组的地址
    //因为同类型矩阵才能相加，所以相加后的矩阵行和列和原来来两个矩阵的行列一样
    C->mu = A.mu;
    C->nu = A.nu;
    //行，列不相同的矩阵不能相加，返回0
    if (A.mu != B.mu || A.nu != B.nu) {
        return 0;
    }
    //同时遍历两个三元组，开始都为1，因为0位置未存元素，当A或者B中其一元素取完循环终止
    for(index_a=1,index_b=1,index_c=1;index_a<=A.tu&&index_b<=B.tu;)
    {

        row_a = A.data[index_a].i;//A矩阵元素的行号
        row_b = B.data[index_b].i;//B矩阵元素的行号
        col_a = A.data[index_a].j;//A矩阵元素的列号
        col_b = B.data[index_b].j;//B矩阵元素的列号

        //因为三元组是按行和列排好序的所以比较行数先判断是否来自同一行
        if(row_a>row_b)//B的行号小于A直接将B中元素加入C矩阵
        {
            //复制B到C
            C->data[index_c].i = B.data[index_b].i;
            C->data[index_c].j = B.data[index_b].j;
            C->data[index_c].e = B.data[index_b].e;
            index_b++;//B矩阵地址加一表示向后取一个元素
            index_c++;//C矩阵地址加一表示下一元素存放的地址
        }
        else if(row_a<row_b)//B的行号大于A直接将A中元素加入C矩阵
        {
            //复制A到C
            C->data[index_c].i = A.data[index_a].i;
            C->data[index_c].j = A.data[index_a].j;
            C->data[index_c].e = A.data[index_a].e;
            index_a++;//A矩阵地址加一表示向后取一个元素
            index_c++;//C矩阵地址加一表示下一元素存放的地址
        }
        else//行号相同时
        {
            //在判断列好号是否来自同一行
            if(col_a>col_b)//B的列号小于A直接将B中元素加入C矩阵
            {
                //复制B到C
                C->data[index_c].i = B.data[index_b].i;
                C->data[index_c].j = B.data[index_b].j;
                C->data[index_c].e = B.data[index_b].e;
                index_b++;//B矩阵地址加一表示向后取一个元素
                index_c++;//C矩阵地址加一表示下一元素存放的地址
            }
            else if(col_a<col_b)//B的列号小于A直接将B中元素加入C矩
            {
                //复制A到C
                C->data[index_c].i = A.data[index_a].i;
                C->data[index_c].j = A.data[index_a].j;
                C->data[index_c].e = A.data[index_a].e;
                index_a++;//A矩阵地址加一表示向后取一个元素
                index_c++;//C矩阵地址加一表示下一元素存放的地址
            }
            else//相等
            {
                //判断元素相加是否为零
                if((A.data[index_a].e+B.data[index_b].e))//相加不为零
                {
                    C->data[index_c].i = A.data[index_a].i;//赋值行号给C
                    C->data[index_c].j = A.data[index_a].j;//赋值列号给C
                    C->data[index_c].e = A.data[index_a].e + B.data[index_b].e;//赋值元素相加结果给C
                    index_c++;//C矩阵地址加一表示下一元素存放的地址
                }
                //无论相加是否为零都执行
                index_a++;//A矩阵地址加一表示向后取一个元素
                index_b++;//B矩阵地址加一表示向后取一个元素
            }
        }
    }

    while (index_a <= A.tu)//B取完A未取完
    {
        //将A中所剩元素依次加入到C中
        C->data[index_c].i = A.data[index_a].i;
        C->data[index_c].j = A.data[index_a].j;
        C->data[index_c].e = A.data[index_a].e;
        index_a++;
        index_c++;
    }

    while (index_b <= B.tu)//A取完B未取完
    {
        //将A中所剩元素依次加入到C中
        C->data[index_c].i = B.data[index_b].i;
        C->data[index_c].j = B.data[index_b].j;
        C->data[index_c].e = B.data[index_b].e;
        index_b++;
        index_c++;
    }
    C->tu = index_c - 1;//index_c是在执行完逻辑后加一的所以比实际上多1，因此C中元素的真实个数为index_c-1
    return 1;
}
juzhen::juzhen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::juzhen)
{
    ui->setupUi(this);
    this->setWindowTitle("矩阵计算器");
    this->setMinimumSize(420,560);
    this->setMaximumSize(420,560);
    QFont f("仿宋",20);
    ui->lineEdit->setFont(f);
}
void juzhen::on_pushButton_12_clicked()
{
    this->hide();
    MainWindow *main = new MainWindow;
    main->show();
}

void juzhen::on_pushButton_clicked()
{
    Qsjuzhen += "0";
    ui->lineEdit->setText(Qsjuzhen);
}
void juzhen::on_pushButton_1_clicked()
{
    Qsjuzhen += "1";
    ui->lineEdit->setText(Qsjuzhen);
}
void juzhen::on_pushButton_2_clicked()
{
    Qsjuzhen += "2";
    ui->lineEdit->setText(Qsjuzhen);
}
void juzhen::on_pushButton_3_clicked()
{
    Qsjuzhen += "3";
    ui->lineEdit->setText(Qsjuzhen);
}
void juzhen::on_pushButton_4_clicked()
{
    Qsjuzhen += "4";
    ui->lineEdit->setText(Qsjuzhen);
}
void juzhen::on_pushButton_5_clicked()
{
    Qsjuzhen += "5";
    ui->lineEdit->setText(Qsjuzhen);
}
void juzhen::on_pushButton_6_clicked()
{
    Qsjuzhen += "6";
    ui->lineEdit->setText(Qsjuzhen);
}
void juzhen::on_pushButton_7_clicked()
{
    Qsjuzhen += "7";
    ui->lineEdit->setText(Qsjuzhen);
}
void juzhen::on_pushButton_8_clicked()
{
    Qsjuzhen += "8";
    ui->lineEdit->setText(Qsjuzhen);
}
void juzhen::on_pushButton_9_clicked()
{
    Qsjuzhen += "9";
    ui->lineEdit->setText(Qsjuzhen);
}

void juzhen::on_pushButton_13_clicked()
{
    m = ui->spinhang->value();
    n = ui->spinlie->value();
}

void juzhen::on_pushButton_10_clicked()
{
    TSMatrix A,B,C;
    int k = m*n;
    int i,j;
    for(i=0;i<k;i++)
    {
        a1[i] = Qsjuzhen.mid(i,1);
        b1[i] = a1[i].toInt();
    }
    for(j=0;j<k;j++)
    {
        a2[j] = Qsjuzhen.mid(j+k,1);
        b2[j] = a2[j].toInt();
    }
    Create_Matrix(&A,m,n,b1);
    Create_Matrix(&B,m,n,b2);
    Matrix_Addition(A, B, &C);
    TtoA(C, num1);
    Qsjuzhen.clear();
    for(i=1;i<=m;i++)
       {
           for(j=1;j<=n;j++)
           {
               jieguo += QString::number(num1[i][j]);
               jieguo += " ";
           }
           jieguo += "\n";
       }
    ui->textEdit->setText(jieguo);
    jieguo.clear();
}
void juzhen::on_pushButton_11_clicked()
{
    Qsjuzhen.clear();
    ui->lineEdit->clear();
}
void juzhen::on_pushButton_delete_clicked()
{
    Qsjuzhen.chop(1);
    ui->lineEdit->setText(Qsjuzhen);
}
