//------电子科技大学-计算机组成原理-指令流程模拟运行演示软件------
//本程序根据GPL协议开源，任何组织或个人不得将本程序和/或源码私有化或作为盈利目的使用
//任何对本程序的修改和再编译都必须注明本程序和原作者信息
//本程序原始作者有：杨时雨、黄家垚、曹灿。杨峻欢、戴洋为程序做其它贡献。

//把各个寄存器，ALU，主存，移位器，各种线定义为类 register_bus。把对寄存器中的数据的操作封装到类中

#ifndef BUSREGISTER_H_
#define BUSREGISTER_H_
#include<iostream>
#include<string>
#include"leftwidget.h"

//#define the_time 0.5  //单位为秒

using namespace std;

//设定定时器间隔的毫秒表示
float the_time = 1.00;
//设定定时器间隔的毫秒表示
float the_time_ms = the_time*1000;

//队列结构声明
typedef struct node{//结构体，存储信息
    string name;
    char value[5];
    string Procedure;
    int color;
    node* next;
}*Node;

string combobox1_value;
string combobox2_value;
string combobox3_value;

Node head;//设立队列头
Node rear;//设立队列尾巴
Node pointer;//浮动指针

Node insert(Node Rear,string name,char value[5],int color)//将信息插入队列
{
    if(head==NULL)
    {
        head=new node;
        head->name=name;
        head->color=color;
        head->next=NULL;
        Rear=head;
        pointer=head;
    }
    else{
        Rear->next=new node;
        Rear=Rear->next;
        Rear->name=name;
        Rear->color=color;
        Rear->next=NULL;
        strcpy(Rear->value,value);}
    return Rear;
}
Node insert(Node Rear,string pro)
{
    if(head==NULL)
    {
        head=new node;
        head->name="STDTET";
        head->Procedure=pro;
        head->next=NULL;
        Rear=head;
        pointer=head;
    }
    else {
        Rear->next=new node;
        Rear=Rear->next;
        Rear->name="STDTET";
        Rear->Procedure=pro;
        Rear->next=NULL;
    }
    return Rear;
}

Node insert(Node Rear)
{
    if(head==NULL)
    {
        head->name="ZERO";
        head->next=NULL;
        Rear=head;
        pointer=head;
    }
    else {
        Rear->next=new node;
        Rear=Rear->next;
        Rear->name="ZERO";
        Rear->next=NULL;
    }
    return Rear;
}

void sy_add(char* a,char* b);
void sy_sub(char* a,char* b);
void sy_com(char* a);
void sy_neg(char* a);
char* sy_binary_to_hex(const char* a);
void sy_neg(char* a){//求补码的函数,取反加1
    //cout<<strlen(a);
    //cout<<a<<endl;
    char* c=new char [17];
    strcpy(c,a);
    //cout<<a<<endl;
    sy_com(c);
    strcpy(a,c);
    //cout<<a<<endl;
    char* b="0000000000000001";
    sy_add(a,b);

    delete c;
}
void sy_com(char* a){
    cout<<sy_binary_to_hex(a)<<endl;
    for(int i=15;i>=0;i--){
        if(a[i]=='0')
            a[i]='1';
        else if(a[i]=='1')
            a[i]='0';
    }
    cout<<sy_binary_to_hex(a)<<endl;
}
void sy_inc(char* a){
    char* b="0000000000000001";
    sy_add(a,b);
}
void sy_dec(char* a){
    //cout<<strlen("0000000000000001")<<endl;
    char* b="0000000000000001";
    sy_sub(a,b);
}
void sy_sl(char* a){
    for(int i=0;i<14;i++){
        a[i]=a[i+1];
    }
    a[14]='0';
}
void sy_sr(char* a){
    for(int i=15;i>1;i--){
        a[i]=a[i-1];
    }
    if(a[0]=='1')
        a[1]='1';
    else a[1]='0';
}
void sy_add(char* a,char* b){//加法
    char ch='0';
    //cout<<a<<endl;
    //cout<<b<<endl;
    for(int i=15;i>=0;i--){
        if(a[i]+b[i]+ch==144){
            a[i]='0';
            ch='0';
        }
        else if(a[i]+b[i]+ch==145){
            a[i]='1';
            ch='0';
        }
        else if(a[i]+b[i]+ch==146){
            a[i]='0';
            ch='1';

        }
        else if(a[i]+b[i]+ch==147){
            a[i]='1';
            ch='1';
        }
    }
}
void sy_sub(char* a,char* b){//减法
    char* c=new char[17];
    strcpy(c,b);
    //cout<<a<<endl;
    sy_neg(c);
    sy_add(a,c);

    delete c;
}

void sy_eor(char* a,char* b){
    for(int i=0;i<15;i++){
        if(a[i]==b[i])
            a[i]='0';
        else a[i]='1';
    }
}

void sy_and(char* a,char* b){
    for(int i=0;i<=15;i++){
        if(a[i]=='0'||b[i]=='0')
            a[i]='0';
        else a[i]='1';
    }
}

void sy_or(char* a,char* b){
    for(int i=0;i<=15;i++){
        if(a[i]=='0'&&b[i]=='0')
            a[i]='0';
        else a[i]='1';
    }
}
char sy_binary_4_to_hex_1(char a,char b,char c,char d){
    int i=(int(d)-48)*1+(int(c)-48)*2+(int(b)-48)*4+(int(a)-48)*8;
    if(i<10)
        return char(i+48);
    else
        return char(65+i-10);
}

char* sy_binary_to_hex(const char* a){
    char* b=new char[5];
    for(int i=3;i>=0;i--){
        b[i]=sy_binary_4_to_hex_1(a[i*4],a[i*4+1],a[i*4+2],a[i*4+3]);
    }
    b[4]=0;
    return b;
}
//char* hex_to_binary(const char* a){
char* sy_hex_to_binary(char* b){//十六进制和4进制转换
    char* a=new char[17];
    a[16]=0;
    for(int i=0;i<4;i++){
        if(b[i]=='0'){
            a[i*4+0]='0';a[i*4+1]='0';a[i*4+2]='0';a[i*4+3]='0';}
        else if(b[i]=='1'){
            a[i*4+0]='0';a[i*4+1]='0';a[i*4+2]='0';a[i*4+3]='1';}
        else if(b[i]=='2'){
            a[i*4+0]='0';a[i*4+1]='0';a[i*4+2]='1';a[i*4+3]='0';}
        else if(b[i]=='3'){
            a[i*4+0]='0';a[i*4+1]='0';a[i*4+2]='1';a[i*4+3]='1';}
        else if(b[i]=='4'){
            a[i*4+0]='0';a[i*4+1]='1';a[i*4+2]='0';a[i*4+3]='0';}
        else if(b[i]=='5'){
            a[i*4+0]='0';a[i*4+1]='1';a[i*4+2]='0';a[i*4+3]='1';}
        else if(b[i]=='6'){
            a[i*4+0]='0';a[i*4+1]='1';a[i*4+2]='1';a[i*4+3]='0';}
        else if(b[i]=='7'){
            a[i*4+0]='0';a[i*4+1]='1';a[i*4+2]='1';a[i*4+3]='1';}
        else if(b[i]=='8'){
            a[i*4+0]='1';a[i*4+1]='0';a[i*4+2]='0';a[i*4+3]='1';}
        else if(b[i]=='9'){
            a[i*4+0]='1';a[i*4+1]='0';a[i*4+2]='0';a[i*4+3]='1';}
        else if(b[i]=='A'){
            a[i*4+0]='1';a[i*4+1]='0';a[i*4+2]='1';a[i*4+3]='0';}
        else if(b[i]=='B'){
            a[i*4+0]='1';a[i*4+1]='0';a[i*4+2]='1';a[i*4+3]='1';}
        else if(b[i]=='C'){
            a[i*4+0]='1';a[i*4+1]='1';a[i*4+2]='0';a[i*4+3]='0';}
        else if(b[i]=='D'){
            a[i*4+0]='1';a[i*4+1]='1';a[i*4+2]='0';a[i*4+3]='1';}
        else if(b[i]=='E'){
            a[i*4+0]='1';a[i*4+1]='1';a[i*4+2]='1';a[i*4+3]='0';}
        else if(b[i]=='F'){
            a[i*4+0]='1';a[i*4+1]='1';a[i*4+2]='1';a[i*4+3]='1';}
    }
    return a;
}


char* Binary(char* value);

class register_bus{
public:
    int sym;
    char ch[17];
    string name;
    void get_color(int color){sym=color;}
    register_bus(){}
    register_bus(string Name){sym=0;strcpy(ch,"0000000000000000");name=Name;}
    //register_bus(string NAME){sym=0;strcpy(ch,"0000000000000000");name=NAME;}
    void get_ch(char* n){strcpy(ch,n);}
    void re_zero(int n){sym=0;strcpy(ch,"0000000000000000");}
    void re_zero(){sym=0;}
    void change_ft(){sym=1;cout<<"    "<<name<<"("<<sy_binary_to_hex(ch)<<")"<<endl;rear=insert(rear,name,sy_binary_to_hex(ch),sym); }//设置FT时的信号
    void change_st(){sym=2;cout<<"    "<<name<<"("<<sy_binary_to_hex(ch)<<")"<<endl;rear=insert(rear,name,sy_binary_to_hex(ch),sym); }//设置ST时的信号
    void change_dt(){sym=3;cout<<"    "<<name<<"("<<sy_binary_to_hex(ch)<<")"<<endl;rear=insert(rear,name,sy_binary_to_hex(ch),sym); }//设置DT时的信号
    void change_et(){sym=4;cout<<"    "<<name<<"("<<sy_binary_to_hex(ch)<<")"<<endl;rear=insert(rear,name,sy_binary_to_hex(ch),sym);}//设置ET时的信号
    virtual char* show_ch(){return ch;}//返回值
    register_bus& operator=(register_bus& p){strcpy(ch,p.show_ch());sym=p.sym; cout<<"    "<<name<<"("<<sy_binary_to_hex(ch)<<")"<<endl;rear=insert(rear,name,sy_binary_to_hex(ch),sym);return *this;}//负责传值
    register_bus& operator+(int n){sy_inc(ch);return *this;}//用于2进制 +1的计算比如可以PC=PC+1;
    register_bus& operator-(int n){sy_dec(ch);return *this;} //自减操作
    int color(){return sym;}

};

class memory:public register_bus{
private:
    struct node{//建立地址和值得联系，用一个数据1");结构表示
        char address[17];
        char ch[17];
    }*Node;
public:
    node* MM;
    memory(string Name){//对MM进行初始化，实现赋予值
        MM=new node [7];
        strcpy(MM[0].address,"000000000000000");
        strcpy(MM[1].address,"0000000000000001");
        strcpy(MM[2].address,"0000000000000010");
        //strcpy(MM[3].address,"1010000000000000");
        //strcpy(MM[4].address,"100010000000000");
        strcpy(MM[0].ch,"000000000000000");
        strcpy(MM[1].ch,"000000000000000");
        strcpy(MM[2].ch,"000000000000010");
        //strcpy(MM[3].ch,"000000000001111");
        //strcpy(MM[4].ch,"000000000011111");
        name=Name;
        strcpy(ch,"0000000000000000");
    }
    ~memory(){delete [] MM;}
    memory& operator=(register_bus& p){//暂时不考虑找不到,
        strcpy(ch,p.show_ch());
        sym=p.sym;
        rear=insert(rear,name,sy_binary_to_hex(ch),sym);
        return *this;
    }
    memory& operator=(char* a){
        for(int i=0;i<7;i++)
            if(strcmp(ch,MM[i].address)==0){
                strcpy(MM[i].ch,a);
            }
        change_et();
        rear=insert(rear,name,sy_binary_to_hex(ch),sym);
        return* this;
    }
    char* show_ch(){
        char* b=new char[17];
        for(int i=0;i<7;i++){
            if(strcmp(MM[i].address,ch)==0){
                strcpy(b,MM[i].ch);
                return b;
            }
        }
        delete b;
        return ch;
    }
    void get_memory(char* a,char* b,int i){cout<<i<<endl;strcpy(MM[3+i].address,a);strcpy(MM[3+i].ch,b);}
};

class alu:public register_bus{
public:
    alu(string Name){name=Name;strcpy(ch,"0000000000000000");}
    alu& operator=(register_bus& r2){strcpy(ch,r2.show_ch());sym=r2.sym;rear=insert(rear,name,sy_binary_to_hex(ch),sym);return* this;}
    friend alu& operator+(alu& r1,register_bus& r2){sy_add(r1.ch,r2.show_ch());return r1;}//2个寄存器之间的加，用于ALU
    friend alu& operator-(alu& r1,register_bus& r2){sy_sub(r1.ch,r2.show_ch());return r1;}//2个寄存器之间的减，用于ALU
    friend alu& AND(alu& r1, register_bus& r2){sy_and(r1.ch,r2.show_ch());return r1;}//2个寄存器之间的与运算，用于ALU
    friend alu& OR(alu& r1, register_bus& r2){sy_or(r1.ch,r2.show_ch());return r1;}//2个寄存器之间的或运算，用于ALU
    friend alu& EOR(alu& r1, register_bus& r2){sy_eor(r1.ch,r2.show_ch());return r1;}//2个寄存器之间的异或运算，用于ALU
    alu& COM(){sy_com(ch);cout<<sy_binary_to_hex(ch)<<endl;return* this;}
    alu& NEG(){sy_neg(ch);return* this;}
    alu& INC(){sy_inc(ch);return* this;}
    alu& DEC(){sy_dec(ch);return* this;}
};

class Shifter:public register_bus{
public:
    Shifter(string Name){name=Name;strcpy(ch,"0000000000000000");}
    Shifter& operator=(alu& r1){strcpy(ch,r1.show_ch());sym=r1.sym;rear=insert(rear,name,sy_binary_to_hex(ch),sym);return* this;}
    Shifter& SL(){sy_sl(ch);return* this;}
    Shifter& SR(){sy_sr(ch);return* this;}
};

register_bus innerbus("innerbus");//内总线;
register_bus A("A"),B("B");
Shifter shifter("shifter");
register_bus R0("R0"),R1("R1"),R2,R3;
register_bus C("C"),D("D");
register_bus MAR("MAR"),MDR("MDR");
register_bus PC("PC"),IR("IR"),SP("SP"),PSW("PSW");
register_bus databus("databus"),addressbus("addressbus"),controlbus("controlbus");
memory M("M");//主存
alu ALU("ALU");

void all_zero(){//不含参数，只有信号变为0
    innerbus.re_zero();
    A.re_zero();
    B.re_zero();
    ALU.re_zero();
    shifter.re_zero();
    R0.re_zero();
    R1.re_zero();
    R3.re_zero();
    C.re_zero();
    D.re_zero();
    MAR.re_zero();
    MDR.re_zero();
    M.re_zero();
    PC.re_zero();
    IR.re_zero();
    SP.re_zero();
    PSW.re_zero();
    databus.re_zero();
    addressbus.re_zero();
    controlbus.re_zero();
}

void all_zero(int n){//包含参数，值和信号全部归0
    innerbus.re_zero(n);
    A.re_zero(n);
    B.re_zero(n);
    ALU.re_zero(n);
    shifter.re_zero(n);
    R0.re_zero(n);
    R1.re_zero(n);
    R3.re_zero(n);
    C.re_zero(n);
    D.re_zero(n);
    MAR.re_zero(n);
    MDR.re_zero(n);
    M.re_zero(n);
    PC.re_zero(n);
    IR.re_zero(n);
    SP.re_zero(n);
    PSW.re_zero(n);
    databus.re_zero(n);
    addressbus.re_zero(n);
    controlbus.re_zero(n);
}

class R{//声明父传址方式，让传址方式继承，方便调用
private:
    int register_address;
public:
    virtual void ST(){}
    virtual void DT_MOV(){}
    virtual void DT_DOUBLE_SINGLE(string index){}
    virtual int ifr(){return 0;}
};


class R_0:public R{
public:
    int ifr(){return 0;}
};

class R_1:public R{//(R0)取址方式
public:
    int ifr(){return 1;}//返回是否是寄存器寻址，只有第一个是寄存器寻址，是就返回1；
    void ST(){
        // rear=insert(rear,"STO:R0-MAR");
        rear=insert(rear,"STO:R0-MAR");
        cout<<"_________________________________________________"<<endl;
        R0.change_st();
        innerbus=R0;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);//全部清O
        cout<<"_________________________________________________"<<endl;
        //rear=insert(rear,"ST1:M->MDR->C");
        rear=insert(rear,"ST1:M->MDR->C");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=MAR;
        M.change_st();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        C=ALU;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    void DT_MOV(){
        //cout<<"DT0:"<<"R1->MAR"<<endl;
        rear=insert(rear,"DT1:R2->MAR");
        cout<<"_________________________________________________"<<endl;
        R1.change_dt();

        innerbus=R1;

        A=innerbus;

        ALU=A;

        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=MAR;
    }
    void DT_DOUBLE_SINGLE(string index){
        //cout<<"DT0:"<<"R1->MAR"<<endl;
        rear=insert(rear,"DT0:R1->MAR");
        cout<<"_________________________________________________"<<endl;
        R1.change_dt();
        innerbus=R1;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter ;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT1:"<<"M->MAR->D"<<endl;
        rear=insert(rear,"DT1:M->MAR->D");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=MAR;
        M.change_dt();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        D=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    void ST_JSR()
    {
        //cout<<"ST0:R0->MAR"<<endl;
        rear=insert(rear,"ST0:R0->MAR");
        cout<<"_________________________________________________"<<endl;
        R0.change_st();
        innerbus=R0;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        cout<<"_________________________________________________"<<endl;
        rear=insert(rear);
        //cout<<"ST1:M->MDR->C"<<endl;
        rear=insert(rear,"ST1:M->MDR->C");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=MAR;
        M.change_st();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        C=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
};

class R_2:public R{//-(R0)
public:
    int ifr(){return 2;}
    void ST(){
        //cout<<"ST0:"<<"R0-1->RO,MAR"<<endl;
        rear=insert(rear,"ST0:R0-1->R0,MAR");
        cout<<"_________________________________________________"<<endl;
        R0.change_st();
        innerbus=R0;
        A=innerbus;
        ALU=innerbus;
        ALU=ALU-1;
        shifter=ALU;
        innerbus=shifter;
        MAR=innerbus;
        PSW=innerbus;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //	cout<<"ST1:"<<"M->MDR->C"<<endl;
        rear=insert(rear,"ST1:M->MDR->C");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=MAR;
        M.change_st();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        //innerbus=shifter;
        C=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    void DT_MOV(){
        cout<<"DT0:"<<"R1-1->R1,MAR"<<endl;
        rear=insert(rear,"DT0:R1-1->R1,MAR");
        cout<<"_________________________________________________"<<endl;
        R1.change_dt();
        innerbus=R1;
        B=innerbus;
        ALU=innerbus;
        ALU=ALU-1;
        shifter=ALU;
        R1=shifter;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=MAR;
    }
    void DT_DOUBLE_SINGLE(string index){
        cout<<"DT0:"<<"R1-1->R1,MAR"<<endl;
        rear=insert(rear,"DT0:R1-1->R1,MAR");
        cout<<"_________________________________________________"<<endl;
        R1.change_dt();
        innerbus=R1;
        A=innerbus;
        innerbus=A;
        ALU=innerbus;
        ALU=ALU-1;
        shifter=ALU;
        R0=shifter;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT1:"<<"M->MDR->D"<<endl;
        rear=insert(rear,"DT1:M->MDR->D");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=MAR;
        M.change_dt();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        //innerbus=shifter;
        D=innerbus;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
};

class R_3:public R{//(R0)+
public:
    int ifr(){return 3;}
    void ST(){
        //cout<<"ST0:"<<"R0->MAR"<<endl;
        rear=insert(rear,"ST0:R0->MAR");
        cout<<"_________________________________________________"<<endl;
        R0.change_st();
        innerbus=R0;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ST1:"<<"M->MDR->C"<<endl;
        rear=insert(rear,"ST1:M->MDR->C");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=MAR;
        M.change_st();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        C=shifter;
        cout<<"_________________________________________________"<<endl;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ST2:"<<"R0+1->R0"<<endl;
        rear=insert(rear,"ST2:R0+1->R0");
        R0.change_st();
        innerbus=R0;
        A=innerbus;
        ALU=A;
        ALU=ALU+1;
        shifter=ALU;
        R0=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    };
    void DT_MOV(){
        //cout<<"DT0:"<<"R1->MAR"<<endl;
        rear=insert(rear,"DT0:R1->MAR");
        cout<<"_________________________________________________"<<endl;
        R1.change_dt();
        innerbus=R1;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        cout<<"_________________________________________________"<<endl;
        M=addressbus;
        //cout<<"DT1:"<<"R1+1->R1"<<endl;
        rear=insert(rear,"DT1:R1+1->R1");
        R1.change_dt();
        innerbus=R1;
        A=innerbus;
        ALU=A;
        ALU=ALU+1;
        shifter=ALU;
        R1=ALU;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    void DT_DOUBLE_SINGLE(string index){
        //cout<<"DT0:"<<"R1->MAR"<<endl;
        rear=insert(rear,"DT0:R1->MAR");
        cout<<"_________________________________________________"<<endl;
        R1.change_dt();
        innerbus=R1;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT1:"<<"M->MDR->D"<<endl;
        rear=insert(rear,"DT1:M->MDR->D");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=MAR;
        M.change_dt();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        D=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT2:"<<"R1+1->R1"<<endl;
        rear=insert(rear,"DT1:R1+1->R1");
        cout<<"_________________________________________________"<<endl;
        R1.change_dt();
        A=innerbus;
        ALU=A;
        ALU=ALU+1;
        shifter=ALU;
        R1=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    void ST_JSR()
    {
        //cout<<"ST0:R0->MAR"<<endl;
        rear=insert(rear,"ST0:R0->MAR");
        cout<<"_________________________________________________"<<endl;
        R0.change_dt();
        innerbus=R0;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ST1:"<<"M->MDR->C"<<endl;
        rear=insert(rear,"ST1:M->MDR->C");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=MAR;
        M.change_dt();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        C=shifter;
        cout<<"_________________________________________________"<<endl;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ST2:R0+1->R0"<<endl;
        rear=insert(rear,"ST2:R0+1->R0");
        R0.change_et();
        innerbus=R0;
        A=innerbus;
        ALU=A;
        ALU=ALU+1;
        shifter=ALU;
        R0=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
};

class R_4:public R{  //@(R)+ , @(PC)+
public:
    int ifr () { return 4; }//返回是否是寄存器寻址，只有第一个是寄存器寻址，就返回1；
    void ST()  //取源操作数
    {
        //cout<<"ST0:"<<"R0->MAR"<<endl;
        rear=insert(rear,"ST0:R0->MAR");
        cout<<"_________________________________________________"<<endl;
        R0.change_st();
        innerbus=R0;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ST1:"<<"M->MDR->C"<<endl;
        rear=insert(rear,"ST1:M->MDR->C");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=addressbus;
        M.change_st();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        C=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ST2"<<"R0+1->R0"<<endl;
        rear=insert(rear,"ST2:R0+1->R0");
        cout<<"_________________________________________________"<<endl;
        R0.change_st();
        innerbus=R0;
        A=innerbus;
        ALU=A;
        ALU=ALU+1;
        shifter=ALU;
        R0=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ST3:"<<"C->MAR"<<endl;
        rear=insert(rear,"ST3:C->MAR");
        cout<<"_________________________________________________"<<endl;
        C.change_st();
        innerbus=C;
        A=C;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ST4:"<<"M->MDR->C"<<endl;
        rear=insert(rear,"ST4:M->MDR->C");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=addressbus;
        M.change_st();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        C=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    void DT_MOV()  //取目的操作数。MOV指令
    {
        //cout<<"DT0:"<<"R1->MAR"<<endl;
        rear=insert(rear,"DT0:R1->MAR");
        cout<<"_________________________________________________"<<endl;
        R1.change_dt();
        innerbus=R1;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        addressbus=MAR;
        M=MAR;
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT1:"<<"R1+1->R1"<<endl;
        rear=insert(rear,"DT1:R1+1->R1");
        cout<<"_________________________________________________"<<endl;
        R1.change_dt();
        innerbus=R1;
        A=innerbus;
        ALU=A;
        ALU=ALU+1;
        shifter=ALU;
        R1=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT2:"<<"M->MDR->MAR"<<endl;//?????????
        rear=insert(rear,"DT2:M->MDR->MAR");
        cout<<"_________________________________________________"<<endl;
        M.change_dt();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    void DT_DOUBLE_SINGLE(string index){  //取目的操作数。 双操作数和单操作数指令
        //cout<<"DT0:"<<"R1->MAR"<<endl;
        rear=insert(rear,"DT1:R1->MAR");
        cout<<"_________________________________________________"<<endl;
        R1.change_dt();
        innerbus=R1;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT1:"<<"M->MDR->D"<<endl;
        rear=insert(rear,"DT1:M->MDR->D");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=addressbus;
        M.change_dt();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        D=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT2:"<<"R1+1->R1"<<endl;
        rear=insert(rear,"DT2:R1+1->R1");
        cout<<"_________________________________________________"<<endl;
        R1.change_dt();
        innerbus=R1;
        A=innerbus;
        ALU=A;
        ALU=ALU+1;
        shifter=ALU;
        R1=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT3:"<<"D->MAR"<<endl;
        rear=insert(rear,"DT3:D->MAR");
        cout<<"_________________________________________________"<<endl;
        D.change_dt();
        innerbus=D;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT4:"<<"M->MDR->D"<<endl;
        rear=insert(rear,"DT4:M->MDR->D");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=addressbus;
        M.change_dt();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        D=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
};

class R_5: public R{ //X(R)  X(PC)
public:
    int ifr(){return 5;}//返回是否是寄存器寻址，只有第一个是寄存器寻址，是就返回1；
    void ST() //取源操作数
    {
        //cout<<"ST0:"<<"PC->MAR"<<endl;
        rear=insert(rear,"ST0:PC->MAR");
        cout<<"_________________________________________________"<<endl;
        PC.change_st();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ST1:"<<"M->MDR->C"<<endl;
        rear=insert(rear,"ST1:M->MDR->C");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=addressbus;
        M.change_st();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        C=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ST2:"<<"PC+1->PC"<<endl;
        rear=insert(rear,"ST2:PC+1->PC");
        cout<<"_________________________________________________"<<endl;
        PC.change_st();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        ALU=ALU+1;
        shifter=ALU;
        PC=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ST3:"<<"C+R0->MAR"<<endl;
        rear=insert(rear,"ST3:C+R0->MAR");
        cout<<"_________________________________________________"<<endl;
        C.change_st();
        innerbus=C;
        A=innerbus;
        ALU=A;
        ////////////////
        innerbus=R0;
        B=innerbus;
        //ALU=A;
        ALU=ALU+B;   //重载+
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ST4:"<<"M->MDR->C"<<endl;
        rear=insert(rear,"ST4:M->MDR->C");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=addressbus;
        M.change_st();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        C=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    void DT_MOV()  //取目的操作数。。MOV指令
    {
        //cout<<"DT0:"<<"PC->MAR"<<endl;
        rear=insert(rear,"DT0:PC->MAR");
        cout<<"_________________________________________________"<<endl;
        PC.change_dt();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT1:"<<"PC+1->PC"<<endl;
        rear=insert(rear,"DT1:PC+1->PC");
        cout<<"_________________________________________________"<<endl;
        PC.change_dt();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        ALU=ALU+1;
        shifter=ALU;
        PC=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT2:"<<"M->MDR->D"<<endl;
        rear=insert(rear,"DT2:M->MDR->D");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=addressbus;
        M.change_dt();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        D=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT3:"<<"D+R1->MAR"<<endl;
        rear=insert(rear,"DT3:D+R1->MAR");
        cout<<"_________________________________________________"<<endl;
        D.change_dt();
        innerbus=D;
        A=innerbus;
        ALU=A;
        innerbus=R1;
        B=innerbus;
        //ALU=A;
        ALU=ALU+B;   //重载+
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        addressbus=MAR;
        M=addressbus;
        cout<<"_________________________________________________"<<endl;
    }
    void DT_DOUBLE_SINGLE(string index){  //取目的操作数。双操作数和单操作数指令
        //cout<<"DT0:"<<"PC->MAR"<<endl;
        rear=insert(rear,"DT1:PC->MAR");
        cout<<"_________________________________________________"<<endl;
        PC.change_dt();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT1:"<<"M->MDR->D"<<endl;
        rear=insert(rear,"DT1:M->MDR->D");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=MAR;
        M.change_dt();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        D=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT2:"<<"PC+1->PC"<<endl;
        rear=insert(rear,"DT1:PC+1->PC");
        cout<<"_________________________________________________"<<endl;
        PC.change_dt();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        ALU=ALU+1;
        shifter=ALU;
        PC=ALU;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT3:"<<"D+R1->MAR"<<endl;
        rear=insert(rear,"DT3:D+R1->MAR");
        cout<<"_________________________________________________"<<endl;
        D.change_dt();
        innerbus=D;
        A=innerbus;
        ALU=A;
        innerbus=R1;
        B=innerbus;
        //ALU=A;
        ALU=ALU+B;   //重载+
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"DT4:"<<"M->MDR->D"<<endl;
        rear=insert(rear,"DT4::M->MDR->D");
        cout<<"_________________________________________________"<<endl;
        addressbus=MAR;
        M=addressbus;
        M.change_dt();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        D=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
};

class pc:public R{
public:
    int ifr(){return 6;}//如果是PC方式，返回6
};
class not_pc:public R{//如果不是PC方式，返回7 结合书看
public:
    int ifr(){return 7;}
};
class skp:public R{//SKP方式
    int ifr(){return 8;}
};

void et_mov(R& r1,R& r2){
    if(r1.ifr()==0&&r2.ifr()==0)//寄存器寻址和寄存器寻址的方式
    {
        //cout<<"ET0:"<<"R0->R1"<<endl;
        rear=insert(rear,"ET0:R0->R1");
        cout<<"_________________________________________________"<<endl;
        R0.change_et();
        innerbus=R0;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        R1=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET1:"<<"PC->MAR"<<endl;
        rear=insert(rear,"ET1:PC->MAR");
        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<binary_to_hex(R1.show_ch())<<endl;
    }
    else if(r1.ifr()!=0&&r2.ifr()==0){//寄存器寻址和非寄存器寻址的方式
        //cout<<"ET0:"<<"R0->MDR"<<endl;
        rear=insert(rear,"ET0:R0->MAR");
        cout<<"_________________________________________________"<<endl;
        R0.change_et();
        innerbus=R0;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MDR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET1:"<<"MDR->M"<<endl;
        rear=insert(rear,"ET1:MDR->M");
        cout<<"_________________________________________________"<<endl;
        MDR.change_et();
        databus=MDR;
        M=databus.show_ch();////////////
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET2:"<<"PC->MAR"<<endl;
        rear=insert(rear,"ET2:PC->MAR");
        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<binary_to_hex(M.show_ch())<<endl;
    }
    else if(r1.ifr()==0&&r2.ifr()!=0){//非寄存器寻址方式和寄存器寻址方式
        //cout<<"ET0:"<<"C->R1"<<endl;
        rear=insert(rear,"ET1:C->R1");
        cout<<"_________________________________________________"<<endl;
        C.change_et();
        innerbus=C;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        R1=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET1:"<<"PC->MAR"<<endl;
        rear=insert(rear,"ET1:PC->MAR");
        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<binary_to_hex(R1.show_ch())<<endl;
    }
    else if(r1.ifr()!=0&&r2.ifr()!=0){
        //cout<<"ET0:"<<"C->MDR"<<endl;
        rear=insert(rear,"ET0:C->MDR");
        cout<<"_________________________________________________"<<endl;
        C.change_et();
        innerbus=C;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MDR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET1:"<<"MDR->M"<<endl;
        rear=insert(rear,"ET1:MDR->M");
        cout<<"_________________________________________________"<<endl;
        MDR.change_et();
        databus=MDR;
        M=databus.show_ch();
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET2:"<<"PC->MAR"<<endl;
        rear=insert(rear,"ET2:PC->MAR");
        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;

    }
}

void et_double(int q,int w,string index){//
    if(q==0&&w==0){
        cout<<"ET0:";
        if(index=="ADD"){ cout<<"R0+R1->R1"<<endl;rear=insert(rear,"ET0:R0+R1->R1");cout<<"_________________________________________________"<<endl;R0.change_et();databus=R0;A=databus;R1.change_et();databus=R1;B=databus;ALU=A;ALU=ALU+B;}
        else if(index=="SUB"){ cout<<"R0-R1->R1"<<endl;rear=insert(rear,"ET0:R0-R1->R1");cout<<"_________________________________________________"<<endl;R0.change_et();databus=R0;A=databus;R1.change_et();databus=R1;B=databus;ALU=A;ALU=ALU-B;}
        else if(index=="AND"){ cout<<"R0 AND R1->R1"<<endl;rear=insert(rear,"ET0:R0 AND R1->R1");cout<<"_________________________________________________"<<endl;R0.change_et();databus=R0;A=databus;R1.change_et();databus=R1;B=databus;ALU=A;ALU=AND(ALU,B);}
        else if(index=="OR"){ cout<<"R0 OR R1->R1"<<endl;rear=insert(rear,"ET0:R0 OR R1->R1");cout<<"_________________________________________________"<<endl;R0.change_et();databus=R0;A=databus;R1.change_et();databus=R1;B=databus;ALU=A;ALU=OR(ALU,B);}
        else if(index=="EOR"){ cout<<"R0 EOR R1->R1"<<endl;rear=insert(rear,"ET0:R0 EOR R1->R1");cout<<"_________________________________________________"<<endl;R0.change_et();databus=R0;A=databus;R1.change_et();databus=R1;B=databus;ALU=A;ALU=EOR(ALU,B);}
        shifter=ALU;
        R1=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET1:"<<"PC->MAR"<<endl;
        rear=insert(rear,"ET1:PC->MAR");
        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    else if(q==0&&w!=0){
        cout<<"ET0:";
        if(index=="ADD"){ cout<<"C+R1->R1"<<endl;rear=insert(rear,"ET0:C+R1->R1");cout<<"_________________________________________________"<<endl;C.change_et();databus=C;A=databus;R1.change_et();databus=R1;B=databus;ALU=A;ALU=ALU+B;}
        else if(index=="SUB"){ cout<<"C-R1->R1"<<endl;rear=insert(rear,"ET0:C-R1->R1");cout<<"_________________________________________________"<<endl;C.change_et();databus=C;A=databus;R1.change_et();databus=R1;B=databus;ALU=A;ALU=ALU-B;}
        else if(index=="AND"){ cout<<"C AND R1->R1"<<endl;rear=insert(rear,"ET0:C AND R1->R1");cout<<"_________________________________________________"<<endl;C.change_et();databus=C;A=databus;R1.change_et();databus=R1;B=databus;ALU=A;ALU=AND(ALU,B);}
        else if(index=="RO"){ cout<<"C OR R1->R1"<<endl;rear=insert(rear,"ET0:C OR R1->R1");cout<<"_________________________________________________"<<endl;C.change_et();databus=C;A=databus;R1.change_et();databus=R1;B=databus;ALU=A;ALU=OR(ALU,B);}
        else if(index=="EOR"){ cout<<"C EOR R1->R1"<<endl;rear=insert(rear,"ET0:C EOR R1->R1");cout<<"_________________________________________________"<<endl;C.change_et();databus=C;A=databus;R1.change_et();databus=R1;B=databus;ALU=A;ALU=EOR(ALU,B);}
        shifter=ALU;
        R1=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET1:"<<"PC->MAR"<<endl;
        rear=insert(rear,"ET1:PC->MAR");
        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    else  if(q!=0&&w==0){
        cout<<"ET0:";
        if(index=="ADD"){ cout<<"R0+D->MDR"<<endl;rear=insert(rear,"ET0:R0+D->R1");cout<<"_________________________________________________"<<endl;R0.change_et();databus=R0;A=databus;D.change_et();databus=D;B=databus;ALU=A;ALU=ALU+B;}
        else if(index=="SUB"){ cout<<"R0-D->MDR"<<endl;rear=insert(rear,"ET0:R0-D->R1");cout<<"_________________________________________________"<<endl;R0.change_et();databus=R0;A=databus;D.change_et();databus=D;B=databus;ALU=A;ALU=ALU-B;}
        else if(index=="AND"){ cout<<"R0 AND D->MDR"<<endl;rear=insert(rear,"ET0:R0 AND D->R1");cout<<"_________________________________________________"<<endl;R0.change_et();databus=R0;A=databus;D.change_et();databus=D;B=databus;ALU=A;ALU=AND(ALU,B);}
        else if(index=="OR"){ cout<<"R0 OR D->MDR"<<endl;rear=insert(rear,"ET0:R0 OR D->R1");cout<<"_________________________________________________"<<endl;R0.change_et();databus=R0;A=databus;D.change_et();databus=D;B=databus;ALU=A;ALU=OR(ALU,B);}
        else if(index=="EOR"){ cout<<"R0 EOR D->MDR"<<endl;rear=insert(rear,"ET0:R0 EOR D->R1");cout<<"_________________________________________________"<<endl;R0.change_et();databus=R0;A=databus;D.change_et();databus=D;B=databus;ALU=A;ALU=EOR(ALU,B);}
        shifter=ALU;
        MDR=shifter;
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET1:"<<"MDR->M"<<endl;
        rear=insert(rear,"ET1;MDR->M");
        cout<<"_________________________________________________"<<endl;
        MDR.change_et();
        databus=MDR;
        M=databus.show_ch();
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET2:"<<"PC->MAR"<<endl;
        rear=insert(rear,"ET2:PC-<MAR");
        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    else if(q!=0&&w!=0){
        cout<<"ET0:";
        if(index=="ADD"){ cout<<"C+D->MDR"<<endl;rear=insert(rear,"ET0:C+D->MDR");cout<<"_________________________________________________"<<endl;C.change_et();databus=C;A=databus;D.change_et();databus=D;B=databus;ALU=A;ALU=ALU+B;}
        else if(index=="SUB"){ cout<<"C-D->MDR"<<endl;rear=insert(rear,"ET0:C-D->MDR");cout<<"_________________________________________________"<<endl;C.change_et();databus=C;A=databus;D.change_et();databus=D;B=databus;ALU=A;ALU=ALU-B;}
        else if(index=="AND"){ cout<<"C AND D->MDR"<<endl;rear=insert(rear,"ET0:C AND D->MDR");cout<<"_________________________________________________"<<endl;C.change_et();databus=C;A=databus;D.change_et();databus=D;B=databus;ALU=A;ALU=AND(ALU,B);}
        else if(index=="OR"){ cout<<"C OR D->MDR"<<endl;rear=insert(rear,"ET0:C OR D->MDR");cout<<"_________________________________________________"<<endl;C.change_et();databus=C;A=databus;D.change_et();databus=D;B=databus;ALU=A;ALU=OR(ALU,B);}
        else if(index=="EOR"){ cout<<"C EOR D->MDR"<<endl;rear=insert(rear,"ET0:C EOR D->MDR");cout<<"_________________________________________________"<<endl;C.change_et();databus=C;A=databus;D.change_et();databus=D;B=databus;ALU=A;ALU=EOR(ALU,B);}
        shifter=ALU;
        MDR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET1:"<<"MDR->M"<<endl;
        rear=insert(rear,"ET1:MDR->M");
        cout<<"_________________________________________________"<<endl;
        MDR.change_et();
        databus=MDR;
        M=databus.show_ch();
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET2:"<<"PC->MAR"<<endl;
        rear=insert(rear,"ET2:PC->MAR");
        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
}

void et_single(R& r,string index){
    if(r.ifr()==0){
        cout<<"ET0:";

        if(index=="COM"){cout<<"COM R1->R1"<<endl;rear=insert(rear,"ET0:COM R1->R1");R1.change_et();innerbus=R1;A=innerbus;ALU=A;cout<<"_________________________________________________"<<endl; shifter=ALU.COM(); }///
        else if(index=="NEG"){cout<<"NEG R1->R1"<<endl;rear=insert(rear,"ET0:NEG R1->R1");R1.change_et();innerbus=R1;A=innerbus;ALU=A;cout<<"_________________________________________________"<<endl; shifter=ALU.NEG(); }//////
        else if(index=="INC"){cout<<"INC R1->R1"<<endl;rear=insert(rear,"ET0:INC R1->R1");R1.change_et();innerbus=R1;A=innerbus;ALU=A;cout<<"_________________________________________________"<<endl;shifter=ALU.INC(); }/////
        else if(index=="DEC"){cout<<"DEC R1->R1"<<endl;rear=insert(rear,"ET0:DEC R1->R1");R1.change_et();innerbus=R1;A=innerbus;ALU=A; cout<<"_________________________________________________"<<endl;shifter=ALU.DEC(); }//////
        else if(index=="SL"){cout<<"SL R1->R1"<<endl;rear=insert(rear,"ET0:SL R1->R1");R1.change_et();innerbus=R1;A=innerbus;ALU=A;cout<<"_________________________________________________"<<endl; shifter=ALU;shifter=shifter.SL(); }///
        else if(index=="SR"){cout<<"SR R1->R1"<<endl;rear=insert(rear,"ET0:SR R1->R1");R1.change_et();innerbus=R1;A=innerbus;ALU=A;cout<<"_________________________________________________"<<endl; shifter=ALU;shifter=shifter.SR();}////////
        R0=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET1:"<<"PC->MAR"<<endl;
        rear=insert(rear,"ET1:PC->MAR");
        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    else{
        cout<<"ET0:";

        if(index=="COM"){cout<<"COM D->R0"<<endl;rear=insert(rear,"ET0:COM D->MDR"); D.change_et();innerbus=D;A=innerbus;ALU=A;cout<<"_________________________________________________"<<endl; shifter=ALU.COM(); }
        else if(index=="NEG"){cout<<"NEG D->R0"<<endl; rear=insert(rear,"ET0:NGE D->MDR");D.change_et();innerbus=D;A=innerbus;ALU=A; cout<<"_________________________________________________"<<endl;shifter=ALU.NEG(); }
        else if(index=="INC"){cout<<"INC D->R0"<<endl; rear=insert(rear,"ET1:INC D->MDR"); D.change_et();innerbus=D;A=innerbus;ALU=A;cout<<"_________________________________________________"<<endl;shifter=ALU.INC(); }
        else if(index=="DEC"){cout<<"DEC D->R0"<<endl; rear=insert(rear,"ET1:DEC D->MDR");D.change_et();innerbus=D;A=innerbus;ALU=A;cout<<"_________________________________________________"<<endl; shifter=ALU.DEC(); }
        else if(index=="SL"){cout<<"SL D->R0"<<endl;rear=insert(rear,"ET1:SL D->MDR"); D.change_et();innerbus=D;A=innerbus;ALU=A; cout<<"_________________________________________________"<<endl;shifter=shifter.SL(); }
        else if(index=="SR"){cout<<"SR D->R0"<<endl; rear=insert(rear,"ET1:SR D->MDR");D.change_et();innerbus=D;A=innerbus;ALU=A;cout<<"_________________________________________________"<<endl; shifter=shifter.SR(); }
        MDR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET1:"<<"MDR->M"<<endl;
        rear=insert(rear,"ET1:MDR->M");
        cout<<"_________________________________________________"<<endl;
        MDR.change_et();
        databus=MDR;
        M=databus.show_ch();
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
}

void et_jmp(R& r){
    if(r.ifr()==6)
    {
        //cout<<"ET0:"<<"PC+1->PC,MAR"<<endl;
        rear=insert(rear,"ET0:PC+1->PC");
        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        PC=PC+1;
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        PC=shifter;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    else if(r.ifr()==7)
    {
        // cout<<"ET0:"<<"PC->MAR"<<endl;
        rear=insert(rear,"ET0:PC->MAR");
        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    else if(r.ifr()==8)
    {
        // cout<<"ET0:PC+1->PC,MAR"<<endl;
        rear=insert(rear,"ET0:PC+1->PC,MAR");
        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        ALU=ALU+1;
        shifter=ALU;
        PC=shifter;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    else if(r.ifr()==0)
    {
        //cout<<"ET0:R0->PC,MAR"<<endl;
        rear=insert(rear,"ET0:R0->PC,MAR");
        cout<<"_________________________________________________"<<endl;
        R0.change_et();
        innerbus=R0;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        PC=shifter;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    else if(r.ifr()==1)
    {
        //cout<<"ET0:R0->MAR"<<endl;
        rear=insert(rear,"ET0:R0->MAR");
        cout<<"_________________________________________________"<<endl;
        R0.change_et();
        innerbus=R0;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET1:M->MDR->PC,MAR"<<endl;
        rear=insert(rear,"ET1:M->MDR->PC,MAR");
        cout<<"_________________________________________________"<<endl;
        M.change_st();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        PC=shifter;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    else if(r.ifr()==3)
    {
        // cout<<"ET0:R0->MAR"<<endl;
        rear=insert(rear,"ET0:R0->MAR");

        cout<<"_________________________________________________"<<endl;
        R0.change_et();
        innerbus=R0;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        // cout<<"ET1:M->MDR->PC,MAR"<<endl;
        rear=insert(rear,"ET1:M->MDR->PC,MAR");
        cout<<"_________________________________________________"<<endl;
        M.change_st();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        PC=shifter;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET2:R0+1->R0"<<endl;
        rear=insert(rear,"ET2:R0+1->R0");

        cout<<"_________________________________________________"<<endl;
        R0.change_et();
        innerbus=R0;
        A=innerbus;
        ALU=A;
        ALU=ALU+1;
        shifter=ALU;
        R0=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    else if(r.ifr()==5)
    {
        // cout<<"ET0:PC->MAR"<<endl;
        rear=insert(rear,"ET0:PC->MAR");
        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=R0;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        //cout<<"ET1:M->MDR->C"<<endl;
        rear=insert(rear,"ET1:M->MDR->C");
        cout<<"_________________________________________________"<<endl;
        M.change_st();
        databus=M;
        MDR=databus;
        innerbus=MDR;
        B=innerbus;
        ALU=B;
        shifter=ALU;
        C=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        // cout<<"ET2:PC+C->PC,MAR";
        rear=insert(rear,"ET2:PC+C->PC,MAR");

        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=PC;
        A=innerbus;
        innerbus=C;
        B=innerbus;
        ALU=A;
        ALU=ALU+C;
        shifter=ALU;
        PC=shifter;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
}

void et_jsr( R & r )  //JSR的ET操作
{
    if(r.ifr()==6) //PC方式寻址
    {
        //cout<<"ET0:PC+1->PC,MAR"<<endl;
        rear=insert(rear,"ET0:PC+1->PC,MAR");

        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        ALU=ALU+1;
        shifter=ALU;
        MAR=shifter;
        PC=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    else if( r.ifr()==7 ) //非PC方式寻址
    {
        //cout<<"ET0:PC->MAR"<<endl;
        rear=insert(rear,"ET0:PC->MAR");
        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    else if( r.ifr()==0 )//寄存器寻址
    {
        //cout<<"ET0:SP-1->SP,MAR"<<endl;
        rear=insert(rear,"ET0:SP-1->SP,MAR");

        cout<<"_________________________________________________"<<endl;
        SP.change_et();
        innerbus=SP;
        A=innerbus;
        ALU=A;
        ALU=ALU-1;
        shifter=ALU;
        SP=shifter;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET1:PC->MDR"<<endl;
        rear=insert(rear,"ET1:PC->MDR");

        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MDR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET2:MDR->M"<<endl;
        rear=insert(rear,"ET2:MDR->M");
        cout<<"_________________________________________________"<<endl;
        MDR.change_et();
        databus=MDR;
        M=databus;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET3:R0->PC,MAR"<<endl;
        rear=insert(rear,"ET3:R0->PC,MAR");

        cout<<"_________________________________________________"<<endl;
        R0.change_et();
        innerbus=R0;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        PC=shifter;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
    else if( r.ifr()==1||r.ifr()==3 )//(R)寻址方式或(R)+寻址方式
    {
        //cout<<"ET0:SP-1->SP,MAR"<<endl;
        rear=insert(rear,"ET0:SP-1->SP,MAR");
        cout<<"_________________________________________________"<<endl;
        SP.change_et();
        innerbus=SP;
        A=innerbus;
        ALU=A;
        ALU=ALU-1;
        shifter=ALU;
        SP=shifter;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET1:PC->MDR"<<endl;
        rear=insert(rear,"ET1:PC->MRD");
        cout<<"_________________________________________________"<<endl;
        PC.change_et();
        innerbus=PC;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        MDR=shifter;
        rear=insert(rear);
        //cout<<"ET2:MDR->M"<<endl;
        rear=insert(rear,"ET2:MDR->M");
        cout<<"_________________________________________________"<<endl;
        MDR.change_et();
        databus=MDR;
        M=databus;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
        //cout<<"ET3:C->PC,MAR"<<endl;
        rear=insert(rear,"ET3:C->PC,MAR");

        cout<<"_________________________________________________"<<endl;
        C.change_et();
        innerbus=C;
        A=innerbus;
        ALU=A;
        shifter=ALU;
        PC=shifter;
        MAR=shifter;
        rear=insert(rear);
        cout<<"_________________________________________________"<<endl;
    }
}

//函数实现
void FT(){
    cout<<"FT0:"<<"M->IR,PC+1->PC"<<endl;
    rear=insert(rear,"FT0:M->IR,PC+1->PC");
    M.change_ft();
    databus=M;
    MDR=databus;
    innerbus=MDR;
    A=innerbus;
    ALU=A;
    shifter=ALU;
    IR=shifter;
    PC.change_ft();
    innerbus=PC;
    A=innerbus;
    ALU=A;
    ALU=ALU+1;
    shifter=ALU;
    PC=shifter;
    rear=insert(rear);
    cout<<"_________________________________________________"<<endl;
}

void MOV(R& r1,string b){

    cout<<"请输入值(用4位16进制)"<<endl;
    //    char ch1[5];
    //    char ch2[5];
    //FT();
    if(b=="R0"){
        R_0 r0;
        r0.ST();
        r1.DT_MOV();
        et_mov(r1,r0);
    }
    else if(b=="(R0)"){
        R_1 r0;
        r0.ST();
        r1.DT_MOV();
        et_mov(r1,r0);}

    else if(b=="-(R0)"){
        R_2 r0;
        r0.ST();
        r1.DT_MOV();
        et_mov(r1,r0);
    }
    else if(b=="(R0)+"){
        R_3 r0;
        r0.ST();
        r1.DT_MOV();
        et_mov(r1,r0);
    }
    else if(b=="@(R0)+"){
        R_4 r0;
        r0.ST();
        r1.DT_MOV();
        et_mov(r1,r0);
    }
    else if(b=="X(R0)"){
        R_5 r0;
        r0.ST();
        r1.DT_MOV();
        et_mov(r1,r0);
    }
    //cout<<binary_to_hex(R1.show_ch())<<endl;
}
void DOUBLE_(R& r1, string index,string b){

    cout<<"请输入值(用4位16进制)"<<endl;
    //    char ch1[5];
    //    char ch2[5];
    //FT();
    int q=r1.ifr(),w;
    if(b=="R0"){
        R_0 r0;
        r0.ST();
        w=r0.ifr();
        r1.DT_DOUBLE_SINGLE(index);
    }
    else if(b=="(R0)"){
        R_1 r0;
        r0.ST();
        w=r0.ifr();
        r1.DT_DOUBLE_SINGLE(index);
    }
    else if(b=="-(R0)"){
        R_2 r0;
        r0.ST();
        w=r0.ifr();
        r1.DT_DOUBLE_SINGLE(index);

    }
    else if(b=="(R0)+"){
        R_3 r0;
        r0.ST();
        w=r0.ifr();
        r1.DT_DOUBLE_SINGLE(index);

    }
    else if(b=="@(R0)+"){
        R_4 r0;
        r0.ST();
        w=r0.ifr();
        r1.DT_DOUBLE_SINGLE(index);

    }
    else if(b=="X(R0)"){
        R_5 r0;
        r0.ST();
        w=r0.ifr();
        r1.DT_DOUBLE_SINGLE(index);
    }
    et_double(q,w,index);
}
void SINGLE_(R& r1,string index){
    //FT();
    r1.DT_DOUBLE_SINGLE(index);
    et_single(r1,index);
}
void JMP(R& r1){
    et_jmp(r1);
}

void program_start(string index,string r1_way,string r0_way)
{
    //    R1.get_ch(sy_hex_to_binary("3333"));
    //    R0.get_ch(sy_hex_to_binary("5555"));
    FT();
    string a=r1_way;
    if(index=="MOV"){
        if(a=="R1"){
            R_0 r1;
            MOV(r1,r0_way);
        }
        else if(a=="(R1)"){
            R_1 r1;
            MOV(r1,r0_way);
        }
        else if(a=="-(R1)"){
            R_2 r1;
            MOV(r1,r0_way);
        }
        else if(a=="(R1)+"){
            R_3 r1;
            MOV(r1,r0_way);
        }
        else if(a=="@(R1)+"){
            R_4 r1;
            MOV(r1,r0_way);
        }
        else if(a=="X(R1)"){
            R_5 r1;
            MOV(r1,r0_way);
        }
    }
    else if(index=="ADD"||index=="SUB"||index=="EOR"||index=="OR"||index=="AND"){
        if(a=="R1"){
            R_0 r1;
            DOUBLE_(r1,index,r0_way);
        }
        else if(a=="(R1)"){
            R_1 r1;
            DOUBLE_(r1,index,r0_way);
        }
        else if(a=="-(R1)"){
            R_2 r1;
            DOUBLE_(r1,index,r0_way);
        }
        else if(a=="(R1)+"){
            R_3 r1;
            DOUBLE_(r1,index,r0_way);
        }
        else if(a=="@(R1)+"){
            R_4 r1;
            DOUBLE_(r1,index,r0_way);
        }
        else if(a=="X(R1)"){
            R_5 r1;
            DOUBLE_(r1,index,r0_way);
        }
    }
    else if(index=="COM"||index=="NEG"||index=="INC"||index=="DEC"||index=="SL"||index=="SR"){
        if(a=="R1"){
            R_0 r1;
            SINGLE_(r1,index);
        }
        else if(a=="(R1)"){
            R_1 r1;
            SINGLE_(r1,index);
        }
        else if(a=="-(R1)"){
            R_2 r1;
            SINGLE_(r1,index);
        }
        else if(a=="(R1)+"){
            R_3 r1;
            SINGLE_(r1,index);
        }
        else if(a=="@(R1)+"){
            R_4 r1;
            SINGLE_(r1,index);
        }
        else if(a=="X(R1)"){
            R_5 r1;
            SINGLE_(r1,index);
        }
    }
    else if(index=="NJP"){
        //FT();
        if(a=="非PC"){
            not_pc r1;
            et_jmp(r1);
        }
        else if(a=="PC"){
            pc r1;
            et_jmp(r1);
        }
    }
    else if(index=="JP,RST"){
        //FT();
        if(a=="SKP"){
            skp  r1;
            et_jmp(r1);
        }
        else if(a=="R1"){
            R_0 r1;
            et_jmp(r1);
        }
        else if(a=="(R1)"){
            R_1 r1;
            et_jmp(r1);
        }
        else if(a=="(R1)+"){
            R_3 r1;
            et_jmp(r1);
        }
        else if(a=="X(PC)")
        {
            R_5 r1;
            et_jmp(r1);
        }
    }
    else if(index=="NJSR"){
        if(r0_way=="非PC"){
            not_pc r1;
            et_jsr(r1);
        }
        else if(r0_way=="PC"){
            pc r1;
            et_jsr(r1);
        }
    }
    else if(index=="JSR"){
        if(r0_way=="R0"){
            R_0 r1;
            et_jsr(r1);
        }
        else if(r0_way=="(R0)"){
            R_1 r1;
            r1.ST_JSR();
            et_jsr(r1);
        }
        else if(r0_way=="(R0)+"){
            R_3 r1;
            r1.ST_JSR();
            et_jsr(r1);
        }
    }
}

void Free_quene(){  //清空队列
    pointer=head;
    while(pointer!=NULL)
    {
        head=pointer->next;
        delete pointer;
        pointer=head;
    }
}


#endif
