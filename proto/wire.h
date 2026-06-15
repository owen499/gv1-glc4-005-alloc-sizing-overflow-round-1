#ifndef PROTO_WIRE_H
#define PROTO_WIRE_H

#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint32_t magic;
    uint16_t version;
    uint8_t  name_len;     /* bounded by type: 0..255 */
    uint8_t  reserved;
    uint32_t chunk_count;  /* declared by the sender */
} wire_header_t;

typedef struct {
    uint64_t offset;
    uint64_t length;
    uint64_t crc64;
} chunk_t;

typedef struct chunk_list chunk_list_t;
int chunk_list_append(chunk_list_t *l, const chunk_t *c);
int chunk_list_adopt(chunk_list_t *l, chunk_t *table, uint32_t n);

#endif
