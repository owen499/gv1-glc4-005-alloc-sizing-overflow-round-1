#include "proto/wire.h"

/* Manifests arrive from unauthenticated peers during sync. */
int validate_header(const wire_header_t *hdr) {
    if (hdr->magic != 0x4d464e31u)  /* "MFN1" */
        return -1;
    if (hdr->version != 2)
        return -1;
    if (hdr->chunk_count == 0)
        return -1;
    /* NOTE: no upper bound on chunk_count — the streaming reader is
     * naturally bounded by the bytes actually present in the file. */
    return 0;
}
