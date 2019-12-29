#include "hash_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main(int argc, char **argv) {
	if(argc != 4) {
		fprintf(stderr, "usage: %s <count> <size power> <bucket default power>\n", *argv);
		return 1;
	}

	const unsigned long size = strtoul(argv[1], NULL, 10);
	struct hash_table *table = hash_table_create(strtoul(argv[2], NULL, 10), strtoul(argv[3], NULL, 10));
	struct timespec updates, accesses, removals;

	for(unsigned long i = 0; i < size; i++) {
		hash_table_update(table, i, NULL);
	}

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &updates);

	for(unsigned long i = 0; i < size; i++) {
		hash_table_access(table, i);
	}

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &accesses);

	for(unsigned long i = 0; i < size; i++) {
		hash_table_remove(table, i);
	}

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &removals);

	hash_table_destroy(table);

	printf("updates:  %lu.%.9lu\naccesses: %lu.%.9lu\nremovals: %lu.%.9lu\n",
		updates.tv_sec, updates.tv_nsec,
		accesses.tv_sec, accesses.tv_nsec,
		removals.tv_sec, removals.tv_nsec);

	return 0;
}

