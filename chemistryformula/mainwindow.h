#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void putwidget(QWidget *widget);
private slots:
    void showCheck();
    void showAuto();

private:
    Ui::MainWindow *ui;
    QWidget *checkPage,*autoPage;
    void delLayout();
};
#endif // MAINWINDOW_H
