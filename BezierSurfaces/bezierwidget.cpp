#include "bezierwidget.h"

double calcBernstein(int n, int i, double u)
{
    int N = n;

    if (i > n || i < 0) {
        return 0;
    }

    double r = 1;
    for (int d = 1; d <= i; ++d) {
        r *= n--;
        r /= d;
    }

    return r *  pow(u, (double) i) * pow(1-u, (double) (N-i));
}

BezierWidget::BezierWidget(QWidget *parent)
    : QOpenGLWidget(parent), ctrlProgram(0)
{
    Q_INIT_RESOURCE(resources);
    modelMatrix.setToIdentity();
    viewMatrix.setToIdentity();
    viewMatrix.lookAt(QVector3D(0.0f, 1.0f, 0.0f), ORIGIN, QVector3D(0.0f, 0.0f, -1.0f));
    projectionMatrix.setToIdentity();

    indexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

    LightPosition = QVector3D(0.0, 10.0, 0.0);
    shadingMode = 0;
    cameraZoom = 1.0f;
    nextColor = 0;
    rotating = false;

    for(int i=0; i<11; i++)
    {
        for(int j=0; j<11; j++)
        {
            for(int k=0; k<11; k++)
            {
                bernstein[i][j][k] = calcBernstein(i, j, (float)k/10);
            }
        }
    }

    xMin = 100.0;
    xMax = -100.0;
    yMin = 100.0;
    yMax = -100.0;

    ControlPoint cp;
    cp.position = QVector3D(-1.5f, -1.5f, 1.0f);
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

    xMin = -1.5;
    xMax = 1.5;
    yMin = -1.5;
    yMax = 1.5;

    startTimer(100);
    setMouseTracking(true);
}

BezierWidget::~BezierWidget()
{
    makeCurrent();

    delete ctrlProgram;

    vbo.destroy();
    vao.destroy();

    doneCurrent();
}

void BezierWidget::addCtrlPoint()
{
    ControlPoint cp;
    cp.position = QVector3D(0.0f, 0.0f, 0.0f);
    cp.color = baseColors[nextColor];
    cp.size = 10.0f;
    cp.selected = true;
    nextColor = (nextColor + 1) % 26;
    ctrlPoints.append(cp);
}

void BezierWidget::selectCtrlPoint(int index)
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

void BezierWidget::moveCtrlPoint(QVector3D moveVector)
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


            if(ctrlPoints[i].position.x() > xMax) {
                xMax = ctrlPoints[i].position.x();
            }
            if(ctrlPoints[i].position.x() < xMin) {
                xMin = ctrlPoints[i].position.x();
            }
            if(ctrlPoints[i].position.y() > yMax) {
                yMax = ctrlPoints[i].position.y();
            }
            if(ctrlPoints[i].position.y() < yMin) {
                yMin = ctrlPoints[i].position.y();
            }
        }
    }

    update();
}

void BezierWidget::deleteCtrlPoint()
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

void BezierWidget::setWireframe()
{
    shadingMode = 0;
}

void BezierWidget::setGouraud()
{
    shadingMode = 1;
}

void BezierWidget::setPhong()
{
    shadingMode = 2;
}

void BezierWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_PROGRAM_POINT_SIZE);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_VERTEX_PROGRAM_TWO_SIDE);
//    glPolygonMode(GL_FRONT, GL_FILL);

    vao.create();
    vao.bind();
    vbo.create();
    indexBuffer.create();

    ctrlProgram = new QOpenGLShaderProgram(this);
    ctrlProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader_points.glsl");
    ctrlProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader_points.glsl");
    ctrlProgram->link();

    wfProgram = new QOpenGLShaderProgram(this);
    wfProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader_wf.glsl");
    wfProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader_wf.glsl");
    wfProgram->link();

    gouraudProgram = new QOpenGLShaderProgram(this);
    gouraudProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader_gouraud.glsl");
    gouraudProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader_gouraud.glsl");
    gouraudProgram->link();

    phongProgram = new QOpenGLShaderProgram(this);
    phongProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader_phong.glsl");
    phongProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader_phong.glsl");
    phongProgram->link();
}

void BezierWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    widgetWidth = w;
    widgetHeight = h;
    aspectRatio = widgetWidth / (float) widgetHeight;

    updateProjection();
}

void BezierWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int numCtrlPoints = ctrlPoints.size();

    vbo.bind();
    vbo.allocate(ctrlPoints.data(), numCtrlPoints * sizeof(ControlPoint));

    ctrlProgram->bind();

    int vPosition = ctrlProgram->attributeLocation("vPosition");
    ctrlProgram->enableAttributeArray(vPosition);
    ctrlProgram->setAttributeBuffer(vPosition, GL_FLOAT, offsetof(ControlPoint, position), 3, sizeof(ControlPoint));

    int vColor = ctrlProgram->attributeLocation("vColor");
    ctrlProgram->enableAttributeArray(vColor);
    ctrlProgram->setAttributeBuffer(vColor, GL_FLOAT, offsetof(ControlPoint, color), 4, sizeof(ControlPoint));

    int vSize = ctrlProgram->attributeLocation("vSize");
    ctrlProgram->enableAttributeArray(vSize);
    ctrlProgram->setAttributeBuffer(vSize, GL_FLOAT, offsetof(ControlPoint, size), 1, sizeof(ControlPoint));

    ctrlProgram->setUniformValue("modelMatrix", modelMatrix);
    ctrlProgram->setUniformValue("viewMatrix", viewMatrix);
    ctrlProgram->setUniformValue("projectionMatrix", projectionMatrix);

    glDrawArrays(GL_POINTS, 0, numCtrlPoints);

    ctrlProgram->release();

    calculateBezier();
    int numVertices = vertices.size();

    if(shadingMode == 0)
    {
        wfProgram->bind();

        vPosition = wfProgram->attributeLocation("vPosition");
        wfProgram->enableAttributeArray(vPosition);
        wfProgram->setAttributeBuffer(vPosition, GL_FLOAT, 0, 3);

        wfProgram->setUniformValue("vColor", QVector4D(1.0, 1.0, 1.0, 1.0));
        wfProgram->setUniformValue("modelMatrix", modelMatrix);
        wfProgram->setUniformValue("viewMatrix", viewMatrix);
        wfProgram->setUniformValue("projectionMatrix", projectionMatrix);

        setIndicesWF();
        indexBuffer.bind();
        indexBuffer.allocate(indices.data(), indices.size() * sizeof(short));

        vbo.allocate(vertices.data(), numVertices * sizeof(QVector3D));

        glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);

        indexBuffer.release();
        wfProgram->release();
    }
    else if(shadingMode == 1)
    {
        setIndicesTri();
        indexBuffer.bind();
        indexBuffer.allocate(indices.data(), indices.size() * sizeof(short));

        vbo.allocate(2 * numVertices * sizeof(QVector3D));
        vbo.write(0, vertices.data(), numVertices * sizeof(QVector3D));
        vbo.write(numVertices * sizeof(QVector3D), normals.data(), numVertices * sizeof(QVector3D));

        gouraudProgram->bind();

        vPosition = gouraudProgram->attributeLocation("vPosition");
        gouraudProgram->enableAttributeArray(vPosition);
        gouraudProgram->setAttributeBuffer(vPosition, GL_FLOAT, 0, 3);

        int vNormal = gouraudProgram->attributeLocation("vNormal");
        gouraudProgram->enableAttributeArray(vNormal);
        gouraudProgram->setAttributeBuffer(vNormal, GL_FLOAT, numVertices * sizeof(QVector3D), 3);

        gouraudProgram->setUniformValue("LightPosition", LightPosition);
        gouraudProgram->setUniformValue("modelMatrix", modelMatrix);
        gouraudProgram->setUniformValue("viewMatrix", viewMatrix);
        gouraudProgram->setUniformValue("projectionMatrix", projectionMatrix);
        gouraudProgram->setUniformValue("AmbientProduct", QVector4D(0.1, 0.1, 0.4, 1.0));
        gouraudProgram->setUniformValue("DiffuseProduct", QVector4D(0.1, 0.4, 0.1, 1.0));
        gouraudProgram->setUniformValue("SpecularProduct", QVector4D(0.4, 0.1, 0.1, 1.0));
        gouraudProgram->setUniformValue("Shininess", 50);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);

        indexBuffer.release();
        gouraudProgram->release();
    }
    else
    {
        setIndicesTri();
        indexBuffer.bind();
        indexBuffer.allocate(indices.data(), indices.size() * sizeof(short));

        vbo.allocate(2 * numVertices * sizeof(QVector3D));
        vbo.write(0, vertices.data(), numVertices * sizeof(QVector3D));
        vbo.write(numVertices * sizeof(QVector3D), normals.data(), numVertices * sizeof(QVector3D));

        phongProgram->bind();

        vPosition = phongProgram->attributeLocation("vPosition");
        phongProgram->enableAttributeArray(vPosition);
        phongProgram->setAttributeBuffer(vPosition, GL_FLOAT, 0, 3);

        int vNormal = phongProgram->attributeLocation("vNormal");
        phongProgram->enableAttributeArray(vNormal);
        phongProgram->setAttributeBuffer(vNormal, GL_FLOAT, numVertices * sizeof(QVector3D), 3);

        phongProgram->setUniformValue("LightPosition", LightPosition);
        phongProgram->setUniformValue("modelMatrix", modelMatrix);
        phongProgram->setUniformValue("viewMatrix", viewMatrix);
        phongProgram->setUniformValue("projectionMatrix", projectionMatrix);
        phongProgram->setUniformValue("AmbientProduct", QVector4D(0.1, 0.1, 0.4, 1.0));
        phongProgram->setUniformValue("DiffuseProduct", QVector4D(0.1, 0.4, 0.1, 1.0));
        phongProgram->setUniformValue("SpecularProduct", QVector4D(0.4, 0.1, 0.1, 1.0));
        phongProgram->setUniformValue("Shininess", 50);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);

        indexBuffer.release();
        phongProgram->release();
    }
}

void BezierWidget::wheelEvent(QWheelEvent * event)
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

void BezierWidget::mousePressEvent(QMouseEvent *event)
{
    rotating = true;
    rotateLastPos = QVector2D(event->localPos());
}

void BezierWidget::mouseReleaseEvent(QMouseEvent *event)
{
    rotating = false;
}

void BezierWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(rotating)
    {
        QVector2D diff = QVector2D(event->localPos()) - rotateLastPos;
        QVector3D n = QVector3D(diff.y(), diff.x(), 0.0);
        viewMatrix.rotate(3, n);

        rotateLastPos = QVector2D(event->localPos());
        update();
    }
}

void BezierWidget::timerEvent(QTimerEvent *event)
{
    QMatrix4x4 rotation;
    rotation.setToIdentity();
    rotation.rotate(1, 1.0, 0.0, 0.0);
    LightPosition = rotation * LightPosition;
    update();
}

void BezierWidget::updateProjection()
{
    float left   = -1.0f * cameraZoom, right = 1.0f * cameraZoom;
    float bottom = -1.0f * cameraZoom, top   = 1.0f * cameraZoom;
    float zNear  = -1.0f * cameraZoom, zFar  = 1.0f * cameraZoom;

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

void BezierWidget::calculateBezier()
{
    int GRID = 3;

    vertices.clear();

    float xRatio = GRID / (xMax - xMin);
    float yRatio = GRID / (yMax - yMin);

    for(int Nu=0; Nu<=10; Nu++)
    {
        for(int Nv=0; Nv<=10; Nv++)
        {
            float X = 0.0;
            float Y = 0.0;
            float Z = 0.0;

            for(int c=0; c<ctrlPoints.size(); c++)
            {
                int xi = static_cast<int> ((ctrlPoints[c].position.x() - xMin) * xRatio) + 0.5;
                int yi = static_cast<int> ((ctrlPoints[c].position.y() - yMin) * yRatio) + 0.5;

                float bi = bernstein[GRID][xi][Nu];
                float bj = bernstein[GRID][yi][Nv];

                X += bi * bj * ctrlPoints[c].position.x();
                Y += bi * bj * ctrlPoints[c].position.y();
                Z += bi * bj * ctrlPoints[c].position.z();
            }

            vertices.append(QVector3D(X, Y, Z));
        }
    }
}

void BezierWidget::setIndicesWF()
{
    indices.clear();

    for(int i=0; i<11; i++)
    {
        for(int j=0; j<11; j++)
        {
            int mid = 11 * i + j;
            int right = mid + 1;
            int bot = mid + 11;

            if(j < 10)
            {
                indices.append(mid);
                indices.append(right);
            }

            if(i < 10)
            {
                indices.append(mid);
                indices.append(bot);
            }
        }
    }
}

void BezierWidget::setIndicesTri()
{
    indices.clear();
    normals.clear();

    int mid, left, right, top, bot;
    QVector3D up, down, leftv, rightv, normal;
    QVector3D nTotal(0.0, 0.0, 0.0);
    float nTotalLength = 0.0;

    for(int i=0; i<11; i++)
    {
        for(int j=0; j<11; j++)
        {
            mid = 11 * i + j;
            left = mid - 1;
            right = mid + 1;
            top = mid - 11;
            bot = mid + 11;

            if(j < 10 && i < 10)
            {
                indices.append(mid);
                indices.append(right);
                indices.append(bot + 1);

                indices.append(bot + 1);
                indices.append(bot);
                indices.append(mid);
            }

            if(j > 0)
            {
                leftv = vertices[left] - vertices[mid];
            }
            if(i < 10)
            {
                down = vertices[bot] - vertices[mid];
            }
            if(j < 10)
            {
                rightv = vertices[right] - vertices[mid];
            }
            if(i > 0)
            {
                up = vertices[top] - vertices[mid];
            }

            if(j > 0 && i < 10)
            {
                normal = QVector3D::crossProduct(leftv, down);
                nTotal += normal;
                nTotalLength += normal.length();
            }
            if(j < 10 && i < 10)
            {
                normal = QVector3D::crossProduct(down, rightv);
                nTotal += normal;
                nTotalLength += normal.length();
            }
            if(j < 10 && i > 0)
            {
                normal = QVector3D::crossProduct(rightv, up);
                nTotal += normal;
                nTotalLength += normal.length();
            }
            if(j > 0 && i > 0)
            {
                normal = QVector3D::crossProduct(up, leftv);
                nTotal += normal;
                nTotalLength += normal.length();
            }

            normals.append(nTotal / nTotalLength);
        }
    }
}
