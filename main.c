#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "utils.c"
//#define DEBUG

static UniversumT universum = {0};
static int pocetMnozin = 0;
static MnozinaT mnoziny[MAX_PARAMETERS] = {0};
static int pocetRelaci = 0;
static RelaceT relace[MAX_PARAMETERS] = {0};

int main(int argc, char **argv)
{
    char file[MAX_ARG_LENGTH];
#ifndef DEBUG
    if (argc < 2)
    {
        Error("missing argument");
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

                if (universum.values[0] != NULL)
                {
                    Error("Universum already declared");
                    printf("Line %i\n", lineIndex);
                    exit(0);
                }

                for (int i = 1; i < wordIndex; i++)
                {
                    char *wordCopy = (char *)malloc(sizeof(char) * MAX_STRING_LENGTH);
                    for (int j = 0; 1; j++)
                    {
                        wordCopy[j] = words[i][j];

                        if (words[i][j] == '\0')
                            break;
                    }

                    universum.values[i - 1] = wordCopy;

                    if (i < MAX_PARAMETERS)
                        universum.values[i] = NULL;
                }

                break;
            case MNOZINA_CHAR:
                for (int i = 1; i < wordIndex; i++)
                {
                    char *wordCopy = (char *)malloc(sizeof(char) * MAX_STRING_LENGTH);
                    for (int j = 0; 1; j++)
                    {
                        wordCopy[j] = words[i][j];

                        if (words[i][j] == '\0')
                            break;
                    }

                    if (!VUniversu(universum, wordCopy))
                    {
                        Error("Value not in universe!");
                        printf("Line %i", lineIndex);
                        exit(0);
                    }

                    mnoziny[pocetMnozin].values[i - 1] = wordCopy;

                    if (i < MAX_PARAMETERS)
                        mnoziny[pocetMnozin].values[i] = NULL;
                }

                mnoziny[pocetMnozin].index = lineIndex;

                pocetMnozin++;

                break;
            case RELACE_CHAR:
            {
                if ((wordIndex - 1) % 2 != 0)
                {
                    Error("Relation must be in pairs!");
                    printf("Line %i", lineIndex);
                    exit(0);
                }

                int pairIndex = 0;
                for (int i = 1; i < wordIndex; i++)
                {
                    int skipedChars = 0;
                    char *wordCopy = (char *)malloc(sizeof(char) * MAX_STRING_LENGTH);
                    for (int j = 0; 1; j++)
                    {
                        if (words[i][j] == '(' || words[i][j] == ')')
                        {
                            skipedChars++;
                            continue;
                        }

                        wordCopy[j - skipedChars] = words[i][j];

                        if (words[i][j] == '\0')
                            break;
                    }

                    if (!VUniversu(universum, wordCopy))
                    {
                        Error("Value not in universe!");
                        printf("Line %i", lineIndex);
                        exit(0);
                    }

                    relace[pocetRelaci].values[i - 1][pairIndex] = wordCopy;

                    if (i < MAX_PARAMETERS)
                        relace[pocetRelaci].values[i][pairIndex] = NULL;

                    if (pairIndex == 0)
                        pairIndex = 1;
                    else
                        pairIndex = 0;
                }

                relace[pocetRelaci].index = lineIndex;

                pocetRelaci++;
            }
            break;
            case PRIKAZ_CHAR:
                if (!strcmp(words[1], "empty"))
                {
                    if (wordIndex == 3)
                    {
                        printf("%s", mnEmpty(atoi(words[2])) ? "true" : "false");
                        printf("\n");
                    }
                    else
                    {
                        Error("This command takes 1 argument");
                        printf("Line %i\n", lineIndex);
                        exit(0);
                    }
                }
                else
                {
                    Error("Unknown command");
                    printf("Line %i", lineIndex);
                    exit(0);
                }

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

    //uncoment this if you want to write out, what is inside mnozina, relace and universum variables
    /*vypisUniversum(&universum);
    vypisMnozinu(&mnoziny[0]);
    vypisMnozinu(&mnoziny[1]);
    vypisRelace(&relace[0]);*/

    //clean memory
    //the way how values are stored is inefective. TODO: change mnoziny and values to use pointer from universum
    for (int i = 1; i < MAX_PARAMETERS; i++)
    {
        for (int j = 0; j < MAX_PARAMETERS; j++)
            free(mnoziny[i].values[j]);
    }

    for (int i = 1; i < MAX_PARAMETERS; i++)
    {
        free(universum.values[i]);
    }

    for (int i = 1; i < MAX_PARAMETERS; i++)
    {
        for (int j = 0; j < MAX_PARAMETERS; j++)
            for (int k = 0; k < 2; k++)
                free(relace[i].values[j][k]);
    }

    fclose(fp);
    printf("konec\n");

    return 0;
}

//------------------------------------------------functions for mnoziny------------------------------------------------

int mnEmpty(int line)
{
    for (int i = 0; i < pocetMnozin; i++)
    {
        if (mnoziny[i].index == line)
        {
            if (mnoziny[i].values[0] == NULL)
                return 1;
            else
                return 0;
        }
    }
    Error("There is no mnozina with this index");
    printf("Passed index %i", line);
    exit(0);
    return 0;
}

//------------------------------------------------functions for relace-------------------------------------------------