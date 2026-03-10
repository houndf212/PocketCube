#pragma once

#include <unordered_map>
#include "pcStatus.h"
#include "pcRotate.h"

namespace pocket_cube {

class pcStatusTree
{
    pcStatusTree(const pcStatusTree &) = delete;
    pcStatusTree &operator=(const pcStatusTree &) = delete;
public:
    pcStatusTree() = default;

    struct innerNode_t
    {
        const innerNode_t *m_parentNode;
        pcNextMoveRotate   m_fromRotate;
        char               m_level;
    };
    static_assert (sizeof(innerNode_t) == 2 * sizeof(void*));

    using StatusMap = std::unordered_map<pcStatus, innerNode_t, pcStatusHash, pcStatusHash>;

    using Node_t = StatusMap::value_type;

    static void make_reverse_rl(std::string &rl, const Node_t *pNode);

    size_t size() const;

    const Node_t *
    find_status(const pcStatus &st) const;

    const Node_t *
    add_init(const pcStatus &st);

    const Node_t *
    try_add_status(const pcStatus &st, const Node_t *parentNode, pcNextMoveRotate rotate);

    const Node_t *
    must_add_status(const pcStatus &st, const Node_t *parentNode, pcNextMoveRotate rotate);

    auto iter_beg() const { return m_statusMap.begin(); }
    auto iter_end() const { return m_statusMap.end(); }
private:
    StatusMap m_statusMap;
};

}
