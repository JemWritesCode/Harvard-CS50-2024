// Passes style50
// Passes check50 cs50/problems/2024/x/scrabble

#include <cs50.h>
#include <ctype.h> // for toUpper();
#include <stdio.h> // for printf();
#include <string.h>

// Function Prototypes
int compute_score(string word);

// Global Variables
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int score = 0;
    int len = strlen(word);

    // Just make all the letters uppercase
    // Then subtract 'A' to get it's position in the alphabet
    // Example: W is the 23rd letter of the alphabet and this will return 22
    // but arrays start at 0 so this will correlate with the
    // correct position within the POINTS array for points for W.
    for (int i = 0; i < len; i++)
    {
        if (isalpha(word[i]))
        {
            score += POINTS[toupper(word[i]) - 'A'];
        }
    }
    return score;
}
