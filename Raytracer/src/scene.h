#pragma once

#include <vector>

#include "image.h"
#include "randomNumber.h"
#include "vec3.h"

class Camera;
class HitableList;

class Scene
{
public:
    Scene(Image* image) : _image(image) {}

    void init(Camera* camera, unsigned int raysPerPixel) { _cam = camera; _raysPerPixel = raysPerPixel; }
    void setupDemoScene(int id);
    void render();

private:
    Vec3_32b color(Ray r, int depth);

    Image* _image;
    unsigned int _raysPerPixel;

    HitableList* _world;
    Camera* _cam;

    RandomNumber _dice;
};
