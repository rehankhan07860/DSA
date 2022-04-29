#include<stdio.h>
#include<string.h>

//recurtion
int checkPalindrom(char* expression, int len, int i)
{
    if(i == len/2)
        return 1;
    
    int result = checkPalindrom(expression, len, i + 1);
    if(result == 1) {
        if(expression[i] == expression[len - 1 - i])
            return 1;
        else
            return 0;
    }
}

//iteration
int checkPalindromIterative(char* expression)
{
    int len = strlen(expression);
    int i = 0;

    for(i = 0;i < len/2;++i)
    {
        if(expression[i] != expression[len - 1 - i])
        {
            return 0;
        }
    }

    return 1;
}

int main()
{
    char name[] = "a";
    
    if(checkPalindrom(name, 1, 0))
    {
        printf("This is a palindrom.\n");
    }
    else
    {
        printf("This is not palindrom.\n");
    }
}