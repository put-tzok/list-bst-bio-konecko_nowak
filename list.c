#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>


unsigned int ns[]={10,20,50,100,500,1000,2500,5000,10000,15000};

struct node {
int key;
struct node *next;
};

struct node*head = NULL;
struct node*wsk;
struct node*prev;


struct node* list_insert(int value) {

    struct node*createnode=malloc(sizeof(*createnode));
    createnode->key=value;
    createnode->next=head;
    head=createnode;
    return head;
}


struct node* list_search(int value) {
    struct node*wsk=head;
    while(wsk!=NULL&&wsk->key!=value){
    wsk=wsk->next;
    }
    return wsk;

}

void list_delete(int value) {
    if (head->key==value){
        head=head->next;
    }
    else{
   prev=head;
    wsk=head->next;
    while(wsk!=NULL&&wsk->key!=value){
        prev=wsk;
        wsk=wsk->next;
    }
    if(wsk!=NULL){
            prev->next=wsk->next;

    }

    }

}

unsigned int list_size() {
    int size=0;
    wsk=head;
    while(wsk!=NULL){
        size+=1;
        wsk=wsk->next;
    }
    return size;

}



void fill_increasing(int *t, int n) {
    for (int i = 0; i < n; i++) {
        t[i] = i;
    }
}


void shuffle(int *t, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % i;
        int temp = t[i];
        t[i] = t[j];
        t[j] = temp;
    }
}
int main(){
bool no_yes[] = { false, true };

    for (unsigned int i = 0; i < sizeof(no_yes) / sizeof(*no_yes); i++) {
        bool enable_shuffle = no_yes[i];

        for (unsigned int j = 0; j < sizeof(ns) / sizeof(*ns); j++) {
            unsigned int n = ns[j];
          int *t = malloc(n * sizeof(*t));
            fill_increasing(t, n);

            // if true, reorder array elements randomly
            if (enable_shuffle) {
                shuffle(t, n);
            }

            // insert elements in the order present in array `t`
            clock_t insertion_time = clock();
            for (unsigned int k = 0; k < n; k++) {
                struct node *iter = list_insert(t[k]);
                assert(iter != NULL);       // inserted element cannot be NULL
                assert(iter->key == t[k]);  // inserted element must contain the expected value
            }
            insertion_time = clock() - insertion_time;

            // reorder array elements before searching
            shuffle(t, n);

            // search for every element in the order present in array `t`
            clock_t search_time = clock();
            for (unsigned int k = 0; k < n; k++) {
                struct node *iter = list_search(t[k]);
                assert(iter != NULL);       // found element cannot be NULL
                assert(iter->key == t[k]);  // found element must contain the expected value
            }
            search_time = clock() - search_time;

            // reorder array elements before deletion
            shuffle(t, n);

            // delete every element in the order present in array `t`
            for (unsigned int k = 0, l = n; k < n; k++, l--) {
                assert(list_size() == l);   // list size must be equal to the expected value
                list_delete(t[k]);
            }
            assert(list_size() == 0);       // after all deletions, the list size is zero
            assert(head == NULL);           // after all deletions, the list's head is NULL

          free(t);


                    printf("%d\t%s\t%f\t%f\n", n, enable_shuffle ? "true" : "false",
                    (double)insertion_time / CLOCKS_PER_SEC,
                    (double)search_time / CLOCKS_PER_SEC);
        }
    }
    return 0;
}
