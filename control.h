#pragma once
#include <Windows.h>

/*
* WASD - rotation 
* Arrow keys - movement
* Space - reset view
*/

enum keys { Released, W, A, S, D, Left, Right, Up, Down, Space };
void rotate_x(vec3& v, double angle) {
    double z = v.z;
    double y = v.y;
    z = v.z * cos(angle) - v.y * sin(angle);
    y = v.z * sin(angle) + v.y * cos(angle);
    v.z = z;
    v.y = y;
}

void rotate_y(vec3& v, double angle) {
    double x = v.x;
    double z = v.z;
    x = v.x * cos(angle) - v.z * sin(angle);
    z = v.x * sin(angle) + v.z * cos(angle);
    v.x = x;
    v.z = z;
}
void rotate_z(vec3& v, double angle) {
    double x = v.x;
    double y = v.y;
    x = (v.x * cos(angle) - v.y * sin(angle));
    y = (v.x * sin(angle) + v.y * cos(angle));
    v.x = x;
    v.y = y;
}

class Control {
    vec3* ro;
    vec3* rd;
    enum keys key_state = Released;
    double rotate_speed = 0.09;
    double move_speed = 0.05;
    double an_z = 17, an_y = 32, an_x = 0;
    bool key_pressed[9] = { 0, }; //W,A,S,D,Left,Right,Up,Down,Spase
public:
    double ro_x = -5;
    double ro_y = 0;
    double ro_z = 0;

    Control() :rd(NULL) {
        ro = NULL;
    }

    ~Control(){}

    void init(vec3* ro_, vec3* rd_) {
        ro = ro_;
        rd = rd_;
    }
    void rotate() {
        if (GetKeyState(87) & 0x8000) {
            if (!key_pressed[0]) {
                key_state = W;
                an_y++;
                key_pressed[0] = true;
            }
        }
        if (GetKeyState(65) & 0x8000) {
            if (!key_pressed[1]) {
                key_state = A;
                an_z++;
                key_pressed[1] = true;

            }
        }
        if (GetKeyState(83) & 0x8000) {
            if (!key_pressed[2]) {
                key_state = S;
                an_y--;
                key_pressed[2] = true;

            }
        }
        if (GetKeyState(68) & 0x8000) {
            if (!key_pressed[3]) {
                key_state = D;
                an_z--;
                key_pressed[3] = true;

            }
        }
        rotate_x(*ro, an_x * rotate_speed);
        rotate_x(*rd, an_x * rotate_speed);

        rotate_y(*ro, an_y * rotate_speed);
        rotate_y(*rd, an_y * rotate_speed);

        rotate_z(*ro, an_z * rotate_speed);
        rotate_z(*rd, an_z * rotate_speed);
    }

    void move() {
        if (GetKeyState(37) & 0x8000) {
            if (!key_pressed[4]) {
                key_state = Left;
                ro_y -= move_speed;
                key_pressed[4] = true;
            }
        }
        ro->y = ro_y;

        if (GetKeyState(39) & 0x8000) {
            if (!key_pressed[5]) {
                key_state = Right;
                ro_y += move_speed;
                key_pressed[5] = true;
            }
        }
        ro->y = ro_y;

        if (GetKeyState(38) & 0x8000) {
            if (!key_pressed[6]) {
                key_state = Up;
                ro_x += move_speed;
                key_pressed[6] = true;
            }
        }
        ro->x = ro_x;

        if (GetKeyState(40) & 0x8000) {
            if (!key_pressed[7]) {
                key_state = Down;
                ro_x -= move_speed;
                key_pressed[7] = true;
            }
        }
        ro->x = ro_x;
    }
    void control() {
        key_state = Released;
        move();
        rotate();
        if (GetKeyState(32) & 0x8000) {
            if (!key_pressed[8]) {
                key_state = Space;
                an_z = 17;
                an_y = 32;
                an_x = 0;
                key_pressed[8] = true;

            }
        }
    }

    keys get_key_state() {
        return key_state;
    }
    vec3& ger_ro() {
        return *ro;
    }
    void reset() {
        for (size_t i = 0; i < 9; i++) {
            key_pressed[i] = false;
        }
    }
};