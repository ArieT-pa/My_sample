#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spell.h"

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as
they are declared before the array in the parameter list. See:
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/

Worst case time complexity to compute the edit distance from T test words
 to D dictionary words where all words have length MAX_LEN:
Student answer:  Theta(............)


Worst case to do an unsuccessful binary search in a dictionary with D words, when
all dictionary words and the searched word have length MAX_LEN
Student answer:  Theta(............)
*/


/* You can write helper functions here */


/*
Parameters:
first_string - pointer to the first string (displayed vertical in the table)
second_string - pointer to the second string (displayed horizontal in the table)
print_table - If 1, the table with the calculations for the edit distance will be printed.
              If 0 (or any value other than 1)it will not print the table
(See sample run)
Return:  the value of the edit distance (e.g. 3)
*/
int min(int m,int n,int o)
{
  int current;
  current=m<n?m:n;
  current=current<o?current:o;
  return current;
}
int edit_distance(char * first_string, char * second_string, int print_table){
  //int first=sizeof(first_string)/sizeof(first_string[0]);
  //int second=sizeof(second_string)/sizeof(second_string[0]);
  int len2=strlen(first_string);
  int len1=strlen(second_string);
  int i,j;
  int table[len1+1][len2+1];
  for(i=0;i<=len1;i++)
  {
    table[i][0]=i;
  }
  for(j=0;j<=len2;j++)
  {
    table[0][j]=j;
  }
  for(i=0;i<len1;i++){
        for(j=0;j<len2;j++){
            if(second_string[i]!=first_string[j])
                table[i+1][j+1] = 1+min(table[i][j+1],table[i+1][j],table[i][j]); // i,j i,j+1, j+1,i
            else
                table[i+1][j+1] = table[i][j];
        }
    }
    int a;
    for(a=0;a<len1+2;a++)
    {
        if(a==0||a==1)
        {
          printf("       |");
        }
        else
        {
          printf("     %c |",second_string[a-2]);
        }
    }
    printf("\n");

    for(a=0;a<len1+2;a++)
    {
      printf("--------");
    }

    printf("\n");

    for(i=0;i<=len2;i++)
    {
      if(i==0)
      {
        printf("       |");
      }
      else
      {
        printf("     %c |",first_string[i-1]);
      }
      for(j=0;j<=len1;j++)
      {
        printf(" %5d |",table[j][i]);
      }
      printf("\n");
      for(a=0;a<len1+2;a++)
      {
        printf("--------");
      }
      printf("\n");
    }
	return table[len1][len2];  // replace this line with your code
}


/*
Parameters:
testname - string containing the name of the file with the paragraph to spell check, includes .txt e.g. "text1.txt"
dictname - name of file with dictionary words. Includes .txt, e.g. "dsmall.txt"
printOn - If 1 it will print EXTRA debugging/tracing information (in addition to what it prints when 0):
			 dictionary as read from the file
			 dictionary AFTER sorting in lexicographical order
			 for every word searched in the dictionary using BINARY SEARCH shows all the "probe" words and their indices indices
			 See sample run.
	      If 0 (or anything other than 1) does not print the above information, but still prints the number of probes.
		     See sample run.
*/
/*int compareStr(const void *pa, const void *pb)
{
  return strcmp(pa, pb);
}
*/
void sortitout(char **str, int* size, int printOn)
{
 char temp[101];
  int count=*size;
  int i;
  int j;
  for(i=0;i<*size;i++)
    for(j=i+1;j<*size;j++)
        if(strcmp(str[i],str[j])>0){
            strcpy(temp,str[i]);
            strcpy(str[i],str[j]);
            strcpy(str[j],temp);
        }
      //qsort(str, *size, 101, compareStr);
      if(printOn==1){
          printf(" Sorted Dictionary (alphabetical order) : \n");
          for(int i = 0; i < *size; i++)
          {
      	    printf("%d. %s",i, str[i]);
          }
      }

}

void readdictintoarray(char* dictname, int* size,int printOn,char* newfile,char list[][101] )
{
  printf("Corrected Output filename: %s \n", newfile);
  printf("\n");
  printf("Loading the dictionary file: %s \n", dictname);
  printf("\n");

  FILE *fp;
  char line[101];
  char *pch;
  //char *del1="\n";
  if((fp=fopen(dictname,"r"))==NULL)
  {
    printf("Invalid Filename.");
    return;
  }
  else
  {

    fgets(line,sizeof(line),fp);
    *size=atoi(strtok(line,del1));
    size_t lineCount = 0;
    //char **list =(char**)malloc(sizeof(char*)*(*size));
    while (fgets(line, sizeof(line), fp)) {
	    //list[lineCount] = malloc(sizeof(char)*101);
      pch=strtok(line,"\n");
	    strcpy(list[lineCount],pch);
	    lineCount++;
    }

    printf("Dictionary has size: %5d \n", *size);

    if(printOn==1)
    {
      printf(" Original dictionary: \n");
      for(int i = 0; i < lineCount; i++){
  	    printf("%d. %s",i, list[i]);
    }
   }
    printf("\n");
    fclose(fp);
  }

}
/*void printword(char** arr, char** sorted,int *size)
{
  printf(" Original dictionary: \n");
  for(int i = 0; i < *size; i++){
    printf("%d. %s",i,arr[i]);
  }
  printf("\n");

  printf(" Sorted Dictionary (alphabetical order) : \n");
  for(int j = 0; j < *size; j++){
    printf("%d. %s",j ,sorted[j]);
  }
  printf("\n");
}*/
int edit_d(char *first_string,char*second_string)
{
  int len2=strlen(first_string);
  int len1=strlen(second_string);
  int i,j;
  int table[len1+1][len2+1];
  for(i=0;i<=len1;i++)
  {
    table[i][0]=i;
  }
  for(j=0;j<=len2;j++)
  {
    table[0][j]=j;
  }
  for(i=0;i<len1;i++){
        for(j=0;j<len2;j++){
            if(second_string[i]!=first_string[j])
                table[i+1][j+1] = 1+min(table[i][j+1],table[i+1][j],table[i][j]); // i,j i,j+1, j+1,i
            else
                table[i+1][j+1] = table[i][j];
        }
      }
   return table[len1][len2];
}

int compare(int a, int b)
{
  if(a<b) return a;
  else return b;
}

char *edit_d_calc(char *token,char** arr, int *size,char *userinput)
{
  printf("-1 - type correction\n");
  printf(" 0 - leave word as is (do not fix spelling)\n");
  //char *userinput=(char*)malloc(sizeof(char)*101);
  int select;
  int i=0;
  int count=1;
  int array[*size];
  int small;
  //computing the edit edit_distance
  int a=edit_d(token, arr[0]);
  array[0]=a;
  for(i=1;i<*size;i++)
  {
    int b=edit_d(token,arr[i]);
    array[i]=b;
    small=compare(a,b);
    a=small;
  }
  //printf("%d",array[0]);
  //printf("%d",array[1]);
  //printf("%d",array[2]);

  printf("     Minimum distance: %2d (computed edit distances: %2d)\n", small,*size);
  printf("     Words that give minimum distance: \n");
  for(i=0;i<*size;i++)
  {
    if(array[i]==small)
    {
      printf(" %d - %s",count, arr[i]);
      array[count-1]=i;
      count++;
    }
  }
  printf("Enter your choice(from the above options): ");
  scanf("%d", &select);
  if(select==-1)
  {
    printf("Enter the correct word: ");
    scanf("%s",userinput);
    return userinput;
    free(userinput);
  }
  else if(select==0)
  {
    return token;
  }
  else
  {
    return arr[array[select-1]];
  }
}

int binary_search(char *target, char** list_of_words, int printOn,int *size)
{
  //printf("%s\n", target);
  //printf("%5d", *size);
  int i=0;
  int a=*size;
  int bottom= 0;
    int mid;
    int top = a - 1;
    if(printOn==1)
    {
      printf("Binary search for: %s\n", target);
    }

    while(bottom <= top){
        mid = (bottom + top)/2;
        if(printOn==1)
        {
          printf("dict[%d]= %s",mid,list_of_words[mid]);
        }
        if (strcmp(list_of_words[mid], target) == 0){
            i++;
            printf("---->|%s|(words compared when searching: %d)\n\n", target,i);
            return 1;
        } else if (strcmp(list_of_words[mid], target) > 0){
            i++;
            top    = mid - 1;
        } else if (strcmp(list_of_words[mid], target) < 0){
          i++;
            bottom = mid + 1;
        }
    }
    if(printOn==1&&bottom>top)
    {
      printf("Not found. \n");
    }
    printf("---->|%s|(words compared when searching: %d)\n\n", target,i);
    return 0;
}

void textfilework(char *testname,char** arr, int printOn, char *newfile, int *size)
{
  FILE *fp, *fp1;
  char line[100000];
  char userinput[101];
  char *token;
  char *s=" ";
  if((fp=fopen(testname,"r"))==NULL)
  {
    printf("Invalid Filename.");
    return;
  }
  else
  {
    fgets(line, sizeof(line), fp);
    //printf("%s",line);
      token=strtok(line,s);
      if((fp1=fopen(newfile,"w"))==NULL)
      {
        printf("Cannot open write-in file");
      }
      while(token!=NULL){
         //printf("%s",token);
         //if(strcmp(token[0],",")==0||strcmp(token[0],".")==0||atrcmp(token[0],"!")==0||strcmp(token[0],"?")==0)
         if(token[0]==','||token[0]=='.'||token[0]=='!'||token[0]=='?'||token[0]==' ')
         {
            fputs(token,fp1);
         }
         else
         {
    	       int a= binary_search(token, arr, printOn,size);
             if(a==1)
             {
               printf("     - OK");
               fputs(token,fp1);
               fputs(s,fp1);
             }
             else{
               char *app=edit_d_calc(token,arr,size,userinput);
               fputs(app,fp1);
               fputs(s,fp1);
             }
         }
         token=strtok(NULL,s);
       }


  }
}

void spell_check(char * testname, char * dictname, int printOn){
  int size=0;
  char newfile[101] = "out_";
  strcat(newfile, testname);
	char arr[size][101];
  readdictintoarray(dictname,&size,printOn,newfile,arr);
  sortitout(arr, &size, printOn);
  textfilework(testname, arr,printOn, newfile,&size);

  /*for(int i=0;i<=size;i++)
  {
    free(arr[i]);
  }*/
  //free(arr);
}
