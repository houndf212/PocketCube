#include "pcStatusTree.h"
#include <assert.h>

using namespace pocket_cube;

static const pcStatusTree::innerNode_t *
_get_inner_node(const pcStatusTree::Node_t *pNode)
{
    return &pNode->second;
}

void pcStatusTree::make_reverse_rl(std::string &rl, const Node_t *pNode)
{
    auto p = _get_inner_node(pNode);
    while (p->m_parentNode)
    {
        auto r = to_opposite_rotate(p->m_fromRotate.m_rotate);
        rl += r;
        if (p->m_fromRotate.m_is180)
        {
            rl += r;
        }
        p = p->m_parentNode;
    }
}

size_t pcStatusTree::size() const
{
    return m_statusMap.size();
}

const pcStatusTree::Node_t *
pcStatusTree::find_status(const pcStatus &st) const
{
    auto it = m_statusMap.find(st);
    if (it == m_statusMap.end())
    {
        return nullptr;
    }

    return it.operator->();
}

const pcStatusTree::Node_t *
pcStatusTree::add_init(const pcStatus &st)
{
   auto ret = m_statusMap.try_emplace(st);
   assert(ret.second);

   innerNode_t &node = ret.first->second;
   node.m_parentNode = nullptr;
   node.m_level = 0;
   node.m_fromRotate = g_noneMove;

   return ret.first.operator->();
}

const pcStatusTree::Node_t *
pcStatusTree::try_add_status(
        const pcStatus &st,
        const Node_t *parentNode,
        pcNextMoveRotate rotate)
{
    assert(parentNode);

    auto ret = m_statusMap.try_emplace(st);
    if (false == ret.second)
    {
        return nullptr;
    }

    auto pInnerNode = _get_inner_node(parentNode);
    innerNode_t &node = ret.first->second;
    node.m_parentNode = pInnerNode;
    node.m_fromRotate = rotate;
    node.m_level = pInnerNode->m_level + 1;

   return ret.first.operator->();
}

const pcStatusTree::Node_t *
pcStatusTree::must_add_status(
        const pcStatus &st,
        const Node_t *parentNode,
        pcNextMoveRotate rotate)
{
    assert(parentNode);

    auto pInnerNode = _get_inner_node(parentNode);

    innerNode_t node;
    node.m_parentNode = pInnerNode;
    node.m_fromRotate = rotate;
    node.m_level      = pInnerNode->m_level + 1;

    auto ret = m_statusMap.emplace(st, node);
    assert(ret.second);

    return ret.first.operator->();
}
