/*
Replace every letter in plaintext using a substition cipher.

1. Get Key
2. Validate Key
    2a. Check Key Length
    2b. Check key is alphabetical
    2c. Check for repeated characters
3. Get plainText
4. Encipher
    4a.Preserve case
5. Print ciperText
*/

#include <cs50.h>
#include <stdio.h> //printf()
#include <string.h> //strlen()
#include <ctype.h> //isalpha(), isUpper()

// Function Prototypes
bool validKey(string key);
string enchipher(string plainText, string key);

int main(int argc, string argv[])
{
    if (argc == 2 && validKey(argv[1]))
    {
        string key = argv[1];
        string plainText = get_string("plaintext: ");
        string cipherText = plainText;
        printf("ciphertext: %s\n", enchipher(cipherText, key));
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

string enchipher(string plainText, string key)
{
    string cipherText = plainText;
    for (int i = 0, len = strlen(plainText); i < len; i++)
    {
        if (isalpha(plainText[i]))
        {
            if (isupper(plainText[i]))
            {
                cipherText[i] = toupper(key[plainText[i] - 'A']);
            }
            else
            {
                cipherText[i] = tolower(key[plainText[i] - 'a']);
            }
        }
    }
    return cipherText;
}

bool validKey(string key)
{
    int len = strlen(key);
    // 2a. Check Key Length
    if (len == 26)
    {
        for (int i = 0; i < len; i++)
        {
            // 2b. Check key is alphabetical
            if (!isalpha(key[i]))
            {
                return false;
            }
            // 2c. Check for repeated characters
            for (int k = i + 1; k < len; k++)
            {
                if (key[i] == key[k])
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}
