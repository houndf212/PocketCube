#include "rcGenStatus.h"
#include <assert.h>
#include <unordered_set>

using namespace rubik_cube;

bool rc_gen::check_status_diff(const rcStatus *pArr, size_t nLen)
{
    using StatusSet = std::unordered_set<rcStatus, rcStatusHash, rcStatusHash>;

    StatusSet s;
    for (size_t i=0; i<nLen; ++i)
    {
        auto ret = s.insert(pArr[i]);
        if (false == ret.second)
        {
            return false;
        }
    }

    return true;
}

void rc_gen::gen_next(
        rcNextArray *nextArray,
        const rcStatus &start)
{
    assert(nextArray->size() == rc_next_mv::g_nextMoveSize);

    for (char i=0; i<rc_next_mv::g_nextMoveSize; ++i)
    {
        rcStatus &st = nextArray->operator[](i);
        st = start;
        st.rotate_next(rc_next_mv::g_nextMoveList[i]);
    }
}
