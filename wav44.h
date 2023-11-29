#include <stdint.h>
#include <stdio.h>

typedef FILE* WAV_file;

typedef struct{
	uint32_t file_size;
	uint32_t fmt_size;
	uint16_t fmt_type;
	uint16_t num_channels;
	uint32_t sample_rate;
	uint32_t audio_size;
	uint16_t audio_type;
	uint16_t bps;
	uint32_t data_size;
}WAV_header;

