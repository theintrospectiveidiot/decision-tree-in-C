#include "tree.h"

#define TOTAL 8

double compute_gini_thingwise(thing **data, int *label, int how_many) {
    
    double yes = 0, no = 0;
    double gini;

    for(int i=0;i<how_many;i++) {
        if (label[data[i]->position[1]]) {
            yes += 1;
            //printf("pos: %d\tit was yes\n", data[i]->position[1]);
        }
        else {
            no += 1;
            //printf("pos: %d\tit was no\n", data[i]->position[1]);
        }
    }

    gini = 1 - (yes/how_many)*(yes/how_many) - (no/how_many)*(no/how_many);

    return gini;
}



double compute_gini_overall(feature *ftr, int *label) {
    
    double gini_weighted = 0;

    for(int i=0;i<ftr->dis_total;i++) {
        thing **arr = give_arr(ftr, ftr->dis_thing[i]);
        double ind_gi = compute_gini_thingwise(arr, label, ftr->how_many_each[i]);
        gini_weighted += (((double) ftr->how_many_each[i]) / ((double) ftr->total)) * ind_gi;
        printf("%s's ind gi is %lf\n", ftr->dis_thing[i]->name, ind_gi);
        free(arr);
    }

    return gini_weighted;
}

feature *give_ftr_personal(thing **data, int how_many, feature *return_ftr) {
    //printf("bonjour again again!!\n"); 
    //printf("[%s] has receieved [%s] as the target feature\nand %d (thing)s to be stuffed\n", "temp", return_ftr->name, how_many);

    feature *ftr = make_feature_man(return_ftr->name, return_ftr->x_pos, return_ftr->dis_total, how_many);
    thing **my_data = malloc(sizeof(thing *)*how_many);
    
    

    for(int i=0;i<how_many;i++) {
        my_data[i] = return_ftr->thing[data[i]->position[1]];
    }

    ftr->dis_thing = return_ftr->dis_thing;
    ftr->thing = my_data;

    ftr->how_many_each = init_to_num(ftr->dis_total, 0);
    
    for(int i=0;i<ftr->total;i++) {
        //printf("name: %s\t index: %d\n", ftr->thing[i]->name, ftr->thing[i]->index);
        ftr->how_many_each[ftr->thing[i]->index] += 1;
    }

    return ftr;
}

feature *make_label(int *l, int size) {
    feature *label = make_feature("label", -1, 2, size);
    label->how_many_each = init_to_num(label->dis_total, 0);
    
    label->dis_thing[0] = make_thing("no", (int[]){-1, 0}, 0);
    label->dis_thing[1] = make_thing("yes", (int[]){-1, 1}, 1);
    

    for(int i=0;i<label->total;i++) {
        label->thing[i] = make_thing((l[i] == 1) ? "yes":"no", (int[]){-1, i}, l[i]);
        //printf("%d\n", label->thing[i]->position[1]);
        label->how_many_each[l[i]] += 1;
    }

    /*for(int i=0;i<label->total;i++) {
        printf("name: %s\npos: %d\thow_many_each: %d\n", label->thing[i]->name, label->thing[i]->position[1], label->how_many_each[label->thing[i]->index]);
    }*/

    return label;
}

double *compute_gini_overall_for_branch(node *root, branch *b, feature *ftr, int *label, int how_many) {
    //printf("bonjour!\n");
    thing **data = give_arr(root->feature, b->thing);
    /*for(int i=0;i<how_many;i++) {
        printf("name: %s\tpos: %d\n", data[i]->name, data[i]->position[1]);
    }*/

    //printf("bonjour again!!\n");
    //print_ftr(ftr);
    feature *temp = give_ftr_personal(data, how_many, ftr);
    double *gini_weighted = (double *)(temp + 1);    
    /*for(int i=0;i<how_many;i++) {
        printf("name: %s\tpos: %d\n", temp->thing[i]->name, temp->thing[i]->position[1]);
    }*/

    //print_ftr(temp);
    //for(int i=0;i<temp->dis_total;i++) printf("%d\n", temp->how_many_each[i]);

    for(int i=0;i<temp->dis_total;i++) {
        if(temp->how_many_each[i] == 0) {
            continue;
        }
        else {
            //printf("bonjour, i est %d est dis_thing[i] est %s\n", i, temp->dis_thing[i]->name);
            thing **data2 = give_arr(temp, temp->dis_thing[i]);
            /*for(int j=0;j<temp->how_many_each[i];j++) {
                printf("name: %s\tpos: %d\n", data2[j]->name, data2[j]->position[1]);
            }*/    
            double ind_gi = compute_gini_thingwise(data2, label, temp->how_many_each[i]);
            *gini_weighted += (((double) temp->how_many_each[i]) / ((double) temp->total)) * ind_gi;
            //printf("%s's ind gi is %lf\n", temp->dis_thing[i]->name, ind_gi);
        }
    } 
    return gini_weighted;
}

int lowest(double **arr, int size) {
    double *least = arr[0];
    int index = 0;
    for(int i=1;i<size;i++) {
        if(*least > *arr[i]) {
            least = arr[i];
            index = i;
        }
    }
    return index;
}

void put_label(node *n, feature *l) {
    
    //feature *l = make_label(label, n->feature->total);
    //print_ftr(l);

    for(int i=0;i<n->feature->dis_total;i++) {
        thing **data = give_arr(n->feature, n->branch[i]->thing);
        n->branch[i]->node = make_node(give_ftr_personal(data, n->feature->how_many_each[i], l));
    }
}

feature **remove_ftr(feature **arr, int index, int ftr_count) {
    feature *temp;
    temp = arr[index];
    arr[index] = arr[ftr_count - 1];
    arr[ftr_count - 1] = temp;

    return arr;
}

void compute_gini_overall_for_node(node *root, int *label, int ftr_count, feature **arr) {
    //double branch_wise_gini_lowest[root->feature->dis_total];
    double *branch_wise_gini_all[ftr_count];
    //feature **arr = malloc(sizeof(feature *)*ftr_count); 
    
    printf("\nbonjour! je suis [%s]\n", root->feature->name);

    if (!strcmp(root->feature->name, "label") || ftr_count == 0) {
        return;
    }

    for(int j=0;j<ftr_count;j++) {
        //arr[j] = va_arg(args, feature *);
    }
    
    for(int i=0;i<root->feature->dis_total;i++) {
        
        if(root->feature->how_many_each[i] == 0) {
            continue;
        }

        for(int j=0;j<ftr_count;j++) {
            branch_wise_gini_all[j] = compute_gini_overall_for_branch(root, root->branch[i], arr[j], label, root->feature->how_many_each[i]);
            //printf("%s as a branch has  gini impurity of %lf for [%s]\n", root->branch[i]->thing->name, *branch_wise_gini_all[j], arr[j]->name);
        }

        if (compute_gini_thingwise(give_arr(root->feature, root->branch[i]->thing), label, root->feature->how_many_each[i]) == 0) {
            //printf("\n%s as a branch has overall gini impurity of %lf and has [%s] as its node\n", root->branch[i]->thing->name, *branch_wise_gini_all[lowest(branch_wise_gini_all, ftr_count)], root->branch[i]->node->feature->name);
            continue;
        }
        else {
            root->branch[i]->node = make_node((feature *)branch_wise_gini_all[lowest(branch_wise_gini_all, ftr_count)] - 1);
            put_label(root->branch[i]->node, make_label(label, TOTAL)); 
            compute_gini_overall_for_node(root->branch[i]->node, label, ftr_count - 1, remove_ftr(arr, lowest(branch_wise_gini_all, ftr_count), ftr_count));
        }
        //print_ftr(root->branch[i]->node->feature);
        printf("\n%s as a branch has overall gini impurity of %lf and has [%s] as its node\n", root->branch[i]->thing->name, *branch_wise_gini_all[lowest(branch_wise_gini_all, ftr_count)], root->branch[i]->node->feature->name);  
    }
    print_node(root);
    for(int i=0;i<root->feature->dis_total;i++) {
        if(root->feature->how_many_each) {
            printf("\n");
            print_ftr(root->branch[i]->node->feature);
        }
    }
    //free(arr);
}

void do_stuff(node *root, int *label, int ftr_count, ...) {
    va_list args;

    feature **arr = malloc(sizeof(feature *)*ftr_count); 

    va_start(args, ftr_count);
    for(int j=0;j<ftr_count;j++) {
        arr[j] = va_arg(args, feature *);
    }
    va_end(args);
    
    compute_gini_overall_for_node(root, label, ftr_count, arr);
    free(arr);
}

int main() {
   feature *stuff = make_feature("coolness", 0, 2, 5);

   push_things(stuff, make_thing("cool",    (int[]){0, 0}, 0), 
                      make_thing("cool",    (int[]){0, 1}, 0), 
                      make_thing("uncool",  (int[]){0, 2}, 1),
                      make_thing("cool",    (int[]){0, 3}, 0),
                      make_thing("uncool",  (int[]){0, 4}, 1));
   //print_ftr(stuff);

   feature *ftr2 = make_feature("weirdness", 1, 3, 5);

   push_things(ftr2, make_thing("totally weird",        (int[]){1, 0}, 0),
                     make_thing("not weird at all",     (int[]){1, 1}, 2),
                     make_thing("somewhat weird",       (int[]){1, 2}, 1),
                     make_thing("not weird at all",     (int[]){1, 3}, 2),
                     make_thing("totally weird",        (int[]){1, 4}, 0));
   
   //print_ftr(ftr2);

   feature *ftr3 = make_feature("academics", 2, 2, 5);

   push_things(ftr3, make_thing("good",         (int[]){2, 0}, 0),
                     make_thing("not so good",  (int[]){2, 1}, 1), 
                     make_thing("good",         (int[]){2, 2}, 0),
                     make_thing("good",         (int[]){2, 3}, 0),
                     make_thing("not so good",  (int[]){2, 4}, 1));
   //print_ftr(ftr3);
   int label[TOTAL] = {1, 1, 1, 0, 0, 1, 0, 1};

   feature *study_hrs = make_feature("Study Hours", 0, 3, TOTAL);
   push_things(study_hrs, make_thing("High",    (int[]){0, 0}, 0),
                          make_thing("High",    (int[]){0, 1}, 0),  
                          make_thing("Medium",  (int[]){0, 2}, 1),
                          make_thing("Low",     (int[]){0, 3}, 2),
                          make_thing("Low",     (int[]){0, 4}, 2),
                          make_thing("Medium",  (int[]){0, 5}, 1),
                          make_thing("Low",     (int[]){0, 6}, 2),
                          make_thing("Medium",  (int[]){0, 7}, 1));
   
   feature *attendance = make_feature("Attendance", 1, 2, TOTAL);
   push_things(attendance, make_thing("Good", (int[]){0, 0}, 0),
                           make_thing("Poor", (int[]){0, 1}, 1),  
                           make_thing("Good", (int[]){0, 2}, 0),
                           make_thing("Good", (int[]){0, 3}, 0),
                           make_thing("Poor", (int[]){0, 4}, 1),
                           make_thing("Poor", (int[]){0, 5}, 1),
                           make_thing("Good", (int[]){0, 6}, 0),
                           make_thing("Good", (int[]){0, 7}, 0));

   feature *ass_subm = make_feature("Assignment Submitted", 2, 2, TOTAL);
   push_things(ass_subm, make_thing("Yes", (int[]){0, 0}, 0),
                         make_thing("Yes", (int[]){0, 1}, 0),  
                         make_thing("Yes", (int[]){0, 2}, 0),
                         make_thing("No",  (int[]){0, 3}, 1),
                         make_thing("No",  (int[]){0, 4}, 1),
                         make_thing("Yes", (int[]){0, 5}, 0),
                         make_thing("Yes", (int[]){0, 6}, 0),
                         make_thing("No",  (int[]){0, 7}, 1));



   node *root = make_node(study_hrs);
   put_label(root, make_label(label, TOTAL));

   //push_nodes(root, make_node(ftr2), make_node(ftr3));
   //print_node(root);
   //node *node1 = make_node(ftr3);
   //print_node(node1);

   do_stuff(root, label, 2, attendance, ass_subm);
   //print_node(root);
   //print_node(root->branch[0]->node);
   //print_node(root->branch[1]->node);
   for(int i=0;i<root->branch[0]->node->feature->dis_total;i++) {
       //print_ftr(root->branch[0]->node->branch[i]->node->feature);
   } 
   
   //thing **things = give_arr(stuff, stuff->dis_thing[0]);
   //thing **persona = give_arr_personal(things, stuff->how_many_each[0], ftr3);
   for(int i=0;i<root->feature->how_many_each[1];i++) {
       //printf("\nname: %s\npos: %d\tindex: %d\n", persona[i]->name, persona[i]->position[1], persona[i]->index);
   } 
   //feature *l = make_label(label, 5);
   //print_ftr(l);
   //printf("%s's gini impurity indivisually is %lf\n", stuff->dis_thing[1]->name, compute_gini_thingwise(give_arr(stuff, stuff->dis_thing[1]), label,stuff->how_many_each[1]));
    
    //printf("%s's weighted mean gini impurity is %lf\n", stuff->name, compute_gini_overall(stuff, label));

    //printf("\n%lf\n", lowest((double[]){6, 4 ,1, 5}, 4));
    //printf("%d\n", stuff->how_many_each[0]); 
    //printf("%s as a branch has %lf gini impurity for all the [thing]s of %s\n", stuff->dis_thing[0]->name, *compute_gini_overall_for_branch(root, root->branch[0], ftr2, label, stuff->how_many_each[0]), ftr2->name);
    //print_node_rec(root);

}
