#version 400 core

precision highp float;

layout(location = 0) out vec4 fragColor;

uniform dvec2 xBounds, yBounds;
uniform int width, height;
const int itters = 300;
const double large = 150.0;

float map(float value, float inMin, float inMax, float outMin, float outMax)
{
    return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
}

double dmap(double value, double inMin, double inMax, double outMin, double outMax)
{
    return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
}

void main()
{
    double A = dmap(gl_FragCoord.x, 0.0, width, xBounds.x, xBounds.y);
    double B = dmap(gl_FragCoord.y, 0.0, height, yBounds.x, yBounds.y);
    double a = A;
    double b = B;
    int i;

    for (i = 0; i < itters; i++)
    {
        double aa = a * a;
        double bb = b * b;
        double ab2 = a * b * 2.0;

        a = aa - bb + A;
        b = ab2 + B;

        if (aa + bb > large) break;
    }

    float p = float(i) / float(itters);
    fragColor = vec4(log(p), sin(p), p, 1);
}