
#include <stdio.h>

extern int global_token;

void incrementGlobal(void);

static int getStaticToken(void)
{
    static int token = 1000;
    token++;
    return token;
}

int main(void)
{
    int i;

    printf("STATIC: ");
    for (i = 0; i < 3; i++)
    {
        printf("%d ", getStaticToken());
    }

    printf("\nAUTO: ");
    for (i = 0; i < 3; i++)
    {
        auto int token = 1000;
        token++;
        printf("%d ", token);
    }

    printf("\nEXTERN: ");
    for (i = 0; i < 3; i++)
    {
        incrementGlobal();
        printf("%d ", global_token);
    }

    printf("\nREGISTER: ");
    for (register int count = 1; count <= 3; count++)
    {
        printf("%d ", count);
    }

    printf("\n");

    return 0;
}

int global_token = 1000;

void incrementGlobal(void)
{
    global_token++;
}
