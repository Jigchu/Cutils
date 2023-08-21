#include <stdio.h>

#include "colours/colours.h"

void colours_t(void)
{
    red();
    fprintf(stdout, "This is red text\n");
    green();
    fprintf(stdout, "This is green text\n");
    blue();
    fprintf(stdout, "This is blue text\n");
    reset();
    fprintf(stdout, "This is normal tex\n");
}