#include "rcMeetInMiddleSolver.h"
#include <assert.h>
#include "rcGenStatus.h"

using namespace rubik_cube;

rcMeetInMiddleSolver::rcMeetInMiddleSolver()
{
    m_initLevel = 0;
    _init_finish_status();
    assert(1 == m_initLevel);
}

bool
rcMeetInMiddleSolver::calc_solve(
        std::string &rl, const rcStatus &st)
{
    // test in already in tree
    {
        auto pNode = m_initTree.find_status(st);
        if (pNode)
        {
            rl.clear();
            rcStatusTree::make_reverse_rl(rl, pNode);
            return true;
        }
    }

    rcStatusTree forwardTree;
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

        const rcStatusTree::Node_t *fromNode = nullptr;
        auto initNode = _find_level_in_tree(fromNode, &m_initTree, &fCurLevel);
        if (initNode)
        {
            assert(fromNode);

            printf("Meet in (%lu) (%lu)\n", otherLevel, m_initLevel);

            std::string s1;
            rcStatusTree::make_reverse_rl(s1, fromNode);
            rl = get_reverse_rotateList(s1);
            rcStatusTree::make_reverse_rl(rl, initNode);
            return true;
        }
    }
}

void rcMeetInMiddleSolver::_init_finish_status()
{
    assert(0 == m_initTree.size());
    assert(0 == m_initCurLevel.size());

    rcStatus initSt;
    initSt.reset();

    auto pNode = m_initTree.add_init(initSt);
    m_initCurLevel.push_back(pNode);

    HashNodeVec nextLevel;

    constexpr size_t g_preLevel = 10;
    for (size_t level=0; level<g_preLevel; ++level)
    {
        bool b = _gen_next_level(&m_initTree, &m_initCurLevel, &nextLevel, level, true);
        assert(b);
        assert(false == m_initCurLevel.empty());
    }

    m_initLevel = g_preLevel;
}

bool
rcMeetInMiddleSolver::_gen_next_level(
        rcStatusTree *statusTree,
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

    rc_gen::rcNextArray nextBuffer;
    constexpr size_t g_buffSize = nextBuffer.size();

    const size_t nOldAll = statusTree->size();

    for (const rcStatusTree::Node_t *parentNode : *curLevel)
    {
        rc_gen::gen_next(&nextBuffer, parentNode->first);

        for (size_t k=0; k<g_buffSize; ++k)
        {
            const rcStatus &nextSt = nextBuffer[k];

            rcNextMoveRotate rotate = rc_next_mv::g_nextMoveList[k];

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
        printf("%s Level: %2ld, All: %12ld %12ld, Cur: %12ld, Next: %12ld %f \n",
               (isInitTree ? "Init" : "Other"),
               nLevel, nOldAll, nNewAll, nCurSize, nNextSize, newRatio);
    }

    curLevel->swap(*nextLevel);

    return true;
}

const rcStatusTree::Node_t *
rcMeetInMiddleSolver::_find_level_in_tree(
        const rcStatusTree::Node_t *&fromNode,
        const rcStatusTree *tree,
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

size_t
rubik_cube::test_cycle_times(const std::string &rl)
{
    rcStatus st;
    st.reset();

    assert(st.isFinish());

    size_t n = 0;
    do {
        ++n;
        st.rotate_string(rl);

    } while (false == st.isFinish());

    return n;
}
