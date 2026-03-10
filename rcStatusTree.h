#pragma once

#include <unordered_map>
#include "rcStatus.h"
#include "rcRotate.h"

namespace rubik_cube {

class rcStatusTree
{
    rcStatusTree(const rcStatusTree &) = delete;
    rcStatusTree &operator=(const rcStatusTree &) = delete;
public:
    rcStatusTree() = default;

    struct innerNode_t
    {
        const innerNode_t *m_parentNode;
        rcNextMoveRotate   m_fromRotate;
        char               m_level;
    };
    static_assert (sizeof(innerNode_t) == 2 * sizeof(void*));

    using StatusMap = std::unordered_map<rcStatus, innerNode_t, rcStatusHash, rcStatusHash>;

    using Node_t = StatusMap::value_type;

    static void make_reverse_rl(std::string &rl, const Node_t *pNode);

    size_t size() const;

    const Node_t *
    find_status(const rcStatus &st) const;

    const Node_t *
    add_init(const rcStatus &st);

    const Node_t *
    try_add_status(const rcStatus &st, const Node_t *parentNode, rcNextMoveRotate rotate);

    const Node_t *
    must_add_status(const rcStatus &st, const Node_t *parentNode, rcNextMoveRotate rotate);

    auto iter_beg() const { return m_statusMap.begin(); }
    auto iter_end() const { return m_statusMap.end(); }
private:
    StatusMap m_statusMap;
};

}
