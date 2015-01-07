#include "cpwidget.h"

float round(float f, float prec)
{
    return (float) ( floor(f * (1.0f / prec) + 0.5)/(1.0f / prec) );
}

CPWidget::CPWidget(QWidget *parent)
    : QOpenGLWidget(parent), program(0)
{
    Q_INIT_RESOURCE(resources);
    modelMatrix.setToIdentity();
    viewMatrix.setToIdentity();
    projectionMatrix.setToIdentity();

    currentView = FRONT_VIEW;
    cameraZoom = 1.0f;
    nextColor = 0;
    movingPoint = false;
    moveLastX = 0;
    moveLastY = 0;
    setMouseTracking(true);

    ControlPoint cp;
    cp.position = QVector3D(-1.5f, -1.5f, 0.0f);
    cp.color = baseColors[nextColor++];
    cp.size = 5.0f;
    cp.selected = false;
    ctrlPoints.append(cp);
    cp.position = QVector3D(-0.5f, -1.5f, 1.5f);
    cp.color = baseColors[nextColor++];
    ctrlPoints.append(cp);
    cp.position = QVector3D(0.5f, -1.5f, 1.0f);
    cp.color = baseColors[nextColor++];
    ctrlPoints.append(cp);
    cp.position = QVector3D(1.5f, -1.5f, 2.0f);
    cp.color = baseColors[nextColor++];
    ctrlPoints.append(cp);
    cp.position = QVector3D(-1.5f, -0.5f, -1.0f);
    cp.color = baseColors[nextColor++];
    ctrlPoints.append(cp);
    cp.position = QVector3D(-0.5f, -0.5f, 1.5f);
    cp.color = baseColors[nextColor++];
    ctrlPoints.append(cp);
    cp.position = QVector3D(0.5f, -0.5f, 1.5f);
    cp.color = baseColors[nextColor++];
    ctrlPoints.append(cp);
    cp.position = QVector3D(1.5f, -0.5f, -0.2f);
    cp.color = baseColors[nextColor++];
    ctrlPoints.append(cp);
    cp.position = QVector3D(-1.5f, 0.5f, 0.5f);
    cp.color = baseColors[nextColor++];
    ctrlPoints.append(cp);
    cp.position = QVector3D(-0.5f, 0.5f, 0.0f);
    cp.color = baseColors[nextColor++];
    ctrlPoints.append(cp);
    cp.position = QVector3D(0.5f, 0.5f, 1.5f);
    cp.color = baseColors[nextColor++];
    ctrlPoints.append(cp);
    cp.position = QVector3D(1.5f, 0.5f, -0.5f);
    cp.color = baseColors[nextColor++];
    ctrlPoints.append(cp);
    cp.position = QVector3D(-1.5f, 1.5f, 0.3f);
    cp.color = baseColors[nextColor++];
    ctrlPoints.append(cp);
    cp.position = QVector3D(-0.5f, 1.5f, 0.8f);
    cp.color = baseColors[nextColor++];
    ctrlPoints.append(cp);
    cp.position = QVector3D(0.5f, 1.5f, 1.0f);
    cp.color = baseColors[nextColor++];
    ctrlPoints.append(cp);
    cp.position = QVector3D(1.5f, 1.5f, 1.6f);
    cp.color = baseColors[nextColor++];
    ctrlPoints.append(cp);
}

CPWidget::~CPWidget()
{
    makeCurrent();

    delete program;

    vbo.destroy();
    vao.destroy();

    doneCurrent();
}

void CPWidget::addCtrlPoint()
{
    ControlPoint cp;
    cp.position = QVector3D(0.0f, 0.0f, 0.0f);
    cp.color = baseColors[nextColor];
    cp.size = 10.0f;
    cp.selected = true;
    nextColor = (nextColor + 1) % 26;
    ctrlPoints.append(cp);
}

void CPWidget::selectCtrlPoint(int index)
{
    if(ctrlPoints[index].selected)
    {
        ctrlPoints[index].selected = false;
        ctrlPoints[index].size /= 2;
    }
    else
    {
        ctrlPoints[index].selected = true;
        ctrlPoints[index].size *= 2;
    }

    update();
}

void CPWidget::moveCtrlPoint(QVector3D moveVector)
{
    for(int i=0; i<ctrlPoints.size(); i++)
    {
        if(ctrlPoints[i].selected)
        {
            ctrlPoints[i].position += moveVector;

            if(ctrlPoints[i].position.x() > 5.0)
            {
                ctrlPoints[i].position.setX(5.0);
            }
            if(ctrlPoints[i].position.y() > 5.0)
            {
                ctrlPoints[i].position.setY(5.0);
            }
            if(ctrlPoints[i].position.z() > 5.0)
            {
                ctrlPoints[i].position.setZ(5.0);
            }
            if(ctrlPoints[i].position.x() < -5.0)
            {
                ctrlPoints[i].position.setX(-5.0);
            }
            if(ctrlPoints[i].position.y() < -5.0)
            {
                ctrlPoints[i].position.setY(-5.0);
            }
            if(ctrlPoints[i].position.z() < -5.0)
            {
                ctrlPoints[i].position.setZ(-5.0);
            }
        }
    }

    update();
}

void CPWidget::deleteCtrlPoint()
{
    int i=0;
    while(i<ctrlPoints.size())
    {
        if(ctrlPoints[i].selected)
        {
            ctrlPoints.remove(i);
        }
        else
        {
            i++;
        }
    }
}

void CPWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_PROGRAM_POINT_SIZE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();

    program = new QOpenGLShaderProgram(this);
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader_points.glsl");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader_points.glsl");
    program->link();
    program->bind();
}

void CPWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    widgetWidth = w;
    widgetHeight = h;
    aspectRatio = widgetWidth / (float) widgetHeight;

    updateProjection();
}

void CPWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int numPoints = ctrlPoints.size();

    vbo.bind();
    vbo.allocate(ctrlPoints.data(), numPoints * sizeof(ControlPoint));

    program->bind();

    int vPosition = program->attributeLocation("vPosition");
    program->enableAttributeArray(vPosition);
    program->setAttributeBuffer(vPosition, GL_FLOAT, offsetof(ControlPoint, position), 3, sizeof(ControlPoint));

    int vColor = program->attributeLocation("vColor");
    program->enableAttributeArray(vColor);
    program->setAttributeBuffer(vColor, GL_FLOAT, offsetof(ControlPoint, color), 4, sizeof(ControlPoint));

    int vSize = program->attributeLocation("vSize");
    program->enableAttributeArray(vSize);
    program->setAttributeBuffer(vSize, GL_FLOAT, offsetof(ControlPoint, size), 1, sizeof(ControlPoint));

    program->setUniformValue("modelMatrix", modelMatrix);
    program->setUniformValue("viewMatrix", viewMatrix);
    program->setUniformValue("projectionMatrix", projectionMatrix);

    glDrawArrays(GL_POINTS, 0, numPoints);
}

void CPWidget::wheelEvent(QWheelEvent * event)
{
    int numSteps = event->delta() / 120;
    if(numSteps > 0 && cameraZoom > 1)
    {
        cameraZoom -= 0.1 * numSteps;
    }
    else if(numSteps < 0 && cameraZoom < 5)
    {
        cameraZoom += 0.1 * abs(numSteps);
    }

    updateProjection();
    update();
}

void CPWidget::mousePressEvent(QMouseEvent * event)
{
    movingPoint = true;
    moveLastX = event->x();
    moveLastY = event->y();
}

void CPWidget::mouseReleaseEvent(QMouseEvent * event)
{
    movingPoint = false;

    if(!movedPoint) {
        unsigned char data[3];
        makeCurrent();
        glReadPixels(event->x(), widgetHeight - event->y(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, data);
        doneCurrent();

        float r = (float) data[0] / 255;
        float g = (float) data[1] / 255;
        float b = (float) data[2] / 255;

        for(int i=0; i<ctrlPoints.size(); i++)
        {
            QVector4D color = ctrlPoints[i].color;

            if(abs(color.x() - r) < 0.1 && abs(color.y() - g) < 0.1 && abs(color.z() - b) < 0.1)
            {
                selectCtrlPoint(i);
                emit ctrlPointSelected(i);
                break;
            }
        }
    }

    movedPoint = false;
}

void CPWidget::mouseMoveEvent(QMouseEvent * event)
{
    if(movingPoint)
    {
        movedPoint = true;

//        float deltaX = round((event->x() - moveLastX) * wRange / widgetWidth, 0.01);
//        float deltaY = round((event->y() - moveLastY) * hRange / widgetHeight, 0.01);

        float deltaX = (event->x() - moveLastX) * wRange / widgetWidth;
        float deltaY = (event->y() - moveLastY) * hRange / widgetHeight;

        QVector3D moveVector(0.0f, 0.0f, 0.0f);

        if(currentView == TOP_VIEW)
        {
            moveVector.setX(deltaX);
            moveVector.setZ(deltaY);
        }
        else if(currentView == SIDE_VIEW)
        {
            moveVector.setY(-deltaY);
            moveVector.setZ(deltaX);
        }
        else if(currentView == FRONT_VIEW)
        {
            moveVector.setX(deltaX);
            moveVector.setY(-deltaY);
        }

        moveCtrlPoint(moveVector);
        emit ctrlPointMoved(moveVector);

        moveLastX = event->x();
        moveLastY = event->y();
    }
}

void CPWidget::setViewTop()
{
    viewMatrix.setToIdentity();
    viewMatrix.lookAt(QVector3D(0.0f, 1.0f, 0.0f), ORIGIN, QVector3D(0.0f, 0.0f, -1.0f));
    currentView = TOP_VIEW;
    updateProjection();
}

void CPWidget::setViewSide()
{
    viewMatrix.setToIdentity();
    viewMatrix.lookAt(QVector3D(-1.0f, 0.0f, 0.0f), ORIGIN, QVector3D(0.0f, 1.0f, 0.0f));
    currentView = SIDE_VIEW;
    updateProjection();
}

void CPWidget::setViewFront()
{
    viewMatrix.setToIdentity();
    viewMatrix.lookAt(QVector3D(0.0f, 0.0f, 1.0f), ORIGIN, QVector3D(0.0f, 1.0f, 0.0f));
    currentView = FRONT_VIEW;
    updateProjection();
}

void CPWidget::updateProjection()
{
    float left   = -1.0f * cameraZoom, right = 1.0f * cameraZoom;
    float bottom = -1.0f * cameraZoom, top   = 1.0f * cameraZoom;
    float zNear  = -10.0f * cameraZoom, zFar  = 10.0f * cameraZoom;

    if ( aspectRatio > 1.0 ) {
        left *= aspectRatio;
        right *= aspectRatio;
    }
    else {
        bottom /= aspectRatio;
        top /= aspectRatio;
    }

    wRange = right - left;
    hRange = top - bottom;

    projectionMatrix.setToIdentity();
    projectionMatrix.ortho(left, right, bottom, top, zNear, zFar);
}
