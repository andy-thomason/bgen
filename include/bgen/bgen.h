#ifndef BGEN_READER_H
#define BGEN_READER_H

#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef unsigned char byte;
typedef int_fast64_t  inti;
typedef double        real;

typedef struct string {
    inti  len;
    byte *str;
} string;

typedef struct BGenFile        BGenFile;
typedef struct Variant         Variant;
typedef struct VariantGenotype VariantGenotype;
typedef struct VariantIndexing VariantIndexing;

BGenFile* bgen_open(const byte *filepath);
void      bgen_close(BGenFile *bgen);

inti      bgen_nsamples(BGenFile *bgen);
inti      bgen_nvariants(BGenFile *bgen);

string  * bgen_read_samples(BGenFile *bgen);
void      bgen_free_samples(const BGenFile *bgen,
                            string         *samples);
Variant * bgen_read_variants(BGenFile         *bgen,
                             VariantIndexing **index);

// VariantGenotype* bgen_read_variant_genotypes(VariantIndexing *indexing,
//                                              inti             variant_start,
//                                              inti             variant_end);

#endif /* end of include guard: BGEN_READER_H */
