#shader vertex
#version 400

layout(location = 0) in vec3 vp;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(vp, 1.0);
};

#shader fragment
#version 400

out vec4 frag_colour;

uniform vec3 color;

void main () {
     frag_colour = vec4(color, 1.0);
};