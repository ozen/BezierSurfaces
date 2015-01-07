#ifndef CPWIDGET_H
#define CPWIDGET_H

#include "commons.h"

class CPWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    CPWidget(QWidget *parent = 0);
    ~CPWidget();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void wheelEvent(QWheelEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);

    void setViewTop();
    void setViewSide();
    void setViewFront();
    void updateProjection();

public slots:
    void addCtrlPoint();
    void selectCtrlPoint(int index);
    void moveCtrlPoint(QVector3D moveVector);
    void deleteCtrlPoint();

signals:
    void ctrlPointSelected(int index);
    void ctrlPointMoved(QVector3D moveVector);

private:
    QOpenGLShaderProgram *program;
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;

    QVector<ControlPoint> ctrlPoints;

    QMatrix4x4 modelMatrix;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 projectionMatrix;

    float cameraZoom;
    float wRange;
    float hRange;

    int widgetWidth;
    int widgetHeight;
    float aspectRatio;

    int currentView;
    int nextColor;
    int moveLastX;
    int moveLastY;

    bool movingPoint;
    bool movedPoint;
};

#endif // CPWIDGET_H
