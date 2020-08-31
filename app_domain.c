//
// Created by tshech on 8/10/2020.
//

#include "app_domain.h"


#define SET_SIZE 3

extern int nd();
extern unsigned int uint_nd();
extern char *str_nd();

static int8_t* g_bgn;
static int8_t* g_end;
static int g_active;
static int remember_id;
extern int8_t* nd_ptr(void);

extern Suser* users_nd();

typedef struct Node {
    int user_id;
    int rank;
    struct Node *next;
} Node;

typedef struct Set{
    Node *head;
} Set;

Node *mk_node (int user_id, int rank) {
    Node* res = (Node*) xmalloc(sizeof(struct Node));
    res->user_id = user_id;
    res->rank = rank;
    res->next = NULL;
    return res;
}

void delete_node(Node* node){
    free(node);
}

Set* mk_list() {
    Set*res = (Set*) xmalloc(sizeof(struct Set));
    res->head = NULL;
    return res;
}

Node* exists(Set* set, int user_id){
    for (Node* it = set->head; it != NULL; it = it->next){
        if (it->user_id == user_id){
            return it;
        }
    }
    return NULL;
}

Node* ranked_user(Set* set, int giver_id, int given_id, int rank){
    Node* user_to_add = exists(set, given_id);
    if (!user_to_add){
        Node *node = mk_node (given_id, 0);
        assume (rank > 0);
        node->rank += rank;
        node->next = set->head;
        set->head = node;

        if (!g_active && nd()){
            g_active = !g_active;
            remember_id = node->user_id;
            assume((int8_t*)node == g_bgn);
            assume(g_bgn + sizeof(struct Node) == g_end);
        }
        else {
            assume((int8_t*)node > g_end);
        }
        return node;
    }
    else {
        return user_to_add;
    }
}

bool exists_in_set(Suser* set, Suser element){
    for (int i = 0; i < 5; ++i) {
        if (set[i] == element){
            return true;
        }
    }
    return false;
}

int main() {
    int remembered_key;
    bool is_remember = false;
    struct Set* all_users_id = set_create();

    //verify an element is really inserted into the set of users
    for (int i = 0; i < SET_SIZE; ++i) {
        char* username = str_nd();
        char* password = str_nd();
        Suser user = create_user(username, password, all_users_id);
        int key = get_user_key(user);
        if (!(is_remember) && is_one_of_the_ghost(all_users_id, key)){
            is_remember = !is_remember;
            remembered_key = key;
        }
        delete_user(user);
    }
    bool b = set_has(all_users_id, remembered_key);
    if (is_remember){
        int value = set_get_element(all_users_id, remembered_key);
        if (remembered_key == value){
            sassert(b);
        }
    }

    //verify that sorting the set is working
    struct Set* posts = set_create();
    for (int i = 0; i < SET_SIZE; ++i) {
        int key = nd();
        int comments = nd();
        assume(comments >= 0);
        Post post = create_post(key, comments, posts);
        delete_post(post);
    }
    int best_post_key = get_best_post(posts);
    int nd_key = nd();
    if (is_one_of_the_ghost(posts, nd_key) && set_has(posts, nd_key) && best_post_key != -1){
        sassert(best_post_key >= nd_key);
        bool cond = set_verify_sort(posts);
        sassert(cond);
    }

    //verify that delete from the set is working
    if (is_remember){
        set_delete(all_users_id, remembered_key);
        sassert(!(set_has(all_users_id, remembered_key)));
    }

    //verify there is no memory overlap on one of the elements in the list
    Set* ranked_users;
    Node *it;
    g_active = 0;
    int user1_key = nd();
    int user2_key = nd();
    assume (user1_key != user2_key && set_has(all_users_id, user1_key) && set_has(all_users_id, user2_key));
    Node* user1 = ranked_user(ranked_users, user1_key, user2_key, 5);
    Node* user2 = ranked_user(ranked_users, user2_key, user1_key, 10);

    for (it = ranked_users->head; it != NULL; it = it->next){
        if (g_active && it->user_id == remember_id){
            sassert((int8_t*)it == g_bgn);
        }else{
            sassert((int8_t*)it > g_end);
        }
    }

    //verify that a partial set of other set (like set of someone's friends in facebook from the set of all users
    //) is totally included in it
    Suser* users = users_nd();
    Suser* best_users = xmalloc(5* sizeof(Suser));
    int k = 0;
    for (int j = 0; j < 5; ++j) {
        assume(users[j] != NULL);
        if(nd()){
            best_users[k++] = users[j];
        }
    }
    int l = nd();
    assume (l >= 0 && l < k);
    sassert(exists_in_set(users, best_users[l]));

    //delete all allocations
    delete_set(all_users_id);
    delete_set(posts);
    delete_node(user1);
    delete_node(user2);
    free(best_users);


return 0;
}
