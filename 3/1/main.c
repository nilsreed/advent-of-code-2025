#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "./input.txt"
#define MAX_LINE_SIZE 128
#define ASCII_ZERO 48

void find_largest_digit(char *str, size_t len, int *max_digit, int *max_digit_index)
{
    *max_digit_index = -1;
    char current_max = ASCII_ZERO;
    for (size_t i = 0; i < len; i++)
    {
        if (str[i] > current_max)
        {
            current_max = str[i];
            *max_digit_index = (int)i;
        }
    }

    if (*max_digit_index != -1)
    {
        *max_digit = (int)(current_max - ASCII_ZERO);
    }
    else
    {
        *max_digit = -1;
    }
}

int find_maximum_joltage(char *battery_bank)
{
    int max_digit = -1;
    int max_joltage = 0;
    int max_index = -1;

    size_t battery_bank_size = strlen(battery_bank) - 1;

    find_largest_digit(battery_bank, battery_bank_size, &max_digit, &max_index);

    if (max_index == -1)
    {
        max_joltage = -1;
    }
    else
    {
        if (max_index == (battery_bank_size - 1))
        {
            max_joltage += max_digit;
            find_largest_digit(battery_bank, battery_bank_size - 1, &max_digit, &max_index);
            if (max_index == -1)
            {
                max_joltage = -1;
            }
            else
            {
                max_joltage += max_digit * 10;
            }
        }
        else
        {
            max_joltage += max_digit * 10;
            find_largest_digit(&battery_bank[max_index + 1], battery_bank_size - max_index - 1, &max_digit, &max_index);
            if (max_index == -1)
            {
                max_joltage = -1;
            }
            else
            {
                max_joltage += max_digit;
            }
        }
    }
    return max_joltage;
}

int main(void)
{
    int str_pos = 0;
    FILE *fp;
    char line[MAX_LINE_SIZE];
    int sum_of_max_joltages = 0;

    fp = fopen(INPUT_FILE, "r");
    if (fp == NULL)
    {
        printf("ERROR: unable to open file\n");
        return -1;
    }

    memset(line, 0, MAX_LINE_SIZE);
    while (fgets(line, sizeof(line), fp))
    {
        int max_joltage = find_maximum_joltage(line);
        if (max_joltage <= 0)
        {
            printf("ERROR zero or negative max joltage\n");
        }
        sum_of_max_joltages += max_joltage;

        memset(line, 0, MAX_LINE_SIZE);
    }

    printf("The sum of the maximum joltages is %d\n", sum_of_max_joltages);
    fclose(fp);

    return 0;
}