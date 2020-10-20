#shader vertex
#version 400

layout(location=0) in vec3 vp;

void main () {
     gl_Position = vec4 (vp, 1.0);
};

#shader fragment
#version 400

out vec4 frag_colour;

void main () {
     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);
};