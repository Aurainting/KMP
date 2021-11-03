#include <QPainter>
#include <QPainterPath>
#include <QTimer>

#include <iostream>

#include "widget.h"
#include "ui_widget.h"

void Widget::paintEvent(QPaintEvent *event)
{
    //QString target = tr("abcaabbabcabaacbacba");
    //QString pattern = tr("abcabaa");

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);//抗锯齿
    painter.setRenderHint(QPainter::TextAntialiasing);//抗锯齿
    int W = this->width();
    int H = this->height();
    int side = qMin(W, H);

    painter.setViewport((W-side)/2, (H-side)/2, side, side);
    painter.setWindow(-100, -100, 200, 200);

    QPen pen;
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    painter.setPen(pen);

    QBrush brush;
    brush.setColor(Qt::blue);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    QPainterPath topArrowPath;
    QPoint points1[] = {
        QPoint (-100, -65),
        QPoint (-90, -65),
        QPoint (-95, -60),
        QPoint (-95, -52)
    };
    topArrowPath.moveTo(points1[0]);
    topArrowPath.lineTo(points1[3]);
    topArrowPath.lineTo(points1[1]);
    topArrowPath.lineTo(points1[2]);
    topArrowPath.closeSubpath();

    QRect topArrowText (-90, -65, 30, 15);

    //Prepare for the pattern string
    QVector<QRect> patternRects{};
    int offset = 0;
    for (int i = 0; i < target.length(); ++i)
    {
        patternRects.push_back(QRect(-100 + offset, -40, 10, 10));
        offset += 10;
    }

    QPainterPath botArrowPath;
    QPoint points2[] = {
        QPoint (-100, -15),
        QPoint (-90, -15),
        QPoint (-95, -20),
        QPoint (-95, -28)
    };
    botArrowPath.moveTo(points2[0]);
    botArrowPath.lineTo(points2[3]);
    botArrowPath.lineTo(points2[1]);
    botArrowPath.lineTo(points2[2]);
    botArrowPath.closeSubpath();

    QRect botArrowText (-90, -20, 30, 15);

    QFont font;
    font.setPointSize(8);
    painter.setFont(font);

    //Draw target string
    QVector<QRect> targetRects{};
    offset = 0;
    for (int i = 0; i < target.length(); ++i)
    {
        targetRects.push_back(QRect(-100 + offset, -50, 10, 10));
        offset += 10;
    }
    for (auto i = 0; i < target.length(); ++i)
    {
        painter.drawText(targetRects.at(i), Qt::AlignCenter, target.at(i));
    }

    pen.setColor(Qt::black);
    painter.setPen(pen);

    //Draw nextval
    QVector<QRect> nextval{};
    offset = 0;
    for (int i = 0; i < pattern.length(); ++i)
    {
        nextval.push_back(QRect(-100 + offset, 50, 10, 10));
        offset += 10;
    }
    QString ans;
    for (const auto& i : next)
    {
        ans += QString::number(i + 1);
    }
    painter.drawText(-110, 50, "Nextval:");
    for (auto i = 0; i < pattern.length(); ++i)
    {
        painter.drawText(nextval.at(i), Qt::AlignCenter, ans.at(i));
    }
    pen.setColor(Qt::red);
    painter.setPen(pen);

    ++targetPtr;
    ++patternPtr;

    if (targetPtr < target.length() && patternPtr < pattern.length()){
        painter.save();
        dist += 10;
        QTransform transform;
        transform.translate(dist, 0);
        painter.setTransform(transform);

        painter.drawPath(topArrowPath);
        painter.drawText(topArrowText, Qt::AlignCenter, "i=" + QString::number(targetPtr + 1));

        painter.drawPath(botArrowPath);
        painter.drawText(botArrowText, Qt::AlignCenter, "j=" + QString::number(patternPtr + 1));
        painter.restore();
        painter.drawText(patternRects.at(targetPtr), Qt::AlignCenter, pattern.at(patternPtr));

        if (patternPtr == -1 || target.at(targetPtr) == pattern.at(patternPtr)) {
            //everything is done before!
        }
        else {//trackback
            dist -= 10;
            patternPtr = next.at(patternPtr);
            --targetPtr;
            --patternPtr;
        }

    }
    if (patternPtr >= pattern.length()){
        painter.drawText(0, 90, "Found pattern at: " + QString::number(targetPtr - patternPtr + 1));
    }
    else if (targetPtr >= target.length()) {
        painter.drawText(0, 90, "Not Found!");
    }
}

Widget::Widget(QString t, QString p, QWidget *parent)
    : target(t), pattern(p), QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1200);
    dist = -20;
    targetPtr = -2;
    patternPtr = -2;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setNext(const QVector<int> &n)
{
    next = n;
}


