#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget.h"
#include <QErrorMessage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    errordlg = new QErrorMessage(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<int> MainWindow::getNext(QString p)
{
    int i {};
    int j (-1);
    QVector<int> next (p.length());
    next[0] = -1;
    while (i < p.length() - 1){
        if (j == -1 || p.at(i) == p.at(j)) {
            ++i;
            ++j;
            if (p.at(i) != p.at(j))
                next[i] = j;
            else next[i] = next.at(j);
        }
        else {
            j = next.at(j);
        }
    }
    return next;
}


void MainWindow::on_submit_clicked()
{
    QString t = ui->targetString->text();
    QString p = ui->patternString->text();
    if (t.isEmpty() || p.isEmpty() || t.isNull() || p.isNull()) {
        errordlg->setWindowTitle("Error Dialog");
        errordlg->showMessage(tr("Not NUll!"));
    }
    else if (p.length() > t.length()) {
        errordlg->setWindowTitle("Error Dialog");
        errordlg->showMessage("Pattern is larger than Target!");
    }
    else {
        sample = new Widget(t, p);
        sample->setNext(getNext(p));
        sample->show();
    }
}
