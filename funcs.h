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



void compute_gini_overall(feature *ftr, int *label) {
    
    double gini_weighted = 0;

    for(int i=0;i<ftr->dis_total;i++) {
        thing **arr = give_arr(ftr, ftr->dis_thing[i]);
        double ind_gi = compute_gini_thingwise(arr, label, ftr->how_many_each[i]);
        gini_weighted += (((double) ftr->how_many_each[i]) / ((double) ftr->total)) * ind_gi;
        //printf("%s's ind gi is %lf\n", ftr->dis_thing[i]->name, ind_gi);
        free(arr);
    }

   *(double *)(ftr + 1) = gini_weighted;    
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
    //printf("(%s)\n", b->thing->name);
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
    feature **arr2 = malloc(sizeof(feature *)*ftr_count);
    for (int i=0;i<ftr_count;i++) {
        arr2[i] = arr[i];
    }

    feature *temp;
    temp = arr2[index];
    arr2[index] = arr2[ftr_count - 1];
    arr2[ftr_count - 1] = temp;

    return arr2;
}

void compute_gini_overall_for_node(node *root, int *label, int ftr_count, feature **arr) {
    //double branch_wise_gini_lowest[root->feature->dis_total];
    double *branch_wise_gini_all[ftr_count];
    //feature **arr = malloc(sizeof(feature *)*ftr_count); 
    
    //printf("\nbonjour! je suis [%s]\n", root->feature->name);

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
            printf("(%s) as a branch of [%s] has  gini impurity of %lf for [%s]\n", root->branch[i]->thing->name, root->feature->name, *branch_wise_gini_all[j], arr[j]->name);
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
        //printf("\n%s as a branch has overall gini impurity of %lf and has [%s] as its node\n", root->branch[i]->thing->name, *branch_wise_gini_all[lowest(branch_wise_gini_all, ftr_count)], root->branch[i]->node->feature->name);  
    }
    //print_node(root);
    /*for(int i=0;i<root->feature->dis_total;i++) {
        if(root->feature->how_many_each) {
            printf("\n");
            print_ftr(root->branch[i]->node->feature);
        }
    }*/
    //printf("");
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

node *pre_do_stuff(int *label, int ftr_count, ...) {
    va_list args;
    
    feature **arr = malloc(sizeof(feature *)*ftr_count);
    double **all_gini = malloc(sizeof(double *)*ftr_count);
    va_start(args, ftr_count);
  
    for(int i=0;i<ftr_count;i++) {
        arr[i] = va_arg(args, feature *);
        compute_gini_overall(arr[i], label);
        all_gini[i] = (double *)(arr[i] + 1);
    }
    
    va_end(args);
    int l = lowest(all_gini, ftr_count);
    feature **arr2 = remove_ftr(arr, l, ftr_count);
    node *root = make_node(arr[l]);
    put_label(root, make_label(label, TOTAL));
    compute_gini_overall_for_node(root, label, ftr_count - 1, arr2);
    //print_node_rec(root);
    free(arr);
    free(all_gini);

    return root;
}
