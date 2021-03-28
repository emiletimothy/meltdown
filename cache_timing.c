#include "cache_timing.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

const size_t REPEATS = 100000;

int main() {
    uint64_t sum_miss = 0;
    uint64_t sum_hit = 0;

    for (size_t i = 0; i < REPEATS; i++) {
        page_t *pages = calloc(UINT8_MAX + 1, PAGE_SIZE);
        assert(pages != NULL);
        flush_cache_line(pages);

        // Times the read-times for the pages (first is a miss, second is a hit)
        uint64_t first_time = time_read(pages);
        uint64_t second_time = time_read(pages);

        // Updates the sum_miss and sum_hit to find the averages later.
        if (second_time <= first_time) {
            sum_miss += first_time;
            sum_hit += second_time;
        }
    }

    printf("average miss = %" PRIu64 "\n", sum_miss / REPEATS);
    printf("average hit  = %" PRIu64 "\n", sum_hit / REPEATS);
}
