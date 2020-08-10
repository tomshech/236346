//
// Created by tshech on 8/10/2020.
//

#ifndef INC_236346_SET_H
#define INC_236346_SET_H

#include <seahorn/seahorn.h>
#include <stdlib.h>
#include <stdbool.h>

extern int nd();

struct Set;

struct Set *set_create();

void set_insert(struct Set *s, int key);

int set_get_element(struct Set *s, int key);

bool is_one_of_the_ghost(struct Set *s, int key);

void set_delete(struct Set *s, int key);

bool set_has(struct Set *s, int key);


#endif //INC_236346_SET_H
