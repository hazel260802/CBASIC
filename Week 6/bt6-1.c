#include"cgen.ic"

void bn_pprint_node(bn_node_t n){
    printf("%p\n", n);
}
dll_t bn_get_leafs(bn_tree_t t){
    bn_traverse_lnr(cur,t){
        if(cur->left == NULL && cur->right == NULL){
            bn_pprint_node(cur);
        }
    }
    return NULL;
}
int main(){
    bn_node_t n1 = bn_create_node();
    bn_node_t n2 = bn_create_node();
    bn_connect2(n1,left, n2, top);
    //n1->left = n2;
    //n2->top = n1;
    bn_node_t n3 = bn_create_node();
    bn_connect2(n1,right, n3, top);
    bn_node_t n4 = bn_create_node();
    bn_connect2(n2,left, n4, top);
    n4->left = n4->right = NULL;
    bn_node_t n5=bn_create_node();
    n5->left = n5->right= NULL;
    bn_node_t n6=bn_create_node();
    bn_connect2(n3,right, n6, top);
    n6->left = n6->right = NULL;

    //Print tree
    bn_tree_t t = bn_create_tree(n1);
    bn_pprint(t, bn_pprint_node);
    //Number of nodes
    printf("Number of nodes: %ld\n",bn_size(t));
    //Height of the tree
    printf("Height of tree: %ld\n",bn_edge_height(t));
    bn_free_tree(&t);
    return 0;
}
//gcc -o prog -I ../c-basic/cgen bt6-1.c
