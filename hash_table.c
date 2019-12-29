#include "hash_table.h"

#include <stdlib.h>

#define HASH_TABLE_BUCKETOF(table, key) ((table)->buckets + (((table)->size - 1) & (key)))

struct hash_table_pair {
	hash_table_value_t *value;
	hash_table_key_t key;
};

struct hash_table_bucket {
	unsigned long capacity;
	unsigned long count;
	struct hash_table_pair *pairs;
};

struct hash_table {
	unsigned long size;
	unsigned long bucketdefault;
	struct hash_table_bucket buckets[];
};

struct hash_table *
hash_table_create(unsigned long sizepower, unsigned long bucketdefaultpower) {
	const unsigned long size = 1 << sizepower;
	struct hash_table *table = calloc(1, sizeof(*table) + size * sizeof(*table->buckets));

	table->size = size;
	table->bucketdefault = 1 << bucketdefaultpower;

	return table;
}

void
hash_table_destroy(struct hash_table *table) {
	struct hash_table_bucket *current = table->buckets,
		* const end = table->buckets + table->size;

	while(current < end) {
		free(current->pairs);
		current++;
	}

	free(table);
}

hash_table_value_t *
hash_table_update(struct hash_table *table, hash_table_key_t key, hash_table_value_t *value) {
	struct hash_table_bucket * const bucket = HASH_TABLE_BUCKETOF(table, key);
	struct hash_table_pair *current = bucket->pairs,
		* const end = bucket->pairs + bucket->count;
	hash_table_value_t *updated;

	while(current < end && current->key != key) {
		current++;
	}

	if(current == end) {
		if(bucket->count == bucket->capacity) {
			bucket->capacity = bucket->capacity == 0 ? table->bucketdefault : (bucket->capacity << 1);
			bucket->pairs = realloc(bucket->pairs, bucket->capacity * sizeof(*bucket->pairs));
		}
		bucket->pairs[bucket->count] = (struct hash_table_pair) { .value = value, .key = key };
		bucket->count++;
		updated = NULL;
	} else {
		current->value = value;
		current->key = key;
		updated = current->value;
	}

	return updated;
}

hash_table_value_t *
hash_table_access(struct hash_table *table, hash_table_key_t key) {
	struct hash_table_bucket * const bucket = HASH_TABLE_BUCKETOF(table, key);
	struct hash_table_pair *current = bucket->pairs,
		* const end = bucket->pairs + bucket->count;

	while(current < end && current->key != key) {
		current++;
	}

	return current == end ? NULL : current->value;
}

hash_table_value_t *
hash_table_remove(struct hash_table *table, hash_table_key_t key) {
	struct hash_table_bucket * const bucket = HASH_TABLE_BUCKETOF(table, key);
	struct hash_table_pair *current = bucket->pairs,
		* const end = bucket->pairs + bucket->count;
	hash_table_value_t *removed;

	while(current < end && current->key != key) {
		current++;
	}

	if(current == end) {
		removed = NULL;
	} else {
		removed = current->value;
		*current = end[-1];
		bucket->count--;
	}

	return removed;
}

