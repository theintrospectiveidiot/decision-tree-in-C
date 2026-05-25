#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>


typedef struct thing {
    char *name;
    int *position;
    int index;
} thing;

typedef struct feature {
    char *name;
    int x_pos;
    
    thing **dis_thing;
    int dis_total;

    thing **thing;
    int total;
} feature;

typedef struct branch branch;
typedef struct node node;

struct node {
    feature *feature;
    struct branch **branch;
};

struct branch {
    thing *thing;
    struct node *node;
};

feature *make_feature(char *name, int x, int dis_total, int total) {
    feature *some_ftr = (feature *)malloc(sizeof(feature));
    
    some_ftr->name = strdup(name);
    some_ftr->x_pos = x;
    some_ftr->dis_total = dis_total;
    some_ftr->dis_thing = malloc(sizeof(thing *)*dis_total);
    some_ftr->total = total;
    some_ftr->thing = malloc(sizeof(thing *)*total);

    return some_ftr;
}

thing *make_thing(char *name, int *position, int index) {
    thing *something = malloc(sizeof(thing));

    something->name = strdup(name);
    something->position = position;
    something->index = index;

    return something;
}

void push_things(feature *feature, ...) {
    va_list args;

    va_start(args, feature);
    
    for(int i=0;i<feature->total;i++) {
        feature->thing[i] = va_arg(args, thing *);
    }

    va_end(args);
}

int main() {
    feature *ftr = make_feature("stuff", 0, 2, 3);

    push_things(ftr, make_thing("cool", (int[]){0, 0}, 0), 
                     make_thing("cool", (int[]){0, 1}, 0), 
                     make_thing("uncool", (int[]){0, 2}, 1));

    for(int i=0;i<ftr->total;i++) {
        printf("pos: %d\nindex: %d\n", ftr->thing[i]->position[1], ftr->thing[i]->index);
        printf("name: %s\n", ftr->thing[i]->name);
    }
}
