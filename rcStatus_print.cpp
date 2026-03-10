#include "rcStatus.h"

using namespace rubik_cube;

static constexpr const char g_terminalCol[] = {'Y', 'W', 'R', 'O', 'G', 'B'};

//static constexpr const char g_terminalCol[] = {'U', 'D', 'L', 'R', 'F', 'B'};

static inline constexpr char
_side_to_col(char e)
{
    return g_terminalCol[e];
}

char
rcStatus::_t_col(char index) const
{
    auto col = m_status[index];
    return _side_to_col(col);
}

void
rcStatus::print() const
{
/*
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
    constexpr char e_up = _side_to_col(ns_side::Side_Up);
    constexpr char e_down = _side_to_col(ns_side::Side_Down);
    constexpr char e_left = _side_to_col(ns_side::Side_Left);
    constexpr char e_right = _side_to_col(ns_side::Side_Right);
    constexpr char e_front = _side_to_col(ns_side::Side_Front);
    constexpr char e_back  = _side_to_col(ns_side::Side_Back);

    printf("      %c %c %c\n", _t_col(0), _t_col(1), _t_col(2));
    printf("      %c %c %c\n", _t_col(7), e_up,      _t_col(3));
    printf("      %c %c %c\n", _t_col(6), _t_col(5), _t_col(4));

    printf("%c %c %c %c %c %c %c %c %c | %c %c %c\n",
           _t_col(16), _t_col(17), _t_col(18),
           _t_col(32), _t_col(33), _t_col(34),
           _t_col(24), _t_col(25), _t_col(26),
           _t_col(40), _t_col(41), _t_col(42));

    printf("%c %c %c %c %c %c %c %c %c | %c %c %c\n",
           _t_col(23), e_left,  _t_col(19),
           _t_col(39), e_front, _t_col(35),
           _t_col(31), e_right, _t_col(27),
           _t_col(47), e_back,  _t_col(43));

    printf("%c %c %c %c %c %c %c %c %c | %c %c %c\n",
           _t_col(22), _t_col(21), _t_col(20),
           _t_col(38), _t_col(37), _t_col(36),
           _t_col(30), _t_col(29), _t_col(28),
           _t_col(46), _t_col(45), _t_col(44));

    printf("      %c %c %c\n", _t_col(8),  _t_col(9),  _t_col(10));
    printf("      %c %c %c\n", _t_col(15), e_down,     _t_col(11));
    printf("      %c %c %c\n", _t_col(14), _t_col(13), _t_col(12));

    putchar('\n');
}
