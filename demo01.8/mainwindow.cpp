#include "mainwindow.h"
#include "ui_mainwindow.h"

//带括号的加减乘除
using namespace std;
typedef struct node{
    int data;
    char* formula;
    struct node* next;
}LNode,*LinkList;
LinkList L,L1;
int length =0;
void InitList();
LinkList save(char* x,int y);
LinkList search();
string mid2back(string);//中缀计算表达式转后缀计算表达式
int compute(string);//计算后缀表达式
bool priority(char a, char b);//辅助函数 判断两个运算符的优先级
QString mid2back(QString sa)
{
    char s[128]={0};
    QString res;
    QStack<char> st;
    int size = sa.size();
    QByteArray ba;
    ba.append(sa);
    strcpy(s,ba.data());
    for (int i = 0; i < size; i++)
    {
        if (s[i] != '('&&s[i] != ')'&&s[i] != '+'&&s[i] != '*'&&s[i]!='-'&&s[i]!='/')
            res += s[i];//数字直接放入算术表达式
        if (s[i] == '(')
            st.push(s[i]);//'('左括号优先级最高 直接入栈
        if (s[i] == '+'||s[i]=='*'||s[i]=='-'||s[i]=='/')//或'*' '+' '-'
        {
            if (st.empty())
                st.push(s[i]);//栈空 算术符号入栈
            else//否则根据算术符号优先级出栈
            while (1)
            {
                char temp = st.top();//栈顶算术符号
                if (priority(s[i], temp))//栈顶算术符号优先级高于当前算术符号
                {
                    st.push(s[i]);//入栈
                    break;//出循环
                }
                else
                {
                    res += temp;//否则栈顶算术符号放入算术表达式
                    st.pop();//直到当前算术符号优先级小于栈顶算术符号
                    if (st.empty())//如果栈空 那么当前算术符号入栈
                    {
                        st.push(s[i]);
                        break;//出循环
                    }
                }
            }

        }
        if (s[i] == ')')//如果是右括号
        {
            while (st.top() != '(')//算术符号出栈 直到栈顶为左括号
            {
                res += st.top();
                st.pop();
            }
            st.pop();//'('出栈 且不放入算术表达式
        }
    }
    while (!st.empty())//栈中剩余算术符号放入算术表达式
    {
        res += st.top();
        st.pop();
    }
    return res;//转换后的算术表达式
}
bool priority(char a, char b)
{
    //算术优先级a>b 返回true
    //加法
    if (a == '+'&&b == '+')
        return false;
    if (a == '+'&&b == '*')
        return false;
    if (a == '+'&&b == '(')
        return true;
    if (a == '+'&&b == '-')
        return false;
    if (a == '+'&&b == '/')
        return false;
    //减法
    if (a == '-'&&b == '+')
        return false;
    if (a == '-'&&b == '-')
        return false;
    if (a == '-'&&b == '*')
        return true;
    if (a == '-'&&b == '(')
        return true;
    if (a == '-'&&b == '/')
        return true;
    //乘法
    if (a == '*'&&b == '+')
        return true;
    if (a == '*'&&b == '-')
        return true;
    if (a == '*'&&b == '*')
        return false;
    if (a == '*'&&b == '(')
        return true;
    if (a == '*'&&b == '/')
        return true;
    //除法
    if (a == '/'&&b == '+')
        return true;
    if (a == '/'&&b == '-')
        return true;
    if (a == '/'&&b == '*')
        return true;
    if (a == '/'&&b == '(')
        return true;
    if (a == '/'&&b == '/')
        return false;
    return false;//语法要求必有返回值
}
int compute(QString sb)//根据后缀算术表达式计算值
{
    char str[128]={0};
    QStack<int> st;
    int size = sb.size();
    QByteArray ba;
    ba.append(sb);
    strcpy(str,ba.data());
    for (int i = 0; i < size; i++)
    {
        if (str[i] != '+'&&str[i] != '*'&&str[i]!='-'&&str[i]!='/')
            st.push(str[i] - '0');//数字入栈 注意char转int
        if (str[i] == '+')//执行加法
        {
            int a = st.top();
            st.pop();
            int b = st.top();//取栈顶两元素
            st.pop();
            st.push(a + b);//加法的和入栈
        }
        if (str[i] == '*')//执行乘法
        {
            int a = st.top();
            st.pop();
            int b = st.top();//取栈顶两元素
            st.pop();
            st.push(a*b);//乘法的积入栈
        }
        if (str[i] == '-')//执行乘法
        {
            int a = st.top();
            st.pop();
            int b = st.top();//取栈顶两元素
            st.pop();
            st.push(b-a);//乘法的积入栈
        }
        if (str[i] == '/')
        {
            int a = st.top();
            st.pop();
            int b = st.top();
            //取栈顶两元素
            st.pop();
            st.push(b/a);//除法的入栈
        }
    }
    return st.top();//返回后缀表达式的计算结果
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    InitList();
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/new/prefix1/1.jpg"));
    this->setWindowTitle("高级计算器");
    this->setMinimumSize(420,560);
    this->setMaximumSize(420,560);
    QFont f("仿宋",20);
    ui->lineEdit->setFont(f);
}
LinkList save(char* x,int y)
{
    LinkList p=(LinkList)malloc(sizeof(LNode));
    p->data=y;
    p->formula=x;
    p->next=L->next;
    L->next=p;
    L1=L;
    return L;
}
void InitList()
{
    L=(LNode*)malloc(sizeof(LNode));
    L->next=NULL;
    L1=(LNode*)malloc(sizeof(LNode));
    L1->next=NULL;
}
LinkList search()
{
    LinkList p=(LinkList)malloc(sizeof(LNode));
    if(L1->next!=NULL)
    {
        L1=L1->next;
        length++;
        return L1;
    }
    else
        return L1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    expression += "0";
    ui->lineEdit->setText(expression);
}
void MainWindow::on_pushButton_1_clicked()
{
    expression += "1";
    ui->lineEdit->setText(expression);
}
void MainWindow::on_pushButton_2_clicked()
{
    expression += "2";
    ui->lineEdit->setText(expression);
}
void MainWindow::on_pushButton_3_clicked()
{
    expression += "3";
    ui->lineEdit->setText(expression);
}
void MainWindow::on_pushButton_4_clicked()
{
    expression += "4";
    ui->lineEdit->setText(expression);
}
void MainWindow::on_pushButton_5_clicked()
{
    expression += "5";
    ui->lineEdit->setText(expression);
}
void MainWindow::on_pushButton_6_clicked()
{
    expression += "6";
    ui->lineEdit->setText(expression);
}
void MainWindow::on_pushButton_7_clicked()
{
    expression += "7";
    ui->lineEdit->setText(expression);
}
void MainWindow::on_pushButton_8_clicked()
{
    expression += "8";
    ui->lineEdit->setText(expression);
}
void MainWindow::on_pushButton_9_clicked()
{
    expression += "9";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_kuohao_1_clicked()
{
    expression += "(";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_kuohao_2_clicked()
{
    expression += ")";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_j_clicked()
{
    expression += "+";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_jian_clicked()
{
    expression += "-";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_c_clicked()
{
    expression += "*";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_chu_clicked()
{
    expression += "/";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_11_clicked()
{
    expression.clear();
    ui->lineEdit->clear();
}

void MainWindow::on_pushButton_delete_clicked()
{
    expression.chop(1);
    ui->lineEdit->setText(expression);
}
void MainWindow::on_pushButton_jinzhi_clicked()
{
    this->hide();
    jinzhi *jin = new jinzhi;
    jin->show();
}
void MainWindow::on_pushButton_d_clicked()

{
    QString str = mid2back(expression);//改写的后缀表达式
    int a = compute(str);
    QByteArray ba = expression.toLatin1();
    char *expression1 = ba.data();
    save(expression1,a);
    QString str2;
    str2=QString::number(a);
    expression.clear();
    ui->lineEdit->clear();
    ui->lineEdit->setText(str2);
}

void MainWindow::on_pushButton_10_clicked()
{
    LinkList his=search();
    ui->lineEdit->setText(QString::number(his->data));
}


void MainWindow::on_pushButton_juzhen_clicked()
{
    this->hide();
    juzhen *ju = new juzhen;
    ju->show();
}
