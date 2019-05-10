#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>


int main(int argc, char* argv[]) {
	int exec_time, samples;
	int i;
	float dt;

	if (argc != 3) {
		printf("Incorect number of arguments.\n");
		printf("Please provide ONLY two arguments.\n");
		printf("First argument: sampling duration in seconds.\n");
		printf("Second argument: sampling interval in seconds.\n");
		exit(1);
	}
	exec_time = atoi(argv[1]);		// first argument is the execution time of the program in seconds
	dt = atof(argv[2]);		// second argument is the elapsed time between 2 samples in seconds

	samples = exec_time / dt + 1;
	printf("samples: %d\n", samples);

	struct timeval time;
	struct timeval *times = (struct timeval*)malloc(samples * sizeof(struct timeval));

	unsigned int sleep_tmr;
	sleep_tmr = dt * 1000000; // multiply times 1,000,000 to convert seconds to microseconds
	printf("sleep sec: %u\n", sleep_tmr);

	long time_offset = 0;
	gettimeofday(&time, NULL);
	times[0] = time;

	for (i = 1; i < samples; i++) {
		usleep(sleep_tmr);

		gettimeofday(&time, NULL);
		times[i] = time;

		time_offset = (times[i].tv_sec - times[i-1].tv_sec)*1000000
							  + times[i].tv_usec - times[i-1].tv_usec - dt*1000000;
		sleep_tmr -= time_offset;
	}

	printf("Time in microseconds: %lu usecs\n",
					((times[samples-1].tv_sec - times[0].tv_sec)*1000000L
	 				+ times[samples-1].tv_usec) - times[0].tv_usec);

	// Save results to file
	FILE *f = fopen("sampling_corrected.txt", "w");
	if (f == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	for (i = 0; i < samples; i++) {
		fprintf(f, "%d: timestamp: %ld   %ld  ", i, times[i].tv_sec, times[i].tv_usec);
		fprintf(f, "Time in microseconds: %ld usecs\n",
						times[i].tv_sec * 1000000 + times[i].tv_usec);
	}

	fclose(f);

	free(times);

	return 0;
}
