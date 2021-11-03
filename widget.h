#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QTimer;

class Widget : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

public:
    explicit Widget(QString t, QString p, QWidget *parent = nullptr);
    ~Widget();
    void setNext(const QVector<int>& n);

private:
    Ui::Widget *ui;
    QTimer *timer;
    int dist;
    int targetPtr;
    int patternPtr;
    QString target;
    QString pattern;
    QVector<int> next;
};
#endif // WIDGET_H

