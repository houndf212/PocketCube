#include "rcStatus.h"
#include "hash_size_t_array.h"

using namespace rubik_cube;

namespace {

using namespace rubik_cube::ns_side;

static constexpr const char
g_init_status[ns_side::g_index_size] =
{
    Side_Up, Side_Up, Side_Up, Side_Up, Side_Up, Side_Up, Side_Up, Side_Up,
    Side_Down, Side_Down, Side_Down, Side_Down, Side_Down, Side_Down, Side_Down, Side_Down,
    Side_Left, Side_Left, Side_Left, Side_Left, Side_Left, Side_Left, Side_Left, Side_Left,
    Side_Right, Side_Right, Side_Right, Side_Right, Side_Right, Side_Right, Side_Right, Side_Right,
    Side_Front, Side_Front, Side_Front, Side_Front, Side_Front, Side_Front, Side_Front, Side_Front,
    Side_Back, Side_Back, Side_Back, Side_Back, Side_Back, Side_Back, Side_Back, Side_Back
};

static constexpr char g_wordSize = sizeof(g_init_status) / sizeof(size_t);

static_assert (6 == g_wordSize);

}

void rcStatus::reset()
{
    const size_t * g_init = reinterpret_cast<const size_t*>(g_init_status);
    size_t *pStatus = reinterpret_cast<size_t*>(m_status);

    for (char i=0; i<g_wordSize; ++i)
    {
        pStatus[i] = g_init[i];
    }
}

bool rcStatus::isFinish() const
{
    const size_t * g_init = reinterpret_cast<const size_t*>(g_init_status);
    const size_t *pStatus = reinterpret_cast<const size_t*>(m_status);

    for (char i=0; i<g_wordSize; ++i)
    {
        if (pStatus[i] != g_init[i])
        {
            return false;
        }
    }

    return true;
}

template<bool TypeClockWise>
void rcStatus::_rotate(ns_side::eSide TypeSide)
{
    const char *r1 = ns_side::g_r1List[TypeSide];
    const char *r2 = ns_side::g_r2List[TypeSide];

    if constexpr (TypeClockWise)
    {
        {
            char bak6 = m_status[r1[6]];
            char bak7 = m_status[r1[7]];
            m_status[r1[7]] = m_status[r1[5]];
            m_status[r1[6]] = m_status[r1[4]];
            m_status[r1[5]] = m_status[r1[3]];
            m_status[r1[4]] = m_status[r1[2]];
            m_status[r1[3]] = m_status[r1[1]];
            m_status[r1[2]] = m_status[r1[0]];
            m_status[r1[1]] = bak7;
            m_status[r1[0]] = bak6;
        }

        {
            char bak9 = m_status[r2[9]];
            char bak10 = m_status[r2[10]];
            char bak11 = m_status[r2[11]];
            m_status[r2[11]] = m_status[r2[8]];
            m_status[r2[10]] = m_status[r2[7]];
            m_status[r2[9]] = m_status[r2[6]];
            m_status[r2[8]] = m_status[r2[5]];
            m_status[r2[7]] = m_status[r2[4]];
            m_status[r2[6]] = m_status[r2[3]];
            m_status[r2[5]] = m_status[r2[2]];
            m_status[r2[4]] = m_status[r2[1]];
            m_status[r2[3]] = m_status[r2[0]];
            m_status[r2[2]] = bak11;
            m_status[r2[1]] = bak10;
            m_status[r2[0]] = bak9;
        }
    }
    else
    {
        {
            char bak0 = m_status[r1[0]];
            char bak1 = m_status[r1[1]];
            m_status[r1[0]] = m_status[r1[2]];
            m_status[r1[1]] = m_status[r1[3]];
            m_status[r1[2]] = m_status[r1[4]];
            m_status[r1[3]] = m_status[r1[5]];
            m_status[r1[4]] = m_status[r1[6]];
            m_status[r1[5]] = m_status[r1[7]];
            m_status[r1[6]] = bak0;
            m_status[r1[7]] = bak1;
        }

        {
            char bak0 = m_status[r2[0]];
            char bak1 = m_status[r2[1]];
            char bak2 = m_status[r2[2]];
            m_status[r2[0]] = m_status[r2[3]];
            m_status[r2[1]] = m_status[r2[4]];
            m_status[r2[2]] = m_status[r2[5]];
            m_status[r2[3]] = m_status[r2[6]];
            m_status[r2[4]] = m_status[r2[7]];
            m_status[r2[5]] = m_status[r2[8]];
            m_status[r2[6]] = m_status[r2[9]];
            m_status[r2[7]] = m_status[r2[10]];
            m_status[r2[8]] = m_status[r2[11]];
            m_status[r2[9]]  = bak0;
            m_status[r2[10]] = bak1;
            m_status[r2[11]] = bak2;
        }
    }
}

void rcStatus::rotate(char ch)
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

void rcStatus::rotate_next(rcNextMoveRotate nr)
{
    rotate(nr.m_rotate);
    if (nr.m_is180)
    {
        rotate(nr.m_rotate);
    }
}

void rcStatus::rotate_string(const std::string &rl)
{
    for (auto c : rl)
    {
        rotate(c);
    }
}

size_t rcStatus::calc_hash() const
{
    constexpr size_t LEN = sizeof(m_status) / sizeof(size_t);
    static_assert (g_wordSize == LEN);

    const size_t *pStat = reinterpret_cast<const size_t *>(m_status);
    size_t h = my_hash::hash_size_array<LEN>(pStat);
    return h;
}

bool rcStatus::equal(const rcStatus &st) const
{
    constexpr size_t LEN = sizeof(m_status) / sizeof(size_t);
    static_assert (g_wordSize == LEN);

    const size_t *p1 = reinterpret_cast<const size_t *>(m_status);
    const size_t *p2 = reinterpret_cast<const size_t *>(st.m_status);

    for (char i=0; i<g_wordSize; ++i)
    {
        if (p1[i] != p2[i])
        {
            return false;
        }
    }

    return true;
}
