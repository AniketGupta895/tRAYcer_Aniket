#include "inclusions.h"

int main(){
    hittable_list world;

    shared_ptr<material> material1 = make_shared<metal>(colour(0.9, 0.9, 0.9));
    shared_ptr<material> material2 = make_shared<lambertian>(colour(0.3, 0.1, 0.6));
    shared_ptr<material> material3 = make_shared<lambertian>(colour(0.4, 0.6, 0.9));
    shared_ptr<material> material4 = make_shared<metal>(colour(0.5, 0.7, 0.6), 0.5);
    shared_ptr<material> material5 = make_shared<metal>(colour(1, 1, 1), 0);
    shared_ptr<material> material6 = make_shared<metal>(colour(0.3, 0.6, 0.2), 0.7);
    shared_ptr<material> material7 = make_shared<metal>(colour(0, 0.6, 0.6), 0.3);
    shared_ptr<material> material8 = make_shared<dielectric>(colour(1, 1, 1), 1.5);
    shared_ptr<material> material9 = make_shared<dielectric>(colour(1, 1, 1), 1 / 1.33);
    shared_ptr<material> material10 = make_shared<dielectric>(colour(1, 1, 1), 1 / 1.5);

    world.add(make_shared<sphere>(vec3(-1,0.5,-6), 0.5, material1));
    world.add(make_shared<sphere>(vec3(0,0,-6), 0.5, material9));
    world.add(make_shared<sphere>(vec3(1,0,-6), 0.5, material3));
    world.add(make_shared<sphere>(vec3(0.5, -0.1, -5), 0.2, material8));
    world.add(make_shared<sphere>(vec3(-0.8,0.8,-5.6), 0.3, material6));
    world.add(make_shared<sphere>(vec3(0,1.3,-6), 0.7, material7));
    world.add(make_shared<sphere>(vec3(0,-100.5,-6), 100, material2));
    world.add(make_shared<sphere>(vec3(-0.3, 0.35, -4.7), 0.5, material8));
    world.add(make_shared<sphere>(vec3(-0.3, 0.35, -4.7), 0.3, material10));

    initrand();

    camera world_camera;
    world_camera.max_depth = 40;
    world_camera.samples_per_pixel = 200;
    world_camera.render(world);
}