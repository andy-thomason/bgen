#ifndef BGEN_LAYOUT_ONE_H
#define BGEN_LAYOUT_ONE_H

#include <stdio.h>

#include "bgen.h"

int bgen_read_probs_header_one(struct bgen_vi *, struct bgen_vg *, FILE *);
void bgen_read_probs_one(struct bgen_vg *, double *);

#endif /* ifndef BGEN_LAYOUT_ONE_H */
