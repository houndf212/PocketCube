#ifndef PCROTATE_H
#define PCROTATE_H

#include <string>

namespace pocket_cube {

bool
is_rotate_char(char ch);

bool
is_opposite_rotate(char c1, char c2);

char
to_opposite_rotate(char ch);

void
simplify_rotateList(std::string &rl);

std::string
get_reverse_rotateList(const std::string &rl);

struct pcNextMoveRotate
{
    char m_rotate;
    bool m_is180;
};

constexpr pcNextMoveRotate g_noneMove = {0, false};

constexpr size_t g_god_num_180 = 11;
constexpr size_t g_god_num_90  = 14;
constexpr size_t g_all_status_num = 88179840;
constexpr size_t g_iso_all_status_num = 3674160;

namespace next_mv {

constexpr pcNextMoveRotate g_nextMoveList[] =
{
    {'u', false},
    {'U', false},
    //{'U', true},

    {'d', false},
    {'D', false},
    //{'D', true},

    {'l', false},
    {'L', false},
    //{'L', true},

    {'r', false},
    {'R', false},
    //{'R', true},

    {'f', false},
    {'F', false},
    //{'F', true},

    {'b', false},
    {'B', false},
    //{'B', true}
};

constexpr size_t g_nextMoveSize = sizeof(g_nextMoveList) / sizeof(g_nextMoveList[0]);
static_assert (g_nextMoveSize == 12);

}

namespace iso_next_mv_180 {

constexpr pcNextMoveRotate g_isoNextMoveList[] =
{
    {'u', false},
    {'U', false},
    {'U', true},

    {'r', false},
    {'R', false},
    {'R', true},

    {'f', false},
    {'F', false},
    {'F', true}
};

constexpr size_t g_isoNextMoveSize = sizeof(g_isoNextMoveList) / sizeof(g_isoNextMoveList[0]);
static_assert (g_isoNextMoveSize == 9);

}

namespace iso_next_mv_90 {

constexpr pcNextMoveRotate g_isoNextMoveList[] =
{
    {'u', false},
    {'U', false},

    {'r', false},
    {'R', false},

    {'f', false},
    {'F', false},
};

constexpr size_t g_isoNextMoveSize = sizeof(g_isoNextMoveList) / sizeof(g_isoNextMoveList[0]);
static_assert (g_isoNextMoveSize == 6);

}

// 24 iso rotate
namespace iso {

struct pcIsoRotateList
{
    const char  *m_arr;
    const size_t m_len;
};

constexpr size_t g_iso_size = 24;

#if 0
constexpr pcIsoRotateList g_isoList[g_iso_size] =
    {
    // keep F && B
    {"",     0},
    {"fB",   2},
    {"Fb",   2},
    {"FbFb", 4},
    // up => front
    {"Lr",     2},
    {"LrfB",   4},
    {"LrFb",   4},
    {"LrFbFb", 6},
    // down =>front
    {"lR",     2},
    {"lRfB",   4},
    {"lRFb",   4},
    {"lRFbFb", 6},
    // left => front
    {"uD",     2},
    {"uDfB",   4},
    {"uDFb",   4},
    {"uDFbFb", 6},
    // right => front
    {"Ud",     2},
    {"UdfB",   4},
    {"UdFb",   4},
    {"UdFbFb", 6},
    // back => front
    {"uDuD",     4},
    {"uDuDfB",   6},
    {"uDuDFb",   6},
    #if 0
    {"uDuDuFbFb", 8},
    #else
    {"lRlR",     4},
    #endif
};
#else
// may order is cached...
constexpr pcIsoRotateList g_isoList[g_iso_size] =
    {
    // keep Up && Down
    {"",     0},
    {"uD",   2},
    {"Ud",   2},
    {"UdUd", 4},
    // front => up
    {"lR",     2},
    {"lRuD",   4},
    {"lRUd",   4},
    {"lRUdUd", 6},
    // back => up
    {"Lr",     2},
    {"LruD",   4},
    {"LrUd",   4},
    {"LrUdUd", 6},
    // left => up
    {"Fb",     2},
    {"FbuD",   4},
    {"FbUd",   4},
    {"FbUdUd", 6},
    // right => up
    {"fB",     2},
    {"fBuD",   4},
    {"fBUd",   4},
    {"fBUdUd", 6},
    // down => up
    {"lRlR",     4},
    {"lRlRuD",   6},
    {"lRlRUd",   6},
    #if 0
    {"lRlRUdUd", 8},
    #else
    {"FbFb",     4},
    #endif
};
#endif

static_assert (sizeof(g_isoList) / sizeof(g_isoList[0]) == g_iso_size);

char trans_mv_by_iso(char isoRotate, char rotate);

}



}


#endif // PCROTATE_H
