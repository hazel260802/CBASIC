#ifndef STOP_WORDS_H_
#define STOP_WORDS_H_

struct word_tf {
	char *word;
	long tf;
};

void stop_words(const char *fname);

#endif // STOP_WORDS_H_
