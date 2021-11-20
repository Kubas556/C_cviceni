#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "utils.c"
#define DEBUG

static UniversumT universum = {NULL, {NULL}};
static MnozinaT mnoziny[] = {NULL};

int main(/*int argc, char **argv*/)
{
    char file[MAX_ARG_LENGTH];
#ifndef DEBUG
    if (argc < 2)
    {
        puts("missing argument");
        exit(0);
    }

    strcpy(file, argv[1]);
#else
    strcpy(file, "file.txt");
#endif

    printf("selected file: %s\n", file);

    FILE *fp;
    char ch;
    fp = fopen(file, "r");

    int characterIndex = 0;
    int lineIndex = 0;
    int wordIndex = 0;
    int wordsCount = 0;
    char words[MAX_ARG_LENGTH][MAX_STRING_LENGTH];
    char lineActionIdentifier;
    while (!feof(fp))
    {
        ch = getc(fp);

        if (ch != UNIVERSUM_CHAR && characterIndex == 0 && lineIndex == 0)
        {
            Error("Missing universum declaration");
            exit(0);
        }

        if (characterIndex == 0)
        {
            lineActionIdentifier = ch;
        }

        if (ch == ' ' || ch == '\n')
        {
            words[wordIndex][wordsCount] = '\0';
            wordIndex++;
            wordsCount = 0;
        }
        else
        {
            if (wordsCount + 1 < MAX_STRING_LENGTH)
            {
                words[wordIndex][wordsCount] = ch;
                wordsCount++;
            }
            else
            {
                Error("Word too long");
                printf("Line %i", lineIndex);
                exit(0);
            }
        }

        if (ch == '\n')
        {
            switch (lineActionIdentifier)
            {
            case UNIVERSUM_CHAR:
                if (universum.values[0] == NULL)
                {
                    for (int i = 0; i < wordIndex; i++)
                    {
                        char *wordCopy = (char *)malloc(sizeof(char) * MAX_STRING_LENGTH);
                        for (int j = 0; 1; j++)
                        {
                            //char *charCopy = (char *)malloc(sizeof(char));

                            //*charCopy = words[i][j];
                            wordCopy[j] = /**charCopy*/ words[i][j];

                            if (words[i][j] == '\0')
                                break;
                        }
                        //char arr[20];
                        //arr[0] = ' ';
                        //printf("%s\n", wordCopy);
                        universum.values[i] = wordCopy;

                        if (i + 1 < MAX_PARAMETERS)
                            universum.values[i + 1] = NULL;
                        //printf("%s\n", wordCopy);
                    }
                }

                break;
            case MNOZINA_CHAR:
                printf("mnozina deklarace\n");
                break;
            case RELACE_CHAR:

                break;
            case PRIKAZ_CHAR:

                break;
            default:
                Error("Unknown character");
                printf("Line %i", lineIndex);
                exit(0);
                break;
            }

            lineIndex++;
            characterIndex = 0;
            wordIndex = 0;
            wordsCount = 0;
        }
        else
        {
            characterIndex++;
        }
    }
    vypisUniversum(&universum);
    //printf("last value %s\n", universum.values[2]);
    fclose(fp);
    printf("konec\n");

    //char t[] = {'t', 'e', 's', 't'};
    /*MnozinaT testovaci;
    testovaci.index = 1;
    testovaci.values[3] = NULL;
    testovaci.values[0] = "test";
    testovaci.values[1] = "test2";
    char f[50];
    scanf("%s", &f[0]);
    testovaci.values[2] = &f[0];

    vypisMnozinu(&testovaci);*/

    return 0;
}

//printf("%c\n", testovaci.values[1]);
/*char *p = &t[0];
    p++;
    printf("%c", *p);*/