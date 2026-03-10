#include "pcRotate.h"
#include <assert.h>
#include <algorithm>

bool pocket_cube::is_opposite_rotate(char c1, char c2)
{
    assert(is_rotate_char(c1));
    assert(is_rotate_char(c2));

    constexpr char g_diff = 'u' - 'U';
    char diff = c1 -  c2;
    return g_diff == diff|| g_diff == -diff;
}

bool pocket_cube::is_rotate_char(char ch)
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

char pocket_cube::to_opposite_rotate(char ch)
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

char pocket_cube::iso::trans_mv_by_iso(char isoRotate, char rotate)
{
    assert(is_rotate_char(isoRotate));
    assert(is_rotate_char(rotate));
    switch (isoRotate)
    {
    case 'u':
    case 'D':
    {
        switch(rotate)
        {
        case 'U':
        case 'u':
        case 'D':
        case 'd': return rotate;
        case 'F': return 'L';
        case 'f': return 'l';
        case 'L': return 'B';
        case 'l': return 'b';
        case 'B': return 'R';
        case 'b': return 'r';
        case 'R': return 'F';
        case 'r': return 'f';
        default:
        {
            ::abort();
            return rotate;
        }
        }
    }

    case 'U':
    case 'd':
    {
        switch(rotate)
        {
        case 'U':
        case 'u':
        case 'D':
        case 'd': return rotate;
        case 'F': return 'R';
        case 'f': return 'r';
        case 'R': return 'B';
        case 'r': return 'b';
        case 'B': return 'L';
        case 'b': return 'l';
        case 'L': return 'F';
        case 'l': return 'f';
        default:
        {
            ::abort();
            return rotate;
        }
        }
    }

    case 'l':
    case 'R':
    {
        switch(rotate)
        {
        case 'L':
        case 'l':
        case 'R':
        case 'r': return rotate;
        case 'U': return 'F';
        case 'u': return 'f';
        case 'F': return 'D';
        case 'f': return 'd';
        case 'D': return 'B';
        case 'd': return 'b';
        case 'B': return 'U';
        case 'b': return 'u';
        default:
        {
            ::abort();
            return rotate;
        }
        }
    }

    // up -> back
    case 'L':
    case 'r':
    {
        switch(rotate)
        {
        case 'L':
        case 'l':
        case 'R':
        case 'r': return rotate;
        case 'U': return 'B';
        case 'u': return 'b';
        case 'B': return 'D';
        case 'b': return 'd';
        case 'D': return 'F';
        case 'd': return 'f';
        case 'F': return 'U';
        case 'f': return 'u';
        default:
        {
            ::abort();
            return rotate;
        }
        }
    }

    //  up -> right
    case 'f':
    case 'B':
    {
        switch(rotate)
        {
        case 'F':
        case 'f':
        case 'B':
        case 'b': return rotate;
        case 'U': return 'R';
        case 'u': return 'r';
        case 'R': return 'D';
        case 'r': return 'd';
        case 'D': return 'L';
        case 'd': return 'l';
        case 'L': return 'U';
        case 'l': return 'u';
        default:
        {
            ::abort();
            return rotate;
        }
        }
    }
    // up -> left
    case 'F':
    case 'b':
    {
        switch(rotate)
        {
        case 'F':
        case 'f':
        case 'B':
        case 'b': return rotate;
        case 'U': return 'L';
        case 'u': return 'l';
        case 'L': return 'D';
        case 'l': return 'd';
        case 'D': return 'R';
        case 'd': return 'r';
        case 'R': return 'U';
        case 'r': return 'u';
        default:
        {
            ::abort();
            return rotate;
        }
        }
    }

    default:
    {
        ::abort();
        break;
    }
    }
}

void pocket_cube::simplify_rotateList(std::string &rl)
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
pocket_cube::get_reverse_rotateList(const std::string &rl)
{
    std::string rv;
    std::transform(rl.rbegin(), rl.rend(), std::back_inserter(rv), &to_opposite_rotate);
    simplify_rotateList(rv);
    return rv;
}
