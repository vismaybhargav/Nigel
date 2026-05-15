#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

uniform sampler2D texture0;
uniform vec2 tiling;

void main() {
    finalColor = texture(texture0, fragTexCoord * tiling);
}