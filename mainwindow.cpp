#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QPainter>
#include <qstack.h>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    maps = new mMap();
    maps->create();
    row = maps->row;
    column = maps->column;
    offy += menuBar()->height();
    setFixedSize(row*mWidth+offx*2,column*mHeight+offy+offx);
    dialog = new message(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAll()
{
    for(int i = 0;i<row;i++){
        for(int j = 0;j<column;j++){
            if(maps->map[i][j]<100){
                maps->map[i][j] += 100;
            }else if(maps->map[i][j] >=200&&maps->map[i][j]<=208){
                maps->map[i][j] -= 100;
            }else if(maps->map[i][j] == 209){
                maps->map[i][j] += 100;
            }
        }
    }
    update();
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap bmp = (":/new/prefix1/item2.bmp");
    int count = 0;
    int **map = maps->map;
    for(int i = 0;i<row;i++){
        for(int j = 0;j<column;j++){
            if(map[i][j] <10&&map[i][j]>=0){
                painter.drawPixmap(i*mWidth+offx,j*mHeight+offy,bmp,10*20,0,20,20);
            }else if(map[i][j]>=100&&map[i][j]<=108){
                painter.drawPixmap(i*mWidth+offx,j*mHeight+offy,bmp,(map[i][j]-100)*20,0,20,20);
                count++;
                if(count == (maps->sum-maps->mineNumber)){
                    if(isNew){
                        dialog->setText(tr("you win"));
                        dialog->show();
                        showAll();
                        isNew = false;
                    }
                }
            }else if(map[i][j] == 109){
                painter.drawPixmap(i*mWidth+offx,j*mHeight+offy,bmp,9*20,0,20,20);
                if(isNew){
                    dialog->setText(tr("you lose"));

                    dialog->show();
                    showAll();
                    isNew = false;
                }

            }else if(map[i][j]>=200&&map[i][j]<=209){
                painter.drawPixmap(i*mWidth+offx,j*mHeight+offy,bmp,11*20,0,20,20);
            }else if(map[i][j] == 309){
                painter.drawPixmap(i*mWidth+offx,j*mHeight+offy,bmp,12*20,0,20,20);
            }

        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPainter painter(this);
     QPixmap bmp = (":/new/prefix1/item2.bmp");
    int x = event->x()-offx;
    int y = event->y()-offy;
    int i = x/mWidth;
    int j = y/mHeight;
    int **map = maps->map;
    if(event->button() == Qt::LeftButton){
        if(map[i][j]>0&&map[i][j]<=9){
            map[i][j]+=100;
        }else if(map[i][j]==0){
            QStack<int> sx;
            QStack<int> sy;
            sx.push(i);
            sy.push(j);
            while(!sx.isEmpty()){
                int mx = sx.top();
                int my = sy.top();
                if(map[mx][my]==0){
                    map[mx][my]+=100;
                }
                sx.pop();
                sy.pop();
                for(int a =-1;a<2;a++){
                    for(int b=-1;b<2;b++){
                            if(mx+a>=0&&mx+a<row&&my+b>=0&&my+b<column){
                                if(map[mx+a][my+b]==0){
                                    sx.push(mx+a);
                                    sy.push(my+b);
                                }else if(map[mx+a][my+b]<9){
                                    map[mx+a][my+b]+=100;
                                }
                            }
                    }
                }
            }
        }
         update();
    }else if(event->button() == Qt::RightButton){
        if(map[i][j]<=9){
            map[i][j]+=200;
        }else if(map[i][j]>=200&&map[i][j]<=209){
            map[i][j]-=200;
        }
        update();
    }
}

void MainWindow::restart(int r, int c, int m )
{
    maps->create(r,c,m);
    row = r;
    column = c;
    isNew = true;
    setFixedSize(row*mWidth+offx*2,column*mHeight+offy+offx);
    update();
}

void MainWindow::on_actionrestart_triggered()
{
    maps->restart();
    update();
}

void MainWindow::on_level1_triggered()
{
    restart(15,10,15);
}

void MainWindow::on_level2_triggered()
{
    restart(30,20,40);
}

void MainWindow::on_level3_triggered()
{
    restart(60,40,240);
}



