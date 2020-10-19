#shader vertex
#version 400

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 col;
out vec4 color;

out vec4 ex_worldPosition;
out vec4 ex_worldNormal;

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vertNormal;

void main () {
    color = vec4(col, 1.0);

    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (vp, 1.0);
    ex_worldPosition =  modelMatrix * vec4(vp, 1.0);
    ex_worldNormal =    modelMatrix * vec4(vertNormal, 1.0);
};

#shader fragment
#version 400

in vec4 ex_worldPosition;
in vec4 ex_worldNormal;

in vec4 color;
out vec4 frag_colour;

void main () {
     frag_colour = color;
};