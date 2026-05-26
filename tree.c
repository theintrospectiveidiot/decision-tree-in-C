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

int *init_to_num(int size, int num) {
    int *numbrs = malloc(sizeof(int)*size);
    for(int i=0;i<size;i++) {
        numbrs[i] = num;
    }
    return numbrs;
}

int categorize(feature* ftr) {
    int *arr = init_to_num(ftr->dis_total, 0);
    int j = 0;
    for(int i=0;i<ftr->total;i++) {
        if(arr[ftr->thing[i]->index]) {
            //printf("bonjour, skipped %s of index %d\n", ftr->thing[i]->name, ftr->thing[i]->index);
            continue;
        }
        else {
            arr[ftr->thing[i]->index] = 1;
            ftr->dis_thing[j] = ftr->thing[i];
            //printf("bonjour, added %s of index %d to the dis_thing\n", ftr->dis_thing[j]->name, ftr->dis_thing[j]->index);
            j += 1;
        }
    }

    free(arr);
    return 0;
}

void push_things(feature *feature, ...) {
    va_list args;

    va_start(args, feature);
    
    for(int i=0;i<feature->total;i++) {
        feature->thing[i] = va_arg(args, thing *);
    }

    va_end(args);

    categorize(feature);

}

void print_ftr(feature * ftr) {
    printf("(%s):\n", ftr->name);
    printf("all the [thing]s:\n");
    for(int i=0;i<ftr->total;i++) {
        printf("pos: %d\nindex: %d\n", ftr->thing[i]->position[1], ftr->thing[i]->index);
        printf("name: %s\n\n", ftr->thing[i]->name);
    }

    printf("\nall the [dis_thing]s:\n");
    for(int i=0;i<ftr->dis_total;i++) {
        printf("index: %d\n", ftr->dis_thing[i]->index);
        printf("name: %s\n\n", ftr->dis_thing[i]->name);
    }
    printf("================================================\n");
}

void print_node(node *n) {
    printf("\n[%s]\n  ", n->feature->name);
    for(int i=0;i<n->feature->dis_total;i++) {
        if (n->branch[i]->node != NULL) printf("|\n  |\n  |___[%s]\n  ", n->branch[i]->node->feature->name);
        else printf("|\n  |\n  |___[%s]\n  ","NULL");
    }    
}

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

int main() {
   feature *stuff = make_feature("coolness", 0, 2, 3);

   push_things(stuff, make_thing("cool",    (int[]){0, 0}, 0), 
                      make_thing("cool",    (int[]){0, 1}, 0), 
                      make_thing("uncool",  (int[]){0, 2}, 1),
                      make_thing("cool",    (int[]){0, 3}, 0),
                      make_thing("uncool",  (int[]){0, 4}, 1));
   //print_ftr(stuff);

   feature *ftr2 = make_feature("weirdness", 1, 3, 5);

   push_things(ftr2, make_thing("totally weird",    (int[]){1, 0}, 0),
                     make_thing("somewhat weird",   (int[]){1, 1}, 1),
                     make_thing("somewhat weird",   (int[]){1, 2}, 1),
                     make_thing("not weird at all", (int[]){1, 3}, 2),
                     make_thing("totally weird",    (int[]){1, 4}, 0));
   
   //print_ftr(ftr2);

   feature *ftr3 = make_feature("academics", 2, 2, 5);

   push_things(ftr3, make_thing("good",         (int[]){2, 0}, 0),
                     make_thing("not so good",  (int[]){2, 1}, 1), 
                     make_thing("good",         (int[]){2, 2}, 0),
                     make_thing("good",         (int[]){2, 3}, 0),
                     make_thing("not so good",  (int[]){2, 4}, 1));
   //print_ftr(ftr3);

   node *root = make_node(stuff);
   push_nodes(root, make_node(ftr2), make_node(ftr3));
   print_node(root);
   print_node(make_node(ftr2));
   
   
}
