#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 13
#define PRIME 7

typedef struct bucket
{
    int key;
    int isFull;
} bucket;

int hash(int key, int i)
{
    return (key % TABLE_SIZE + i * (PRIME - (key % PRIME))) % TABLE_SIZE;
}

void insert(bucket table[TABLE_SIZE], int key)
{
    int i = 0, bk_code;
    while (i < 1000 * TABLE_SIZE)
    {
        bk_code = hash(key, i);
        if (!table[bk_code].isFull)
        {
            table[bk_code].isFull = 1;
            table[bk_code].key = key;
            fprintf(stderr, "insert[%2d]=%d\ti=%d\n", bk_code, key, i);
            return;
        }
        else
            ++i;
    }
    fprintf(stderr, "Failed to insert %d i=%d !\n", key, i);
}

int main()
{
    int input_key;
    char c;
    bucket hash_table[TABLE_SIZE] = {};

    // Insert key into hash table
    while (scanf("%d%c", &input_key, &c) >= 1)
        insert(hash_table, input_key);

    // Print hash table
    for (int i = 0; i < TABLE_SIZE; ++i)
        if (hash_table[i].isFull)
            printf("%d->%d%s", i, hash_table[i].key, i == TABLE_SIZE - 1 ? "" : "\n");
    return 0;
}