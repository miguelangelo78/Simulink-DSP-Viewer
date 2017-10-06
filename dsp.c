#include "dsp.h"

void DFT(char * csv_file) {
	signal_t s1 = signal(0, 360, 0.25);
	signal_t s2_re = signal(0, 360, 0.25);
	signal_t s2_im = signal(0, 360, 0.25);
	signal_t s2 = signal(0, 360, 0.25);
	
	/* Create sinewave */
	foreach(s1, x, y)	
		y[xn] = sin(rad(2 * pi * x)) + sin(rad(2 * pi * 2 * x)) + sin(rad(2 * pi * 4 * x));
	
	/* Perform DFT */
	foreach(s2_re, k, y_re) {
		var(s2_im, y_im);
		var(s2, y_spectrum);

		y_re[kn] = 0;
		y_im[kn] = 0;

		foreach(s1, x, y) {
			y_re[kn] += y[xn] * cos((pi / s1.sample_count) * x * (kn - (180 / kr)) * 2) / s1.sample_count;
			y_im[kn] += y[xn] * sin((pi / s1.sample_count) * x * (kn - (180 / kr)) * 2) / s1.sample_count;
		}

		y_spectrum[kn] = sqrt(pow(y_re[kn], 2) + pow(y_im[kn], 2));
	}

	export(s1);
	export(s2);

	export_to_csv(csv_file);
	signalgroup_end();
}

int main(int argc, char ** argv) {
	DFT(argv[1]);
	return 0;
}