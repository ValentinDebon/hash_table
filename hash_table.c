/*
	hash_table.c
	Copyright (c) 2019, Valentin Debon

	This file is part of the hash_table repository
	subject the BSD 3-Clause License, see LICENSE
*/
#include "hash_table.h"

#include <stdlib.h>

struct hash_table_bucket {
	struct hash_table_bucket *next;
	hash_table_value_t *value;
	hash_table_key_t key;
};

struct hash_table {
	uint64_t length;
	struct hash_table_bucket buckets[];
};

static struct hash_table_bucket *
hash_table_bucket_create(hash_table_key_t key,
	hash_table_value_t *value) {
	struct hash_table_bucket *bucket = malloc(sizeof(*bucket));

	bucket->next = NULL;
	bucket->value = value;
	bucket->key = key;

	return bucket;
}

static void
hash_table_bucket_destroy(struct hash_table_bucket *bucket) {

	if(bucket->next != NULL) {
		hash_table_bucket_destroy(bucket->next);
	}

	free(bucket);
}

struct hash_table *
hash_table_create(uint64_t length) {
	struct hash_table *table = NULL;

	if(length != 0
		&& (table = calloc(sizeof(*table) + sizeof(struct hash_table_bucket[length]), 1)) != NULL) {
		table->length = length;
	}

	return table;
}

void
hash_table_destroy(struct hash_table *table) {
	struct hash_table_bucket *bucket = table->buckets,
		* const end = table->buckets + table->length;

	while(bucket != end) {
		if(bucket->next != NULL) {
			hash_table_bucket_destroy(bucket->next);
		}
		++bucket;
	}

	free(table);
}

void
hash_table_insert(struct hash_table *table,
	hash_table_key_t key, hash_table_value_t *value) {
	struct hash_table_bucket *bucket = table->buckets + key % table->length;

	if(value != NULL) {
		if(bucket->value == NULL) {
			bucket->value = value;
			bucket->key = key;
		} else {
			while(bucket->key != key
				&& bucket->next != NULL) {
				bucket = bucket->next;
			}
	
			if(bucket->key == key) {
				bucket->value = value;
			} else {
				bucket->next = hash_table_bucket_create(key, value);
			}
		}
	}
}

void
hash_table_remove(struct hash_table *table,
	hash_table_key_t key) {
	struct hash_table_bucket *bucket = table->buckets + key % table->length;

	if(bucket->key == key) {
		if(bucket->next != NULL) {
			struct hash_table_bucket *next = bucket->next;
			*bucket = *next;
			next->next = NULL;
			hash_table_bucket_destroy(next);
		} else {
			bucket->value = NULL;
		}
	} else {
		struct hash_table_bucket *previous;

		while(bucket->key != key
			&& bucket->next != NULL) {
			previous = bucket;
			bucket = bucket->next;
		}

		if(bucket->key == key) {
			previous->next = bucket->next;
			bucket->next = NULL;
			hash_table_bucket_destroy(bucket);
		}
	}
}

hash_table_value_t *
hash_table_find(const struct hash_table *table,
	hash_table_key_t key) {
	const struct hash_table_bucket *bucket = table->buckets + key % table->length;
	hash_table_value_t *value;

	while(bucket->key != key
		&& bucket->next != NULL) {
		bucket = bucket->next;
	}

	if(bucket->key == key) {
		value = bucket->value;
	} else {
		value = NULL;
	}

	return value;
}

