#pragma once
#ifndef CSeek_points
#define CSeek_points
#include "size_t.h"

/// <summary>
/// used for correct positioning error
/// </summary>
struct points {
    char val;
    size_t colum;
    size_t line;
    points() { val = 0; colum = 0; line = 0; }
    points(char v, size_t c, size_t l) { val = v; colum = c; line = l; }
};
#endif