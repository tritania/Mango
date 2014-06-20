#include <QtWidgets>

#include "notifier.h"

Notifier::Notifier(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint)
{
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setToolTip(tr("Drag the clock with the left mouse button.\n"
                  "Use the right mouse button to open a context menu."));
    setWindowTitle(tr("Shaped Analog Clock"));
}

void Notifier::paintEvent(QPaintEvent *)
{
    QColor backgroundColor = palette().light().color();
    backgroundColor.setAlpha(200);
    QPainter customPainter(this);
    customPainter.fillRect(rect(),backgroundColor);
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
    return QSize(100, 100);
}
