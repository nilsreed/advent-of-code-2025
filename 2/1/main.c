#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_FILE "./input.txt"
#define INPUT_LINE_SIZE_MAX 1024
#define TMP_BUF_SIZE_MAX 16
#define ASCII_ZERO 48
#define ASCII_NINE ASCII_ZERO + 9


typedef struct range
{
    long long int min;
    long long int min_trunk;
    long long int max;
    long long int max_trunk;
    int digits;
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
                ranges[range_no].min = atoll(tmp_line_buf);

                if (digits % 2 == 1)
                {
                    ranges[range_no].min_trunk = (long long)pow(10.0, (double)(digits));
                    ranges[range_no].digits = digits + 1;
                }
                else
                {
                    ranges[range_no].min_trunk = ranges[range_no].min;
                    ranges[range_no].digits = digits;
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
                ranges[range_no].max = atoll(tmp_line_buf);

                if (digits % 2 == 1)
                {
                    ranges[range_no].max_trunk = (long long int)pow(10.0,(double)(digits - 1)) - 1;
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

void find_invalid_ids(range_t id_range, long long int** inval_ids, int* no_inval_ids)
{
    *no_inval_ids = 0;
    if (((id_range.digits % 2) == 0) && id_range.min_trunk <= id_range.max_trunk)
    {
        char *min;
        min = calloc(id_range.digits + 1, sizeof(char));
        if (min == NULL)
        {
            printf("ERROR: unable to allocate char buffer for min");
            *no_inval_ids = -1;
            return;
        }

        snprintf(min, id_range.digits + 1, "%lld", id_range.min_trunk);

        long long int current = id_range.min_trunk;
        // BRUTE FORCE BABYY
        while (current <= id_range.max_trunk)
        {
            if (memcmp(min, &min[id_range.digits / 2], id_range.digits / 2) == 0)
            {
                (*no_inval_ids)++;
                long long int* tmp_inval_ids = realloc(*inval_ids, (*no_inval_ids)*sizeof(long long int));
                if (tmp_inval_ids == NULL)
                {
                    if (*no_inval_ids > 0)
                    {
                        free(*inval_ids);
                        *no_inval_ids = -1;
                    }
                    break;
                }

                *inval_ids = tmp_inval_ids;
                (*inval_ids)[*no_inval_ids - 1] = current;
            }

            for (int i = id_range.digits - 1; i >= 0; i--)
            {
                if (min[i] == ASCII_NINE)
                {
                    min[i] = ASCII_ZERO;
                }
                else
                {
                    min[i]++;
                    break;
                }
            }
            current++;
        }
        free(min);
    }
    return;
}

int main(void)
{
    FILE* fp;
    range_t* ranges = NULL;
    char input_line[INPUT_LINE_SIZE_MAX];
    long long int sum_of_invalid_ids = 0;

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

    long long int* invalid_ids = NULL;
    int no_invalid_ids = 0;

    for (int i = 0; i < no_ranges; i++)
    {
        find_invalid_ids(ranges[i], &invalid_ids, &no_invalid_ids);
        if (no_invalid_ids > 0)
        {
            printf("%2d Invalid IDs in range %d-%d (trunk: %d-%d) (digits: %d): ", no_invalid_ids, ranges[i].min, ranges[i].max, ranges[i].min_trunk, ranges[i].max_trunk, ranges[i].digits);
            for (int j = 0; j < no_invalid_ids - 1; j++)
            {
                printf("%d, ", invalid_ids[j]);
            }
            printf("%d\n", invalid_ids[no_invalid_ids - 1]);


            for (int j = 0; j < no_invalid_ids; j++)
            {
                sum_of_invalid_ids += invalid_ids[j];
            }

            free(invalid_ids);
            invalid_ids = NULL;
        }
        else if (no_invalid_ids == -1)
        {
            printf("ERROR: find_invalid_ids returned -1!\n");
        }
        else if (no_invalid_ids == 0)
        {
            printf("No invalid IDs in range %d-%d (trunk: %d-%d) (digits: %d)\n", ranges[i].min, ranges[i].max, ranges[i].min_trunk, ranges[i].max_trunk, ranges[i].digits);
        }
    }

    printf("The sum of the invalid ids is: %lld\n", sum_of_invalid_ids);
    free(ranges);
    fclose(fp);

    return 0;
}
