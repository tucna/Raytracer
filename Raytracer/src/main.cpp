#include <iostream>

#include "camera.h"
#include "image.h"
#include "scene.h"
#include "vec3.h"

int main(int argc, char *argv[])
{
  std::cout << "In progress..." << std::endl;

  unsigned int width = 400;
  unsigned int height = 200;
  unsigned int ns = 100;

  Vec3_32b lookFrom(0, 0, 1);
  Vec3_32b lookAt(0, 0, -1);

  float distToFocus = (lookFrom - lookAt).length();
  float aperture = 0.05f;

  Camera cam(lookFrom, lookAt, Vec3_32b(0, 1, 0), 50, (float)width / (float)height, aperture, distToFocus);
  Image image(width, height);
  Scene scene(&image);

  scene.init(&cam, ns);
  scene.setupDemoScene(1);
  scene.render();

  image.saveToBMP("res/output.bmp");

  return 0;
}
