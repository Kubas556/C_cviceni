#define MAX_PARAMETERS 10
#define MAX_ARG_LENGTH 10
#define MAX_STRING_LENGTH 7
#define UNIVERSUM_CHAR 'U'
#define MNOZINA_CHAR 'S'
#define RELACE_CHAR 'R'
#define PRIKAZ_CHAR 'C'

#define Error(msg) printf("\033[0;31m%s\033[0m\n", msg)

struct Universum
{
    char *values[MAX_PARAMETERS];
};

struct Mnozina
{
    int index;
    char *values[MAX_PARAMETERS];
};

struct Relace
{
    char *values[MAX_PARAMETERS][2];
};

typedef struct Mnozina MnozinaT;

typedef struct Universum UniversumT;

typedef struct Relace RelaceT;