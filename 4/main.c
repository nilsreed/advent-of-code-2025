#include <stdio.h>
#include <string.h>


#define INPUT_FILE "./input.txt"
#define MAX_ROW_LEN 256
#define MAX_ROWS 256

int count_accessible_stacks(char* prev_row, char* current_row, char* next_row, int row_len)
{
    int num_accessible_stacks = -1;

    for (int i = 0; i < row_len; i++)
    {
        if(prev_row != NULL)
        {

        }

        if(next_row != NULL)
        {

        }
    }


    return num_accessible_stacks;
}

int main(void)
{
    FILE* fp;
    char line[MAX_ROW_LEN];

    fp = fopen(INPUT_FILE, "r");
    if (fp == NULL)
    {
        printf("ERROR: unable to open file\n");
        return -1;
    }

    char** rows = (char**)malloc(MAX_ROWS*sizeof(char*));

    if (rows == NULL)
    {
        printf("ERROR: Unable to allocate buffer for rows!\n");
        fclose(fp);
        return -2;
    }

    rows[0] = NULL;
    int index = 1;
    int initialised = 1;
    while (fgets(line, sizeof(line), fp))
    {
        size_t line_len = strnlen(line, MAX_ROW_LEN);
        if (line[line_len - 1] == '\n')
        {
            line[line_len - 1] = '\0';
        }

        rows[index] = strndup(line, MAX_ROW_LEN);
        if (rows[index] == NULL)
        {
            printf("ERROR: unable to allocate buffer for single row!\n");
            initialised = -1;
            break;
        }
        index++;
    }
    rows[index] = NULL;
    

    int total_accesible_stacks = 0;
    if (initialised == 1)
    {
        int current_index = 1;
        while (rows[current_index] != NULL)
        {
            int accessible_stacks = count_accessible_stacks(rows[current_index - 1], rows[current_index], rows[current_index + 1], ROW LENGTH);
            accessible_stacks += total_accesible_stacks;
        }
    }

    printf("Number of accessible stacks: %d\n", total_accesible_stacks);
    

    for (int i = 1; i < index - 1; i++)
    {
        if (rows[i] != NULL)
        {
            free(rows[i]);
        }
    }

    fclose(fp);

    return 0;
}