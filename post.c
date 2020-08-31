//
// Created by tshech on 8/12/2020.
//

#include "post.h"

typedef struct post{
    int key;
    int comments;
}*Post;

Post create_post(int key, int comments, struct Set* posts){
    Post post = malloc(sizeof(*post));
    post->key = key;
    post->comments = comments;
    set_insert(posts, comments);
    return post;
}

void delete_post(Post post){
    free(post);
}

int get_best_post(struct Set* posts){
    return set_get_max_element(posts);
}