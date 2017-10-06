#ifndef _DSP_H_
#define _DSP_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define STRSTR(x) #x
#define STR(x) STRSTR(x)

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define pi M_PI

#define rad(degrees) ((degrees) * M_PI / 180)
#define deg(radians) ((radians) * 180 / M_PI)

#define MAX_SIGNAL_COUNT 16

#define foreach(s, x, y) for(float *y = s.samples, x ## r = s.resolution, x = 0; y <= s.samples; y++) for(int x ## n = 0; x ## n < s.sample_count; x ## n++, x += x ## r)
#define var(s,y) float * y = s.samples;

typedef struct {
	int sample_count;
	float resolution;
	float * samples;
} signal_t;

struct {
	int signal_count;
	int max_sample_count;
	float max_resolution;
	signal_t * signals[MAX_SIGNAL_COUNT];
} signal_export_fmt = {
	0, 0, 0.0f
};

#define export(s) _export(&s)

static char _export(signal_t * s) {
	if(signal_export_fmt.signal_count >= MAX_SIGNAL_COUNT)
		return 1;

	signal_export_fmt.signals[signal_export_fmt.signal_count] = s;
	signal_export_fmt.signal_count++;
	if(signal_export_fmt.max_sample_count < s->sample_count)
		signal_export_fmt.max_sample_count = s->sample_count;

	if(signal_export_fmt.max_resolution < s->resolution)
		signal_export_fmt.max_resolution = s->resolution;

	return 0;
}

void export_to_csv(char * csv_filename) {
	FILE * f = fopen(csv_filename, "w");
	char buff[(MAX_SIGNAL_COUNT * 128) + 3];

	for(int i = 0; i < signal_export_fmt.max_sample_count; i++) {
		sprintf(buff, "%.10f", i * signal_export_fmt.max_resolution);
		for(int j = 0; j < signal_export_fmt.signal_count; j++) {
			float sample;
			char floatStr[128];
			
			if(i < signal_export_fmt.signals[j]->sample_count)
				sample = signal_export_fmt.signals[j]->samples[i];
			else
				sample = 0.0f;

			sprintf(buff, "%s;%.4f", buff, sample);
		}
		fprintf(f, "%s\n", buff);
	}

	fclose(f);
}

void cleanup_dsp() {
	for(int i = 0; i < signal_export_fmt.signal_count; i++)
		free(signal_export_fmt.signals[i]->samples);
}

signal_t signal(int sample_count, float resolution) {
	signal_t ret;
	ret.sample_count = (sample_count + 1) * (1 / resolution);
	ret.resolution = resolution;
	ret.samples = (float*)malloc(sizeof(float) * ret.sample_count);
	memset(ret.samples, 0, sizeof(float) * ret.sample_count);
	return ret;
}

#endif
