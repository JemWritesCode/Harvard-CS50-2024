#include <stdio.h>
#include <cs50.h>

void print_row(int length);

int main(void){

    int height = get_int("Height: ");

    for(int i = 0; i < height; i++)
    {
        print_row(i + 1);
        printf("\n");
    }
}

void print_row(int length)
{
    for (int j = 0; j < length; j++)
        {
            printf("#");
        }
}
