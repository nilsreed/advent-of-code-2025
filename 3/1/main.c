#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "./input.txt"
#define MAX_LINE_SIZE 128
#define ASCII_ZERO 48
#define NO_DIGITS 2

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

long long int find_maximum_joltage(char *battery_bank, size_t battery_bank_size)
{
    int max_digit = -1;
    long long int max_joltage = 0;
    int max_index = -1;
    int offset = 0;
    int effective_length = battery_bank_size - (size_t)(NO_DIGITS - 1);

    for (int i = 0; i < NO_DIGITS; i++)
    {
        find_largest_digit(&battery_bank[offset], effective_length, &max_digit, &max_index);
        max_joltage += (long long int)max_digit * ((long long int)(pow(10.0, (double)(NO_DIGITS - (i + 1)))));
        offset += max_index + 1;
        effective_length = battery_bank_size - (size_t)(offset - 1) - (size_t)(NO_DIGITS - 1 - i);
    }

    return max_joltage;
}

int main(void)
{
    int str_pos = 0;
    FILE *fp;
    char line[MAX_LINE_SIZE];
    long long int sum_of_max_joltages = 0;

    fp = fopen(INPUT_FILE, "r");
    if (fp == NULL)
    {
        printf("ERROR: unable to open file\n");
        return -1;
    }

    memset(line, 0, MAX_LINE_SIZE);
    while (fgets(line, sizeof(line), fp))
    {
        size_t line_len = strlen(line);
        if (line[line_len - 1] == '\n')
        {
            line[line_len - 1] = '\0';
            line_len--;
        }

        long long int max_joltage = find_maximum_joltage(line, line_len);
        if (max_joltage <= 0)
        {
            printf("ERROR zero or negative max joltage\n");
        }
        sum_of_max_joltages += max_joltage;

        memset(line, 0, MAX_LINE_SIZE);
    }

    printf("The sum of the maximum joltages is %lld\n", sum_of_max_joltages);
    fclose(fp);

    return 0;
}