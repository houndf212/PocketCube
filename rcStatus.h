#pragma once

#include <string>
#include "rcDefine.h"
#include "rcRotate.h"

namespace rubik_cube {

class rcStatus
{
public:
    void reset();

    bool fromString(const std::string &str);

    bool isFinish() const;

    void rotate(char ch);

    void rotate_next(rcNextMoveRotate nr);

    void rotate_string(const std::string &rl);

    size_t calc_hash() const;

    bool equal(const rcStatus &st) const;

    void print() const;
private:
    char _t_col(char index) const;

    template<bool TypeClockWise>
    void _rotate(ns_side::eSide TypeSide);
private:
    char m_status[ns_side::g_index_size];
};

struct rcStatusHash
{
    bool operator()(const rcStatus &st1, const rcStatus &st2) const noexcept
    {
        return st1.equal(st2);
    }

    size_t operator()(const rcStatus &st) const noexcept
    {
        return st.calc_hash();
    }
};

}
