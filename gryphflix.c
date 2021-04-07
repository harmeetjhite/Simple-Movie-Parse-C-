#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gryphflix.h"

#define NUMBER_REVIEWERS 10
#define NUMBER_MOVIES 3
#define MAX_STR 50
#define MAX_WORDS 10


FILE *openFileForReading(char *filename)
{

    FILE * fPointer = fopen(filename, "r");
    if (fPointer != NULL) 
    {
        return fPointer;
    }

    else 
    {
        return fPointer = NULL;
    }
}

int readMovies(FILE *file, char movieNames[NUMBER_MOVIES][MAX_STR])
{

    if (file == NULL)
    {
       // printf("hi");
        return 0;
    }

    else 
    {
        for (int i=0; i < NUMBER_MOVIES; i++)
        {
        fgets(movieNames[i], MAX_STR, file);
        //printf("%s", movieNames[i]);
        }
    return 1;
    }
}


int readReviews(FILE *file, struct reviewStruct reviews[NUMBER_REVIEWERS])
{

    char temp;

    if (file == NULL)
    {
        return 0;
    }

    else 
    {
        for (int i=0; i < NUMBER_REVIEWERS; i++)
        {
            fscanf(file, "%s", reviews[i].reviewer);

            for (int j=0; j< NUMBER_MOVIES; j++) 
            {
                getc(file);
                fscanf(file, "%c", &temp);

                if(temp == 'Y' || temp == 'y') {
                    reviews[i].feedback[j] = 1;
                }
                else if (temp == 'N' || temp == 'n') {
                    reviews[i].feedback[j] = 0;
                }
      // printf("%d %s", reviews[i].feedback[j], reviews[i].reviewer);
            }
     //   printf("\n");
        }

    return 1;
    }

}

int getMostCriticalReviewers(struct reviewStruct reviews[NUMBER_REVIEWERS], char mostCriticalReviewers[NUMBER_REVIEWERS][MAX_STR])
{

int scores[NUMBER_REVIEWERS] = {0};
int lowest = NUMBER_MOVIES;

for(int i = 0; i < NUMBER_REVIEWERS; i++)
{
    for(int j = 0; j < NUMBER_MOVIES; j++)
    {
            scores[i] =  scores[i] + reviews[i].feedback[j];
    }   

    if (scores[i] < lowest) 
    {
        lowest =  scores[i];
    }

}

int j=0;

for (int i =0; i<NUMBER_REVIEWERS; i++)
{
    if (scores[i] == lowest) 
    {
        strcpy(mostCriticalReviewers[j], reviews[i].reviewer);
        j++;
    }
}

for (int i =0; i<j; i++)
    {
   // printf("%s \n", mostCriticalReviewers[i]);
    }


return j+1;
}

int getMostRecommendedMovies(
    const char movies[NUMBER_MOVIES][MAX_STR],
    const struct reviewStruct reviews[NUMBER_REVIEWERS],
    char mostRecommendedMovies[NUMBER_REVIEWERS][MAX_STR]
) 
{

int scores[NUMBER_REVIEWERS] = {0};
int highest = NUMBER_MOVIES;

for(int i = 0; i < NUMBER_MOVIES; i++)
{
    for(int j = 0; j < NUMBER_REVIEWERS; j++)
    {
            scores[i] =  scores[i] + reviews[j].feedback[i];
    }   
    //printf("%d\n", scores[i]);

    if (scores[i] > highest) 
    {
        highest =  scores[i];
    }

}

int j=0;

for (int i =0; i<NUMBER_MOVIES; i++)
{
    if (scores[i] == highest) 
    {
        strcpy(mostRecommendedMovies[j], movies[i]);
        j++;
    }
}

for (int i =0; i<NUMBER_MOVIES; i++)
    {
 //  printf("%s \n", mostRecommendedMovies[i]);
    }
return j+1;
}


int enumerateMovie(const char movie[MAX_STR], int charCounts[MAX_WORDS])
{

int i=0;
int countwords = 1;

while (movie[i] != '\0') {
    if(movie[i] == ' ') {
        countwords++;
    }
    else {
        charCounts[countwords-1]++;
    }
    i++;
}

charCounts[countwords-1] =  charCounts[countwords-1] - 1;

/*printf("words: %d\n", countwords);
for(int i=0; i<countwords; i++) {
printf("chars in: %d\n", charCounts[i]);
}


printf("%s",movie);
*/

return countwords;

}


int predictMovie(const char movie[MAX_STR])
{
int charcount[MAX_WORDS] = {0};
int words = 1;
words = enumerateMovie(movie, charcount);
int salescore[4] = {0};
int counteven=0;

//printf("%s\n", movie);
//printf("number words: %d\n", words);

for(int j=0; j<words; j++) {
    //printf("number chars in word %d: %d\n", j+1, charcount[j]);
}

if(words > 2) {
    salescore[0] = -1;;
   // printf("-1\n");
}

if (words == 1) {
    salescore[1] = -2;
    //printf("-2\n");
}

for(int i=0; i < words; i++) 
{
    if (charcount[i] % 2 == 0)
    {
        counteven++;
    }
    if (counteven > 1) {
        salescore[2] = 1;
       // printf("1\n");
    break;
    }
}

salescore[3] = 2;
for (int i=0; i<words-1; i++) 
{
    if (charcount[0] != charcount[i])
    {
        salescore[3] = 0;
        break;
    }
}

//printf("%d\n", salescore[3]);

int finalscore = 0;

for(int j=0; j < 4; j++) 
{
    finalscore = finalscore + salescore[j];
}

if (finalscore < -2){
    finalscore = -2;
}

if (finalscore > 2) {
    finalscore = 2;
}

//printf("final score: %d\n", finalscore);

return finalscore;


}






