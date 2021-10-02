

// #include <QtOpenGL>

#include "MyOpenGLWidget.h"

#include "ui_MyOpenGLWidget.h"

#include <QIcon>
#include <QKeyEvent>
#include <iostream>


MyOpenGLWidget::MyOpenGLWidget(QWidget* parent)
:
    QGLWidget(parent),
    ui(new Ui::MyOpenGLWidget),
    // m_camera(QVector3D(0, 5, 0). QVector3D(0, 0, 0), QVector3D(0, 1, 0)),
    // m_cube(),
    m_timer()
    // m_degrees(0.0),
    // m_distance(5.0)
{
    setWindowIcon(QIcon(":images/logo.png"));    

    ui->setupUi(this);

    m_timer.start(1000);
    // connect(&m_timer, SIGNAL(timeout()), this, SLOT(tick(void)));
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    makeCurrent();

    m_timer.stop();

    delete texture;
    delete geometries;
    doneCurrent();

    delete ui;
}

// void MyOpenGLWidget::tick(void)
// {
//     paintGL();

//     updateGL();
//     update();
// }

void MyOpenGLWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }
}

void MyOpenGLWidget::initializeGL()
{
    std::clog << "MyOpenGLWidget::initializeGL()" << std::endl;

    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]

    geometries = new GeometryEngine;

    // Use QBasicTimer because its faster than QTimer
    m_timer.start(12); //, this);



    // glClearColor(0,0,0,1);

    // glEnable(GL_DEPTH_TEST);

    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    // glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    // glEnable(GL_COLOR_MATERIAL);
}

void MyOpenGLWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]

//! [4]
void MyOpenGLWidget::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
//! [4]

QSize MyOpenGLWidget::minimumSizeHint() const
{
    return QSize(512, 512);
}

QSize MyOpenGLWidget::sizeHint() const
{
    return QSize(800, 600);
}

void MyOpenGLWidget::qNormalizeAngle(int& angle)
{
    while (angle < 0)
    {
        angle += 360 * 16;
    }
    while (angle > 360 * 16)
    {
        angle -= 360 * 16;
    }
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);


    // glViewport(0, 0, (GLint) width, (GLint) height);
    
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // gluPerspective(45,     // fov
    //                (float) width/height, // aspect
    //                0.01,   // zNear
    //                100.0); // zFar


    // gluLookAt(m_camera.m_eye().x(),  m_camera.m_eye().y(), m_camera.m_eye().z(), // eye
    //           m_camera.center().x(), m_camera.center().y(), m_camera.center().z(), // reference
    //           m_camera.up().x(),     m_camera.up().y(),     m_camera.up().z()); // up (positive)
}

void MyOpenGLWidget::drawLine(int x1, int y1, int x2, int y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void MyOpenGLWidget::paintGL()
{
    std::clog << "MyOpenGLWidget::paintGL()" << std::endl;
    
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

//! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);
//! [6]

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    // Draw cube geometry
    geometries->drawCubeGeometry(&program);


    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();

    // // gluLookAt(m_camera.m_eye().x(),  m_camera.m_eye().y(), m_camera.m_eye().z(), // eye
    // //           m_camera.center().x(), m_camera.center().y(), m_camera.center().z(), // reference
    // //           m_camera.up().x(),     m_camera.up().y(),     m_camera.up().z()); // up (positive)

    // glBegin(GL_TRIANGLES);
    // glColor3f(1.0, 0.0, 0.0); // red
    // glVertex3f(-0.5, -0.5, 0);

    // glColor3f(0.0, 1.0, 0.0); // green
    // glVertex3f( 0.5, -0.5, 0);

    // glColor3f(0.0, 0.0, 1.0); // blue
    // glVertex3f( 0, 0.5, 0);
    // glEnd();


    // glBegin(GL_POINTS);
    // glColor3f(1.0, 1.0, 1.0); // white

    // glVertex3f(-2, 0, 2);
    // glVertex3f(-1, 0, 2);
    // glVertex3f( 0, 0, 2);
    // glVertex3f( 1, 0, 2);
    // glVertex3f( 2, 0, 2);

    // glVertex3f(-2, 0, 1);
    // glVertex3f(-1, 0, 1);
    // glVertex3f( 0, 0, 1);
    // glVertex3f( 1, 0, 1);
    // glVertex3f( 2, 0, 1);

    // glVertex3f(-2, 0, 0);
    // glVertex3f(-1, 0, 0);
    // glVertex3f( 0, 0, 0);
    // glVertex3f( 1, 0, 0);
    // glVertex3f( 2, 0, 0);

    // glVertex3f(-2, 0, -1);
    // glVertex3f(-1, 0, -1);
    // glVertex3f( 0, 0, -1);
    // glVertex3f( 1, 0, -1);
    // glVertex3f( 2, 0, -1);

    // glVertex3f(-2, 0, -2);
    // glVertex3f(-1, 0, -2);
    // glVertex3f( 0, 0, -2);
    // glVertex3f( 1, 0, -2);
    // glVertex3f( 2, 0, -2);
    // glEnd();
}

void MyOpenGLWidget::keyPressEvent(QKeyEvent* e)
{
    switch (e->key())
    {
        case Qt::Key_Escape:
            QCoreApplication::instance()->quit();
            break;
        
        // Camera Controls
        case Qt::Key_W:
            std::clog << "Qt::Key_W" << std::endl;
            // m_camera.moveUp();
        case Qt::Key_A:
            std::clog << "Qt::Key_A" << std::endl;
        case Qt::Key_S:
            std::clog << "Qt::Key_S" << std::endl;
        case Qt::Key_D:
            std::clog << "Qt::Key_D" << std::endl;
        case Qt::Key_Q:
            std::clog << "Qt::Key_Q" << std::endl;
        case Qt::Key_E:
            std::clog << "Qt::Key_E" << std::endl;
        case Qt::Key_Space:
            std::clog << "Qt::Key_Space" << std::endl;

        default:
            QGLWidget::keyPressEvent(e);
    }
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent* e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent* e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}