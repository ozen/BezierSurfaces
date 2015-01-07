#version 150

in vec4 vPosition;
out vec4 color;
uniform vec4 vColor;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    color = vColor;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vPosition;
}
