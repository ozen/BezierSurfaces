#version 150

in vec4 vPosition;
in vec3 vNormal;
out vec3 fN;
out vec3 fE;
out vec3 fL;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 LightPosition;

void main()
{
    fN = vNormal;
    fE = vPosition.xyz;
    fL = LightPosition - vPosition.xyz;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vPosition;
}
