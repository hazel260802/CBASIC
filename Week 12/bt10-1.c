#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cgen.h"
#include "ext/io.h"
#include"all.h"

int main(int argc, char const *argv[]) {
  if (argc != 2) {
		printf("Usage: ./prog songs.txt\n");
		return 1;
	}
	FILE *inp = fopen(argv[1], "r");
	if (!inp) {
		printf("Loi mo tep %s.\n", argv[1]);
		return 1;
	}
  //Doc du lieu
  int count = 0;
  char *line = NULL;
  song_t *list=malloc(count*sizeof(song_t));
  while (cgetline(&line, 0, inp)) {
    //printf("%s", line);
    count++;
    list = (song_t*)realloc(list,count*sizeof(song_t));
    list[count-1] = malloc(sizeof(struct song));
    process(line,list[count-1]);

  }
  free(line);
  // Lua chon
  int c=0,c1;
  int r,order[count];
  char str[1024], song[1024], singer[1024], musician[1024], year[1024];
  while(c!=5){
    menu();
    c=menu_choice();
    switch (c)
    {
    case 1:
      property();
      c1=prop_choice();
      sort(list,count,c1);
      heading();
      print_song(list,count);
      break;
    
    case 2:
      property();
      c1=prop_choice();
      if (c1 ==1){
        printf("Nhap ten bai hat can tim: ");
        clear_stdin();
        fgets(str, 1024, stdin);
        remove_tail_lf(str);
        search_name(list,str,count);
      }
      else if (c1 ==2){
        printf("Nhap ten ca si can tim: ");
        clear_stdin();
        fgets(str, 1024, stdin);
        remove_tail_lf(str);
        search_singer(list,str,count);
      }
      else if (c1 ==3){
        printf("Nhap ten nhac si can tim: ");
        clear_stdin();
        fgets(str, 1024, stdin);
        remove_tail_lf(str);
        search_musician(list,str,count);
      }
      else if (c1 ==4){
        printf("Nhap ten nam can tim: ");
        clear_stdin();
        fgets(str, 1024, stdin);
        remove_tail_lf(str);
        search_singer(list,str,count);
      }
      break;
    case 3:
      printf("Nhap thong tin cho bai hat:\n");
      clear_stdin();
      printf("Nhap ten bai hat: ");
      fgets(song, 1024, stdin);
      remove_tail_lf(song);
      printf("Nhap ten ca si: ");
      fgets(singer, 1024, stdin);
      remove_tail_lf(singer);
      printf("Nhap ten nhac si: ");
      fgets(musician, 1024, stdin);
      remove_tail_lf(musician);
      printf("Nhap nam sang tac: ");
      fgets(year, 1024, stdin);
      remove_tail_lf(year);
      list = (song_t*)realloc(list,count*sizeof(song_t));
      list[count-1] = malloc(sizeof(struct song));
      add_song(list[count-1],song,singer,musician,year,1);
      break;
    case 4:
      clear_stdin();
      printf("Nhap so thu tu bai ban muon xoa: ");
      scanf("%d", &r);
      clear_stdin();
      printf("Ban thuc su muon xoa toan bo thong tin cua bai hat nay (Y/N):  ");
      char c3;
      scanf("%c", &c3);
						if (c3 == 'Y') {
							list[r-1]->ex = 0;
        			printf("Danh sach sau khi xoa: \n");
              heading();
        			print_song(list, count);
        			save_song(list, count);
						} else {
							continue;
						}
        break;
  }
  save_song(list, count);
  }
  fclose(inp);
  return 0;
}
//gcc -o prog -I ../cgen  bt10-1.c
// in file bt10-1: ./prog songs9.txt  

//cmake (in file b): ./prog songs9.txt  