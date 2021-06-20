#ifndef CHECK_H
#define CHECK_H

#include <QWidget>

namespace Ui {
class check;
}

class check : public QWidget
{
    Q_OBJECT

public:
    check(QWidget *parent = nullptr);
    ~check();
private slots:
    void checkFormula();
private:
    Ui::check *ui;

    int change(char c);
    void count2(int l,int r,bool tag,int tim);
    void count(int l,int r,bool tag);
    void solve(int l,int r,bool tag);
    int n;
    char s[1010];
    struct element{
        int name,num;
    }a[2][1010];
    int u[2][1010];
    int mod=211;
    int numEle[2],unum[2];
    int pos[1010],st[1010];
    int vis[2][3000];
};

#endif // CHECK_H
