#include "inclusions.h"

int main(){
    hittable_list world;

    auto material_ground = make_shared<lambertian>(colour(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(colour(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(colour(1, 1 ,1), 1.50);
    auto material_bubble = make_shared<dielectric>(colour(1, 1 ,1), 1.00 / 1.50);
    auto material_right  = make_shared<metal>(colour(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(vec3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(vec3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<sphere>(vec3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(vec3(-1.0,    0.0, -1.0),   0.4, material_bubble));
    world.add(make_shared<sphere>(vec3( 1.0,    0.0, -1.0),   0.5, material_right));


    initrand();
    

    camera world_camera;
    world_camera.max_depth = 20;
    world_camera.samples_per_pixel = 10;
    world_camera.vfov     = 20;
    world_camera.camera_origin = vec3(-2,2,1);
    world_camera.lookat   = vec3(0,0,-1);
    world_camera.v_up      = vec3(0,1,0);
    world_camera.defocus_angle = 10.0;
    world_camera.focus_dist    = 3.4;
    world_camera.render(world);
}