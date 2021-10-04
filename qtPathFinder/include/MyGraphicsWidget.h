


#ifndef MYGRAPHICSSCENEWIDGET_H
#define MYGRAPHICSSCENEWIDGET_H


#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>



class MyGraphicsWidget : public QGraphicsView
{
    Q_OBJECT

public:

    MyGraphicsWidget(QWidget *parent = nullptr);
    virtual ~MyGraphicsWidget() override;
    

    void loadFile(const QString& filename);
    void saveFile(const QString& filename);
    
    void updateSceneSize(qreal width, qreal height);

    void addStartLocation(int x, int y, int radius);
    void addEndLocation(int x, int y, int radius);

    void removeStartLocation();
    void removeEndLocation();

    void addObstacle(int x, int y, int radius);

public slots:

    void updateSceneWidth(int width);
    void updateSceneHeight(int height);

    void clear();
    void generate();

    void updateOwnshipRadius(double radius);

private slots:

protected:

    void keyPressEvent(QKeyEvent* event) override;

private:

    void removeSelectedItems();

    QGraphicsItem* m_startLocationItem;
    QGraphicsItem* m_endLocationItem;

    QGraphicsScene* m_scene;

    // Ui::MyGraphicsWidget* ui;
};


#endif // MAINWINDOW_H