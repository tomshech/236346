//
// Created by tshech on 8/12/2020.
//

#ifndef INC_236346_POST_H
#define INC_236346_POST_H

#include "set.h"

typedef struct post *Post;

Post create_post(int key, int comments, struct Set* posts);

void delete_post(Post post);

int get_best_post(struct Set* posts);
#endif //INC_236346_POST_H
