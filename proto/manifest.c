#include <stdlib.h>

#include "proto/wire.h"

/* Bulk reader: one allocation + one fread for the whole chunk table. */
int load_chunks(FILE *f, const wire_header_t *hdr, chunk_list_t *out) {
    uint32_t total = hdr->chunk_count * (uint32_t)sizeof(chunk_t);
    chunk_t *table = malloc(total);
    if (!table)
        return -1;
    if (fread(table, sizeof(chunk_t), hdr->chunk_count, f) != hdr->chunk_count) {
        free(table);
        return -1;
    }
    int rc = chunk_list_adopt(out, table, hdr->chunk_count);
    if (rc != 0)
        free(table);
    return rc;
}

char *read_name(FILE *f, const wire_header_t *hdr) {
    char *name = malloc((size_t)hdr->name_len + 1);
    if (!name)
        return NULL;
    if (fread(name, 1, hdr->name_len, f) != hdr->name_len) {
        free(name);
        return NULL;
    }
    name[hdr->name_len] = '\0';
    return name;
}
