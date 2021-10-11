


#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H


// #include <QWidget>
#include <QGraphicsScene>


class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:

    MyGraphicsScene(QObject *parent);

    // virtual ~MyGraphicsScene() override;
    
protected:

   void drawBackground(QPainter * painter, const QRectF & rect) override;

private:
};

#endif // MYGRAPHICSSCENE_H
