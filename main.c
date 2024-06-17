#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX_GIVEN_WORDS 300000
#define MAX_WORD_COUNT 100
#define MAX_WORD_SIZE 20
#define MAX_VECTOR_SIZE 400
#define MAX_DICT_WORDS 2000
#define VECTOR_SIZE 200
#include <stdlib.h>
#include <string.h>

void splitString(char* str, char** words, int* numWords) {
    int wordCount = 0;
    int inWord = 0;
    int strIndex = 0;
    int wordStartIndex = 0;
    
    while (str[strIndex] != '\0') {
        if (str[strIndex] == ' ') {
            if (inWord) {
                // Allocate memory for the word and copy characters
                int wordLength = strIndex - wordStartIndex;
                words[wordCount] = (char*) malloc((wordLength + 1) * sizeof(char));
                strncpy(words[wordCount], &str[wordStartIndex], wordLength);
                words[wordCount][wordLength] = '\0'; // Null-terminate the word
                wordCount++;
                inWord = 0;
            }
        } else if (!inWord) {
            inWord = 1;
            wordStartIndex = strIndex;
        }
        
        strIndex++;
    }
    
    // Handle the last word if there's no trailing space
    if (inWord) {
        int wordLength = strIndex - wordStartIndex;
        words[wordCount] = (char*) malloc((wordLength + 1) * sizeof(char));
        strncpy(words[wordCount], &str[wordStartIndex], wordLength);
        words[wordCount][wordLength] = '\0'; // Null-terminate the word
        wordCount++;
    }
    
    
    *numWords = wordCount;
}


int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]){
   int words=0;
   FILE *fp = fopen(file_name,"r");
   if( fp == NULL)
   {
   	printf("Error opening the file.\n");
   }
   int c = fgetc(fp); 
   while ((c = fgetc(fp)) != EOF) {
   fscanf(fp,"%s",dict[words]);
   if(c == '\n') 
   	words++;
   }
   dict[words-1][0] = '-';
   dict[words-1][1] = '\0';
   fclose(fp);
   return words;  
}
int read_text(const char * text_file, const char * ignore_file, char words[][MAX_WORD_SIZE]){
    FILE* file = fopen(text_file, "r");
    if (!file) {
        printf("Error opening input file\n");
        return -1;
    }

    // Open ignore file
    FILE* ptr_ignore_file = fopen(ignore_file, "r");
    if (!ptr_ignore_file) {
        printf("Error opening ignore file\n");
        fclose(file);
        return -1;
    }

    char ignored_words[MAX_WORD_COUNT][MAX_WORD_SIZE];
    int num_ignored_words = 0;
    while (fscanf(ptr_ignore_file, "%s", ignored_words[num_ignored_words]) == 1) {
        num_ignored_words++;
    }
    fclose(ptr_ignore_file);

    int num_words = 0;
    while (fscanf(file, "%s", words[num_words]) == 1) {
        char* p = words[num_words];
        char* q = words[num_words];
        while (*p) {
            if (!((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z'))) {
                p++;
            } else {
                *q++ = *p++;
            }
        }
        *q = '\0';

        int is_ignored = 0;
        for (int i = 0; i < num_ignored_words; i++) {
            if (strcmp(words[num_words], ignored_words[i]) == 0) {
                is_ignored = 1;
                break;
            }
        }

        if (!is_ignored) {
            num_words++;
        }
    }
   fclose(file);
   words[num_words][0] = '-';
   words[num_words][1] = '\0';
   return num_words;
   }
int dissimilarity(char * w1, char dict[][MAX_WORD_SIZE], int index){
double threshold=6.00;
double vector_arr[1000][VECTOR_SIZE];
FILE* file = fopen("dictionary.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }
        int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            break;
        }
    }

    
    for (int i = 0; i < 1000; i++) {
        // Ignore the word in each line
        char word[MAX_WORD_SIZE];
        fscanf(file, "%s", word);

        for (int j = 0; j < VECTOR_SIZE; j++) {
            fscanf(file, "%lf", &vector_arr[i][j]);
        }
    }

    fclose(file);
		
int index2;
double temp;
double temp2;
double distance=10.00;
for(int i=0;i<1100;i++){
double sum=0;
	for(int j=0;j<VECTOR_SIZE;j++){

		temp = (vector_arr[index][j] - vector_arr[i][j]) * (vector_arr[index][j] - vector_arr[i][j]);
	sum = sum+temp;
	}
	
	
	temp2 = sqrt(sum);
	if(distance>temp2 && temp2!=0.00){
	distance=temp2;
	index2=i;
	}


}
if(distance<threshold && distance!=0.00){
return index2;
}
else{
return 0;
}
}

int histogram(int word_counter, const int occurences[]){
int max_occurence=0,scale;
for(int i=0;i<word_counter;i++){
if(max_occurence<occurences[i]){
max_occurence=occurences[i];
}
}
if(max_occurence>20){
if (max_occurence%20!=0){
scale=(max_occurence/20)+1;
}
else{
scale = max_occurence/20;
}
}
else{
scale=1;
}
return scale;
}

int main(){
const char * text_file = "input.txt";
const char * ignore_file = "ignore.txt";
const char * file_name = "dictionary.txt";
char input_txt[MAX_GIVEN_WORDS][MAX_WORD_SIZE];
int word_counter = 0, inputwordc=0, frequencyi=0, word_index=0, dictionarywordc=0, frequencyd=0, distance=0,most_frequency=0,scale,sekil=0;
char input[MAX_WORD_SIZE], similar[MAX_WORD_SIZE];
char dict[MAX_DICT_WORDS][MAX_WORD_SIZE];
char* words[MAX_WORD_COUNT];
char* w1;
int occurences[MAX_WORD_COUNT];
printf("Enter word(s): ");
scanf("%[^\n]s",input);
inputwordc=read_text(text_file, ignore_file, input_txt);

splitString(input, words, &word_counter);
if(word_counter==1){
      for (int i = 0; i < inputwordc; i++) {
            if (strcmp(input, input_txt[i]) == 0) {
                frequencyi++;
            }
        }
        if(frequencyi>0){
        printf("%s appears in input.txt %d times." ,input ,frequencyi);
        }
        else{
        dictionarywordc=read_dict(file_name, dict);
        for (int j = 0; j < dictionarywordc; j++) {
            if (strcmp(input, dict[j]) == 0) {
                word_index=j;
                }
                }
                w1=input;
                distance = dissimilarity(w1, dict, word_index);
                if(distance>0){

           	 for (int k = 0; k < inputwordc; k++) {
            	 if (strcmp(dict[distance], input_txt[k]) == 0) {
               	 frequencyd++;
              		}
        	 }
        	 if(frequencyd>0){
        	 	printf("%s doesn't appear in input.txt but %s appears %d times.", input, dict[distance], frequencyd);
        	 }
        	 else{
        	 printf("%s doesn't appear in input.txt!" ,input);
        	 }
        	 }

            
            else{
            printf("%s doesn't appear in input.txt." ,input);
            }
        }
        
     }


else{
for (int x=0;x<word_counter;x++){
for (int i = 0; i < inputwordc; i++) {
            if (strcmp(words[x], input_txt[i]) == 0) {
                frequencyi++;               
            }
        }
        
        if(frequencyi>0){
            occurences[x] = frequencyi;
            
        }
        
        else{
        dictionarywordc=read_dict(file_name, dict);
        for (int j = 0; j < dictionarywordc; j++) {
            if (strcmp(words[x], dict[j]) == 0) {
                word_index=j;
                }
                }
                w1==words[x];
                distance = dissimilarity(w1, dict, word_index);
                if(distance>0){

           	 for (int k = 0; k < inputwordc; k++) {
            	 if (strcmp(dict[distance], input_txt[k]) == 0) {
               	 frequencyd++;
              		}
              	 	
        	 }
        	 
        	 
        	 }
         occurences[x] = frequencyd;
         
        }
        
        
}
frequencyi=0;
frequencyd=0;
scale=histogram(word_counter,occurences);
if(scale==1){
for(int y=0;y<word_counter;y++){
printf("%s          ",words[y]);
if(occurences[y]==0){
printf("NO MATCHES");
}
else{
for(int z=0;z<occurences[y];z++){
           	 for (int k = 0; k < inputwordc; k++) {
            	 if (strcmp(words[y], input_txt[k]) == 0) {
            	 	sekil=1;
               	}

 }

if(sekil==1){
printf("*");
}
if(sekil==0){
printf("+");
}
}
}
printf("\n");
}
}
else if(scale!=0){
printf("Scale: %d\n", scale);
for(int y=0;y<word_counter;y++){
int c = occurences[y]/scale;
printf("%s          ",words[y]);
	if(occurences[y]==0){
	printf("NO MATCHES");
	}
	else{
	for(int z=0;z<c;z++){
           	 	for (int k = 0; k < inputwordc; k++) {
            	 	if (strcmp(words[y], input_txt[k]) == 0) {
            	 		sekil=1;
               		}
               	
 	}

	if(sekil==1){
	printf("*");
	}
	else{
	printf("+");
	}
	}
}
printf("\n");
}

}
}

return 0;
}




