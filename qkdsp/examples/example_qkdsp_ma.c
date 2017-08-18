#include <stdio.h>
#include "qk_dsp.h"

#define SAMPLES         20
#define MA_WINDOW_SIZE  8   // Should be a power of 2, for efficiency purposes
#define MA_INIT_VALUE   0

int main()
{
    puts("-------------------------------------------------");
    puts(" QkDSP Example: Moving Average (MA)");
    puts("-------------------------------------------------");


    uint32_t i;
    int16_t in[SAMPLES] = {900,500,900,900,800,600,800,700,300,600,900,0,300,700,500,300,800,700,600,200};
    int16_t out[SAMPLES];

    // NOTE to RECURSIVE mode:
    // Input values divided by window size should always result in an integer value.
    // Otherwise (severe) truncature errors occur. You may test it with the following samples:
    //int16_t in[SAMPLES] = {9,5,9,9,8,6,8,7,3,6,9,0,3,7,5,3,8,7,6,2};

    puts("Input samples:");
    for(i = 0; i < SAMPLES; i++)
        printf("in[%2d]= %d\n", i, in[i]);

    int16_t ma_window[MA_WINDOW_SIZE];
    qk_avg_ma ma;
    qk_avg_ma_setup(&ma, ma_window, MA_WINDOW_SIZE);

    puts(" -- non-recursive mode");
    qk_avg_ma_init(&ma, MA_INIT_VALUE);
    qk_avg_ma_set_mode(&ma, QK_AVG_MA_MODE_NONRECURSIVE);

    for(i = 0; i < SAMPLES; i++)
    {
        out[i] = qk_avg_ma_filter(&ma, in[i]);
        printf("out[%2d]= %d\n", i, out[i]);
    }

    puts(" -- recursive mode");
    qk_avg_ma_init(&ma, 0);
    qk_avg_ma_set_mode(&ma, QK_AVG_MA_MODE_RECURSIVE);

    for(i = 0; i < SAMPLES; i++)
    {
        out[i] = qk_avg_ma_filter(&ma, in[i]);
        printf("out[%2d]= %d\n", i, out[i]);
    }

    puts("Done");
    return 0;
}
