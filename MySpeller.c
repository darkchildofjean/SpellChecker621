#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include "levenshtein.c"


void printUsage();
void printVersion();
void lookItUp12(char* word);
int searchMyWordz(int wordRows, char* word, char words[][1024]);

/*This function will loop over my array and
see it has the string value already. I will use this
function to get rid of duplicate entries in my list of
output.*/
int searchMyWordz(int wordRows, char* word, char words[][1024]){
  int isItThere = 1;
  //printf ("in searchMyWordz\n");
  for (int i = 0; i < wordRows; i++) {
    //printf("%s\n", words[i]);
    //printf( "word is %s \nword at index %d is %s", word, i, words[i]);
    if(strcmp(word, words[i]) == 0){
        isItThere = 0;
    }
  }
  return isItThere;
}

/*This function will take in a char*. It will then open the
dictionary file and search it for words that come close in
levenshtein distance. It will populate an array with the first 12
entries from the dictionary that come the closest. */
void lookItUp12(char* word){
  int wordscounter = 0;
  FILE* file = fopen("/usr/share/dict/words", "r");
  //int distance;
  //char *line = NULL;
  char words[12][1024];
  char *word2Compare;//[100];
  while (fgets(word2Compare, sizeof(word2Compare), file)) {
    if(levenshtein_distance(word, word2Compare) == 1){
      printf("%s\n", word);
      exit(0);
    }
  }
  rewind(file);
  while (fgets(word2Compare, sizeof(word2Compare), file)){
    //printf( "word2Compare: %s\n", word2Compare);
    if (searchMyWordz(12, word2Compare, words) != 0) {
      while(levenshtein_distance(word, word2Compare) == 2 && wordscounter < 12){
        strcpy(words[wordscounter], word2Compare);
        //printf( "does this word count: %s\n", words[wordscounter]);
        wordscounter++;
        //file++;
        //printf("%d\n",wordscounter );
        break;
      }
    }
  }
  /*fseek(file,1, SEEK_SET);
  while(levenshtein_distance(word, word2Compare) == 3 && wordscounter < 12){
  strcpy(words[wordscounter], word2Compare);
  wordscounter++;
  printf("%d\n",wordscounter );
}*/
  for (size_t i = 0; i < 12; i++) {
    //if (words[i] != NULL)
      printf(/*"index: %zu and word:*/ "%s\n", /* i,*/ words[i] );
  }
  fclose(file);
}

//This function prints usage
void printUsage() {
  printf("%s\n","MySpeller[-h|--help]    :Output this usage message" );
  printf("%s\n","Myspeller[-v|--version]    :Display this software's version" );
  printf("%s\n","Myspeller[-n|--count]    :Override the default maximum number of suggestions" );
  printf("%s\n","Myspeller[-d|--dictionary]    :Override the default dictionary with a different file" );
}



//This function prints version
void printVersion() {
  printf("%s\n", "MySpeller version 1.00" );
}

int main(int argc, char *argv[]) {
//int wasItThere = 0;
//lookItUp12("pwalz");
//char testwerdz[3][16] = {"apple", "orange", "banana"};
//printf( "first test word is %s \n", testwerdz[0]);
//strcpy( testwerdz [0], "apple");
//strcpy( testwerdz [1], "orange");
//strcpy( testwerdz [2], "banana");
//wasItThere = searchMyWordz(testwerdz, "apple", sizeof(testwerdz));
//printf("%d\n", wasItThere );

static struct option long_options[] = {
  {"dictionary", 0 , NULL, 'd'},
  {"version", 0, NULL, 'v'},
  {"count", 0, NULL, 'n'},
  {"help", 0, NULL, 'h'},
  {0,0,0,0}
};
  int option_index = 0;
  if (argc < 2) {
    printf("%s\n","This command requires arguments!" );
    exit(0);
      }
  int option;
  while (1){
    option = getopt_long(argc, argv, "hv", long_options, &option_index);
    if(option == -1)
      break;

    switch(option){
      case 'h':
        printUsage();
        break;
      case 'v':
        printVersion();
        break;
      default:
        printUsage();
        exit(1);
    }
  }
  lookItUp12(argv[1]);

}
