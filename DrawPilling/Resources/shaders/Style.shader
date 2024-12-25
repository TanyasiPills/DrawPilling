#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform float xRatio;
uniform float yRatio;

out vec2 fragTexCoord;

void main()
{
	float clampedX = clamp(position.x, -0.8, 0.8);
	float clampedY = clamp(position.y, -0.8, 0.8);

	float normalizedX = 0.5 * (clampedX + 1.0);
    float normalizedY = 0.5 * (clampedY + 1.0);

    normalizedX *= xRatio;
    normalizedY *= yRatio;

    clampedX = (normalizedX * 2.0) - 1.0;
    clampedY = (normalizedY * 2.0) - 1.0;

	vec2 adjustedPosition = vec2(clampedX, clampedY);
	gl_Position = vec4(adjustedPosition, position.zw);
	fragTexCoord = adjustedPosition;
}

#shader fragment
#version 330 core

uniform vec3 circleColor;
void main() {
    gl_FragColor = vec4(circleColor, 1.0);
}