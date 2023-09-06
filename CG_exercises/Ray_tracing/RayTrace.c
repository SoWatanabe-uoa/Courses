#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <float.h>
#include <stdlib.h>

#include <time.h>
#include <stdio.h>

#include "Scene.h"
#include "RayTrace.h"
#include "Geometry.h"


// Clamp c's entries between m and M. 
static void clamp(Color* c, float m, float M) {
    c->_red = fminf(fmaxf(c->_red, m), M);
    c->_green = fminf(fmaxf(c->_green, m), M);
    c->_blue = fminf(fmaxf(c->_blue, m), M);
}


// Complete
// Given a ray (origin, direction), check if it intersects a given
// sphere.
// Return 1 if there is an intersection, 0 otherwise.
// *t contains the distance to the closest intersection point, if any.
static int
hitSphere(Vector3 origin, Vector3 direction, Sphere sphere, float* t)
{
    Vector3 direction_nm, o;
    float od_prod, d_len, o_len, root;

    normalize(direction, &direction_nm);

    // |d|^2
    computeDotProduct(direction_nm, direction_nm, &d_len);
    //o Vector
    sub(origin, sphere._center, &o);
    //od product
    computeDotProduct(direction_nm, o, &od_prod);
    od_prod *= 2.0;

    
    // |o|^2
    computeDotProduct(o, o, &o_len);

    o_len -= powf(sphere._radius, 2.0);
    
    root = sqrtf(od_prod * od_prod - 4.0 * d_len * o_len);
    if(root < 0) return 0;

    *t = (-od_prod - root) / (2.0 * d_len);

    if(*t < 0){
        return 0;
    } else {
        return 1;
    }

}


// Check if the ray defined by (scene._camera, direction) is intersecting
// any of the spheres defined in the scene.
// Return 0 if there is no intersection, and 1 otherwise.
//
// If there is an intersection:
// - the position of the intersection with the closest sphere is computed 
// in hit_pos
// - the normal to the surface at the intersection point in hit_normal
// - the diffuse color and specular color of the intersected sphere
// in hit_color and hit_spec
static int
hitScene(Vector3 origin, Vector3 direction, Scene scene,
    Vector3* hit_pos, Vector3* hit_normal,
    Color* hit_color, Color* hit_spec)
{
    Vector3 o = origin;
    Vector3 d = direction;

    float t_min = FLT_MAX;
    int hit_idx = -1;
    Sphere hit_sph;

    // For each sphere in the scene
    int i;
    for (i = 0; i < scene._number_spheres; ++i) {
        Sphere curr = scene._spheres[i];
        float t = 0.0f;
        if (hitSphere(o, d, curr, &t)) {
            if (t < t_min) {
                hit_idx = i;
                t_min = t;
                hit_sph = curr;
            }
        }
    }

    if (hit_idx == -1) return 0;

    Vector3 td;
    mulAV(t_min, d, &td);
    add(o, td, hit_pos);

    Vector3 n;
    sub(*hit_pos, hit_sph._center, &n);
    mulAV(1.0f / hit_sph._radius, n, hit_normal);

    // Save the color of the intersected sphere in hit_color and hit_spec
    *hit_color = hit_sph._color;
    *hit_spec = hit_sph._color_spec;

    return 1;
}


// Save the image in a raw buffer (texture)
// The memory for texture is allocated in this function. It needs to 
// be freed in the caller.
static void saveRaw(Color** image, int width, int height, GLubyte** texture) {
    int count = 0;
    int i;
    int j;
    *texture = (GLubyte*)malloc(sizeof(GLubyte) * 3 * width * height);

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            unsigned char red = (unsigned char)(image[i][j]._red * 255.0f);
            unsigned char green = (unsigned char)(image[i][j]._green * 255.0f);
            unsigned char blue = (unsigned char)(image[i][j]._blue * 255.0f);

            (*texture)[count] = red;
            count++;

            (*texture)[count] = green;
            count++;

            (*texture)[count] = blue;
            count++;
        }
    }
}


// Complete
// Given an intersection point (hit_pos),
// the normal to the surface at the intersection point (hit_normal),
// and the color (diffuse and specular) terms at the intersection point,
// compute the colot intensity at the point by applying the Phong
// shading model.
// Return the color intensity in *color.
static void
shade(Vector3 hit_pos, Vector3 hit_normal,
    Color hit_color, Color hit_spec, Scene scene, Color* color)
{

    float nl_prod, cos, in_prod, vr_prod;
    Vector3 L, V, I, N, R, light;
    Vector3 pos, normal;
    Color cl, spec;
    // Complete
    // ambient component

    color->_red += hit_color._red * scene._ambient._red;
    color->_green += hit_color._green * scene._ambient._green;
    color->_blue += hit_color._blue * scene._ambient._blue; 

     // for each light in the scene
    int l;
    for (l = 0; l < scene._number_lights; l++) {
        // Complete
        // Form a shadow ray and check if the hit point is under
        // direct illumination from the light source

        // Complete
        // diffuse component

        int isHit = 0;
        sub(scene._lights[l]._light_pos, hit_pos, &light);
        normalize(light, &light);
        float sigma = pow(10, -5);

        Vector3 hit_normal_mul;
        hit_normal_mul._x = sigma * hit_normal._x;
        hit_normal_mul._y = sigma * hit_normal._y;
        hit_normal_mul._z = sigma * hit_normal._z;

        Vector3 res;
        add(hit_pos, hit_normal_mul, &res);
        isHit = hitScene(res, light, scene, &pos, &normal, &cl, &spec);

        if(isHit) continue;
        sub(scene._lights[l]._light_pos, hit_pos, &L);
        normalize(L, &L);

        computeDotProduct(hit_normal, L, &nl_prod);
        cos = fmaxf(nl_prod, 0.0);

        color->_red += hit_color._red * scene._lights[l]._light_color._red * cos;
        color->_green += hit_color._green * scene._lights[l]._light_color._green * cos;
        color->_blue += hit_color._blue * scene._lights[l]._light_color._blue * cos;

        // Complete
        // specular component

        sub(scene._camera, hit_pos, &V); // V vector
        sub(hit_pos, scene._lights[l]._light_pos, &I); // I Vector
        N = hit_normal;

        normalize(V, &V);
        normalize(I, &I);

        computeDotProduct(I, N, &in_prod);

        mulVA(N, in_prod * -2.0, &R);
        add(I, R, &R);

        computeDotProduct(V, R, &vr_prod);
        cos = pow(fmaxf(vr_prod, 0.0), 10);    

		color->_red += hit_spec._red * scene._lights[l]._light_color._red * cos;
        color->_green += hit_spec._green * scene._lights[l]._light_color._green * cos;
        color->_blue += hit_spec._blue * scene._lights[l]._light_color._blue * cos;
    }
}


static void rayTrace(Vector3 origin, Vector3 direction_normalized,
    Scene scene, Color* color)
{
    Vector3 hit_pos;
    Vector3 hit_normal;
    Color hit_color;
    Color hit_spec;
    int hit;

    // does the ray intersect an object in the scene?
    hit =
        hitScene(origin, direction_normalized, scene,
            &hit_pos, &hit_normal, &hit_color,
            &hit_spec);

    // no hit
    if (!hit) {
        color->_red = scene._background_color._red;
        color->_green = scene._background_color._green;
        color->_blue = scene._background_color._blue;
        return;
    }

    // otherwise, apply the shading model at the intersection point
    shade(hit_pos, hit_normal, hit_color, hit_spec, scene, color);
}


void rayTraceScene(Scene scene, int width, int height, GLubyte** texture) {
    Color** image;
    int i;
    int j;

    Vector3 camera_pos;
    float screen_scale;

    image = (Color**)malloc(height * sizeof(Color*));
    for (i = 0; i < height; i++) {
        image[i] = (Color*)malloc(width * sizeof(Color));
    }

    // get parameters for the camera position and the screen fov
    camera_pos._x = scene._camera._x;
    camera_pos._y = scene._camera._y;
    camera_pos._z = scene._camera._z;

    screen_scale = scene._scale;

    float random;
    srand(time(NULL));   // Initialization, should only be called once.
    int k;
    int sample = 10;
    Color avg;


    // go through each pixel
    // and check for intersection between the ray and the scene
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Compute (x,y) coordinates for the current pixel 
            // in scene space

            avg._red = 0.f;
            avg._green = 0.f;
            avg._blue = 0.f;

            for (k = 0; k < sample; k++){
                random = rand();      // Returns a pseudo-random integer between 0 and RAND_MAX.
                random -= RAND_MAX / 2;
                random /= RAND_MAX / 2;
                random *= screen_scale / 2;

                float x = screen_scale * j - 0.5f * screen_scale * width + random;
                float y = screen_scale * i - 0.5f * screen_scale * height + random;

                // Form the vector camera to current pixel
                Vector3 direction;
                Vector3 direction_normalized;

                direction._x = x - camera_pos._x;
                direction._y = y - camera_pos._y;
                direction._z = -camera_pos._z;

                normalize(direction, &direction_normalized);

                Vector3 origin = scene._camera;
                Color color; 
                color._red = 0.f;
                color._green = 0.f;
                color._blue = 0.f;
                rayTrace(origin, direction_normalized, scene, &color);
                clamp(&color, 0.f, 1.f);
                avg._red += color._red;
                avg._green += color._green;
                avg._blue += color._blue;
            }
            avg._red /= sample;
            avg._green /= sample;
            avg._blue /= sample;
            image[i][j] = avg;
        }
    }

    // save image to texture buffer
    saveRaw(image, width, height, texture);

    for (i = 0; i < height; i++) {
        free(image[i]);
    }

    free(image);
}
