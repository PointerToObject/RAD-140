#include "W2S.h"

bool W2S(const ImVec2& screen_size, const CVector& WorldPos, CVector& out, view_matrix_t matrix) {
	out.x = matrix[0][0] * WorldPos.x + matrix[0][1] * WorldPos.y + matrix[0][2] * WorldPos.z + matrix[0][3];
	out.y = matrix[1][0] * WorldPos.x + matrix[1][1] * WorldPos.y + matrix[1][2] * WorldPos.z + matrix[1][3];

	float w = matrix[3][0] * WorldPos.x + matrix[3][1] * WorldPos.y + matrix[3][2] * WorldPos.z + matrix[3][3];

	if (w < 0.01f)
		return false;

	float inv_w = 1.f / w;
	out.x *= inv_w;
	out.y *= inv_w;

	float x = screen_size.x * .5f;
	float y = screen_size.y * .5f;

	x += 0.5f * out.x * screen_size.x + 0.5f;
	y -= 0.5f * out.y * screen_size.y + 0.5f;

	out.x = x;
	out.y = y;

	return true;
}