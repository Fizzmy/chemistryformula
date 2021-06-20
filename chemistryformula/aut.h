#ifndef AUT_H
#define AUT_H

#include <QWidget>

namespace Ui {
class aut;
}

class aut : public QWidget
{
    Q_OBJECT

public:
    aut(QWidget *parent = nullptr);
    ~aut();

private:
    Ui::aut *ui;
    void solve(int l,int r,bool tag);
    void count(int l,int r,bool tag);
    void count2(int l,int r,bool tag);
    void print(int l,int r);
    int change(char s);
    void count2(int l,int r,bool tag,int tim);
    int n,lcm;
    char s[1010];
    std::string fin;
    int totnum,elenum;
    int pos[1010],st[1010];
    int vis[3000];

    struct frac{
        int a,b;//a分子 b分母
        int gcd(int x,int y)
        {
            if (!y) return x;
            return gcd(y,x%y);
        }
        frac operator +(frac y)//(frac x,frac y)
        {
            frac z;bool zf=0;
            z.a=a*y.b+b*y.a;
            z.b=b*y.b;
            if (z.a<0) zf=1,z.a*=-1;
            int g=gcd(z.a,z.b);
            z.a/=g,z.b/=g;
            if (zf) z.a*=-1;
            return z;
        }
        frac operator -(frac y)
        {
            frac z;bool zf=0;
            z.a=a*y.b-b*y.a;
            z.b=b*y.b;
            if (z.a<0) zf=1,z.a*=-1;
            int g=gcd(z.a,z.b);
            z.a/=g,z.b/=g;
            if (zf) z.a*=-1;
            return z;
        }
        frac operator *(frac y)
        {
            frac z;bool zf=0;
            z.a=a*y.a;
            z.b=b*y.b;
            if (z.a<0) zf=1,z.a*=-1;
            int g=gcd(z.a,z.b);
            z.a/=g,z.b/=g;
            if (zf) z.a*=-1;
            return z;
        }
        frac operator /(frac y)
        {
            frac z;bool zf=0;
            z.a=a*y.b;
            z.b=b*y.a;
            if (z.a<0) zf^=1,z.a*=-1;
            if (z.b<0) zf^=1,z.b*=-1;
            int g=gcd(z.a,z.b);
            z.a/=g,z.b/=g;
            if (zf) z.a*=-1;
            return z;
        }
        bool operator <(frac y)
        {
            if (a<0) a*=-1;
            if (y.a<0) y.a*=-1;
            return y.a*b>a*y.b;
        }
    }a[100][100],ans[100];

private slots:
    void autoFormula();
};

#endif // AUT_H
