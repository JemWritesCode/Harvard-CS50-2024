// passes check50 cs50/problems/2024/x/mario/less
// passes style50 mario.c
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
    for (int x = 0; x < blanks; x++)
    {
        printf(" ");
    }
    for (int j = 0; j < length; j++)
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
    while (height < 1);
    return height;
}
