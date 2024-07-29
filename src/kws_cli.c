#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <signal.h>
#include <string.h>

#include "fbank.h"

#define CHUNK_SIZE (SAMPLE_LEN / 2)

static volatile bool byebye = false;

static void INThandler(int sig)
{
    byebye = true;
}

int main(int argc, char *argv[])
{
    int16_t in[CHUNK_SIZE] = {0.0};
    float input[SAMPLE_LEN] = {0.0};
    float fbins[NUM_FRAMES][NUM_FILT];
    size_t n = 0;
    size_t label;
    float logit;
    bool debounce_active = false;

    struct sigaction sa = {.sa_handler = INThandler, .sa_flags = 0};
    sigaction(SIGINT, &sa, 0);

    fprintf(stderr, "\nStarting...\n");

    while (!byebye)
    {
        size_t m = fread(&in[n], sizeof(int16_t), CHUNK_SIZE - n, stdin);
        n += m;

        if (m == 0)
        {
            break;
        }

        if (n == CHUNK_SIZE)
        {
            if (CHUNK_SIZE < SAMPLE_LEN)
            {
                memmove(input, &input[CHUNK_SIZE], (SAMPLE_LEN - CHUNK_SIZE) * sizeof(float));
            }

            for (size_t i = 0; i < CHUNK_SIZE; i++)
            {
                input[SAMPLE_LEN - CHUNK_SIZE + i] = in[i];
            }

            fbank(input, fbins);
            fbank_speech_detect(fbins, &label, &logit);
            if (debounce_active)
            {
                if (label == 0)
                {
                    debounce_active = false;
                }
            }
            else
            {
                if (label > 0)
                {
                    fprintf(stderr, "label: '%s', label_idx: %ld, logit: %f\n", fbank_label_idx_to_str(label), label, logit);
                    fflush(stderr);
                    debounce_active = true;
                }
            }
            n = 0;
        }
    }
}
