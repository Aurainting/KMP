#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QErrorMessage;
class Widget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QVector<int> getNext(QString t);

private slots:
    void on_submit_clicked();

private:
    Ui::MainWindow *ui;
    QErrorMessage *errordlg;
    Widget *sample;
};
#endif // MAINWINDOW_H
