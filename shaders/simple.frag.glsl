#version 460 core

in vec3 customColor;
out vec4 fragColor;

void main() {
    fragColor = vec4(customColor, 1.0);
}
