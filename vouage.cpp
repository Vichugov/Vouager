#include "vouage.h"
#include "ui_vouage.h"
#include <cmath>
#include <QMessageBox>
bool notall=0;
int r,ris=0,prirost,xcenter,ycenter,mins=10000,leng,s;
double gradus=360;
int ways[10][10];
bool *was;
int *way, *minway;
struct Uzel{
    int x,y;
};
Uzel *uzel;
Vouage::Vouage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Vouage)
{
    ui->setupUi(this);
    ui->build->hide();
    ui->go->hide();
    Hider();
    QPixmap back("C:/3.jpg");
    back = back.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, back);
    //palette.setColor(QPalette::Window,QColor(200,200,200));
    this->setPalette(palette);
}
void Vouage::Hider(){
    QString sear;
    for (int i=1;i<10;i++){
        sear="clh" + QString::number(i);
        this->findChild<QWidget*>(sear)->hide();
    }
   for (int i=1;i<10;i++){
        sear="clv" + QString::number(i);
        this->findChild<QWidget*>(sear)->hide();
        sear="d" + QString::number(i);
        this->findChild<QWidget*>(sear)->hide();
        for (int e=i+1;e<10;e++){
            sear="p" + QString::number(i) + QString::number(e);
            this->findChild<QWidget*>(sear)->hide();
        }
        for (int e=1;e<i;e++){
            sear="l" + QString::number(i) + QString::number(e);
            this->findChild<QWidget*>(sear)->hide();
        }
    }
}
void Vouage::Shower(){
    QString sear;
    for (int i=1;i<r+1;i++){
        sear="clh" + QString::number(i);
        this->findChild<QWidget*>(sear)->show();
    }
   for (int i=1;i<r+1;i++){
        sear="clv" + QString::number(i);
        this->findChild<QWidget*>(sear)->show();
        sear="d" + QString::number(i);
        this->findChild<QWidget*>(sear)->show();
        for (int e=i+1;e<r+1;e++){
            sear="p" + QString::number(i) + QString::number(e);
            this->findChild<QWidget*>(sear)->show();
        }
        for (int e=1;e<i;e++){
            sear="l" + QString::number(i) + QString::number(e);
            this->findChild<QWidget*>(sear)->show();
        }
    }
}
Vouage::~Vouage()
{
    delete ui;
}

void Vouage::Poisk(int l, int i){
    leng+=l;
    was[i]=1;
    bool b=0;
    way[s]=i;
    s++;
    for (int e=0;e<r;e++){
        if (!was[e]){
            if (ways[i][e]) Poisk(ways[i][e],e);
            b=1;
        }
    }
    if(!b){
        if (leng<mins){
            mins=leng;
            for (int z=0;z<r;z++) minway[z]=way[z];
        }
    }
    leng-=l;
    s--;
    was[i]=0;
}

void Vouage::on_go_clicked()
{
    ui->go->setStyleSheet("color: rgb(0,250,0);background-color: rgb(150,150,150);border: 1px solid rgb(0,250,0);border-radius: 10px;");
    QString searcher,buffer;
    leng=0;
    s=0;
    mins=10000;
    was = new bool [r];
    way = new int [r];
    minway = new int [r];
    for (int i=0;i<r;i++) Poisk(0,i);
    buffer="Кратчайший путь: " + QString::number(minway[0]+1);
    for (int i=1;i<r;i++) buffer += "->" + QString::number(minway[i]+1);
    if (mins==10000){
        QMessageBox::warning(this,"Предупреждение","Не существует маршрута, позволяющего посетить все города, или невозможно посетить их без повторного посещения пройденных дорог и городов. ");
    }
    else{
    buffer+= " (или обратный ему).\n Длина пути: " +QString::number(mins);
    ris=3;
    this->repaint();
    QMessageBox::information(this,"Результат",buffer);
    }
    delete[] was;
    delete[] way;
}
void Vouage::paintEvent(QPaintEvent *)
{ 
    if (ris){
    int otstup;
    gradus/=r;
    prirost=gradus;
    gradus=0;
    QPainter paint;
    QPen pen;
    QBrush brush;
    QString stroka;
    QFont font;
    pen.setColor(Qt::blue);
    pen.setWidth(7);
    pen.setStyle(Qt::SolidLine);
    font.setPointSize(20);
    brush.setStyle(Qt::Dense3Pattern);
    brush.setColor(Qt::white);
    paint.begin(this);
    paint.setPen(pen);
    paint.setFont(font);
    paint.setBrush(brush);
    for (int i=0;i<r;i++){
        otstup=-10;
        if (gradus>180) otstup=130;
        stroka=QString::number(i+1);
        uzel[i].x=xcenter+(200*cos(gradus/57));
        uzel[i].y=ycenter+(200*-sin(gradus/57));
        paint.drawEllipse(uzel[i].x,uzel[i].y,100,100);
        paint.drawText(uzel[i].x+48,uzel[i].y+otstup,stroka);
        gradus+=prirost;
    }
    if (ris>1){
        for (int i=0;i<r;i++){
            for (int e=i+1;e<r;e++){
                if (ways[i][e]){
                    pen.setStyle(Qt::DashLine);
                    pen.setWidth(3);
                    paint.setPen(pen);
                    paint.drawLine(uzel[i].x+50,uzel[i].y+50,uzel[e].x+50,uzel[e].y+50);
                }
            }
        }
    }
    if (ris==3){
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(5);
        pen.setColor(Qt::green);
        paint.setPen(pen);
        for (int i=1;i<r;i++){
         paint.drawLine(uzel[minway[i-1]].x+50,uzel[minway[i-1]].y+50,uzel[minway[i]].x+50,uzel[minway[i]].y+50);
        }
    }
    paint.end();
    }
}

void Vouage::on_gotab_clicked()
{
    ui->gotab->setStyleSheet("color: rgb(0,250,0);background-color: rgb(150,150,150);border: 1px solid rgb(0,250,0);border-radius: 10px;");
    ui->go->hide();
    if (ui->quantitylabel->text().toInt()<3||ui->quantitylabel->text().toInt()>9){
        ui->quantitylabel->setText("");
        ui->build->hide();
        Hider();
        ris=0;
        this->repaint();
        QMessageBox::warning(this,"Предупреждение","Количество городов должно являться числом и иметь значение не менее 3 и не более 9! ");
    }
    else{
        Hider();
        ui->build->show();
        r=ui->quantitylabel->text().toInt();
        Shower();
        uzel = new Uzel[r];
        xcenter=800;
        ycenter=300;
        ris=1;
        this->repaint();
    }
}

void Vouage::on_build_clicked()
{
    ui->build->setStyleSheet("color: rgb(0,250,0);background-color: rgb(150,150,150);border: 1px solid rgb(0,250,0);border-radius: 10px;");
    ui->go->hide();
    QString searcher,buffer;
    for (int i=1;i<r;i++){
        for (int e=i+1;e<r+1;e++){
            searcher="p"+QString::number(i) + QString::number(e);
            buffer=this->findChild<QLineEdit*>(searcher)->text();
            if (!buffer.length()) buffer='0';
            searcher="l"+QString::number(e) + QString::number(i);
            this->findChild<QLabel*>(searcher)->setText(buffer);
        }
    }
    for (int i=0;i<r-1;i++){
        for (int e=i+1;e<r;e++){
            searcher="l"+QString::number(e+1) + QString::number(i+1);
            buffer=this->findChild<QLabel*>(searcher)->text();
            if (!buffer.length()) buffer='0';
           ways[i][e]=buffer.toInt();
           ways[e][i]=ways[i][e];
        }
    }
    ui->go->show();
    ris=2;
    this->repaint();
}

void Vouage::on_gotab_pressed(){ui->gotab->setStyleSheet("color: rgb(250,0,0);background-color: rgb(150,150,150);border: 1px solid rgb(250,0,0);border-radius: 10px;");}
void Vouage::on_build_pressed(){ui->build->setStyleSheet("color: rgb(250,0,0);background-color: rgb(150,150,150);border: 1px solid rgb(250,0,0);border-radius: 10px;");}
void Vouage::on_go_pressed(){ui->go->setStyleSheet("color: rgb(250,0,0);background-color: rgb(150,150,150);border: 1px solid rgb(250,0,0);border-radius: 10px;");}
