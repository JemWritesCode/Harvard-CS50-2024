//passes check50 cs50/problems/2024/x/cash
// passes style50 cash.c
#include <cs50.h>
#include <stdio.h>

// Function Prototypes
int get_cents(void);
int calculate_coin(int cents, int coinValue);

int main(void)
{
    int cents = get_cents();
    int quarters = calculate_coin(cents, 25);
    cents = cents - (quarters * 25);
    int dimes = calculate_coin(cents, 10);
    cents = cents - (dimes * 10);
    int nickles = calculate_coin(cents, 5);
    cents = cents - (nickles * 5);
    int pennies = calculate_coin(cents, 1);
    cents = cents - (pennies);
    printf("%i\n", quarters + dimes + nickles + pennies);
}

int calculate_coin(int cents, int coinValue)
{
    int coins = 0;
    while (cents >= coinValue)
    {
        coins++;
        cents = cents - coinValue;
    }
    return coins;
}

int get_cents(void)
{
    int change;
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 1);
    return change;
}
