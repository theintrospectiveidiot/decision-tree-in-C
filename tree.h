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
    int *how_many_each;

    thing **thing;
    int count;
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
    some_ftr->count = 0;
    return some_ftr;
}

feature *make_feature_man(char *name, int x, int dis_total, int total) {
    feature *some_ftr = malloc(sizeof(feature) + sizeof(double));
    
    some_ftr->name = name;
    some_ftr->x_pos = x;
    some_ftr->dis_total = dis_total;
    //some_ftr->dis_thing = malloc(sizeof(thing *)*dis_total);
    some_ftr->total = total;
    //some_ftr->thing = malloc(sizeof(thing *)*total);
    some_ftr->count = 0;
    
    return some_ftr;
}

thing *make_thing(char *name, int *position, int index) {
    thing *something = malloc(sizeof(thing));

    something->name = strdup(name);

    something->position = malloc(sizeof(int *)*2);
    something->position[0] = position[0];
    something->position[1] = position[1];

    something->index = index;

    return something;
}

int *init_to_num(int size, int num) {
    int *numbrs = malloc(sizeof(int)*size);
    for(int i=0;i<size;i++) {
        numbrs[i] = num;
    }
    return numbrs;
}

int *categorize(feature* ftr) {
    int *arr = init_to_num(ftr->dis_total, 0);
    for(int i=0;i<ftr->total;i++) {
        if(arr[ftr->thing[i]->index]) {
            arr[ftr->thing[i]->index] += 1;
            //printf("bonjour, skipped %s of index %d\n", ftr->thing[i]->name, ftr->thing[i]->index);
            continue;
        }
        else {
            arr[ftr->thing[i]->index] = 1;
            ftr->dis_thing[ftr->thing[i]->index] = ftr->thing[i];
            //printf("bonjour, added %s of index %d to the dis_thing\n", ftr->dis_thing[j]->name, ftr->dis_thing[j]->index);
        }
    }
    return arr;
}

void push_things(feature *feature, ...) {
    va_list args;

    va_start(args, feature);
    
    for(int i=0;i<feature->total;i++) {
        feature->thing[i] = va_arg(args, thing *);
    }
    feature->count = feature->total;
    va_end(args);

    feature->how_many_each = categorize(feature);

}

void push_things_man(feature *feature, int count,...) {
    va_list args;

    va_start(args, count);
    
    for(int i=feature->count;i<count;i++) {
        if (feature->count >= feature->total) {
            printf("Full!!\n");
            break;
        }
        feature->thing[feature->count] = va_arg(args, thing *);
        feature->count += 1;
    }
    va_end(args);

    feature->how_many_each = categorize(feature);

}

void print_ftr(feature * ftr) {
    printf("[%s]:\n", ftr->name);
    printf("all the [(thing)s:\n");
    for(int i=0;i<ftr->total;i++) {
        printf("pos: %d\nindex: %d\n", ftr->thing[i]->position[1], ftr->thing[i]->index);
        printf("name: %s\n\n", ftr->thing[i]->name);
    }

    printf("\nall the (dis_thing)s:\n");
    for(int i=0;i<ftr->dis_total;i++) {
        printf("index: %d\n", ftr->dis_thing[i]->index);
        printf("name: %s\n\n", ftr->dis_thing[i]->name);
    }
    printf("================================================\n");
}

void print_node(node *n) {
    printf("\n[%s]\n  ", n->feature->name);
    for(int i=0;i<n->feature->dis_total;i++) {
        if (n->feature->how_many_each[i] >= 0) {
            if (n->branch[i]->node != NULL) {
                printf("|\n  |\n  |___(%s - {%d})___[%s]\n  ", n->branch[i]->thing->name, n->feature->how_many_each[i], n->branch[i]->node->feature->name);
                //for(int i=0;i<node->)
            }
            else printf("|\n  |\n  |___(%s - {%d})___[%s]\n  ", n->branch[i]->thing->name, n->feature->how_many_each[i], "NULL");
        }
        else return;
    }
}

void print_node_rec(node *n) {
    print_node(n);
    if(n->branch[0]->node != NULL) {
        for(int i=0;i<n->feature->dis_total;i++) {
            printf("\n(%s)", n->branch[i]->thing->name);
            print_node_rec(n->branch[i]->node);
        }
    }
    else return;
}

feature *make_label(int *l, int size); 
branch *make_branch(thing *stuff) {
    branch *branch = malloc(sizeof(branch));
    branch->thing = stuff;
    branch->node = malloc(sizeof(node));
    
    branch->node = NULL;
    return branch;
}

node *make_node(feature *ftr) {
    node *current_node = malloc(sizeof(node));
    current_node->feature = ftr;
    current_node->branch = malloc(sizeof(branch *)*ftr->dis_total);
    
    //printf("%s has %d branches:\n", ftr->name, ftr->dis_total);
    for(int i=0;i<ftr->dis_total;i++) {
        current_node->branch[i] = make_branch(ftr->dis_thing[i]);
        //printf("%s\n", current_node->branch[i]->thing->name);
    }

    return current_node;
}

void push_nodes(node *c_node, ...) {
    va_list args;

    va_start(args, c_node);
    
    for(int i=0;i<c_node->feature->dis_total;i++) {
        c_node->branch[i]->node = va_arg(args, node *);
    }

    va_end(args);
}

thing **give_arr(feature *feature, thing *th) {
    /*if(strcmp(th->name, feature->dis_thing[th->index]->name)) {
        printf("\nthe branch (%s) doesnt belong to the node [%s]\n", th->name, feature->name);
        exit(1);
    }*/
    int n = 0;
    thing **arr = malloc(sizeof(thing *)*(feature->how_many_each[th->index]));
    //printf("name est %s et index est %d est %d allocated\n", th->name, th->index, feature->how_many_each[th->index]);
    for(int i=0;i<feature->total;i++) {
        if (th->index == feature->thing[i]->index) {
            arr[n] = feature->thing[i];
            //printf("name: %s\t pos: %d", arr[n]->name, arr[n]->position[1]);
            n += 1;
        }
    }
    return arr;
}
