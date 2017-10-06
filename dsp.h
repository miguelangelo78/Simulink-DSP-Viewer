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

#define MAX_SIGNAL_COUNT 16

#define foreach(s, x, y) for(float * y = s.samples, x ## r = s.resolution, x = s.lower_bound / s.resolution; y <= s.samples; y++) for(int x ## n = 0; x ## n < s.sample_count; x ## n++, x += x ## r)
#define forrange(s, x, y, start, end) for(float * y = s.samples, x ## r = s.resolution, x = (start) / s.resolution; y <= s.samples; y++) for(int x ## n = (int)(start); x ## n < s.sample_count && x ## n < (end); x ## n++, x += x ## r)
#define var(s, y) float * y = s.samples;

typedef struct {
	int sample_count;
	float lower_bound;
	float upper_bound;
	float resolution;
	float * samples;
} signal_t;

struct {
	int signal_count;
	float max_lower_bound;
	float max_upper_bound;
	float max_resolution;
	signal_t * signals[MAX_SIGNAL_COUNT];
} signal_export_fmt = {
	0, 0.0f, 0.0f, 0.0f
};

#define export(s) _export(&s)

static char _export(signal_t * s) {
	if(signal_export_fmt.signal_count >= MAX_SIGNAL_COUNT)
		return 1;

	signal_export_fmt.signals[signal_export_fmt.signal_count] = s;
	signal_export_fmt.signal_count++;

	if(signal_export_fmt.max_lower_bound > s->lower_bound)
		signal_export_fmt.max_lower_bound = s->lower_bound;

	if(signal_export_fmt.max_upper_bound < s->upper_bound)
		signal_export_fmt.max_upper_bound = s->upper_bound;

	if(signal_export_fmt.max_resolution < s->resolution)
		signal_export_fmt.max_resolution = s->resolution;

	return 0;
}

void export_to_csv(char * csv_filename) {
	FILE * f = fopen(csv_filename, "w");
	char buff[(MAX_SIGNAL_COUNT * 128) + 3];

	for(float i = signal_export_fmt.max_lower_bound, i2 = 0; i <= signal_export_fmt.max_upper_bound; i += signal_export_fmt.max_resolution, i2++) {
		sprintf(buff, "%.10f", i);
		for(int j = 0; j < signal_export_fmt.signal_count; j++) {
			float sample;
			char floatStr[128];
			
			if(i2 < signal_export_fmt.signals[j]->sample_count)
				sample = signal_export_fmt.signals[j]->samples[(int)i2];
			else
				sample = 0.0f;

			sprintf(buff, "%s;%.4f", buff, sample);
		}
		fprintf(f, "%s\n", buff);
	}

	fclose(f);
}

void signalgroup_end() {
	for(int i = 0; i < signal_export_fmt.signal_count; i++)
		free(signal_export_fmt.signals[i]->samples);
	signal_export_fmt.signal_count = 0;
	signal_export_fmt.max_lower_bound = 0.0f;
	signal_export_fmt.max_upper_bound = 0.0f;
}

signal_t signal(float lower_bound, float upper_bound, float resolution) {
	signal_t ret;
	ret.sample_count = ((abs(lower_bound) + abs(upper_bound)) + 1) / resolution;
	ret.lower_bound = lower_bound;
	ret.upper_bound = upper_bound;
	ret.resolution = resolution;
	ret.samples = (float*)malloc(sizeof(float) * ret.sample_count);
	memset(ret.samples, 0, sizeof(float) * ret.sample_count);
	return ret;
}

/* Constants/Transformations */
#define pi M_PI
#define rad(degrees) ((degrees) * M_PI / 180)
#define deg(radians) ((radians) * 180 / M_PI)
#define sign(y) (((y) > 0) ? 1 : 0)

#endif
