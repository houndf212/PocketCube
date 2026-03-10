#pragma once

namespace rubik_cube {

namespace ns_side {

enum eSide
{
    Side_Up    = 0,
    Side_Down  = 1,
    Side_Left  = 2,
    Side_Right = 3,
    Side_Front = 4,
    Side_Back  = 5,
};

constexpr const char g_side_size = 6;

/*
 *   ===========================
 *   |       U U U
 *   |       U U U
 *   |       U U U
 *   | L L L F F F R R R | B B B
 *   | L L L F F F R R R | B B B
 *   | L L L F F F R R R | B B B
 *   |       D D D
 *   |       D D D
 *   |       D D D
 *   ==========================
 *
 *   ========================================
 *   |           0  1  2
 *   |           7  U  3
 *   |           6  5  4
 *   | 16 17 18 32 33 34 24 25 26 | 40 41 42
 *   | 23  L 19 39  F 35 31 R  27 | 47  B 43
 *   | 22 21 20 38 37 36 30 29 28 | 46 45 44
 *   |           8  9 10
 *   |          15  D 11
 *   |          14 13 12
 *   =======================================
 *
 */

constexpr const char g_index_size = 48;

constexpr const char g_Up_1[] = {0, 1, 2, 3, 4, 5, 6, 7};
constexpr const char g_Up_2[] = {42, 41, 40, 26, 25, 24, 34, 33, 32, 18, 17, 16};

constexpr const char g_Down_1[] = {8, 9, 10, 11, 12, 13, 14, 15};
constexpr const char g_Down_2[] = {22, 21, 20, 38, 37, 36, 30, 29, 28, 46, 45, 44};

constexpr const char g_Left_1[] = {16, 17, 18, 19, 20, 21, 22, 23};
constexpr const char g_Left_2[] = {0, 7, 6, 32, 39, 38, 8, 15, 14, 44, 43, 42};

constexpr const char g_Right_1[] = {24, 25, 26, 27, 28, 29, 30, 31};
constexpr const char g_Right_2[] = {12, 11, 10, 36, 35, 34, 4, 3, 2, 40, 47, 46};

constexpr const char g_Front_1[] = {32, 33, 34, 35, 36, 37, 38, 39};
constexpr const char g_Front_2[] = {6, 5, 4, 24, 31, 30, 10, 9, 8, 20, 19, 18};

constexpr const char g_Back_1[] = {40, 41, 42, 43, 44, 45, 46, 47};
constexpr const char g_Back_2[] = {2, 1, 0, 16, 23, 22, 14, 13, 12, 28, 27, 26};

constexpr const char g_size_r1 = sizeof(g_Up_1);
constexpr const char g_size_r2 = sizeof(g_Up_2);

static_assert(g_size_r1 == 8, "");
static_assert(g_size_r2 == 12, "");

constexpr const char* g_r1List[g_side_size] =
{
    g_Up_1, g_Down_1, g_Left_1, g_Right_1, g_Front_1, g_Back_1
};

constexpr const char* g_r2List[g_side_size] =
{
    g_Up_2, g_Down_2, g_Left_2, g_Right_2, g_Front_2, g_Back_2
};

}

}
