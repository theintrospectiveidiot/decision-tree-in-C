#include "tree.h"

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
    
    feature *ftr = make_feature_man("temp", return_ftr->x_pos, return_ftr->dis_total, how_many);
    
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

double compute_gini_overall_for_branch(node *root, branch *b, feature *ftr, int *label, int how_many) {
    //printf("bonjour!\n");
    thing **data = give_arr(root->feature, b->thing);
    /*for(int i=0;i<how_many;i++) {
        printf("name: %s\tpos: %d\n", data[i]->name, data[i]->position[1]);
    }*/

    //printf("bonjour again!!\n");
    feature *temp = give_ftr_personal(data, how_many, ftr);

    /*for(int i=0;i<how_many;i++) {
        printf("name: %s\tpos: %d\n", temp->thing[i]->name, temp->thing[i]->position[1]);
    }*/

    //print_ftr(temp);
    //for(int i=0;i<temp->dis_total;i++) printf("%d\n", temp->how_many_each[i]);
    double gini_weighted = 0;

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
            gini_weighted += (((double) temp->how_many_each[i]) / ((double) temp->total)) * ind_gi;
            //printf("%s's ind gi is %lf\n", temp->dis_thing[i]->name, ind_gi);
        }
    }
   
    return gini_weighted;
}

double lowest(double *arr, int size) {
    double least = arr[0];

    for(int i=1;i<size;i++) {
        if(least > arr[i]) {
            least = arr[i];
        }
    }
    return least;
}

double compute_gini_overall_for_node(node *root, int *label, int ftr_count,...) {
    va_list args;
    double branch_wise_gini_lowest[root->feature->dis_total];
    double branch_wise_gini_all[ftr_count];

    va_start(args, ftr_count);
    
    for(int i=0;i<root->feature->dis_total;i++) {
        for(int j=0;j<ftr_count;j++) {
            feature *ftr = va_arg(args, feature *);
            branch_wise_gini_all[j]= compute_gini_overall_for_branch(root, root->branch[i], ftr, label, root->feature->how_many_each[i]);
        }
        branch_wise_gini_lowest[i] = lowest(branch_wise_gini_all, ftr_count);
    }

    va_end(args);
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

   node *root = make_node(stuff);
   push_nodes(root, make_node(ftr2), make_node(ftr3));
   print_node(root);
   node *node1 = make_node(ftr3);
   print_node(node1);

   int label[5] = {0, 1, 0, 0, 1};

   //thing **things = give_arr(stuff, stuff->dis_thing[0]);
   //thing **persona = give_arr_personal(things, stuff->how_many_each[0], ftr3);
   for(int i=0;i<root->feature->how_many_each[1];i++) {
       //printf("\nname: %s\npos: %d\tindex: %d\n", persona[i]->name, persona[i]->position[1], persona[i]->index);
   } 
    
   //printf("%s's gini impurity indivisually is %lf\n", stuff->dis_thing[1]->name, compute_gini_thingwise(give_arr(stuff, stuff->dis_thing[1]), label,stuff->how_many_each[1]));
    
    //printf("%s's weighted mean gini impurity is %lf\n", stuff->name, compute_gini_overall(stuff, label));

    //printf("\n%lf\n", lowest((double[]){6, 4 ,1, 5}, 4));
    //printf("%d\n", stuff->how_many_each[0]); 
    printf("%s as a branch has %lf gini impurity for all the [thing]s of %s\n", stuff->dis_thing[0]->name, compute_gini_overall_for_branch(root, root->branch[0], ftr3, label, stuff->how_many_each[0]), ftr3->name);

}
