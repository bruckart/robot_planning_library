

#include "MyGraphicsScene.h"

#include <QPainter>

static const int GRID_STEP = 10;

inline qreal round(qreal val, int step)
{
   int tmp = int(val) + step /2;
   tmp -= tmp % step;
   return qreal(tmp);
}
 
MyGraphicsScene::MyGraphicsScene(QObject *parent)
:
    QGraphicsScene(parent)
{
    // setSceneRect(QRectF(0, 0, 80, 40));
}

void MyGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    // int step = GRID_STEP;
    // painter->setPen(QPen(QColor(200, 200, 255, 125)));
    // // draw horizontal grid
    // qreal start = round(rect.top(), step);
    // if (start > rect.top())
    // {
    //     start -= step;
    // }
    // for (qreal y = start - step; y < rect.bottom(); )
    // {
    //     y += step;
    //     painter->drawLine(rect.left(), y, rect.right(), y);
    // }

    // // now draw vertical grid
    // start = round(rect.left(), step);
    // if (start > rect.left())
    // {
    //     start -= step;
    // }
    // for (qreal x = start - step; x < rect.right(); ) 
    // {
    //     x += step;
    //     painter->drawLine(x, rect.top(), x, rect.bottom());
    // }
}
