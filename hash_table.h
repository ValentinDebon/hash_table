/*
	hash_table.h
	Copyright (c) 2019, Valentin Debon

	This file is part of the hash_table repository
	subject the BSD 3-Clause License, see LICENSE
*/
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdint.h>

typedef void hash_table_value_t;
typedef uint64_t hash_table_key_t;

/**
 * Creates a new hash table.
 * @param length contiguous-first-buckets size != 0.
 * @return Valid hash table, NULL else.
 */
struct hash_table *
hash_table_create(uint64_t length);

/**
 * Destroys a previously hash_table_create()'d hash table.
 * Recursively destroys each inner-bucket.
 * @param table Hash table to destroy.
 */
void
hash_table_destroy(struct hash_table *table);

/**
 * Insert a new key-value pair, overwrite previous value if there was already one.
 * @param table Valid hash table.
 * @param key Key for which we insert or overwrite.
 * @param value Value to insert, non-NULL.
 */
void
hash_table_insert(struct hash_table *table,
	hash_table_key_t key, hash_table_value_t *value);

/**
 * Removes a key-value pair from the hash table.
 * @param table Valid hash table.
 * @param key Key associated to the couple to delete.
 */
void
hash_table_remove(struct hash_table *table,
	hash_table_key_t key);

/**
 * Find the value associated to the key.
 * @param table Valid hash table.
 * @param key Key associated to the couple to find.
 * @return The value associated, or NULL if it doesn't exist.
hash_table_value_t *
hash_table_find(const struct hash_table *table,
	hash_table_key_t key);

/* HASH_TABLE_H */
#endif
