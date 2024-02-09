// Passes check50 cs50/problems/2024/x/mario/more
// However, the file must be named mario.c to run the check.
// passes style50
#include <cs50.h>
#include <stdio.h>

void print_row(int length, int height);
int get_height(void);

int main(void)
{
    int height = get_height();
    for (int i = 0; i < height; i++)
    {
        print_row(i + 1, height);
    }
}

void print_row(int length, int height)
{
    int blanks = height - length;
    for (int i = 0; i < blanks; i++)
    {
        printf(" ");
    }
    for (int i = 0; i < length; i++)
    {
        printf("#");
    }
    printf("  ");
    for (int i = 0; i < length; i++)
    {
        printf("#");
    }
    printf("\n");
}

int get_height(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    return height;
}
