#pragma once

#include <string>

namespace rubik_cube {

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

struct rcNextMoveRotate
{
    char m_rotate;
    bool m_is180;
};

constexpr rcNextMoveRotate g_noneMove = {0, false};

namespace rc_next_mv {

constexpr rcNextMoveRotate g_nextMoveList[] =
{
    {'u', false},
    {'U', false},
    {'U', true},

    {'d', false},
    {'D', false},
    {'D', true},

    {'l', false},
    {'L', false},
    {'L', true},

    {'r', false},
    {'R', false},
    {'R', true},

    {'f', false},
    {'F', false},
    {'F', true},

    {'b', false},
    {'B', false},
    {'B', true}
};

constexpr char g_nextMoveSize = sizeof(g_nextMoveList) / sizeof(g_nextMoveList[0]);
static_assert (g_nextMoveSize == 18);

}

}
