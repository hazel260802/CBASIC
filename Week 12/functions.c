#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct song{
  char *name;
  char *singer;
  char *musician;
  char *year;
  int ex;
} * song_t; //song_ptr


void add_song(song_t s, char *name, char *singer, char *musician, char *year, int q){
    s->name = strdup(name);
    s->singer = strdup(singer);
    s->musician = strdup(musician);
    s->year = strdup(year);
    s->ex=q;
}
void print_single_song(song_t s){
    printf("%30s%30s%30s%30s\n", s->name, s->singer,s->musician,s->year);
}
void process(char *line, song_t s){
    char *name;
    char *singer;
    char *musician;
    char *year;
    remove_tail_lf(line);	
    name = strtok(line,"*#*");
    singer = strtok(NULL,"*#*");
    musician = strtok(NULL,"*#*");
    year = strtok(NULL,"*#*");
    add_song(s,name,singer,musician,year,1);

}
void print_song(song_t *s,int count){
    int id=0;
    for(int i=0;i<count;i++){
        if(s[i]->ex){
            printf("%d ",id+1);
            print_single_song(s[i]);
            id++;
        }
    }
}
void save_song(song_t *s, int count){
    FILE *out = fopen("song.txt","w");
    int id=0;
    for(int i=0;i<count;i++){
        if(s[i]->ex){
            if(id)fprintf(out,"\n");
            fprintf(out,"%s#*#%s#*#%s#*#%s",s[i]->name, s[i]->singer,s[i]->musician, s[i]->year);
            id++;
        }   
    }
    fclose(out);
    
}