#include "bgen_reader.h"

#include <stdlib.h>

int64_t bgen_reader_sample_id(BGenFile *bgenfile, uint64_t idx, char **id,
                              uint64_t *length)
{
    if (idx >= bgen_reader_nsamples(bgenfile)) return EXIT_FAILURE;

    SampleId *sampleid = &(bgenfile->sampleid_block.sampleids[idx]);

    *length = sampleid->length;
    *id     = sampleid->id;

    return 0;
}