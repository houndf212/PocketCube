#include "pcSolveTree.h"
#include <vector>

using namespace pocket_cube;

#if 0

pcSolveTree::pcSolveTree() {}

void pcSolveTree::build_graph()
{
    std::vector<const NodeType *> curVec;
    std::vector<const NodeType *> nextVec;

    auto pInit = _init();

    curVec.push_back(pInit);

    // while (false == curVec.empty())
    // {
    //     for (auto pSt : curVec)
    //     {
    //         pcStatus tmp = pSt->first;

    //         pcMove.m_hashNode = pSt;

    //         pcMove.m_rotate     = Col_Up;
    //         pcMove.m_bClockWise = true;
    //         tmp.rotate(pcMove.m_rotat, pcMove.m_bClockWis);

    //     }
    // }
}

const pcSolveTree::NodeType *
pcSolveTree::_try_add(const pcStatus &st, const pcMove &mv)
{
    auto ret = m_allStatMap.emplace(st, mv);
    if (false == ret.second)
    {
        return nullptr;
    }
}

const pcSolveTree::NodeType *
pcSolveTree::_init()
{
    pcStatus initStatus;
    initStatus.reset();

    pcMove nullMove;
    nullMove.m_hashNode = nullptr;

    auto ret = m_allStatMap.emplace(initStatus, nullMove);
    return ret.first.operator->();
}

#endif
