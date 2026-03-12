#include <iostream>
#include <array>
#include <assert.h>
#include <unordered_set>
#include <vector>
#include "pcStatus.h"
#include "pcStatusGen.h"
#include "pcIsoSolver.h"
#include "pcMeetInMiddleSolver.h"
#include "rcStatus.h"
#include "rcMeetInMiddleSolver.h"

using namespace std;
using namespace pocket_cube;

using StatusSet = std::unordered_set<pcStatus, pcStatusHash, pcStatusHash>;
using StatusVec = std::vector<pcStatus>;

static void
_test_gen_rnd()
{
    pcStatus st;
    string rl;
    string rv;

    std::random_device rng;

    size_t k = 10000;
    for (size_t i=1; i<=k; ++i)
    {
        rl.clear();
        rv.clear();

        pcStatusGen::gen_rnd(&st, &rl, &rv, rng);

#ifndef NDEBUG
        {
            pcStatus test = st;
            test.rotate_string(rv);
            assert(test.isFinish());
        }
#endif
        printf("%ld gen rand: %s %s\n", i, rl.c_str(), rv.c_str());
        st.print();
    }
}

static void
_test_pc()
{
    printf("gen all status:\n");
    //_test_all_status();
    //_test_iso_all_status();

    std::random_device rng;

    pcIsoSolver solver;
    solver.build_status();

    //return ;

    pcMeetInMiddleSolver msolver;

#if 0

    printf("test gen rnd:\n");
    _test_gen_rnd();
#endif

    pcStatus st;
    st.reset();

    string rl;
    string rv;

    pcStatusGen::gen_rnd(&st, &rl, &rv, rng);
    printf("gen rand: %s %s\n", rl.c_str(), rv.c_str());
    st.print();

    char c;
    while ((c = getchar()))
    {
        switch (c)
        {
        case 'u' :
        case 'U' :
        case 'd' :
        case 'D' :
        case 'l' :
        case 'L' :
        case 'r' :
        case 'R' :
        case 'f' :
        case 'F' :
        case 'b' :
        case 'B' : st.rotate(c); break;
        case 'g':
        {
            st.reset();
            pcStatusGen::gen_rnd(&st, &rl, &rv, rng);
            printf("gen rand: %s %s\n", rl.c_str(), rv.c_str());
            break;
        }
        case 'i':
        {
            printf("input col:\n");
            char buffer[256] = {0};
            scanf("%s", buffer);
            string ss = buffer;
            printf("input str: %s\n", ss.c_str());
            if (false == st.fromString(ss))
            {
                printf("input error!\n");
                st.reset();
            }

            break;
        }
        case 's':
        {
            string srl;
            size_t n1 = 0;
            size_t n2 = 0;
            if (true)
            {
                bool isFind = solver.find_solve(srl, st);
                if (isFind)
                {
                    printf("A solve: %s %lu\n", srl.c_str(), srl.size());
                    n1 = srl.size();
                }
                else
                {
                    printf("Fatal: cannot solve:\n");
                    st.print();
                    std::abort();
                }
            }

            {
                bool isFind = msolver.calc_solve(srl, st);

                if (isFind)
                {
                    printf("M solve: %s %lu\n", srl.c_str(), srl.size());
                    n2 = srl.size();

                    assert(n1 == n2);
                }
                else
                {
                    printf("Fatal: cannot solve:\n");
                    st.print();
                    std::abort();
                }
            }
            continue;
        }
        default  : continue;
        }

        if (st.isFinish())
        {
            printf("*Done*\n");
        }

        st.print();
    }
}

static void
_test_rc()
{
    using namespace rubik_cube;

    //rcMeetInMiddleSolver solver;

    rcStatus st;
    st.reset();

    st.print();

    char c;
    while ((c = getchar()))
    {
        switch (c)
        {
        case 'u' :
        case 'U' :
        case 'd' :
        case 'D' :
        case 'l' :
        case 'L' :
        case 'r' :
        case 'R' :
        case 'f' :
        case 'F' :
        case 'b' :
        case 'B' : st.rotate(c); break;
        case 't':
        {
            printf("input test pattern: ");
            char buffer[256] = {0};
            scanf("%s", buffer);
            string ss = buffer;
            printf("input str: %s\n", ss.c_str());

            size_t cn = test_cycle_times(ss);
            printf("cycle times: %zu\n", cn);
            continue;
        }

        default  : continue;
        }

        if (st.isFinish())
        {
            printf("*Done*\n");
        }

        st.print();
    }
}

int main()
{
    _test_rc();

    return 0;
}
