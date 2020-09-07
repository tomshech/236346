//
// Created by tshech on 8/10/2020.
//

#include <seahorn/seahorn.h>
#include <stdlib.h>
#include "set.h"
#include "user.h"
#include "post.h"


#define SET_SIZE 3

extern int nd();

extern unsigned int uint_nd();

extern char *str_nd();

static int8_t *g_bgn;
static int8_t *g_end;
static int g_active;
static int remember_id;

extern int8_t *nd_ptr(void);

extern Suser *users_nd();

typedef struct Node {
    int user_id;
    int rank;
    struct Node *next;
} Node;

typedef struct Set {
    Node *head;
} Set;

//creates a set_node
Node *mk_node(int user_id, int rank) {
    Node *res = (Node *) safe_malloc(sizeof(struct Node));
    res->user_id = user_id;
    res->rank = rank;
    res->next = NULL;
    return res;
}

//delete a set_node
void delete_node(Node *node) {
    free(node);
}

//created an empty set
Set *mk_set() {
    Set *res = (Set *) safe_malloc(sizeof(struct Set));
    res->head = NULL;
    return res;
}

//gets a set and an user id and returns the user if exists in the set, otherwise returns NULL
Node *exists(Set *set, int user_id) {
    for (Node *it = set->head; it != NULL; it = it->next) {
        if (it->user_id == user_id) {
            return it;
        }
    }
    return NULL;
}

//gets a set, a user_id and a rank to give to the user
//the user is added to the set if it hasn't already been part of it
//one user is picked and its begin and end address are saved
//if we don't pick this specific user we demand it will be allocated in a later address.
//finally the added user is returned
Node *ranked_user(Set *set, int given_id, int rank) {
    Node *user_to_add = exists(set, given_id);
    if (!user_to_add) {
        Node *node = mk_node(given_id, 0);
        assume(rank > 0);
        node->rank += rank;
        node->next = set->head;
        set->head = node;

        if (!g_active && nd()) {
            g_active = !g_active;
            remember_id = node->user_id;
            assume((int8_t *) node == g_bgn);
            assume(g_bgn + sizeof(struct Node) == g_end);
        } else {
            assume((int8_t *) node > g_end);
        }
        return node;
    } else {
        return user_to_add;
    }
}

//gets a set and a set element
//returns true if the element is part of the set, false otherwise
bool exists_in_set(Suser *set, Suser element) {
    for (int i = 0; i < 5; ++i) {
        if (set[i] == element) {
            return true;
        }
    }
    return false;
}

int main() {
    int remembered_key;
    bool is_remember = false;
    struct Set *all_users_id = set_create();

    //verify an element is really inserted into the set of users
    for (int i = 0; i < SET_SIZE; ++i) {
        char *username = str_nd();
        char *password = str_nd();
        //in that function below i send the credentials to the DB. therefore i can delete the user itself after that to
        //avoid memory leaks. i treat all_users_id set as a set i got after a request from the DB.
        Suser user = create_user(username, password, all_users_id);
        int key = get_user_key(user);
        //Non-deterministically choose one user to remember
        if (!(is_remember) && is_one_of_the_ghost(all_users_id, key) && nd()) {
            is_remember = !is_remember;
            remembered_key = key;
        }
        //To avoid memory leaks
        delete_user(user);
    }
    bool b = set_has(all_users_id, remembered_key);
    //here we can argue that it was really inserted to the set, only if the flag is true
    if (is_remember) {
        int value = set_get_element(all_users_id, remembered_key);
        if (remembered_key == value) {
            sassert(b);
        }
    }

    //verify that sorting the set is working
    struct Set *posts = set_create();
    for (int i = 0; i < SET_SIZE; ++i) {
        int key = nd();
        int comments = nd();
        assume(comments >= 0);
        //every post's key has to be unique
        if (is_one_of_the_ghost(posts, key)) {
            assume(!set_has(posts, key));
            Post post = create_post(key, comments, posts);
            //To avoid memory leaks
            delete_post(post);
        }
    }
    int best_post_key = get_best_post(posts);
    int num_of_comments = nd();
    if (is_one_of_the_ghost(posts, num_of_comments) && set_has(posts, num_of_comments) && best_post_key != -1) {
        //first check: i took a number at random. after checking that it's a part of the set, i verified that it must be
        //smaller than the first element in the set
        sassert(best_post_key >= num_of_comments);
        bool cond = set_verify_sort(posts);
        //second check: take every two number in the set, if the first number you took appeared before in the set, than
        // it must be bigger than the other one.
        sassert(cond);
    }

    //verify that delete from the set is working
    if (is_remember) {
        set_delete(all_users_id, remembered_key);
        sassert(!(set_has(all_users_id, remembered_key)));
    }

    //verify there is no memory overlap on one of the elements in the set
    Set *ranked_users;
    Node *it;
    g_active = 0;
    int user1_key = nd();
    int user2_key = nd();
    assume(user1_key != user2_key && set_has(all_users_id, user1_key) && set_has(all_users_id, user2_key));
    Node *user1 = ranked_user(ranked_users, user1_key, 5);
    Node *user2 = ranked_user(ranked_users, user2_key, 10);

    for (it = ranked_users->head; it != NULL; it = it->next) {
        if (g_active && it->user_id == remember_id) {
            sassert((int8_t *) it == g_bgn);
        } else {
            sassert((int8_t *) it > g_end);
        }
    }

    //verify that a partial set of other set (like set of someone's friends in facebook from the set of all users
    //) is totally included in it
    Suser *users = users_nd();
    Suser *best_users = safe_malloc(5 * sizeof(Suser));
    int k = 0;
    for (int j = 0; j < 5; ++j) {
        assume(users[j] != NULL);
        if (nd()) {
            best_users[k++] = users[j];
        }
    }
    int l = nd();
    assume(l >= 0 && l < k);
    sassert(exists_in_set(users, best_users[l]));





    //delete all allocations to avoid memory leaks
    delete_set(all_users_id);
    delete_set(posts);
    delete_node(user1);
    delete_node(user2);
    free(best_users);


    return 0;
}
