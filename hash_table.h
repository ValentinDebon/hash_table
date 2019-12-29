#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef unsigned long hash_table_key_t;
typedef void hash_table_value_t;

struct hash_table *
hash_table_create(unsigned long sizepower, unsigned long bucketdefaultpower);

void
hash_table_destroy(struct hash_table *table);

hash_table_value_t *
hash_table_update(struct hash_table *table, hash_table_key_t key, hash_table_value_t *value);

hash_table_value_t *
hash_table_access(struct hash_table *table, hash_table_key_t key);

hash_table_value_t *
hash_table_remove(struct hash_table *table, hash_table_key_t key);

/* HASH_TABLE_H */
#endif
