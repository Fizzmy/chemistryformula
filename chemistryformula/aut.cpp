#include "aut.h"
#include "ui_aut.h"
#include<QDebug>

aut::aut(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aut)
{
    ui->setupUi(this);
    connect(ui->autoButton,SIGNAL(clicked()),this,SLOT(autoFormula()));
}

aut::~aut()
{
    delete ui;
}

int gcd(int x,int y)
{
    if (!y) return x;
    return gcd(y,x%y);
}

int aut::change(char s)
{
    if (s<='Z'&&s>='A') return s-'A';
    return s-'a'+26;
}
void aut::count2(int l,int r,bool tag,int tim)
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
                int ha;
                if (s[i+1]>='a'&&s[i+1]<='z')
                {
                    ha=change(s[i])*52+change(s[i+1]);
                    if (!vis[ha]) vis[ha]=++elenum;
                    a[vis[ha]][totnum].a=tim;
                    i+=2;
                }
                else
                {
                    ha=change(s[i]);
                    if (!vis[ha]) vis[ha]=++elenum;
                    a[vis[ha]][totnum].a=tim;
                    i++;
                }
                int pi=i,num=0;
                while (s[i]<='9'&&s[i]>='0') num=num*10+s[i]-'0',i++;
                if (pi==i) num=1;
                a[vis[ha]][totnum].a*=num;
                if (tag) a[vis[ha]][totnum].a*=-1;

            }
        }
    }
}
void aut::count(int l,int r,bool tag)
{
    int i=l,num=0;totnum++;
    while (s[i]<='9'&&s[i]>='0') num=num*10+s[i]-'0',s[i]='#',i++;
    if (l==i) num=1;
    count2(i,r,tag,1);
}
void aut::solve(int l,int r,bool tag)
{
    int pre=l;
    for (int i=l;i<=r;i++)
        if (s[i]=='+') count(pre,i-1,tag),pre=i+1;
    count(pre,r,tag);
}
void aut::print(int l,int r)
{
    int pre=l;
    for (int i=l;i<=r;i++)
        if (s[i]=='+')
        {
            totnum++;
            int val=ans[totnum].a*(lcm/ans[totnum].b);
            //if (val==0) continue;
            if (val!=1)
                fin=fin+std::to_string(val);
                //printf("%d",val);
            for (int j=pre;j<=i;j++)
                if (s[j]!='#') fin=fin+s[j];//printf("%c",s[j]);
            pre=i+1;
        }
    totnum++;
    int val=ans[totnum].a*(lcm/ans[totnum].b);
    //if (val==0) return;
    if (val!=1)
        fin=fin+std::to_string(val);
        //printf("%d",val);
    for (int j=pre;j<=r;j++)
        if (s[j]!='#') fin=fin+s[j];//printf("%c",s[j]);
}
void aut::autoFormula()
{
    QString formula=ui->formulaA->text();
    int n=formula.length();
    std::string formula2=formula.toStdString();
    bool can=1;
    for (int i=0;i<n;i++)
        s[i+1]=formula2[i];
    totnum=0;elenum=0;fin="";
    memset(vis,0,sizeof(vis));
    int cnt=0;
    for (int i=1;i<=n;i++)
    {
        if (s[i]=='(') st[++cnt]=i;
        else if (s[i]==')') pos[st[cnt--]]=i;
    }
    for (int i=1;i<=n;i++)
        if (s[i]=='=') solve(1,i-1,0),solve(i+1,n,1);
    for (int i=1;i<=elenum;i++)
        for (int j=1;j<=totnum;j++)
            a[i][j].b=1;
    for (int i=1;i<=elenum;i++) a[i][totnum].a*=-1;
    for (int i=1;i<=std::min(totnum-1,elenum);i++)
    {
        int nw=i;
        for (int j=i+1;j<=elenum;j++) if (a[nw][i]<a[j][i]) nw=j;
        for (int j=1;j<=totnum;j++) std::swap(a[nw][j],a[i][j]);
        if (a[i][i].a==0) {can=0;break;}
        for (int j=1;j<=elenum;j++)
        {
            if (j==i) continue;
            frac x=a[j][i]/a[i][i];
            for (int k=1;k<=totnum;k++)
                a[j][k]=a[j][k]-x*a[i][k];
        }
    }
    lcm=1;
    if (can==0||elenum>=totnum)
    {
        ui->statusA->setText("配平失败，请检查您输入的方程式");
    }
    else
    {
        for (int i=1;i<=std::min(totnum-1,elenum);i++)
        {
            frac x=a[i][totnum]/a[i][i];
            ans[i]=x;
            lcm=lcm*x.b/gcd(lcm,x.b);
            //qDebug()<<ans[i].a<<" "<<ans[i].b;
        }
        ans[totnum].a=1,ans[totnum].b=1;
        totnum=0;
        for (int i=1;i<=n;i++)
            if (s[i]=='=') print(1,i-1),fin=fin+"=",print(i+1,n);
        QString finstr=QString::fromStdString(fin);
        ui->statusA->setText("配平结果："+finstr);
    }
    for (int i=1;i<=elenum;i++)
        for (int j=1;j<=totnum;j++)
            a[i][j].a=a[i][j].b=0;
}
