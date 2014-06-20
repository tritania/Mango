#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <QWidget>

class Notifier : public QWidget
{
    Q_OBJECT

public:
    Notifier(QWidget *parent = 0);
    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QPoint dragPosition;
};

#endif
