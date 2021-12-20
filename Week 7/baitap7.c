#include "baitap7.h"
#include"bns.h"

long bn_xdist(bn_tree_t t, bn_node_t n){
    long x=0;
    bn_node_t tmp=n;
    while(tmp!= t->root) {
        if(tmp==tmp->top->right) {
            x++;
        }
        else if(tmp==tmp->top->left) {
            x--;
        }
        tmp=tmp->top;
    }
    return x;
}
int bn_is_bns(bn_tree_t t){
    bn_traverse_lnr(cur,t){
        if(t->root->left==NULL && t->root->right==NULL)return 1;
        if(cur!=t->root) {
            if(cur==cur->top->left){
                if(bns_tree_g_cmp(t)(bns_node_g_key(cur),bns_node_g_key(cur->top))>0)return 0;
                else if(cur==cur->top->right){
                    //neu node con ben phai
                    if(bns_tree_g_cmp(t)(bns_node_g_key(cur->top),bns_node_g_key(cur))>0)return 0;
                }
            }
        }
    }
    return 1;
}
//gcc -o prog b7-is-bns.c baitap7.c -I ../cgen
// ./prog
bn_node_t bn_lca(bn_node_t n1, bn_node_t n2){
    if(n1->top== NULL||n2->top== NULL)return NULL;
    if(n1->top==n2->top)return n1->top;
}

void arr_to_bns(bn_tree_t t, int *a, int start, int end){
    if(start>end)return;
    bns_insert_g(t,(gtype){.i=a[(start+end)/2]});
    arr_to_bns(t,a,start,(start+end)/2);
    arr_to_bns(t,a,(start+end)/2+1,end);
}
bn_tree_t bns_parse_arri(int *a, size_t n){
    bn_tree_t t = bns_create_tree_g(NULL, gtype_cmp_i);
    arr_to_bns(t,a,0,n-1);
    return t;
}