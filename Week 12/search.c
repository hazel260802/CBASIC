#include"sort.c"
#include<ctype.h>
char *strlwr(char* s){ 
    char* tmp = s;
    for (;*tmp;++tmp){
        *tmp = tolower((unsigned char) *tmp);
    }
    return s;
}

void search_name(song_t *s, char *p, int n) {
    song_t *find = calloc(n,sizeof(song_t));
    int fo=0;
    char *tmp;
    for(int i=0; i<n; i++){
        tmp = strdup(s[i]->name);
        if(strstr(strlwr(tmp),strlwr(p))){
            find[fo] = s[i];
            fo++;
        }
    }
    print_song(find,fo);
}
void search_singer(song_t *s, char *p,int n){
    song_t *find = calloc(n, sizeof(song_t));
    int fo=0;
    char *tmp;
    for (int i = 0; i < n; i++){
        tmp = strdup(s[i]->singer);
        if(strstr(strlwr(tmp),strlwr(p))){
            find[fo] = s[i];
            fo++;
        }
    }
    print_song(find,fo);
}
void search_musician(song_t *s, char *p,int n){
    song_t *find = calloc(n, sizeof(song_t));
    int fo=0;
    char *tmp;
    for (int i = 0; i < n; i++){
        tmp = strdup(s[i]->musician);
        if(strstr(strlwr(tmp),strlwr(p))){
            find[fo] = s[i];
            fo++;
        }
    }
    print_song(find,fo);
}
void search_year(song_t *s, char *p,int n){
    song_t *find = calloc(n, sizeof(song_t));
    int fo=0;
    char *tmp;
    for (int i = 0; i < n; i++){
        tmp = strdup(s[i]->year);
        if(strstr(strlwr(tmp),strlwr(p))){
            find[fo] = s[i];
            fo++;
        }
    }
    print_song(find,fo);
}