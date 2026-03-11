#include "pcIsoSolver.h"
#include <vector>
#include "pcStatusGen.h"
#include <assert.h>

using namespace pocket_cube;

template<bool Type180>
void pcIsoSolver::_build_iso_status_v3()
{
    assert(m_nodeTree.size() == 0);

    // improve speed by mul by some times
    m_nodeTree.reserve(g_iso_all_status_num * 2);

    using HashNodeVec = std::vector<const pcStatusTree::Node_t *>;
    HashNodeVec curLevel;
    HashNodeVec nextLevel;

    pcIsoArray isoBuffer;
    constexpr size_t g_isoBuffSize = isoBuffer.size();

    pcIsoNextArray90 nextBuffer90;
    pcIsoNextArray180 nextBuffer180;

    constexpr size_t g_buffSize = Type180 ?
                nextBuffer180.size() :
                nextBuffer90.size();

    const pcStatus *nextBuffer = Type180 ?
                nextBuffer180.cbegin() :
                nextBuffer90.cbegin();

    constexpr const pcNextMoveRotate *
            nextMoveRotatList = Type180 ?
                iso_next_mv_180::g_isoNextMoveList :
                iso_next_mv_90::g_isoNextMoveList;

    {
        pcStatus initSt;
        initSt.reset();

        auto pInitNode = m_nodeTree.add_init(initSt);
        assert(pInitNode);
        curLevel.push_back(pInitNode);
    }

    size_t nLevel = 0;
    while (false == curLevel.empty())
    {
        assert(nextLevel.empty());

        if (nLevel >= 14)
        {
            assert(m_level14.empty());
            m_level14 = curLevel;
        }

        const size_t nOldAll = m_nodeTree.size();

        const size_t nCurSize = curLevel.size();
        for (const pcStatusTree::Node_t *parentNode : curLevel)
        {
            const pcStatus &parentSt = parentNode->first;

            if constexpr (Type180)
            {
                pcStatusGen::gen_iso_next_180(&nextBuffer180, parentSt);
            }
            else
            {
                pcStatusGen::gen_iso_next_90(&nextBuffer90, parentSt);
            }

            for (size_t k=0; k<g_buffSize; ++k)
            {
                const pcStatus &nextSt = nextBuffer[k];

                if (pcStatusGen::is_iso_next_in_tree(&m_nodeTree, nextSt))
                {
                    continue;
                }

                pcNextMoveRotate rotate = nextMoveRotatList[k];
#if 0
                auto pNextNode = m_nodeTree.try_add_status(nextSt, parentNode, rotate);

                assert(pNextNode);
#else
                auto pNextNode = m_nodeTree.must_add_status(nextSt, parentNode, rotate);
#endif

                nextLevel.push_back(pNextNode);
            }
        }

        size_t nNextSize = nextLevel.size();
        size_t nNewAll = m_nodeTree.size();
        assert(nNewAll - nOldAll == nNextSize);

        double testSize = nCurSize * g_buffSize * g_isoBuffSize;
        assert(testSize >= nNextSize);
        double newRatio = nNextSize / testSize;

        printf("Level: %2ld, All: %8ld %8ld, Cur: %8ld, Next: %8ld %f \n",
               nLevel, nOldAll, nNewAll, nCurSize, nNextSize, newRatio);

        curLevel.swap(nextLevel);
        nextLevel.clear();
        ++nLevel;
    }

    constexpr size_t god_num = Type180 ? g_god_num_180 : g_god_num_90;
    if ( god_num != nLevel - 1 ||
         g_iso_all_status_num != m_nodeTree.size())
    {
        printf("Fatal: all iso status wrong!\n");
        abort();
    }
}

pcIsoSolver::pcIsoSolver()
{

}

void pcIsoSolver::build_status()
{
    constexpr bool b180 = false;
    _build_iso_status_v3<b180>();

#if 0
    if (false == _check_some_status())
    {
        ::abort();
    }

    if (false == _check_find_all_status())
    {
        ::abort();
    }
#endif

#if 0
    {
        std::string rl;
        pcMeetInMiddleSolver ms;
        for (auto pNode : m_level14)
        {
            auto b = ms.calc_solve(rl, pNode->first);
            assert(b);
        }
    }
#endif
}

bool pcIsoSolver::find_solve(
        std::string &rl,
        const pcStatus &st) const
{
    pcStatus isoSt;
    const iso::pcIsoRotateList *prefix = nullptr;
    auto pNode = pcStatusGen::find_iso_status(&isoSt, &prefix, &m_nodeTree, st);
    if (nullptr == pNode)
    {
        return false;
    }

    assert(nullptr != prefix);

    rl.clear();
    pcStatusTree::make_reverse_rl(rl, pNode);

    assert(0 == prefix->m_len % 2);

    for (size_t k=prefix->m_len; 0 != k; k-=2)
    {
        auto isoRotate = prefix->m_arr[k-1];
        for (char &rotate : rl)
        {
            rotate = iso::trans_mv_by_iso(isoRotate, rotate);
        }
    }

    return true;
}
