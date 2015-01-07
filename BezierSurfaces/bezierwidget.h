#ifndef BEZIERWIDGET_H
#define BEZIERWIDGET_H

#include "commons.h"

class BezierWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    BezierWidget(QWidget *parent = 0);
    ~BezierWidget();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event);

    void updateProjection();

public slots:
    void addCtrlPoint();
    void selectCtrlPoint(int index);
    void moveCtrlPoint(QVector3D moveVector);
    void deleteCtrlPoint();
    void setWireframe();
    void setGouraud();
    void setPhong();

private:
    void calculateBezier();
    void setIndicesWF();
    void setIndicesTri();

    QOpenGLShaderProgram *ctrlProgram;
    QOpenGLShaderProgram *wfProgram;
    QOpenGLShaderProgram *gouraudProgram;
    QOpenGLShaderProgram *phongProgram;

    QOpenGLVertexArrayObject vao;

    QOpenGLBuffer vbo;
    QOpenGLBuffer indexBuffer;

    QVector<ControlPoint> ctrlPoints;
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QVector<short> indices;

    QMatrix4x4 modelMatrix;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 projectionMatrix;

    int shadingMode;
    float cameraZoom;
    float wRange;
    float hRange;
    int widgetWidth;
    int widgetHeight;
    float aspectRatio;
    int nextColor;

    bool rotating;
    QVector2D rotateLastPos;

    QVector3D LightPosition;

    float bernstein[11][11][11];
    float xMin, xMax, yMin, yMax;
};

#endif // BEZIERWIDGET_H
