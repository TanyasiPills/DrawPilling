#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform float xRatio;
uniform float yRatio;
uniform float xOffset;
uniform float yOffset;
uniform float scale;

out vec2 fragTexCoord;

void main()
{
	
	float clampedX = clamp(position.x, -1.0, 1.0);
	float clampedY = clamp(position.y, -1.0, 1.0);

	float normalizedX = 0.5 * (position.x + 1.0);
    float normalizedY = 0.5 * (position.y + 1.0);

    normalizedX *= xRatio;
    normalizedY *= yRatio;

    clampedX = (normalizedX * 2.0) - 1.0;
    clampedY = (normalizedY * 2.0) - 1.0;

	clampedX += xOffset;
	clampedY += yOffset;
	clampedX *= scale;
	clampedY *= scale;

	vec2 adjustedPosition = vec2(clampedX, clampedY);
	gl_Position = vec4(adjustedPosition, 0.0, 1.0);
	fragTexCoord = adjustedPosition;
}

#shader fragment
#version 330 core

uniform vec3 uColor;
void main() {
    gl_FragColor = vec4(uColor, 1.0);
}