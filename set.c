//
// Created by tshech on 8/10/2020.
//
#include "set.h"
#include <seahorn/seahorn.h>
#include <stdlib.h>

extern int nd();

#define N 2

struct ghost{
    int val;
    bool has;
};

struct Set {
     struct ghost ghosts[N];
};


struct Set *set_create() {
    struct Set *a = malloc(sizeof(struct Set));
    for (int i = 0; i < N; i++) {
        a->ghosts[i].val = nd();
        a->ghosts[i].has = 0;
    }
    return a;
}

void set_insert(struct Set *s, int key) {
    for (int i = 0; i < N; i++) {
        if (key == s->ghosts[i].val)
            s->ghosts[i].has = 1;
    }
}

int set_get_element(struct Set *s, int index){
    assume (index >= 0 && index < N);
    return s->ghosts[index].val;
}

void set_delete(struct Set *s, int key){
    for (int i = 0; i < N; i++) {
        if (key == s->ghosts[i].val)
            s->ghosts[i].has = 0;
    }
}

bool set_has(struct Set *s, int key) {
    for (int i = 0; i < N; i++) {
        if (key == s->ghosts[i].val)
            return s->ghosts[i].has;
    }
    return nd();
}