#include <errno.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rfi.h"

static int get_one(char *s) {
	int i;
	struct rfi r;
	i = rfi_get_one(s, &r);
	if(i != 0) {
		return i;
	}
	printf("%s: %s\n", r.name, r.value);
	rfi_destroy_one(&r);
	return 0;
}

static int get_all(void) {
	int i;
	struct rfi *a[RFIBUILTINLEN];
	i = rfi_get_all(a);
	if(i != 0) {
		return i;
	}
	for(i = 0; a[i] != NULL; i++) {
		printf("%s: %s\n", a[i]->name, a[i]->value);
	}
	rfi_destroy_all(a);
	return 0;
}

void usage(void) {
	fprintf(stderr, "usage: rfi [options] [NAME]\n"
			"\n"
			"Options:\n"
			"\t-a, --all    gather all info\n"
			"\t-h, --help   display this message\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
	int i;
	if(argc <= 1) {
		if((i = get_all()) != 0) {
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}

	static struct option lopts[] = {
		{"all", no_argument, NULL, 'a'},
		{"help", no_argument, NULL, 'h'},
		{NULL, 0, NULL, '\0'}
	};

	while((i = getopt_long(argc, argv, "ah", lopts, NULL)) != -1) {
		switch(i) {
			case 'a':
				break;
			case 'h':
			default:
				usage();
		}
	}

        if((i = get_one(argv[optind])) != 0) {
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
