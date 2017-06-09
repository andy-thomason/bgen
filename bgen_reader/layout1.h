#ifndef LAYOUT1_H
#define LAYOUT1_H

int64_t bgen_genotype_block_layout1(BGenFile     *bgenfile,
                                    int64_t       compression,
                                    int64_t       nsamples,
                                    VariantBlock *vb,
                                    uint32_t     *ui_probs);

#endif /* ifndef LAYOUT1_H */