//
// Created by tshech on 8/10/2020.
//
#include "set.h"

#define N 2

int get_set_element(struct set_element s){
    return s.val;
}

struct Set {
    struct set_element ghosts[N];
};

static void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

static void bool_swap(bool *xp, bool *yp)
{
    bool temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort - the bigger will be in the beginning
static void bubbleSort(struct Set *s)
{
    int i, j;
    for (i = 0; i < N; i++){
    // Last i elements are already in place
        for (j = 0; j < N-i-1; j++){
            if (s->ghosts[j].val < s->ghosts[j+1].val){
                swap(&(s->ghosts[j].val), &(s->ghosts[j+1].val));
                bool_swap(&(s->ghosts[j].has), &(s->ghosts[j+1].has));
            }
        }
    }
}


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

int set_get_element(struct Set *s, int key){
    for (int i = 0; i < N; i++) {
        if (key == s->ghosts[i].val)
            return key;
    }
    return nd();
}

bool is_one_of_the_ghost(struct Set *s, int key){
    for (int i = 0; i < N; i++) {
        if (key == s->ghosts[i].val)
            return true;
    }
    return false;
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

void set_sort(struct Set *s){
    bubbleSort(s);
}

int set_get_max_element(struct Set *s){
    set_sort(s);
    for (int i = 0; i < N; i++) {
        if (s->ghosts[i].has)
            return s->ghosts[i].val;
    }
    return -1;
}

struct set_element* get_set_elements(struct Set *s){
    return s->ghosts;
}