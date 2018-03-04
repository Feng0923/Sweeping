#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mmap.h"
#include<message.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    mMap *maps;
    int mWidth = 20;
    int mHeight = 20;
    int offy = 15;
    int offx = 20;
    int row ;
    int column ;
    message *dialog;
    bool isNew = true;
    void showAll();
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
private slots:
    void restart(int r,int c,int m);
    void on_actionrestart_triggered();
    void on_level1_triggered();
    void on_level2_triggered();
    void on_level3_triggered();
};

#endif // MAINWINDOW_H
