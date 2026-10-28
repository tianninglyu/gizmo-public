#include <assert.h>
#include <math.h>
#include "../cooling/species_table_redshift.h"

static void check(double redshift, int lower, double upper_weight)
{
    SpeciesCoolingTableRedshift selection = species_cooling_table_redshift(redshift);
    assert(selection.lower == lower);
    assert(fabs(selection.upper_weight - upper_weight) < 1e-12);
}

int main(void)
{
    double z6_position = 48.0 * log10(7.0);

    check(0.0, 0, 0.0);
    check(6.0, 40, z6_position - 40.0);
    check(1.0 / (1.0 / 7.0) - 1.0, 40, z6_position - 40.0);
    check(pow(10.0, 1.0 / 48.0) - 1.0, 1, 0.0);
    check(9.0, 48, 0.0);
    check(20.0, 48, 0.0);
    return 0;
}
