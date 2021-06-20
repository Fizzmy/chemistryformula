#include "check.h"
#include "ui_check.h"
#include <string>
#include <QDebug>

check::check(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::check)
{
    ui->setupUi(this);
    connect(ui->checkButton,SIGNAL(clicked()),this,SLOT(checkFormula()));
}

check::~check()
{
    delete ui;
}
int check::change(char s)
{
    if (s<='Z'&&s>='A') return s-'A';
    return s-'a'+26;
}
void check::count2(int l,int r,bool tag,int tim)
{
    int i=l;
    while (i<=r)
    {
        if (s[i]=='(')
        {
            int j=pos[i]+1,num=0;
            while (s[j]<='9'&&s[j]>='0') num=num*10+s[j]-'0',j++;
            if (j==pos[i]+1) num=1;
            count2(i+1,pos[i]-1,tag,tim*num);
            i=j;
        }
        else
        {
            if (s[i]<='Z'&&s[i]>='A')
            {
                if (s[i+1]>='a'&&s[i+1]<='z')
                {
                    numEle[tag]++;
                    a[tag][numEle[tag]].name=change(s[i])*52+change(s[i+1]);
                    a[tag][numEle[tag]].num=tim;
                    i+=2;
                }
                else
                {
                    numEle[tag]++;
                    a [tag] [numEle[tag]].name=change(s[i]);
                    a [tag] [numEle[tag]].num=tim;
                    i++;
                }
                int pi=i,num=0;
                while (s[i]<='9'&&s[i]>='0') num=num*10+s[i]-'0',i++;
                if (pi==i) num=1;
                a[tag][numEle[tag]].num*=num;
            }
        }
    }
}
void check::count(int l,int r,bool tag)
{
    int i=l,num=0;
    while (s[i]<='9'&&s[i]>='0') num=num*10+s[i]-'0',i++;
    if (l==i) num=1;
    count2(i,r,tag,num);
}
void check::solve(int l,int r,bool tag)
{
    int pre=l;
    for (int i=l;i<=r;i++)
        if (s[i]=='+') count(pre,i-1,tag),pre=i+1;
    count(pre,r,tag);
}
void check::checkFormula()
{
    QString formula=ui->formula->text();
    int n=formula.length();
    std::string formula2=formula.toStdString();
    for (int i=0;i<n;i++)
        s[i+1]=formula2[i];
    numEle[0]=numEle[1]=0;int cnt=0;
    for (int i=1;i<=n;i++)
    {
        if (s[i]=='(') st[++cnt]=i;
        else if (s[i]==')') pos[st[cnt--]]=i;
    }
    for (int i=1;i<=n;i++)
        if (s[i]=='=') solve(1,i-1,0),solve(i+1,n,1);
    unum[0]=unum[1]=0;
    for (int tag=0;tag<=1;tag++)
        for (int i=1;i<=numEle[tag];i++)
        {
            if (!vis[tag][a[tag][i].name])
                u[tag][++unum[tag]]=a[tag][i].name;
            vis[tag][a[tag][i].name]+=a[tag][i].num;
        }
    bool can=1;
    if (unum[0]!=unum[1]) can=0;
    else
        for (int i=1;i<=unum[0];i++)
        {
            if (vis[0][u[0][i]]!=vis[1][u[0][i]])
            {
                can=0;break;
            }
        }
    QPalette redP,blackP;
    redP.setColor(QPalette::WindowText,Qt::red);
    blackP.setColor(QPalette::WindowText,Qt::black);
    if (can) ui->status->setText("化学方程式已配平"),ui->status->setPalette(redP);
    else ui->status->setText("化学方程式未配平"),ui->status->setPalette(blackP);
    for (int tag=0;tag<=1;tag++)
        for (int i=1;i<=unum[tag];i++)
            vis[tag][u[tag][i]]=0;
}
