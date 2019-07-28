#version 400 core

precision highp float;

layout(location = 0) out vec4 fragColor;

uniform dvec2 xBounds, yBounds;
uniform int width, height;
uniform int iters = 300;
const double large = 150.0;

double map(double value, double inMin, double inMax, double outMin, double outMax)
{
    return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
}

void main()
{
    double A = map(gl_FragCoord.x, 0.0, width, xBounds.x, xBounds.y);
    double B = map(gl_FragCoord.y, 0.0, height, yBounds.x, yBounds.y);
    double a = A;
    double b = B;
    int i;

    for (i = 0; i < iters; i++)
    {
        double aa = a * a;
        double bb = b * b;
        double ab2 = a * b * 2.0;

        a = aa - bb + A;
        b = ab2 + B;

        if (aa + bb > large) break;
    }

    float p = float(i) / float(iters);
    fragColor = vec4(log(p), sin(p), p, 1);
}