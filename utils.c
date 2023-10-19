#include <stdio.h>

int getLength(char* arr)
{
    return sizeof(arr) / sizeof(arr[0]);
}

void getInput(char* msg, char* result)
{
    printf("%s", msg);

    scanf("%s", result);
}
