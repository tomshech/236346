//
// Created by tshech on 8/10/2020.
//

#ifndef INC_236346_SET_H
#define INC_236346_SET_H

#include <seahorn/seahorn.h>
#include <stdlib.h>
#include <stdbool.h>

extern int nd();

extern unsigned int uint_nd();

//gets the size to allocate and safely allocate - checked that non-NULL pointer is returned
void *safe_malloc(size_t sz);

struct set_element {
    int val;
    bool has;
};

struct Set;

//returns an abstract set. guaranteed there are no two ghosts with the same value in the set
struct Set *set_create();

//gets a set and a key and insert the key into the set if the key is one of the set's key
void set_insert(struct Set *s, int key);

//gets a set and a key and return the key if the key is one of the ghosts
//else it returns nd value
int set_get_element(struct Set *s, int key);

//gets a set and a key and return true if the key is one of the ghosts and false otherwise
bool is_one_of_the_ghost(struct Set *s, int key);

//gets a set and a key and deletes the key from the set
void set_delete(struct Set *s, int key);

//gets a set and a key and return true if the key is in the set and nd value otherwise
bool set_has(struct Set *s, int key);

//gets a set and returns a sorted set
void set_sort(struct Set *s);

// gets a set and returns the biggest element in the set
int set_get_max_element(struct Set *s);

//gets a set and returns the set of the ghosts in the set
struct set_element *get_set_elements(struct Set *s);

//gets a set and returns true if the set is sorted and false otherwise
//checks every two elements in the set that they are in their right place in the hierarchy
bool set_verify_sort(struct Set *s);

//gets a set and deletes it
void delete_set(struct Set *s);


#endif //INC_236346_SET_H
