#pragma once

#include <array>
#include "rcRotate.h"
#include "rcStatus.h"

namespace rubik_cube {

namespace rc_gen {

using rcNextArray = std::array<rcStatus, rc_next_mv::g_nextMoveSize>;

bool
check_status_diff(const rcStatus *pArr, size_t nLen);

void
gen_next(rcNextArray *nextArray, const rcStatus &start);

}

}
