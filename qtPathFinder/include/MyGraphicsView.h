


#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H


// #include <QWidget>
// #include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>

#include "MyGraphicsScene.h"


class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:

    MyGraphicsView(QWidget *parent = nullptr);

    virtual ~MyGraphicsView() override;
    
    // virtual void resizeEvent(QResizeEvent* event) override
    // {
    //     const QRectF rect = QRectF(-0.5,-0.5, 1, 1);
    //     fitInView(rect, Qt::KeepAspectRatio);
    //     setSceneRect(rect);
    // }

    // virtual void showEvent(QShowEvent* event) override
    // {
    //     const QRectF rect = QRectF(-0.5,-0.5, 1, 1);
    //     fitInView(rect, Qt::KeepAspectRatio);
    //     setSceneRect(rect);
    // }

    void loadFile(const QString& filename);
    void saveFile(const QString& filename);

    void addStartLocation(int x, int y, int radius);
    void addEndLocation(int x, int y, int radius);

    void addDeathStar(int x, int y, int radius);

public slots:

    void updateSceneWidth(int width);
    void updateSceneHeight(int height);

    void clear();

    void generatePath();

private slots:

protected:

    void keyPressEvent(QKeyEvent* event) override;

private:

    void removeSelectedItems();

    QGraphicsItem* m_droidStartLocationItem;
    QGraphicsItem* m_droidEndLocationItem;

    MyGraphicsScene* m_scene;
};


#endif // MYGRAPHICSVIEW_H