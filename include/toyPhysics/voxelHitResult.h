#ifndef VOXELHITRESULT_H
#define VOXELHITRESULT_H

#include <glm/glm.hpp>

using glm::vec3;

class VoxelHitResult
{
public:
    void setVoxelHit(bool v) { voxelHit = v; }
    bool getVoxelHit() { return voxelHit; }

    void setStartPenetrating(bool s) { startPenetrating = s;}
    bool getStartPenetrating() { return startPenetrating; }

    void setTime(float t) { time = t; }
    float getTime() { return time; }

    void setDistance(float d) { distance = d; }
    float setDistance() { return distance; }

    void setLocation(vec3 l) { location = l; }
    vec3 getLocation() { return location; }

    void setImpactPoint(vec3 i) { impactPoint = i; }
    vec3 getImpactPoint() { return impactPoint; }

    void setNormal(vec3 n) { normal = glm::normalize(n); }
    vec3 getNormal() { return normal; }

    void setImpactNormal(vec3 n) { impactNormal = glm::normalize(n); }
    vec3 setImpactNormal() { return impactNormal; }

    void setTraceStart(vec3 t) { traceStart = t; }
    vec3 getTraceStart() { return traceStart; }

    void setTraceEnd(vec3 t) { traceEnd = t; }
    vec3 getTraceEnd() { return traceEnd; }

    void setPenetrationDepth(float p) { penetrationDepth = p; }
    float getPenetrationDepth() { return penetrationDepth; }
private:
    bool voxelHit;
    bool startPenetrating;
    float time;
    float distance;
    vec3 location;
    vec3 impactPoint;
    vec3 normal;
    vec3 impactNormal;
    vec3 traceStart;
    vec3 traceEnd;
    float penetrationDepth;
};

#endif // VOXELHITRESULT_H
