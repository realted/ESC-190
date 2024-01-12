/*
ESC190 Project 1
Completed with Alex Cho
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autocomplete.h"
#define my_max(a,b) (((a) > (b)) ? (a) : (b))
#define my_min(a,b) (((a) < (b)) ? (a) : (b))

int my_str_cmp(char *substr, char *str, int lowest_match){
    //- value to go search to the left and + value to search to the right
    int length = strlen(substr);

    for(int i = 0; i < length; i++){
        if(substr[i] != str[i]){
            return substr[i] - str[i];
        }
    }
    if(lowest_match == 1) return -9999;
    else return 9999;
}

int comparator(const void* p, const void* q){
    return strcmp(((term *)p)->term, ((term *)q)->term);
}

int comparator_num(const void* n1, const void* n2){
    return ((term *)n2)->weight - ((term *)n1)->weight;
}

void read_in_terms(term **terms, int *pnterms, char *filename){

    FILE *fp = fopen(filename, "r");

    if (fp == NULL) return;

    char num_terms[50];
    fgets(num_terms, 10, fp);
    *pnterms = atoi(num_terms);

    *terms = (term *)malloc(sizeof(term) * (*pnterms));

    for(int i = 0; i < *pnterms; i++){
        char weight[15];
        fgets(weight, 15, fp);
        (*terms + i)->weight = strtod(weight, NULL);

        fgetc(fp);
        fgets((*terms + i)->term, 200, fp);

        for(int j = 0; j < strlen((*terms + i)->term); j++){
            if((*terms + i)->term[j] == '\n'){
                (*terms + i)->term[j] = '\0';
            }
        }
    }
    qsort((*terms), *pnterms, sizeof(term), comparator);
    fclose(fp);
}

int lowest_match(term *terms, int nterms, char *substr){
    // return index in terms of the first time matching substr with binary search
     
    int low = 0; int high = nterms;
    int cmp_value = 1;
    int index;
    do{
        index = (high + low) / 2;
        cmp_value = my_str_cmp(substr, (terms+index)->term, 1);
        
        if(cmp_value < 0)   high = my_max(index - 1, low);
        else if(cmp_value > 0)  low = my_min(index + 1, high);
    }while(high != low);

    if (my_str_cmp(substr, (terms+high)->term, 1) == -9999) return high;
    else    return high + 1;
}

int highest_match(struct term *terms, int nterms, char *substr){
    /*return index in terms of the last term */

    int low = 0; int high = nterms;
    int cmp_value = 1;
    int index;
    do{
        index = (high + low) / 2;
        cmp_value = my_str_cmp(substr, (terms+index)->term, 0);
        
        if(cmp_value < 0)   high = my_max(index - 1, low);
        else if(cmp_value > 0)  low = my_min(index + 1, high);
    }while(high != low);

    if (my_str_cmp(substr, (terms+high)->term, 0) == 9999)  return high;
    else    return high - 1;
}

void autocomplete(term **answer, int *n_answer, term *terms, int nterms, char *substr){
    /*take in terms, and all that, and then return place the answer with n_answer being number of answers --> sorted by weight in non-increasing order
    must use qsort for this qeustion*/

    int index_low = lowest_match(terms, nterms, substr);
    int index_high = highest_match(terms, nterms, substr);

    *n_answer = index_high - index_low + 1;
    *answer = (term *)malloc(sizeof(term) * (*n_answer));

    for(int i = index_low; i <= index_high; i++){
        strcpy((*answer + i - index_low)->term, (terms + i)->term);
        (*answer + i - index_low)->weight = (terms + i)->weight;
    }
    qsort((*answer), *n_answer, sizeof(term), comparator_num);
}