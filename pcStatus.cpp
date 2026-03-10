#include "pcStatus.h"
#include <stdio.h>
#include <string.h>
#include <functional>
#include <unordered_set>
#include <assert.h>
#include "hash_size_t_array.h"
#include "pcRotate.h"

using namespace pocket_cube;

namespace {

using namespace side;

static constexpr const char
g_init_status[g_index_size] =
{
    Side_Up, Side_Up, Side_Up, Side_Up,
    Side_Down, Side_Down, Side_Down, Side_Down,
    Side_Left, Side_Left, Side_Left, Side_Left,
    Side_Right, Side_Right, Side_Right, Side_Right,
    Side_Front, Side_Front, Side_Front, Side_Front,
    Side_Back, Side_Back, Side_Back, Side_Back
};

}

void pcStatus::reset()
{
    constexpr size_t LEN = sizeof(m_status) / sizeof(size_t);
    static_assert (3 == LEN);

    const size_t *pInit = reinterpret_cast<const size_t *>(g_init_status);
    size_t *pStat = reinterpret_cast<size_t *>(m_status);

    pStat[0] = pInit[0];
    pStat[1] = pInit[1];
    pStat[2] = pInit[2];
}

bool pcStatus::isFinish() const
{
#if 0
    return _isSameCol(side::g_Up_1) &&
           _isSameCol(side::g_Down_1) &&
           _isSameCol(side::g_Left_1) &&
           _isSameCol(side::g_Right_1) &&
           _isSameCol(side::g_Front_1) &&
           _isSameCol(side::g_Back_1);
#else
    for (char i=0; i<side::g_side_size; ++i)
    {
        if (false == _isSameCol(side::g_r1List[i]))
        {
            return false;
        }
    }
    return true;
#endif
}

bool pcStatus::_isSameCol(const char *r1) const
{
    auto   col  = m_status[r1[0]];
    return col == m_status[r1[1]] &&
           col == m_status[r1[2]] &&
           col == m_status[r1[3]];
}

template<bool TypeClockWise>
void pcStatus::_rotate(side::eSide TypeSide)
{
    const char *r1 = side::g_r1List[TypeSide];
    const char *r2 = side::g_r2List[TypeSide];

    if constexpr (TypeClockWise)
    {
        {
            char bak3 = m_status[r1[3]];
            m_status[r1[3]] = m_status[r1[2]];
            m_status[r1[2]] = m_status[r1[1]];
            m_status[r1[1]] = m_status[r1[0]];
            m_status[r1[0]] = bak3;
        }

        {
            char bak7 = m_status[r2[7]];
            char bak6 = m_status[r2[6]];
            m_status[r2[7]] = m_status[r2[5]];
            m_status[r2[6]] = m_status[r2[4]];
            m_status[r2[5]] = m_status[r2[3]];
            m_status[r2[4]] = m_status[r2[2]];
            m_status[r2[3]] = m_status[r2[1]];
            m_status[r2[2]] = m_status[r2[0]];
            m_status[r2[1]] = bak7;
            m_status[r2[0]] = bak6;
        }
    }
    else
    {
        {
            char bak0 = m_status[r1[0]];
            m_status[r1[0]] = m_status[r1[1]];
            m_status[r1[1]] = m_status[r1[2]];
            m_status[r1[2]] = m_status[r1[3]];
            m_status[r1[3]] = bak0;
        }

        {
            char bak0 = m_status[r2[0]];
            char bak1 = m_status[r2[1]];
            m_status[r2[0]] = m_status[r2[2]];
            m_status[r2[1]] = m_status[r2[3]];
            m_status[r2[2]] = m_status[r2[4]];
            m_status[r2[3]] = m_status[r2[5]];
            m_status[r2[4]] = m_status[r2[6]];
            m_status[r2[5]] = m_status[r2[7]];
            m_status[r2[6]] = bak0;
            m_status[r2[7]] = bak1;
        }
    }
}

void pcStatus::rotate(char ch)
{
    switch(ch)
    {
    case 'U': _rotate<true >(Side_Up);  break;
    case 'u': _rotate<false>(Side_Up); break;
    case 'D': _rotate<true >(Side_Down);  break;
    case 'd': _rotate<false>(Side_Down); break;
    case 'L': _rotate<true >(Side_Left);  break;
    case 'l': _rotate<false>(Side_Left); break;
    case 'R': _rotate<true >(Side_Right);  break;
    case 'r': _rotate<false>(Side_Right); break;
    case 'F': _rotate<true >(Side_Front);  break;
    case 'f': _rotate<false>(Side_Front); break;
    case 'B': _rotate<true >(Side_Back);  break;
    case 'b': _rotate<false>(Side_Back); break;
    default:
        std::abort();
        break;
    }
}

void pcStatus::rotate_next(pcNextMoveRotate nr)
{
    rotate(nr.m_rotate);
    if (nr.m_is180)
    {
        rotate(nr.m_rotate);
    }
}

void pcStatus::rotate_string(const std::string &rl)
{
    for (auto ch : rl)
    {
        rotate(ch);
    }
}

void pcStatus::rotate_frl(const iso::pcIsoRotateList *frl)
{
    auto beg = frl->m_arr;
    auto end = beg + frl->m_len;
    for (; beg != end; ++beg)
    {
        rotate(*beg);
    }
}

size_t pcStatus::calc_hash() const
{
    constexpr size_t LEN = sizeof(m_status) / sizeof(size_t);
    static_assert (3 == LEN);

    const size_t *pStat = reinterpret_cast<const size_t *>(m_status);
    size_t h = my_hash::hash_size_array<LEN>(pStat);
    return h;
}

bool pcStatus::equal(const pcStatus &st) const
{
    constexpr size_t LEN = sizeof(m_status) / sizeof(size_t);
    static_assert (3 == LEN);

    const size_t *p1 = reinterpret_cast<const size_t *>(m_status);
    const size_t *p2 = reinterpret_cast<const size_t *>(st.m_status);

    return  p1[0] == p2[0] &&
            p1[1] == p2[1] &&
            p1[2] == p2[2];
}
