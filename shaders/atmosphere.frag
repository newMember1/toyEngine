#version 330 core

in vec3 skyCoord;
out vec4 FragColor;

uniform vec3 sunDirec;

//all in kilometer
const float earthRadius = 6360e3;
const float atmosphereRadius = 6420e3;
const float rayleighScaleHeight = 7994;
const float mieScaleHeight = 1200;
const float PI = 3.1415926;
const vec3 betaRayleigh = vec3(3.8e-6f, 13.5e-6f, 33.1e-6f);
const vec3 betaMie = vec3(21e-6);

bool solveQuadratic(float a, float b, float c, out float x1, out float x2)
{
    if (b == 0)
    {
        // Handle special case where the the two vector ray.dir and V are perpendicular
        // with V = ray.orig - sphere.centre
        if (a == 0) return false;
        x1 = 0;
        x2 = sqrt(-c / a);
        return true;
    }
    float discr = b * b - 4 * a * c;
    if (discr < 0) return false;
    float q = (b < 0) ? -0.5 * (b - sqrt(discr)) : -0.5 * (b + sqrt(discr));
    x1 = q / a;
    x2 = c / q;

    return true;
}

bool raySphereIntersect(vec3 orig, vec3 dir, float radius, out float t0, out float t1)
{
    // They ray dir is normalized so A = 1
    float A = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
    float B = 2 * (dir.x * orig.x + dir.y * orig.y + dir.z * orig.z);
    float C = orig.x * orig.x + orig.y * orig.y + orig.z * orig.z - radius * radius;

    if (!solveQuadratic(A, B, C, t0, t1)) return false;

    if (t0 > t1)
    {
        float t = t0;
        t0 = t1;
        t1 =  t;
    }

    return true;
}

void main()
{
    float tmin = 0.1;
    float tmax = 1e8;
    vec3 sunDirection = -normalize(sunDirec);
    vec3 atmospherePoint = skyCoord * atmosphereRadius;
    vec3 orig = vec3(0, earthRadius + 1, 0);
    vec3 dir = normalize(atmospherePoint - orig);

    float t0, t1;
    if (!raySphereIntersect(orig, dir, atmosphereRadius, t0, t1) || t1 < 0) return;
    if (t0 > tmin && t0 > 0) tmin = t0;
    if (t1 < tmax) tmax = t1;

    int numSamples = 16;
    int numSamplesLight = 8;
    float segmentLength = (tmax - tmin) / numSamples;
    float tCurrent = tmin;
    vec3 sumR = vec3(0);
    vec3 sumM = vec3(0); // mie and rayleigh contribution
    float opticalDepthR = 0, opticalDepthM = 0;
    float mu = dot(dir, sunDirection); // mu in the paper which is the cosine of the angle between the sun direction and the ray direction
    float phaseR = 3.f / (16.f * PI) * (1 + mu * mu);
    float g = 0.76f;
    float phaseM = 3.f / (8.f * PI) * ((1.f - g * g) * (1.f + mu * mu)) / ((2.f + g * g) * pow(1.f + g * g - 2.f * g * mu, 1.5f));
    for (int i = 0; i < numSamples; ++i)
    {
        vec3 samplePosition = orig + (tCurrent + segmentLength * 0.5f) * dir;
        float height = length(samplePosition) - earthRadius;
        // compute optical depth for light
        float hr = exp(-height / rayleighScaleHeight) * segmentLength;
        float hm = exp(-height / mieScaleHeight) * segmentLength;
        opticalDepthR += hr;
        opticalDepthM += hm;
        // light optical depth
        float t0Light, t1Light;
        raySphereIntersect(samplePosition, sunDirection, atmosphereRadius, t0Light, t1Light);
        float segmentLengthLight = t1Light / numSamplesLight, tCurrentLight = 0;
        float opticalDepthLightR = 0, opticalDepthLightM = 0;
        int j;
        for (j = 0; j < numSamplesLight; ++j)
        {
            vec3 samplePositionLight = samplePosition + (tCurrentLight + segmentLengthLight * 0.5f) * sunDirection;
            float heightLight = length(samplePositionLight) - earthRadius;
            if (heightLight < 0) break;
            opticalDepthLightR += exp(-heightLight / rayleighScaleHeight) * segmentLengthLight;
            opticalDepthLightM += exp(-heightLight / mieScaleHeight) * segmentLengthLight;
            tCurrentLight += segmentLengthLight;
        }
        if (j == numSamplesLight)
        {
            vec3 tau = betaRayleigh * (opticalDepthR + opticalDepthLightR) + betaMie * 1.1f * (opticalDepthM + opticalDepthLightM);
            vec3 attenuation = exp(-tau);
            sumR += attenuation * hr;
            sumM += attenuation * hm;
        }
        tCurrent += segmentLength;
    }
    FragColor = vec4((sumR * betaRayleigh * phaseR + sumM * betaMie * phaseM) * 20, 1.0f);
}
