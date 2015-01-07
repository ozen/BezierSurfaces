#ifndef COMMONS
#define COMMONS

#include <cmath>
#include <QOpenGLWidget>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QWheelEvent>

#define TOP_VIEW 0
#define SIDE_VIEW 1
#define FRONT_VIEW 2

const QVector3D ORIGIN = QVector3D(0.0f, 0.0f, 0.0f);

const QVector4D baseColors[] = {
    QVector4D(0.5f, 0.0f, 0.0f, 1.0f),
    QVector4D(1.0f, 0.0f, 0.0f, 1.0f),
    QVector4D(0.0f, 0.5f, 0.0f, 1.0f),
    QVector4D(0.5f, 0.5f, 0.0f, 1.0f),
    QVector4D(1.0f, 0.5f, 0.0f, 1.0f),
    QVector4D(0.0f, 1.0f, 0.0f, 1.0f),
    QVector4D(0.5f, 1.0f, 0.0f, 1.0f),
    QVector4D(1.0f, 1.0f, 0.0f, 1.0f),
    QVector4D(0.0f, 0.0f, 0.5f, 1.0f),
    QVector4D(0.5f, 0.0f, 0.5f, 1.0f),
    QVector4D(1.0f, 0.0f, 0.5f, 1.0f),
    QVector4D(0.0f, 0.5f, 0.5f, 1.0f),
    QVector4D(0.5f, 0.5f, 0.5f, 1.0f),
    QVector4D(1.0f, 0.5f, 0.5f, 1.0f),
    QVector4D(0.0f, 1.0f, 0.5f, 1.0f),
    QVector4D(0.5f, 1.0f, 0.5f, 1.0f),
    QVector4D(1.0f, 1.0f, 0.5f, 1.0f),
    QVector4D(0.0f, 0.0f, 1.0f, 1.0f),
    QVector4D(0.5f, 0.0f, 1.0f, 1.0f),
    QVector4D(1.0f, 0.0f, 1.0f, 1.0f),
    QVector4D(0.0f, 0.5f, 1.0f, 1.0f),
    QVector4D(0.5f, 0.5f, 1.0f, 1.0f),
    QVector4D(1.0f, 0.5f, 1.0f, 1.0f),
    QVector4D(0.0f, 1.0f, 1.0f, 1.0f),
    QVector4D(0.5f, 1.0f, 1.0f, 1.0f),
    QVector4D(1.0f, 1.0f, 1.0f, 1.0f)
};

typedef struct ControlPoint
{
    QVector3D position;
    QVector4D color;
    float size;
    bool selected;
} ControlPoint;

#endif // COMMONS

