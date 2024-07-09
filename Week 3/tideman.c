// Not currently passing Check50
// Solution by JemWritesCode

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool cycleCheck(pair currentPair);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        // after all of the voting (creating the ranks array for this voter), then we
        // are able to create the preferences array
        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}
// === FUNCTIONS TO IMPLEMENT ======================================================
// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // The point of this function is to create the ranks[] array for this voter.
    // 1. verify it's a valid candidate name
    // 2. add the name'd candidate of rank to ranks
    // 3. return true if success, false if invalid vote
    for (int i = 0; i < candidate_count; i++)
    {
        // if the name passed into the vote function matches a candidate in the candidates[] array
        if (strcmp(name, candidates[i]) == 0)
        {
            // exampe: Rank #2 would be set to the index that represents a candidate (ex: candidate 0 is alice)
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // this is actually used to go through ranks[], since every candidate gets ranked
    for (int i = 0; i < candidate_count; i++)
    {
        // we create a second pointer, k, to go through the rest of the array
        // so we can say everyone after candidates[i] is less preferred
        for (int k = i + 1; k < candidate_count; k++ )
        {
            // this variable is for readability
            int currentCandidateIndex = ranks[i];
            // they beat everyone else that comes in the ranks[] array after them so +1
            // the count to show they are preferred.
            preferences[currentCandidateIndex][k]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int k = i + 1; k < candidate_count; k++)
        {
            // with these if/elseif we don't record ties, they get skipped
            // [i][k] will be the same pair of candidates as [k][i].
            // ex Alice vs Bob and then Bob vs Alice. We're taking the higher number
            // because that means more people prefer that candidate over the other
            // hence we would have a winner and a loser between those two candidates
            // by checking these two places in the preferences array
            if (preferences[i][k] > preferences[k][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = k;
                pair_count++;
            }
            else if (preferences[i][k] < preferences[k][i])
            {
                pairs[pair_count].winner = k;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // I opted for Bubble Sort because it's simpler than Merge Sort.
    // If we are lucky and the pairs array is already sorted we also get Omega(n) which
    // will beat Selection Sort for speed.

    int swaps = 0;
    for (int i = 0; i < pair_count - 1; i++)
    {
        swaps = 0; //reset each time we're about to go through
        // after going through this with k once the highest will bubble to the top
        // but we have to go back to the outer loop to do it again and keep pushing the
        // next biggest to the top. as i increments we will end up ignoring
        // the final already sorted elements.
        for (int k = 0; k < pair_count - i - 1; k++)
        {

            int pairOneStrength = preferences[pairs[k].winner][pairs[k].loser];
            int pairTwoStrength = preferences[pairs[k + 1].winner][pairs[k + 1].loser];

            if (pairOneStrength > pairTwoStrength)
            {
                pair tempForSwap = pairs[k];
                pairs[k] = pairs[k+1];
                pairs[k + 1] = tempForSwap;
                swaps++;
            }
        }
        if (swaps == 0)
        {
            break; // no swaps means it's already sorted
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //locked an array of booleans. locked[j][k] would mean arrow pointing from j to k
    //at first everything in locked is set to false, this is done in main

    // so we need go go through the now sorted pairs[] array
    // if != createACycle then set that to true
    // how do i know if it makes a cycle

    // to know if it has a cycle. lets take a pair like d, a.
    // so a is the loser. we say is there any locked[a][?]?
    // if no, safe to lock
    // if yes, we need to follow the chain down. so who does a beat? we are once again checking
    // the loser. so there's the recursion right there.
    // either we go until there are no pairs where the loser of the pair has no other pairs in the locked
    // array that are already locked.
    // or we find our way back to the begining of the cycle, so we don't lock.


//=================
    // Go through all of pairs[] to see if each pair should be locked or not.
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycleCheck(pairs[i]))
        {
            // if it doesn't create a cycle we can lock it into the graph
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

bool cycleCheck(pair currentPair)
{
        // k is used to go through locked[loser][k]
        // to see if the loser beats anyone
    for (int k = 0; k < candidate_count; k++)
    {
        if (locked[currentPair.loser][k] == true)
        {
            // the loser beat someone else.
            // we need to go further down the chain before we know if it's safe to lock.
            // so same recursion again
            if(k == currentPair.winner)
            {
                // we have come full circle. this is a cycle.
                return true;
            }
            pair nextPair;
            nextPair.winner = currentPair.loser;
            nextPair.loser = k;
            cycleCheck(nextPair);

        }
        // if it's not true it's false so it will just go to the next loop of the for loop
    }
    // if we got through this whole loop without exiting it then ok to lock it in, there's no cycle
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // basically you go through the candidates and if every person that is pointing at them
    // is false then they are the source because no one beats them.
    // that's why you flip the [j][i]. we're checking who is pointing at our current i'th candidate
    // then we print candidates[i] if no one is pointing at them
 for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;
                if (false_count == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
}
