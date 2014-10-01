#version 330
in vec2 uv;
out vec3 color;

void main() {
    color = vec3(uv[0], uv[1], 0.0);
}
