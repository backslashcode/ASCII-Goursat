#include <iostream>
#include <math.h>
#include <stdio.h>
#include "goursat.h"
#include "control.h"

#define WIDTH 100
#define HEIGHT 29
#define MIN_IT 10000
#define ratio 1.8

void render()
{
    const int width = WIDTH, height = HEIGHT;
    char gradient[] = " .':,\"!/r(l1Z4H9W8$@";
    char framebuff[width * height + 1] = { '@', };
    framebuff[width * height] = '\0';
    vec3 light = norm(vec3(-0.5, 0, 0));

    Control control;

    for (size_t t = 0;; t++) {
        for (size_t i = 0; i < width; i++) {

            for (size_t j = 0; j < height; j++) {
                int x = i, y = j;

                vec2 uv = vec2(i, j) / vec2(width, height) - 0.5;
                uv.x *= ratio;
                vec3 ro = vec3(control.ro_x, control.ro_y, control.ro_z);
                vec3 rd = norm(vec3(1, uv + 0.1));

                control.init(&ro, &rd);
                control.control();

                int color = 0;
                double diff = 0;
                double min_it = MIN_IT;
                vec3 n = 0;

                double ra = 1.5 + 0.015 * cos(t * 0.01);
                double rb = ra + 0.6 * sin(t * 0.05);

                vec2 it_h = goursat_intersect(ro, rd, ra, rb);
                if (it_h.x > 0 && it_h.x <= min_it) {
                    min_it = it_h.x;
                    vec3 pos = ro + vec3(it_h.x) * rd;
                    n = goursat_normal(pos, rb);
                }


                diff = dot(light, n);
                if (min_it < MIN_IT) {
                    diff = diff * 0.2 + 0.3;
                    color = diff * 20;
                    if (color < 0) color = 0;
                    if (color > 19) color = 19;
                }
                framebuff[j * width + i] = gradient[color];
            }
        }
        control.reset();
        printf("%s", framebuff);
    }
}

int main() 
{
    system("mode con cols=100 lines=29");
    render();
}