#ifndef SHAPEDCLOCK_H
#define SHAPEDCLOCK_H

#include <QWidget>

class ShapedClock : public QWidget
{
    Q_OBJECT

public:
    ShapedClock(QWidget *parent = 0);
    QSize sizeHint() const;

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QPoint dragPosition;
};

#endif
