#include <iostream>

#include "camera.h"
#include "image.h"
#include "hitablelist.h"
#include "material.h"
#include "sphere.h"
#include "randomNumber.h"
#include "ray.h"
#include "vec3.h"
#include "scene.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "In progress..." << endl;

    unsigned int width = 400;
    unsigned int height = 200;
    unsigned int ns = 100;

    Vec3_32b lookFrom(0,0,1);
    Vec3_32b lookAt(0, 0, -1);
    float dist_to_focus = (lookFrom - lookAt).length();
    float aperture = 0.05f;

    Camera cam(lookFrom, lookAt, Vec3_32b(0,1,0), 50, (float)width / (float)height, aperture, dist_to_focus);

    Image image(width, height);
    Scene scene(image);
    scene.init(&cam, ns);

    image.saveToBMP("res/output.bmp");

    return 0;
}
