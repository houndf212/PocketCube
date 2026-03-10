#include "pcStatus.h"
#include <stdio.h>

using namespace pocket_cube;

static constexpr const char g_terminalCol[] = {'W', 'Y', 'O', 'R', 'G', 'B'};

//static constexpr const char g_terminalCol[] = {'U', 'D', 'L', 'R', 'F', 'B'};

static inline char
_side_to_col(char e)
{
    return g_terminalCol[e];
}

static bool
_col_to_side(char &sideIndex, char col)
{
    switch (col)
    {
    case 'w' :
    case 'W' :
        sideIndex = side::Side_Up; return true;
    case 'y' :
    case 'Y' :
        sideIndex = side::Side_Down; return true;
    case 'o' :
    case 'O' :
        sideIndex = side::Side_Left; return true;
    case 'r' :
    case 'R' :
        sideIndex = side::Side_Right; return true;
    case 'g' :
    case 'G' :
        sideIndex = side::Side_Front; return true;
    case 'b' :
    case 'B' :
        sideIndex = side::Side_Back; return true;
    default:
        return false;
    }
}

char pcStatus::_t_col(char index) const
{
    auto col = m_status[index];
    return _side_to_col(col);
}

bool pcStatus::fromString(const std::string &str)
{
    if (str.size() < side::g_index_size)
    {
        printf("Error: too small size %zu\n", str.size());
        return false;
    }

    size_t side_count[side::g_side_size] = {0};

    size_t nIndex = 0;
    for (char ch : str)
    {
        if  (nIndex >= side::g_index_size)
        {
            break;
        }

        char sideChar;
        if (_col_to_side(sideChar, ch))
        {
            side_count[sideChar]++;

            m_status[nIndex++] = sideChar;
        }
        else
        {
            printf("skip char: %c\n", ch);
        }
    }

    if (side::g_index_size != nIndex)
    {
        printf("Error: too small index %zu\n", nIndex);
        return false;
    }

   for (size_t i=0; i<side::g_side_size; ++i)
   {
       if (4 != side_count[i])
       {
           printf("Error: side %zu, count %zu\n", i, side_count[i]);
           return false;
       }
   }

   return true;
}

void pcStatus::print() const
{
    /*
 *   ==================
 *   |      U U
 *   |     U U
 *   | L L F F R R B B
 *   | L L F F R R B B
 *   |     D D
 *   |      D D
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
    printf("    %c %c\n", _t_col(0), _t_col(1));
    printf("    %c %c\n", _t_col(3), _t_col(2));

    printf("%c %c %c %c %c %c | %c %c\n",
           _t_col(8), _t_col(9), _t_col(16), _t_col(17), _t_col(12), _t_col(13), _t_col(20), _t_col(21));
    printf("%c %c %c %c %c %c | %c %c\n",
           _t_col(11), _t_col(10), _t_col(19), _t_col(18), _t_col(15), _t_col(14), _t_col(23), _t_col(22));

    printf("    %c %c\n", _t_col(4), _t_col(5));
    printf("    %c %c\n", _t_col(7), _t_col(6));
    printf("\n");
    for (size_t index=0; index<side::g_index_size; ++index)
    {
        putchar(_t_col(index));
    }
    putchar('\n');
}
