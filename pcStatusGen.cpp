#include "pcStatusGen.h"
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <unordered_set>
#include "pcStatusTree.h"

using namespace pocket_cube;

static constexpr const char * g_allRotate = "UuDdLlRrFfBb";
static constexpr size_t       g_rotateSize = ::strlen(g_allRotate);
static_assert (12 == g_rotateSize);

void
pcStatusGen::gen_rnd(
        pcStatus *st,
        std::string *rl,
        std::string *rv,
        std::random_device &rng)
{
    rl->clear();
    // god num is 11
    constexpr size_t g_max_rl = 50;

    size_t rlSize = rng() % g_max_rl;
    for(; rlSize != 0; --rlSize)
    {
        auto index = rng() % g_rotateSize;
        char ch = g_allRotate[index];
        rl->push_back(ch);
    }

    simplify_rotateList(*rl);
    *rv = get_reverse_rotateList(*rl);

    st->reset();

    for (auto ch : *rl)
    {
        st->rotate(ch);
    }

#ifndef NDEBUG
    {
        pcStatus test = *st;
        test.rotate_string(*rv);
        assert(test.isFinish());
    }
#endif
}

void pcStatusGen::gen_next(pcNextArray *nextArray, const pcStatus &start)
{
    assert (nextArray->size() == next_mv::g_nextMoveSize);

    for (size_t i=0; i<next_mv::g_nextMoveSize; ++i)
    {
        pcStatus &st = nextArray->operator[](i);
        st = start;
        st.rotate_next(next_mv::g_nextMoveList[i]);
    }

    //too slow in debug mode
    assert(check_status_is_diff(nextArray->begin(), nextArray->size()));
}

void pcStatusGen::gen_iso_next_180(pcIsoNextArray180 *nextIsoArray, const pcStatus &start)
{
    assert (nextIsoArray->size() == iso_next_mv_180::g_isoNextMoveSize);

    for (size_t i=0; i<nextIsoArray->size(); ++i)
    {
        pcStatus &st = nextIsoArray->operator[](i);
        st = start;
        st.rotate_next(iso_next_mv_180::g_isoNextMoveList[i]);
    }

#if 1
    assert(check_status_is_diff(nextIsoArray->begin(), nextIsoArray->size()));
    //too slow in debug mode
    assert(check_status_is_iso_diff(nextIsoArray->begin(), nextIsoArray->size()));
#endif
}

void pcStatusGen::gen_iso_next_90(pcIsoNextArray90 *nextIsoArray, const pcStatus &start)
{
    assert (nextIsoArray->size() == iso_next_mv_90::g_isoNextMoveSize);

    for (size_t i=0; i<nextIsoArray->size(); ++i)
    {
        pcStatus &st = nextIsoArray->operator[](i);
        st = start;
        st.rotate_next(iso_next_mv_90::g_isoNextMoveList[i]);
    }

#if 1
    assert(check_status_is_diff(nextIsoArray->begin(), nextIsoArray->size()));
    //too slow in debug mode
    assert(check_status_is_iso_diff(nextIsoArray->begin(), nextIsoArray->size()));
#endif
}

bool
pcStatusGen::is_iso_next_in_tree(const pcStatusTree *tree, const pcStatus &start)
{
    if (tree->find_status(start))
    {
        return true;
    }

    //skip first idle
    static_assert (0 == iso::g_isoList[0].m_len);

    constexpr size_t g_from1 = 1;
    for (size_t i=g_from1; i<iso::g_iso_size; ++i)
    {
        pcStatus stBuffer = start;
        stBuffer.rotate_frl(iso::g_isoList + i);

        if (tree->find_status(stBuffer))
        {
            return true;
        }
    }

    return false;
}

void pcStatusGen::gen_iso_status(pcIsoArray *isoArray, const pcStatus &start)
{
    assert(isoArray->size() == iso::g_iso_size);

    //skip first idle
    static_assert (0 == iso::g_isoList[0].m_len);
    *isoArray->begin() = start;

    constexpr size_t g_from1 = 1;
    for (size_t i=g_from1; i<iso::g_iso_size; ++i)
    {
        pcStatus &st = isoArray->operator[](i);
        st = start;
        st.rotate_frl(iso::g_isoList + i);
    }
}

bool pcStatusGen::contains_iso_status(
        const StatusSet *allSet,
        const pcStatus &st)
{
    if (allSet->contains(st))
    {
        return true;
    }

    //skip first idle
    static_assert (0 == iso::g_isoList[0].m_len);

    constexpr size_t g_from1 = 1;
    for (size_t i=g_from1; i<iso::g_iso_size; ++i)
    {
        pcStatus isoSt = st;
        isoSt.rotate_frl(iso::g_isoList + i);

        if (allSet->contains(isoSt))
        {
            return true;
        }
    }

    return false;
}

const pcStatusTree::Node_t *
pcStatusGen::find_iso_status(
        pcStatus *isoSt,
        const iso::pcIsoRotateList **prefRL,
        const pcStatusTree *tree,
        const pcStatus &st)
{
    auto pNode = tree->find_status(st);
    if (pNode)
    {
        *isoSt  = st;
        *prefRL = &iso::g_isoList[0];
        assert(0 == iso::g_isoList[0].m_len);
        return pNode;
    }

    constexpr size_t g_from1 = 1;
    for (size_t i=g_from1; i<iso::g_iso_size; ++i)
    {
        const iso::pcIsoRotateList *rl = iso::g_isoList +i;

        *isoSt = st;

        isoSt->rotate_frl(rl);

        pNode = tree->find_status(*isoSt);
        if (pNode)
        {
            *prefRL = rl;
            return pNode;
        }
    }

    return nullptr;
}


static bool
_check_make_set(
        pcStatusGen::StatusSet *s,
        const pcStatus *arr,
        size_t nLen)
{
    auto arr_end = arr + nLen;
    for (; arr != arr_end; ++arr)
    {
        auto ret = s->insert(*arr);
        if (false == ret.second)
        {
            return false;
        }
    }

    return true;
}

static bool
_check_not_in_set(
        const pcStatusGen::StatusSet *s,
        const pcStatus *beg,
        const pcStatus *end)
{
    for (; beg != end; ++beg)
    {
        if (s->contains(*beg))
        {
            return false;
        }
    }

    return true;
}

bool pcStatusGen::check_status_is_diff(const pcStatus *arr, size_t nLen)
{
    StatusSet s;
    return _check_make_set(&s, arr, nLen);
}

bool pcStatusGen::check_status_is_iso_diff(const pcStatus *arr, size_t nLen)
{
    StatusSet s;
    bool b = _check_make_set(&s, arr, nLen);
    if (false == b)
    {
        return false;
    }

    pcIsoArray isoArray;
    auto it  = arr;
    auto end = arr + nLen;
    for (; it != end; ++it)
    {
        gen_iso_status(&isoArray, *it);

        assert(isoArray.size() >= 1);
        assert(isoArray.front().equal(*it));

        if (false == _check_not_in_set(&s, isoArray.begin() + 1, isoArray.end()))
        {
            return false;
        }
    }

    return true;
}
