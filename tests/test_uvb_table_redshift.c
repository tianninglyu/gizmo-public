#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "../cooling/uvb_table_redshift.h"

int main(void)
{
    const float synthetic[] = {0.0f, 0.5f, 1.0f};
    UVBTableRedshift selection;
    float table[250];
    double hydrogen_ionization[250];
    FILE *input = fopen("cooling/TREECOOL", "r");
    char line[512];
    int count = 0;

    selection = uvb_table_redshift(0.25, synthetic, 3);
    assert(selection.lower == 0 && selection.upper == 1);
    assert(fabs(selection.upper_weight - 0.5) < 1e-12);
    selection = uvb_table_redshift(0.5, synthetic, 3);
    assert(selection.lower == 0 && selection.upper == 1);
    assert(fabs(selection.upper_weight - 1.0) < 1e-12);
    selection = uvb_table_redshift(1.0, synthetic, 3);
    assert(!selection.beyond_max && selection.lower == 1 && selection.upper == 2);
    selection = uvb_table_redshift(1.1, synthetic, 3);
    assert(selection.beyond_max);

    assert(input != NULL);
    while(fgets(line, sizeof(line), input) && count < 250) {
        float log1pz;
        double rate;
        if(sscanf(line, "%f %lf", &log1pz, &rate) == 2) {
            table[count] = log1pz;
            hydrogen_ionization[count++] = rate;
        }
    }
    fclose(input);
    assert(count > 2);
    selection = uvb_table_redshift(log10(7.0), table, count);
    assert(!selection.beyond_max);
    assert(table[selection.lower] <= log10(7.0));
    assert(log10(7.0) <= table[selection.upper]);
    assert(selection.upper == selection.lower + 1);
    assert(selection.upper_weight > 0.0 && selection.upper_weight < 1.0);
    assert(hydrogen_ionization[selection.lower] > 0.0);
    assert(hydrogen_ionization[selection.upper] > 0.0);
    return 0;
}
