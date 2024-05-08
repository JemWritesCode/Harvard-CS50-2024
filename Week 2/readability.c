/* Passes check50 cs50/problems/2021/x/readability

Coleman-Liau Index - Determine Text's Reading Grade Level
index = 0.0588 * L - 0.296 * S - 15.8
L == Average Number of Letters per 100 words
S == Average Number of sentences per 100 words

- Consider any sequence of characters separated by a space to be a word
- You may assume that a sentence will not start or end with a space, and you may assume that a sentence will not have multiple spaces in a row.
- Consider any sequence of characters that ends with a . or a ! or a ? to be a sentence
---------
Note: Could just iterate through the text once and count everything as you go. It would be more efficient for runtime and memory.
However, I broke it into separate functions so it's easier to read since this is for learning.
*/

#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h> // strlen();
#include <ctype.h> // isalpha();

// Function Prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int compute_reading_level(string text);

int main(void)
{
    string userText = get_string("Text: ");
    int level = compute_reading_level(userText);

    if (level < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (level > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", level);
    }
}

int count_letters(string text)
{
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 1;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}

int compute_reading_level(string text)
{
    int words = count_words(text);
    int letters = count_letters(text);
    int sentences = count_sentences(text);
    return round(0.0588 * letters / words * 100 - 0.296 * sentences / words * 100 - 15.8);
}
