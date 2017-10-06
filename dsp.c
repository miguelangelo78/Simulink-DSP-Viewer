#include "dsp.h"

int main(int argc, char ** argv) {
	signal_t s1 = signal(360, 0.1);
	signal_t s2 = signal(360, 0.1);
	signal_t s3 = signal(360, 0.1);

	foreach(s1, x, y) {
		var(s2, y2);
		var(s3, y3);

		y[x] = !x ? 1 : x % 2 ? -1 : 1;

		y2[x] = sin(rad(xr));

		if(xr < 180)
			y3[x] = exp(rad(180-xr));
		else
			y3[x] = exp(rad(xr-180));
	}

	export(s1);
	export(s2);
	export(s3);

	export_to_csv("signal_samples.csv");
	cleanup_dsp();
	return 0;
}