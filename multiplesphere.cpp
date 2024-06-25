#include "inclusions.h"

int main(){
    hittable_list world;

    world.add(make_shared<sphere>(vec3(0,0,-3), 0.5));
    world.add(make_shared<sphere>(vec3(0,-100.5,-3), 100));

    initrand();

    camera world_camera;
    world_camera.samples_per_pixel = 200;
    world_camera.renderNreflectances(world, 10);
}