#ifndef AIRDAC_FIRMWARE_AUDIO_COMMON_H
#define AIRDAC_FIRMWARE_AUDIO_COMMON_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define STOP_DECODER                    BIT0
#define CONTINUE_DECODER                BIT1
#define RUN_DECODER                     BIT2
#define PAUSE_DECODER                  BIT3
#define RESUME_DECODER                 BIT4

struct AudioContext {
    size_t (*fill_buffer)(uint8_t* encoded_buffer, size_t buff_len);
    bool (*write)(const int32_t* left_samples, const int32_t* right_samples, size_t sample_length, unsigned int sample_rate, unsigned int bit_depth);
    void (*decoder_failed)(void);
    void (*decoder_finished)(void);
    size_t (*bytes_elapsed)(void);
    size_t (*total_bytes)(void);
    bool (*eof)(void);
};
typedef struct AudioContext AudioContext_t;

struct DecoderWrapper {
    void (*init)(void);
    void (*run)(const AudioContext_t* ctx);
    void (*delete)(void);
};
typedef struct DecoderWrapper DecoderWrapper_t;

#endif //AIRDAC_FIRMWARE_AUDIO_COMMON_H
