// Program to implement the KMP algorithm in C

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to implement the KMP algorithm
void KMP(const char *X, const char *Y, int m, int n)
{

    if (*Y == '\0' || n == 0)
    {
        printf("[+]The pattern occurs in index: 0");
    }

    if (*X == '\0' || n > m)
    {
        printf("[-]Pattern not found !!");
    }

    int next[n + 1];
    for (int i = 0; i < n + 1; i++)
    {
        next[i] = 0;
    }

    for (int i = 1; i < n; i++)
    {
        int j = next[i + 1];

        while (j > 0 && Y[j] != Y[i])
        {
            j = next[j];
        }

        if (j > 0 || Y[j] == Y[i])
        {
            next[i + 1] = j + 1;
        }
    }

    for (int i = 0, j = 0; i < m; i++)
    {
        if (*(X + i) == *(Y + j))
        {
            if (++j == n)
            {
                printf("[+]The pattern occurs in index: %d\n", i - j + 1);
            }
        }
        else if (j > 0)
        {
            j = next[j];
            i--;
        }
    }
}

int main()
{
    char *text;
    char *pattern;

    printf("[+]Enter a String: ");
    scanf("%s", *text);

    printf("[+]Enter the Pattern: ");
    scanf("%s", *pattern);

    int n = strlen(text);
    int m = strlen(pattern);

    KMP(text, pattern, n, m);

    return 0;
}