#version 330 core

precision highp float;

layout(location = 0) out vec4 fragColor;

uniform int width;
uniform int height;
const int itters = 200;
const float large = 100.0;

float map(float value, float min1, float max1, float min2, float max2)
{
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main()
{
    float A = map(gl_FragCoord.x, 0.0, width, -2.0, 1);
    float B = map(gl_FragCoord.y, 0.0, height, -1.5, 1.5);
    float a = A;
    float b = B;
    int i;

    for (i = 0; i < itters; i++)
    {
        float aa = a * a;
        float bb = b * b;
        float ab2 = a * b * 2.0;

        a = aa - bb + A;
        b = ab2 + B;

        if (aa + bb > large) break;
    }

    float p = float(i) / float(itters);
    fragColor = vec4(log(p), sin(p), p, 1);
}