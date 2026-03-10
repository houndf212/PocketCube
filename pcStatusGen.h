#pragma once

#include <array>
#include <string>
#include <unordered_set>
#include <random>
#include "pcStatus.h"
#include "pcRotate.h"
#include "pcStatusTree.h"

namespace pocket_cube {

using pcNextArray  = std::array<pcStatus, next_mv::g_nextMoveSize>;
using pcIsoNextArray180 = std::array<pcStatus, iso_next_mv_180::g_isoNextMoveSize>;
using pcIsoNextArray90  = std::array<pcStatus, iso_next_mv_90::g_isoNextMoveSize>;
using pcIsoArray   = std::array<pcStatus, iso::g_iso_size>;

namespace pcStatusGen {

using StatusSet = std::unordered_set<pcStatus, pcStatusHash, pcStatusHash>;

void
gen_rnd(pcStatus *st, std::string *rl, std::string *rv, std::random_device &rng);

void
gen_next(pcNextArray *nextArray, const pcStatus &start);

void
gen_iso_next_180(pcIsoNextArray180 *nextIsoArray, const pcStatus &start);

void
gen_iso_next_90(pcIsoNextArray90 *nextIsoArray, const pcStatus &start);

bool
is_iso_next_in_tree(const pcStatusTree *tree, const pcStatus &start);

const pcStatusTree::Node_t *
find_iso_status(
        pcStatus *isoSt,
        const iso::pcIsoRotateList **prefRL,
        const pcStatusTree *tree,
        const pcStatus &st);

void
gen_iso_status(pcIsoArray *isoArray, const pcStatus &start);

bool
contains_iso_status(const StatusSet *allSet, const pcStatus &st);

bool
check_status_is_diff(const pcStatus *arr, size_t nLen);

bool
check_status_is_iso_diff(const pcStatus *arr, size_t nLen);

}

}
