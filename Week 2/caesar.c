/*
Passes check50 cs50/problems/2024/x/caesar

Encrypt messages using Caesar’s cipher.
Take a command line argument for the key
Turn plaintext into ciphertext.
*/

#include <cs50.h>
#include <stdio.h> // printf()
#include <string.h> // strlen()
#include <ctype.h> //isdigit()
#include <stdlib.h> // atoi()

// Function Prototypes
bool only_digits(string s);
char rotate(char letter, int key);

int main(int argc, string argv[])
{
    // argc is program name + arguments. so arc == 2 is one argument
    // argv[1] is the first argument in the array of arguments, 0 is the program name
    if (argc == 2 && only_digits(argv[1]))
    {
        int key = 0;
        key = atoi(argv[1]);
        string userText = get_string("plaintext: ");
        string cipherText = userText;
        for (int i = 0, len = strlen(userText); i < len; i++)
        {
            cipherText[i] = rotate(userText[i], key);
        }
        printf("ciphertext: %s\n", cipherText);
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

char rotate(char letter, int key)
{
    if (isalpha(letter))
    {
        if (islower(letter))
        {
            return (letter - 'a' + key) % 26 + 'a';
        }
        else
        {
            return (letter - 'A' + key) % 26 + 'A';
        }
    }
    else
    {
        return letter; // if not alpha don't change the letter
    }
}

bool only_digits(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}
