#include "pcIsoSolver.h"
#include <assert.h>
#include "pcStatusGen.h"

using namespace pocket_cube;

static bool
_test_status(const char *pStr, const pcIsoSolver *solver)
{
    std::string str = pStr;
    pcStatus st;
    bool b1 = st.fromString(str);
    assert(b1);
    if (false == b1)
    {
        return false;
    }

    std::string rl;
    bool b2 = solver->find_solve(rl, st);
    if (false == b2)
    {
        printf("unsolve: %s\n", str.c_str());
        return false;
    }

    return true;
}

bool pcIsoSolver::_check_some_status() const
{
    return _test_status("OWORROOGWYGYBRGBBWYWBGRY", this);
}

static bool
_test_solve(std::string &rl, const pcIsoSolver *solver, const pcStatus &st)
{
    bool b = solver->find_solve(rl, st);
    if (false == b)
    {
        printf("ERROR: cannot find: \n");
        st.print();
        return false;
    }

    pcStatus stBuffer = st;
    stBuffer.rotate_string(rl);

    if (false == stBuffer.isFinish())
    {
        printf("ERROR: cannot solve: \n");
        st.print();
        return false;
    }

    return true;
}

bool pcIsoSolver::_check_find_all_status() const
{
    printf("Start Check All: %lu\n", m_nodeTree.size());

    size_t nChecked = 0;

    auto it  = m_nodeTree.iter_beg();
    auto end = m_nodeTree.iter_end();

    std::string rl;
    pcIsoArray isoBuffer;

    for (; it != end; ++it)
    {
        const pcStatus &st = it->first;
        {
            // dircet find
            auto pNode = m_nodeTree.find_status(st);
            if (nullptr == pNode)
            {
                printf("ERROR: cannot direct find: \n");
                st.print();
                return false;
            }

            pcStatusGen::gen_iso_status(&isoBuffer, st);

            if (false == st.equal(isoBuffer.front()))
            {
                printf("ERROR: iso first not equal: \n");
                return false;
            }

            auto isoIt  = isoBuffer.begin() + 1;
            auto isoEnd = isoBuffer.end();
            for (; isoIt != isoEnd; ++isoIt)
            {
                pNode = m_nodeTree.find_status(*isoIt);
                if (nullptr != pNode)
                {
                    printf("ERROR: find other iso status: \n");
                    isoIt->print();
                    return false;
                }
            }

            for (const pcStatus &isoSt : isoBuffer)
            {
                bool b = _test_solve(rl, this, isoSt);
                if (false == b)
                {
                    return false;
                }
            }
        }

        nChecked++;
        if (0 == (nChecked % 10000))
        {
            printf("Checked: %lu\n", nChecked);
        }
    }

    printf("Checked: %lu\n", nChecked);

    return true;
}
