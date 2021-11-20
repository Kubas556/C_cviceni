#define CONSOlE_DELIMETER "----------------\n"

int VUniversu(UniversumT universum, char *value)
{
    for (int i = 0; universum.values[i] != NULL; i++)
    {
        //printf("%s\n", universum.values[i]);
        //printf("%s", value);
        if (!strcmp(universum.values[i], value))
            return 1;
    }
    return 0;
}

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