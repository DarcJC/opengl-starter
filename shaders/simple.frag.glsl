#version 460 core

in vec3 customColor;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D customTexture;
uniform sampler2D texture1;

void main() {
    fragColor = mix(texture(customTexture, texCoord), texture(texture1, texCoord), 0.2) * vec4(customColor, 1.0);
}
