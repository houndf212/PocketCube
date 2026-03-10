#pragma once

#include <string>
#include <vector>
#include "pcStatusTree.h"

namespace pocket_cube {

class pcIsoSolver
{
    pcIsoSolver(const pcIsoSolver &) = delete;
    pcIsoSolver &operator=(const pcIsoSolver &) = delete;
public:
    pcIsoSolver();

    void build_status();

    bool find_solve(std::string &rl, const pcStatus &st) const;
private:

    template<bool Type180>
    void _build_iso_status_v3();

    bool _check_some_status() const;

    bool _check_find_all_status() const;

    std::string get_solve_rl(const pcStatus &st) const;
private:
    pcStatusTree m_nodeTree;
    std::vector<const pcStatusTree::Node_t *> m_level14;
};

}
