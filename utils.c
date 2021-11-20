#define CONSOlE_DELIMETER "----------------\n"

void vypisMnozinu(MnozinaT *t)
{
    printf(CONSOlE_DELIMETER);
    printf("Hodnoty mnoziny s indexem %i:\n", t->index);
    for (int i = 0; i < (int)(sizeof t->values / sizeof t->values[0]); i++)
    {
        if (t->values[i])
        {
            printf("%s\n", t->values[i]);
        }
        else
            break;
    }
    printf(CONSOlE_DELIMETER);
};

void vypisUniversum(UniversumT *t)
{
    printf(CONSOlE_DELIMETER);
    printf("Hodnoty univerza: \n");
    for (int i = 0; i < (int)(sizeof t->values / sizeof t->values[0]); i++)
    {
        if (t->values[i])
        {
            printf("%s ", t->values[i]);
        }
        else
            break;
    }
    printf("\n");
    printf(CONSOlE_DELIMETER);
};