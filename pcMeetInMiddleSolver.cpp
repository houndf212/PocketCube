#include "pcMeetInMiddleSolver.h"
#include "pcStatusGen.h"
#include <assert.h>

using namespace pocket_cube;

pcMeetInMiddleSolver::pcMeetInMiddleSolver()
{
    m_initLevel = 0;
    _init_finish_status();
    assert(1 == m_initLevel);
}

bool
pcMeetInMiddleSolver::calc_solve(
        std::string &rl, const pcStatus &st)
{
    // test in already in tree
    {
        auto pNode = m_initTree.find_status(st);
        if (pNode)
        {
            rl.clear();
            pcStatusTree::make_reverse_rl(rl, pNode);
            return true;
        }
    }

    pcStatusTree forwardTree;
    auto fNode = forwardTree.add_init(st);
    assert(fNode);

    HashNodeVec fCurLevel;
    HashNodeVec bufferLevel;

    fCurLevel.push_back(fNode);

    size_t otherLevel = 0;
    while (true)
    {
        if (otherLevel < m_initLevel)
        {
            ++otherLevel;
            bool b1 = _gen_next_level(&forwardTree, &fCurLevel, &bufferLevel, otherLevel, false);
            assert(b1);
            assert(fCurLevel.size() > 0);
        }
        else
        {
            ++m_initLevel;
            bool b1 = _gen_next_level(&m_initTree, &m_initCurLevel, &bufferLevel, m_initLevel, true);
            assert(b1);
            assert(m_initCurLevel.size() > 0);
        }

        const pcStatusTree::Node_t *fromNode = nullptr;
        auto initNode = _find_level_in_tree(fromNode, &m_initTree, &fCurLevel);
        if (initNode)
        {
            assert(fromNode);

            printf("Meet in (%lu) (%lu)\n", otherLevel, m_initLevel);

            std::string s1;
            pcStatusTree::make_reverse_rl(s1, fromNode);
            rl = get_reverse_rotateList(s1);
            pcStatusTree::make_reverse_rl(rl, initNode);
            return true;
        }
    }
}

void pcMeetInMiddleSolver::_init_finish_status()
{
    assert(0 == m_initTree.size());
    assert(0 == m_initCurLevel.size());

    pcIsoArray initArray;
    {
        pcStatus initSt;
        initSt.reset();

        pcStatusGen::gen_iso_status(&initArray, initSt);
    }

    for (const pcStatus &st : initArray)
    {
        auto pNode = m_initTree.add_init(st);
        m_initCurLevel.push_back(pNode);
    }

    HashNodeVec nextLevel;

    m_initTree.reserve(800 * 10000);

    constexpr size_t g_preLevel = 8;
    for (size_t level=0; level<g_preLevel; ++level)
    {
        bool b = _gen_next_level(&m_initTree, &m_initCurLevel, &nextLevel, level, true);
        if (false == b)
        {
            assert(m_initCurLevel.empty());
            break;
        }
    }

    m_initLevel = g_preLevel;
}

bool
pcMeetInMiddleSolver::_gen_next_level(
        pcStatusTree *statusTree,
        HashNodeVec *curLevel,
        HashNodeVec *nextLevel,
        size_t nLevel,
        bool isInitTree)
{
    if (curLevel->empty())
    {
        return false;
    }

    nextLevel->clear();

    pcNextArray nextBuffer;
    constexpr size_t g_buffSize = nextBuffer.size();

    const size_t nOldAll = statusTree->size();

    for (const pcStatusTree::Node_t *parentNode : *curLevel)
    {
        pcStatusGen::gen_next(&nextBuffer, parentNode->first);

        for (size_t k=0; k<g_buffSize; ++k)
        {
            const pcStatus &nextSt = nextBuffer[k];

            pcNextMoveRotate rotate = next_mv::g_nextMoveList[k];

            auto pNextNode = statusTree->try_add_status(nextSt, parentNode, rotate);
            if (nullptr == pNextNode)
            {
                continue;
            }

            nextLevel->push_back(pNextNode);
        }
    }

    size_t nCurSize = curLevel->size();
    size_t nNextSize = nextLevel->size();
    size_t nNewAll = statusTree->size();
    assert(nNewAll - nOldAll == nNextSize);

    double testSize = nCurSize * g_buffSize;
    assert(testSize >= nNextSize);
    double newRatio = nNextSize / testSize;

    if (isInitTree)
    {
        printf("%s Level: %2ld, All: %8ld %8ld, Cur: %8ld, Next: %8ld %f \n",
               (isInitTree ? "Init" : "Other"),
               nLevel, nOldAll, nNewAll, nCurSize, nNextSize, newRatio);
    }

    curLevel->swap(*nextLevel);

    return true;
}

const pcStatusTree::Node_t *
pcMeetInMiddleSolver::_find_level_in_tree(
        const pcStatusTree::Node_t *&fromNode,
        const pcStatusTree *tree,
        const HashNodeVec *levelVec)
{
    assert(tree->size() > 0);
    assert(levelVec->size() > 0);

    for (auto pNode : *levelVec)
    {
        auto p = tree->find_status(pNode->first);
        if (p)
        {
            fromNode = pNode;
            return p;
        }
    }

    return nullptr;
}
