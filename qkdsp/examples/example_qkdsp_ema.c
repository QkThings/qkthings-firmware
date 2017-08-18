#include <stdio.h>
#include "qk_dsp.h"

#define SAMPLES     20
#define EMA_ALPHA   3670    //  = 0.112 * 2^15

int main()
{
    puts("-------------------------------------------------");
    puts(" QkDSP Example: Exponential Moving Average (EMA)");
    puts("-------------------------------------------------");

    uint32_t i;
    int16_t in[SAMPLES] = {900,500,900,900,800,600,800,700,300,600,900,0,300,700,500,300,800,700,600,200};
    int16_t out[SAMPLES];

    puts("Input samples:");
    for(i = 0; i < SAMPLES; i++)
        printf("in[%2d]= %d\n", i, in[i]);

    qk_avg_ema ema;
    qk_avg_ema_setup(&ema, EMA_ALPHA);
    qk_avg_ema_init(&ema, 0);

    for(i = 0; i < SAMPLES; i++)
    {
        out[i] = qk_avg_ema_filter(&ema, in[i]);
        printf("out[%2d]= %d\n", i, out[i]);
    }

    puts("Done");
    return 0;
}
