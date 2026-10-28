#ifndef SPECIES_TABLE_REDSHIFT_H
#define SPECIES_TABLE_REDSHIFT_H

#include <math.h>

typedef struct {
    int lower;
    double upper_weight;
} SpeciesCoolingTableRedshift;

/* The metal-line tables are spaced by 1/48 in log10(1+z). */
static inline SpeciesCoolingTableRedshift species_cooling_table_redshift(double redshift)
{
    SpeciesCoolingTableRedshift selection;
    double position = 48.0 * log10(1.0 + redshift);

    if(position < 0.0) position = 0.0;
    if(position > 48.0) position = 48.0;
    if(fabs(position - nearbyint(position)) < 1e-12) position = nearbyint(position);
    selection.lower = (int)position;
    selection.upper_weight = position - selection.lower;
    return selection;
}

#endif
