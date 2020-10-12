#shader vertex
#version 330

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 col;
out vec4 color;

layout(location=0) in vec3 vp;

void main () {
    color = vec4(col, 1.0);

    gl_Position = modelMatrix * vec4 (vp, 1.0);
};

#shader fragment
#version 330

in vec4 color;
out vec4 frag_colour;

void main () {
     frag_colour = color;
};