#include <stdio.h>
#include "pico/stdlib.h"

#define MINIMP3_IMPLEMENTATION
#include "minimp3.h"

extern const uint8_t mp3_data_start[];
extern const uint8_t mp3_data_end[];

int main() {
    stdio_init_all();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    uint32_t mp3_size = mp3_data_end - mp3_data_start;

    static mp3dec_t mp3d = {0}; // mp3 decoder
    mp3dec_frame_info_t mp3_info = {0};

    short pcm_buffer[MINIMP3_MAX_SAMPLES_PER_FRAME];
    int bytes_left = mp3_size;
    const uint8_t *curr_data = mp3_data_start;

    int samples = mp3dec_decode_frame(&mp3d, curr_data, bytes_left, pcm_buffer, &mp3_info);

    while (true) {
        printf("MP3 size: %i\n", mp3_size);
        if (samples > 0) {
            printf("Sample Rate: %i Hz\n", mp3_info.hz);
            printf("Channels: %i\n", mp3_info.channels);
            printf("Bitrate: %i kbps\n", mp3_info.bitrate_kbps);
        } else {
            printf("Failed to decode the MP3\n");
        }

        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(250);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(250);
    }
}
