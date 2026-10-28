#ifndef UVB_TABLE_REDSHIFT_H
#define UVB_TABLE_REDSHIFT_H

typedef struct {
    int lower;
    int upper;
    double upper_weight;
    int beyond_max;
} UVBTableRedshift;

static inline UVBTableRedshift uvb_table_redshift(double log1pz, const float *table_log1pz, int count)
{
    UVBTableRedshift selection = {0, 1, 0.0, 0};
    int i;

    if(log1pz > table_log1pz[count - 1]) {
        selection.beyond_max = 1;
        return selection;
    }
    if(log1pz <= table_log1pz[0]) return selection;

    for(i = 1; i < count - 1 && table_log1pz[i] < log1pz; i++) {}
    selection.lower = i - 1;
    selection.upper = i;
    selection.upper_weight = (log1pz - table_log1pz[selection.lower]) /
                             (table_log1pz[selection.upper] - table_log1pz[selection.lower]);
    return selection;
}

#endif
