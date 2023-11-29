#include "wav44.h"

int main(int argc, char** argv)
{
	// Define the syncword
	uint32_t syncword = 0b10100110110001101010101010101010;

	// Open the file
	WAV_file f = fopen("/home/ryland/Downloads/FLEX_bits.wav","r");

	// Ensure file is readable
	if(f == NULL) return 1;

	// Get header data
	WAV_header h;
	char buffer[44];
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
	printf("File size:\t\t\t%uB\n", h.file_size);
	printf("Format size:\t\t\t%uB\n", h.fmt_size);
	printf("Format type:\t\t\t%u\n", h.fmt_type);
	printf("Number of channels:\t\t%u\n", h.num_channels);
	printf("Sample rate:\t\t\t%uHz\n", h.sample_rate);
	printf("Raw audio size:\t\t\t%uB\n", h.audio_size);
	printf("Audio type:\t\t\t%u\n", h.audio_type);
	printf("Bits per sample:\t\t%u\n", h.bps);
	printf("Formatted sudio size:\t\t%uB\n", h.data_size);

	// Find syncwords and compute time between elapsed
	// between them
	unsigned interval_duration = 0;
	float interval_average = 0;
	unsigned syncword_count = 0;
	uint32_t sample;
	while(fread(&sample,2,1,f))
	{
		if(sample & syncword == syncword)
		{
			syncword_count++;
			if(interval_average)
			{
				interval_average += interval_average;
				interval_average /= 2;
			}
			else
			{
				interval_average = interval_duration;
			}
			interval_duration = 0;
		}
		else
		{
			interval_duration++;
		}
	}

	// Close file and print findings
	printf("Number of syncwords found:\t%u\n", syncword_count);
	printf("Time elapsed between syncwords:\t%1.6fms\n", interval_average/(((float)h.sample_rate)/1000));
	return(fclose(f));
}

