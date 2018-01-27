#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "layout1.h"
#include "variant_genotype.h"
#include "variant_indexing.h"

#include "bgen.h"
#include "util/file.h"
#include "util/bits.h"
#include "util/zlib_wrapper.h"
#include "util/zstd_wrapper.h"
#include "util/mem.h"
#include "util/choose.h"

#define FAIL EXIT_FAILURE

inline static inti bgen_read_ploidy_layout1(byte ploidy_miss)
{
    return ploidy_miss & 127;
}

inline static inti bgen_read_missingness_layout1(byte ploidy_miss)
{
    return (ploidy_miss & 256) >> 7;
}

inline static inti bit_sample_start_layout1(inti sample_idx, inti nbits,
                                            inti ncomb)
{
    return sample_idx * (nbits * (ncomb - 1));
}

inline static inti bit_geno_start_layout1(inti geno_idx, inti nbits)
{
    return geno_idx * nbits;
}

inline static int get_bit_layout1(const byte *mem, inti bit_idx)
{
    inti bytes = bit_idx / 8;

    return GetBit(*(mem + bytes), bit_idx % 8);
}

void bgen_read_unphased_genotype_layout1(VariantGenotype *vg,
                                         real            *probabilities)
{
    uint16_t ui_prob;
    inti     ui_prob_sum;

    inti sample_start, geno_start, bit_idx;

    real denom = 32768;

    inti i, j;

    byte *chunk = vg->current_chunk;

    for (j = 0; j < vg->nsamples; ++j)
    {
        ui_prob_sum = 0;

        for (i = 0; i < 3; ++i)
        {
            MEMCPY(&ui_prob, &chunk, 2);
            probabilities[j * 3 + i] = ui_prob / denom;
            ui_prob_sum             += ui_prob;
        }

        if (ui_prob_sum == 0)
        {
            for (i = 0; i < 3; ++i) probabilities[j * 3 + i] = NAN;
        }
    }
}

void bgen_read_variant_genotype_probabilities_layout1(VariantIndexing *indexing,
                                                      VariantGenotype *vg,
                                                      real            *probabilities)
{
    bgen_read_unphased_genotype_layout1(vg, probabilities);
}

byte* bgen_uncompress_layout1(VariantIndexing *indexing, FILE *file)
{
    inti  clength = 0, ulength = 0;
    byte *cchunk;
    byte *uchunk;

    if (bgen_read(file, &clength, 4) == FAIL) return NULL;

    cchunk = malloc(clength);

    if (bgen_read(file, cchunk, clength) == FAIL)
    {
        free(cchunk);
        return NULL;
    }

    if (indexing->compression != 1)
    {
        free(cchunk);
        fprintf(stderr,
                "Compression flag should be 1; not %lld.\n",
                indexing->compression);
        return NULL;
    }

    ulength = 10 * clength;
    uchunk  = malloc(ulength);

    zlib_uncompress_chunked(cchunk, clength, &uchunk, &ulength);

    free(cchunk);

    return uchunk;
}

inti bgen_read_variant_genotype_header_layout1(
    VariantIndexing *indexing,
    VariantGenotype *vg, FILE *file)
{
    byte *c;
    byte *chunk;

    if (indexing->compression > 0)
    {
        chunk = bgen_uncompress_layout1(indexing, file);
        c     = chunk;
    }
    else {
        chunk = malloc(6 * indexing->nsamples);

        if (bgen_read(file, chunk, 6 * indexing->nsamples) == FAIL) return FAIL;

        c = chunk;
    }

    vg->nsamples      = indexing->nsamples;
    vg->nalleles      = 2;
    vg->ncombs        = 3;
    vg->ploidy        = 2;
    vg->chunk         = chunk;
    vg->current_chunk = c;

    return EXIT_SUCCESS;
}