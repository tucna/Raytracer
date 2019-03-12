#pragma once

#include "randomNumber.h"
#include "vec3.h"

class Camera;
class Image;
class HitableList;

class Scene
{
public:
    Scene(Image* image) : _image(image) {}

    void init(Camera* camera, unsigned int raysPerPixel) { _cam = camera; _raysPerPixel = raysPerPixel; }
    void setupDemoScene(int id);
    void render();

private:
    Vec3_32b color(const Ray& r, int depth);

    Camera* _cam;
    HitableList* _world;
    Image* _image;
    RandomNumber _dice;

    unsigned int _raysPerPixel;
};
