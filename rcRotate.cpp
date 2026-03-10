#include "rcRotate.h"
#include <assert.h>
#include <algorithm>

bool rubik_cube::is_rotate_char(char ch)
{
    switch (ch)
    {
    case 'U':
    case 'u':
    case 'D':
    case 'd':
    case 'L':
    case 'l':
    case 'R':
    case 'r':
    case 'F':
    case 'f':
    case 'B':
    case 'b':
        return true;
    default:
        return false;
    }
}

bool rubik_cube::is_opposite_rotate(char c1, char c2)
{
    assert(is_rotate_char(c1));
    assert(is_rotate_char(c2));

    constexpr char g_diff = 'u' - 'U';
    char diff = c1 -  c2;
    return g_diff == diff|| g_diff == -diff;
}

char rubik_cube::to_opposite_rotate(char ch)
{
    assert(is_rotate_char(ch));
    switch (ch)
    {
    case 'U': return 'u';
    case 'D': return 'd';
    case 'L': return 'l';
    case 'R': return 'r';
    case 'F': return 'f';
    case 'B': return 'b';

    case 'u': return 'U';
    case 'd': return 'D';
    case 'l': return 'L';
    case 'r': return 'R';
    case 'f': return 'F';
    case 'b': return 'B';
    default:
    {
        ::abort();
        break;
    }
    }
}

void rubik_cube::simplify_rotateList(std::string &rl)
{
    int nLen = rl.size();
    if (nLen <= 1)
    {
        return;
    }

    int backIndex = 0;
    int cursor    = 1;
    do {
        char ch = rl[cursor++];

        if (-1 == backIndex)
        {
            rl[0] = ch;
            backIndex = 0;
            continue;
        }

        assert(0 <= backIndex && backIndex <rl.size());

        char bch = rl[backIndex];
        if (is_opposite_rotate(ch, bch))
        {
            --backIndex;
        }
        else
        {
            rl[++backIndex] = ch;
        }
    } while (cursor != nLen);

    rl.resize(backIndex + 1);
}

std::string
rubik_cube::get_reverse_rotateList(const std::string &rl)
{
    std::string rv;
    std::transform(rl.rbegin(), rl.rend(), std::back_inserter(rv), &to_opposite_rotate);
    simplify_rotateList(rv);
    return rv;
}
