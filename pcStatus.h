#ifndef PCSTATUS_H
#define PCSTATUS_H

#include <stddef.h>
#include "pcDefine.h"
#include "pcRotate.h"

namespace pocket_cube {

class pcStatus final
{
public:
    void reset();

    bool fromString(const std::string &str);

    bool isFinish() const;

    void rotate(char ch);

    void rotate_next(pcNextMoveRotate nr);

    void rotate_string(const std::string &rl);

    void rotate_frl(const iso::pcIsoRotateList *frl);

    size_t calc_hash() const;

    bool equal(const pcStatus &st) const;

    void print() const;
private:
    char _t_col(char index) const;

    bool _isSameCol(const char *r1) const;

    template<bool TypeClockWise>
    void _rotate(side::eSide TypeSide);
private:
    char m_status[side::g_index_size];
};

struct pcStatusHash
{
    bool operator()(const pcStatus &st1, const pcStatus &st2) const noexcept
    {
        return st1.equal(st2);
    }

    size_t operator()(const pcStatus &st) const noexcept
    {
        return st.calc_hash();
    }
};

}

#endif // PCSTATUS_H
