#include "pch.h"
#include "Light.h"

Light::Light(
    const std::array<float, 4>& ambient,
    const std::array<float, 4>& diffuse,
    const std::array<float, 4>& position,
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
    //std::cout << "Position: x: " << diffuseLightPos.data()[0] << std::endl;
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

const std::array<float, 4>& Light::GetAmbient() const {
    return ambientLight;
}

const std::array<float, 4>& Light::GetDiffuse() const {
    return diffuseLight;
}

const std::array<float, 4>& Light::GetPosition() const {
    return diffuseLightPos;
}

GLenum Light::GetLightID() const {
    return lightID;
}

// -------------------
//      Setters
// -------------------

void Light::SetAmbient(const std::array<float, 4>& ambient) {
    ambientLight = ambient;
}

void Light::SetAmbient(float x, float y, float z, float a) {
    ambientLight = { x, y, z, a};
}

void Light::SetDiffuse(const std::array<float, 4>& diffuse) {
    diffuseLight = diffuse;
}

void Light::SetDiffuse(float x, float y, float z, float a) {
    diffuseLight = { x, y, z , a};
}

void Light::SetPosition(const std::array<float, 4>& position) {
    diffuseLightPos = position;
}

void Light::SetPosition(float x, float y, float z) {
    diffuseLightPos = { x, y, z };
}
