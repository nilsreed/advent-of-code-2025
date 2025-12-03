#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "./input.txt"
#define MAX_LINE_SIZE 16
#define MAX_CLICKS 100
#define STARTING_POS 50
#define ASCII_ZERO 48
#define ASCII_NINE ASCII_ZERO + 9

typedef enum dir {
    LEFT,
    RIGHT,
    INVAL_DIR
} dir_t;

int rotate(dir_t direction, int current_pos, int clicks)
{
    int new_pos = 0;

    if (clicks >= 0)
        {
        if (direction == LEFT)
        {
            if (current_pos > clicks)
            {
                new_pos = current_pos - clicks;
            }
            else{
                new_pos = MAX_CLICKS + ((current_pos - clicks) % MAX_CLICKS);
            }        
        }
        else if (direction == RIGHT)
        {
            new_pos = (current_pos + clicks) % MAX_CLICKS;
        }
        else {
            new_pos = -1;
        }
    }
    else
    {
        new_pos = -1;
    }

    return new_pos;
}

dir_t decode_direction(char d)
{
    if (d == 'R' || d == 'r')
    {
        return RIGHT;
    }
    else if (d == 'L' || d == 'l')
    {
        return LEFT;
    }
    return INVAL_DIR;
}

int decode_clicks(char* clicks_str)
{
    int num_clicks = -1;
    char* tmp_str = strdup(clicks_str);
    for(int i = 0; i < strlen(clicks_str); i++)
    {
        if(clicks_str[i] < ASCII_ZERO || clicks_str[i] > ASCII_NINE)
        {
            tmp_str[i] = '\0';
        }
    }

    num_clicks = atoi(tmp_str);
    free(tmp_str);

    return num_clicks;
}


int main(void)
{
    FILE *fp;
    char line[MAX_LINE_SIZE];
    dir_t dir = INVAL_DIR;
    int clicks = -1;
    int position = STARTING_POS;
    int num_zeroes = 0;
    int iteration = 0;

    fp = fopen(INPUT_FILE, "r");
    if (fp == NULL)
    {
        printf("ERROR: unable to open file\n");
        return -1;
    }

    while (fgets(line, sizeof(line), fp))
    {
        iteration++;
        dir = decode_direction(line[0]);
        clicks = decode_clicks(&line[1]);
        position = rotate(dir, position, clicks);
//        printf("dir: %d, clicks: %d it: %d c_p: %d\n", dir, clicks, iteration, position);

        if (position == 0)
        {
            num_zeroes++;
        }
//        else if (position < 0)
//        {
//            printf("ERROR: negative position during iteration %d!\n", iteration);
//        }

//        if (iteration > 10)
//        {
//            break;
//        }
    }

    printf("Num lines: %d\n", iteration);
    printf("The code is %d\n", num_zeroes);

    fclose(fp);

    return 0;
}