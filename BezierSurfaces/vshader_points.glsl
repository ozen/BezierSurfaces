#version 150

in vec4 vPosition;
in vec4 vColor;
in float vSize;
out vec4 color;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    color = vColor;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vPosition;
    gl_PointSize = vSize;
}
