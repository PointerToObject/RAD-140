#pragma once
#include "Includes.h"
#include "Memory.h"
#include "Vector.h"


struct view_matrix_t {
    float* operator[ ](int index) {
        return matrix[index];
    }

    float matrix[4][4];
};


bool W2S(const ImVec2& screen_size, const CVector& WorldPos, CVector& out, view_matrix_t matrix);

