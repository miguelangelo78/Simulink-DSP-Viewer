#include "dsp.h"

int main(int argc, char ** argv) {
	signal_t s1 = signal(360, 0.1);
	signal_t s2 = signal(360, 0.1);
	signal_t s3 = signal(360, 0.1);

	foreach(s1, x, y) {
		var(s2, y2);
		var(s3, y3);

		y[xn] = !xn ? 1 : xn % 2 ? -1 : 1;

		y2[xn] = sin(rad(3*x));

		if(x < 180)
			y3[xn] = exp(rad(180-x));
		else
			y3[xn] = exp(rad(x-180));
	}

	export(s1);
	export(s2);
	export(s3);

	export_to_csv("signal_samples.csv");
	cleanup_dsp();
	return 0;
}