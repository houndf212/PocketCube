#pragma once

#include <string>
#include <vector>
#include "rcStatus.h"
#include "rcStatusTree.h"

namespace rubik_cube {

class rcMeetInMiddleSolver
{
    rcMeetInMiddleSolver(const rcMeetInMiddleSolver &) = delete;
    rcMeetInMiddleSolver &operator=(const rcMeetInMiddleSolver &) = delete;
public:
    rcMeetInMiddleSolver();

    // inc solve, so cannot be const
    bool calc_solve(std::string &rl, const rcStatus &st);
private:
    void _init_finish_status();

    using HashNodeVec = std::vector<const rcStatusTree::Node_t *>;

    static bool
    _gen_next_level(rcStatusTree *statusTree,
                    HashNodeVec *curLevel,
                    HashNodeVec *nextLevel,
                    size_t nLevel, bool isInitTree);

   static const rcStatusTree::Node_t *
   _find_level_in_tree(const rcStatusTree::Node_t *&fromNode,
                       const rcStatusTree *tree,
                       const HashNodeVec *levelVec);
private:
    rcStatusTree m_initTree;
    HashNodeVec  m_initCurLevel;
    size_t       m_initLevel;
};

size_t
test_cycle_times(const std::string &rl);

}
