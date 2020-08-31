//
// Created by tshech on 8/12/2020.
//

#ifndef INC_236346_POST_H
#define INC_236346_POST_H

#include "set.h"

typedef struct post *Post;

//gets key, number of comments and set of posts
//insert the post to a set of all posts
//returns the post
Post create_post(int key, int comments, struct Set* posts);

//delete a post
void delete_post(Post post);

//gets a set of posts and return the most commented post
int get_best_post(struct Set* posts);
#endif //INC_236346_POST_H
