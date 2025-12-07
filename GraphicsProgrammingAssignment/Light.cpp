#include "pch.h"
#include "Light.h"

Light::Light(
    const std::array<float, 3>& ambient,
    const std::array<float, 3>& diffuse,
    const std::array<float, 3>& position,
    GLenum id
): 
    ambientLight(ambient),
    diffuseLight(diffuse),
    diffuseLightPos(position),
    lightID(id)
{
}

void Light::Move(float x, float y, float z) {
    diffuseLightPos[0] = x;
    diffuseLightPos[1] = y;
    diffuseLightPos[2] = z;
}

void Light::Update() {
    glLightfv(lightID, GL_AMBIENT, ambientLight.data());
    glLightfv(lightID, GL_DIFFUSE, diffuseLight.data());
    glLightfv(lightID, GL_POSITION, diffuseLightPos.data());
}

void Light::Enable() {
    glEnable(lightID);
}

void Light::Disable() {
    glDisable(lightID);
}

// -------------------
//      Getters
// -------------------

const std::array<float, 3>& Light::GetAmbient() const {
    return ambientLight;
}

const std::array<float, 3>& Light::GetDiffuse() const {
    return diffuseLight;
}

const std::array<float, 3>& Light::GetPosition() const {
    return diffuseLightPos;
}

GLenum Light::GetLightID() const {
    return lightID;
}

// -------------------
//      Setters
// -------------------

void Light::SetAmbient(const std::array<float, 3>& ambient) {
    ambientLight = ambient;
}

void Light::SetAmbient(float x, float y, float z) {
    ambientLight = { x, y, z };
}

void Light::SetDiffuse(const std::array<float, 3>& diffuse) {
    diffuseLight = diffuse;
}

void Light::SetDiffuse(float x, float y, float z) {
    diffuseLight = { x, y, z };
}

void Light::SetPosition(const std::array<float, 3>& position) {
    diffuseLightPos = position;
}

void Light::SetPosition(float x, float y, float z) {
    diffuseLightPos = { x, y, z };
}
