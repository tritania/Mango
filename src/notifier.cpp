#include <QtWidgets>
#include "notifier.h"

Notifier::Notifier(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::ToolTip)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setWindowTitle(tr("Mango"));
}

void Notifier::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(QRectF(0, 0, 400, 400), QImage(":/images/hand.png"));
}

void Notifier::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void Notifier::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}


QSize Notifier::sizeHint() const
{
    return QSize(400, 400);
}
