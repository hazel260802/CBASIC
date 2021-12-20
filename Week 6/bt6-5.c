#include"cgen.ic"
#include<stdio.h>

int main(int argc, char *argv[]){
    if (argc !=2){
        printf("Usage: ./wu story.txt\n");
        return 1;
    }
    FILE *inp = fopen(argv[1],"r");
    if (!inp) {
    printf("Lỗi mở tệp %s\n", argv[1]);
    return 1;
    }
    char buff[100][100];// create tree to save words
    bn_tree_t t = bns_create_tree_g(NULL, gtype_cmp_s);
    int i=0;
    while(feof(inp)==0){
        fscanf(inp, "%s", buff[i]); 
    if(!bns_search_g(t, gtype_s(buff[i]))){
        bns_insert_g(t, gtype_s(buff[i]));
        i++;
        }
    }
    printf("Number of words: %d\n", i);
    printf("The seperated words:\n");
    bns_pprint(t,gtype_print_s);

    bn_free_tree(&t);
    return 0;
}
//gcc -o wu -I ../c-basic/cgen bt6-5.c
// ./wu story.txt  