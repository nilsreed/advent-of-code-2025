#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_FILE "./example_input.txt"
#define INPUT_LINE_SIZE_MAX 1024
#define TMP_BUF_SIZE_MAX 16


typedef struct range
{
    int min;
    int min_trunk;
    int max;
    int max_trunk;
} range_t;

typedef enum find_mode
{
    FIND_MIN,
    FIND_MAX
} find_mode_t;

int count_commas(char* line)
{
    int commas = 0;
    for (size_t i = 0; i < strlen(line); i++)
    {
        if (line[i] == ',')
        {
            commas++;
        }
    }
    return commas;
}

void decode_ranges(char* line, int no_ranges, range_t* ranges)
{
    char tmp_line_buf[TMP_BUF_SIZE_MAX];
    int digits = 0;

    memset(tmp_line_buf, 0, TMP_BUF_SIZE_MAX);
    find_mode_t mode = FIND_MIN;
    int range_no = 0;

    for(size_t i = 0; i < strlen(line) + 1; i++)
    {
        if (mode == FIND_MIN)
        {
            if(line[i] != '-')
            {
                tmp_line_buf[digits] = line[i];
                digits++;
            }
            else
            {
                tmp_line_buf[digits + 1] = '\0';
                ranges[range_no].min = atoi(tmp_line_buf);

                if (digits % 2 == 1)
                {
                    ranges[range_no].min_trunk = (int)pow(10.0, (double)(digits));
                }
                else
                {
                    ranges[range_no].min_trunk = ranges[range_no].min;
                }
                mode = FIND_MAX;
                digits = 0;
                memset(tmp_line_buf, 0, TMP_BUF_SIZE_MAX);

            }
        }
        else // mode == FIND_MAX
        {
            if((line[i] != ',') && (line[i] != '\0'))
            {
                tmp_line_buf[digits] = line[i];
                digits++;
            }
            else
            {
                tmp_line_buf[digits + 1] = '\0';
                ranges[range_no].max = atoi(tmp_line_buf);

                if (digits % 2 == 1)
                {
                    ranges[range_no].max_trunk = (int)pow(10.0,(double)(digits - 1)) - 1;
                }
                else
                {
                    ranges[range_no].max_trunk = ranges[range_no].max;
                }
                mode = FIND_MIN;
                digits = 0;
                memset(tmp_line_buf, 0, TMP_BUF_SIZE_MAX);
                range_no++;
            }
        }
    }
}

int find_invalid_ids(range_t id_range)
{
    int no_invalid_ids = 0;
    if (id_range.min_trunk <= id_range.max_trunk)
    {
        // Convert both max and min to char*
        // Check if its even possible to get errors with those strings - HOW?
        // If not break
        // Else change only one digit at a time?
        // Maybe be smart and see if it even can be possible to make inval id?
    }
    return no_invalid_ids;
}

int main(void)
{
    FILE* fp;
    range_t* ranges = NULL;
    char input_line[INPUT_LINE_SIZE_MAX];
    int sum_of_invalid_ids = 0;

    fp = fopen(INPUT_FILE, "r");
    if (fp == NULL)
    {
        printf("ERROR: unable to open file\n");
        return -1;
    }

    if (!fgets(input_line, sizeof(input_line), fp))
    {
        printf("ERROR: unable to read line\n");
        fclose(fp);
        return -2;
    }

    int no_ranges = count_commas(input_line) + 1;
    ranges = malloc(no_ranges*sizeof(range_t));

    if (ranges == NULL)
    {
        printf("ERROR: unable to allocate memory\n");
        fclose(fp);
        return -3;
    }

    decode_ranges(input_line, no_ranges, ranges);

    for (int i = 0; i < no_ranges; i++)
    {
//        sum_of_invalid_ids += find_invalid_ids(ranges[i]);
        printf("range_no: %2d min: %10d, max %10d, min_trunk: %10d, max_trunk %10d\n", i, ranges[i].min, ranges[i].max, ranges[i].min_trunk, ranges[i].max_trunk);
    }

    printf("The sum of the invalid ids is: %d\n", sum_of_invalid_ids);
    free(ranges);
    fclose(fp);

    return 0;
}
