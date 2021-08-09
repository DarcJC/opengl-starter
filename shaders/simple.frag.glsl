#version 460 core

in vec3 customColor;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D customTexture;

void main() {
    fragColor = texture(customTexture, texCoord) * vec4(customColor, 1.0);
}
