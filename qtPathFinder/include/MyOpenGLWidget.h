
#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include "GeometryEngine.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>


class GeometryEngine;

#include <QWidget>
// #include <QtOpenGL>
#include <QGLWidget>
// #include <QtOpenGL>
// #include <QKeyEvent>
#include <QTimer>


// #include "GL/glu.h"#if defined(__APPLE__)
// #include <OpenGL/gl.h>
// #include <OpenGL/glu.h>
// #else
// #include <GL/gl.h>
// #include <GL/glu.h>
// #endif

#include "glu.h"

namespace Ui
{
    class MyOpenGLWidget;
}


class MyOpenGLWidget : public QGLWidget, 
                       protected QOpenGLFunctions
          
{
    Q_OBJECT

public:
    MyOpenGLWidget(QWidget* parent=0);

    virtual ~MyOpenGLWidget() override;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void drawLine(int x1, int y1, int x2, int y2);


    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    virtual void keyPressEvent(QKeyEvent* e) override;
    virtual void mousePressEvent(QMouseEvent* e) override;
    virtual void mouseMoveEvent(QMouseEvent* e) override;
    void timerEvent(QTimerEvent *e) override;


    void initShaders();
    void initTextures();

    static void qNormalizeAngle(int& angle);

protected slots:

public slots:

    // void tick(void);

private:

    // QtCube* m_cube;

    QTimer m_timer;

    QOpenGLShaderProgram program;
    GeometryEngine *geometries = nullptr;

    QOpenGLTexture *texture = nullptr;

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    QQuaternion rotation;


    // double m_degrees;
    // double m_distance;

    // SimpleCamera m_camera;

    Ui::MyOpenGLWidget* ui;
};

#endif // MYOPENGLWIDGET_H