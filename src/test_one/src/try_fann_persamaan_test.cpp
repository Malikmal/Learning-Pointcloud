#include <stdio.h>
#include "floatfann.h"

int main()
{
    fann_type *calc_out;
    fann_type input[2];

    struct fann *ann = fann_create_from_file("testPersamaan.net");

    input[0] = 5;
    // input[1] = 4;
    calc_out = fann_run(ann, input);

    printf("xor test (%f) -> %f\n", input[0], calc_out[0]);

    fann_destroy(ann);
    return 0;
}