#ifndef PCDEFINE_H
#define PCDEFINE_H

namespace pocket_cube {

namespace side {

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

constexpr const char g_index_size = 24;

/*
 *   ==================
 *   |     U U
 *   |     U U
 *   | L L F F R R B B
 *   | L L F F R R B B
 *   |     D D
 *   |     D D
 *   ===================
 *
 *   ==================
 *   |        0  1
 *   |        3  2
 *   | 8  9   16 17  12 13 20 21
 *   | 11 10  19 18  15 14 23 22
 *   |        4  5
 *   |        7  6
 *   ===================
 *
 */

constexpr const char g_Up_1[] = {0, 1, 2, 3};
constexpr const char g_Up_2[] = {21, 20, 13, 12, 17, 16, 9, 8};

constexpr const char g_Down_1[] = {4, 5, 6, 7};
constexpr const char g_Down_2[] = {11, 10, 19, 18, 15, 14, 23, 22};

constexpr const char g_Left_1[] = {8, 9, 10, 11};
constexpr const char g_Left_2[] = {0, 3, 16, 19, 4, 7, 22, 21};

constexpr const char g_Right_1[] = {12, 13, 14, 15};
constexpr const char g_Right_2[] = {6, 5, 18, 17, 2, 1, 20, 23};

constexpr const char g_Front_1[] = {16, 17, 18, 19};
constexpr const char g_Front_2[] = {3, 2, 12, 15, 5, 4, 10, 9};

constexpr const char g_Back_1[] = {20, 21, 22, 23};
constexpr const char g_Back_2[] = {1, 0, 8, 11, 7, 6, 14, 13};

constexpr const char g_size_r1 = sizeof(g_Up_1);
constexpr const char g_size_r2 = sizeof(g_Up_2);

static_assert(g_size_r1 == 4, "");
static_assert(g_size_r2 == 8, "");

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


#endif // PCDEFINE_H
