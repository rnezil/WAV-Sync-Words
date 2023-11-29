#include "wav44.h"

int main()
{
	// Open the file
	WAV_file f = fopen("/home/ryland/Downloads/FLEX_bits.wav","r");

	// Ensure file is readable
	if(f == NULL) return 1;

	// Get header data
	WAV_header h;
	unsigned char buffer[44];
	uint32_t tmp;
	if(44 != fread(buffer,1,44,f)) return 1;
	h.file_size = *(uint32_t*)&buffer[4];
	h.fmt_size = *(uint32_t*)&buffer[16];
	h.fmt_type = *(uint16_t*)&buffer[20];
	h.num_channels = *(uint16_t*)&buffer[22];
	h.sample_rate = *(uint32_t*)&buffer[24];
	h.audio_size = *(uint32_t*)&buffer[28];
	h.audio_type = *(uint16_t*)&buffer[32];
	h.bps = *(uint16_t*)&buffer[34];
	h.data_size = *(uint32_t*)&buffer[40];
	
	// Print header data
	printf("File Size: \t\t%uB\n", h.file_size);
	printf("Format Size: \t\t%uB\n", h.fmt_size);
	printf("Format Type: \t\t%u\n", h.fmt_type);
	printf("Number of Channels: \t%u\n", h.num_channels);
	printf("Sample Rate: \t\t%uHz\n", h.sample_rate);
	printf("Raw Audio Size: \t%uB\n", h.audio_size);
	printf("Audio Type: \t\t%u\n", h.audio_type);
	printf("Bits per Sample: \t%u\n", h.bps);
	printf("Formatted Audio Size: \t%uB\n", h.data_size);

	return 0;
}

