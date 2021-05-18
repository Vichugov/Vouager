#ifndef VOUAGE_H
#define VOUAGE_H

#include <QMainWindow>
#include <QPainter>
QT_BEGIN_NAMESPACE
namespace Ui { class Vouage; }
QT_END_NAMESPACE

class Vouage : public QMainWindow
{
    Q_OBJECT

public:
    Vouage(QWidget *parent = nullptr);
    ~Vouage();

private slots:
    void on_go_clicked();
    void on_gotab_clicked();
    void Poisk(int l, int i);
    void Hider();
    void Shower();
    void on_build_clicked();

    void on_gotab_pressed();

    void on_build_pressed();

    void on_go_pressed();

private:
    Ui::Vouage *ui;

protected:
    void paintEvent(QPaintEvent*) override;
};
#endif // VOUAGE_H
