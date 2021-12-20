#include "cgen.h"
#include "ext/io.h"
#include "stop_words.h"

#define TF(p) (((struct word_tf*)p)->tf)
int word_tf_inc_cmp(const void *p1, const void *p2) {
	return TF(p2) - TF(p1);
}

#define N 10

void stop_words(const char *fname) {
	FILE *inp = fopen(fname, "r");
	char buff[1024];
	rbm_t words = rbm_create(gtype_cmp_s);
	while (fscanf(inp, "%s", buff) == 1) {
		//Meo: insert -1 de phan biet nut da co va nut moi
		char *key = strdup(buff);
		rbm_node_t n = rbm_insert(words, gtype_s(key), gtype_i(-1));
		if (n->value.i == -1) {
			n->value.i = 1;
		} else {
			n->value.i += 1;
			free(key);
		}

	}
	fclose(inp);
	long sz = bn_size((bn_tree_t)words);
	printf("So luong tu duy nhat = %ld\n", sz);
	struct word_tf *a = malloc(sizeof(struct word_tf) * sz);
	long idx = 0;
	rbm_traverse(cur, words) {
		//printf("%s - %ld: %ld\n", cur->key.s, strlen(cur->key.s), cur->value.i);
		a[idx].word = cur->key.s;
		a[idx].tf = cur->value.i;
		++idx;
	}
	qsort(a, idx, sizeof(struct word_tf), word_tf_inc_cmp);
	for (long i = 0; i < N; ++i) {
		printf("%s - %ld\n", a[i].word, a[i].tf);
	}
	rbm_traverse(cur, words) {
		free(cur->key.s);
	}
	rbm_free(words);
	free(a);
}
