//
// Created by tshech on 8/12/2020.
//

#ifndef INC_236346_POST_H
#define INC_236346_POST_H

#include "set.h"

void create_post(int key, int comments, struct Set* posts);
int get_best_post(struct Set* posts);
#endif //INC_236346_POST_H
