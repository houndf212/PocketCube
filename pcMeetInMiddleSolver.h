#pragma once

#include <string>
#include <vector>
#include "pcStatus.h"
#include "pcStatusTree.h"

namespace pocket_cube {

class pcMeetInMiddleSolver
{
    pcMeetInMiddleSolver(const pcMeetInMiddleSolver &) = delete;
    pcMeetInMiddleSolver &operator=(const pcMeetInMiddleSolver &) = delete;
public:
    pcMeetInMiddleSolver();

    // inc solve, so cannot be const
    bool calc_solve(std::string &rl, const pcStatus &st);
private:
    void _init_finish_status();

    using HashNodeVec = std::vector<const pcStatusTree::Node_t *>;

    static bool
    _gen_next_level(pcStatusTree *statusTree,
                    HashNodeVec *curLevel,
                    HashNodeVec *nextLevel,
                    size_t nLevel, bool isInitTree);

   const pcStatusTree::Node_t *
   _find_level_in_tree(const pcStatusTree::Node_t *&fromNode,
                       const pcStatusTree *tree,
                       const HashNodeVec *levelVec);
private:
    pcStatusTree m_initTree;
    HashNodeVec  m_initCurLevel;
    size_t       m_initLevel;
};

}
