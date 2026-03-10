#ifndef PCSOLVETREE_H
#define PCSOLVETREE_H

#include <unordered_map>
#include "pcStatus.h"

#if 0

namespace pocket_cube {

struct pcMove
{
    const void *m_hashNode;
    eSide      m_rotate;
    bool       m_bClockWise;

    bool is_finish_status() const
    {
        return nullptr == m_hashNode;
    }
};

struct pcMoveFrom
{
    pcMove m_fromList[6 * 2];
};

class pcSolveTree
{
public:
    pcSolveTree();

    void build_graph();
private:
    using StateMap = std::unordered_map<pcStatus, pcMove, pcStatusHash, pcStatusHash>;
    using NodeType = StateMap::value_type;
    const NodeType *_init();
    const NodeType *_try_add(const pcStatus &st, const pcMove &mv);
private:
    StateMap m_allStatMap;
};


}

#endif

#endif // PCSOLVETREE_H
