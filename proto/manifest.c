#include <stdlib.h>

#include "proto/wire.h"

/* Streaming reader: one chunk at a time into a growable list. */
int load_chunks(FILE *f, const wire_header_t *hdr, chunk_list_t *out) {
    for (uint32_t i = 0; i < hdr->chunk_count; i++) {
        chunk_t c;
        if (fread(&c, sizeof(c), 1, f) != 1)
            return -1;
        if (chunk_list_append(out, &c) != 0)
            return -1;
    }
    return 0;
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
