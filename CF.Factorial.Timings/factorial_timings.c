//
//  main.c
//  CF.Factorial.Timings
//
//  Created by Alan Sampson on 2/16/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//

//  MARK: - Setup and header includes
//  TODO: Timing tool. Choose just one!
#define GETRUSAGE_  /* use getrusage()    */
#undef  GETTOD_     /* use gettimeofday() */
#undef  CLOCK_      /* use clock()        */

//  TODO: timings tool selector
#if defined(CLOCK_)
# include <time.h>
#endif
#if defined(GETTOD_)
# include <sys/time.h>
#endif
#if defined(GETRUSAGE_)
# include <sys/resource.h>
#endif

#include "factorials.h"

//  MARK: - Definitions.
static
void flush_environment_loop(size_t const);
static
void flush_environment_recurse(size_t const, size_t);

typedef uint64_t (* factorial)(uint64_t, bool *);

//  MARK: Structure and typedef 'facs'
struct facs {
  factorial fp;
  char description[20];
};
typedef struct facs facs;

//  MARK: - Implementation.
/*
 *  MARK: main()
 */
int main(int argc, const char * argv[]) {

  printf("CF.Factorial.Timings\n");
#ifdef __STDC_VERSION__
  printf("C Version: %ld\n", __STDC_VERSION__);
#endif

  //  set up table of pointers to factorial calculator functions
  facs ffuns[] = {
    { .fp = fact_u64_iterative, .description = "Iterative", },
    { .fp = fact_u64_recursive, .description = "Recursive", },
    { .fp = fact_u64_unrolled,  .description = "Unrolled",  },
    { .fp = fact_u64_tabular,   .description = "Tabular",   },
  };
  size_t ffuns_c = sizeof(ffuns) / sizeof(*ffuns);

  //  timing loop iteration count
  size_t iters = 5000000;
  size_t iters_flush = 174000;  //  TODO: understand that recursion chokes > 174,000

  //  clear out the pipes and get the system rollong.
  flush_environment_loop(iters_flush);
  flush_environment_recurse(iters_flush, 0);

  //  TODO: timings tool selector
#if defined(GETTOD_)
  struct timeval tv1, tv2;
#endif
#if defined(CLOCK_)
  clock_t tc1, tc2;
#endif
#if defined(GETRUSAGE_)
  struct rusage rusage1, rusage2;
#endif

  uint64_t shriek_result = 0;

  //  loop over factorial functions table
  for (size_t fx = 0; fx < ffuns_c; ++fx) {
    facs ffx = ffuns[fx];

//  TODO: timings tool selector
#if defined(GETTOD_)
    gettimeofday(&tv1, NULL);
#endif
#if defined(CLOCK_)
    tc1 = clock();
#endif
#if defined(GETRUSAGE_)
    getrusage(RUSAGE_SELF, &rusage1);
#endif

    bool overflow = false;
    //  timed loop. loops for the specified count of iterations
    for (size_t t_ = 0; t_ < iters; ++t_) {
      //  call the factorial calculator
      shriek_result = ffx.fp(20, &overflow);
    }

//  TODO: timings tool selector
#if defined(GETRUSAGE_)
    getrusage(RUSAGE_SELF, &rusage2);
#endif
#if defined(CLOCK_)
    tc2 = clock();
#endif
#if defined(GETTOD_)
    gettimeofday(&tv2, NULL);
#endif

    char const * bof = overflow ? "true" : "false";

    printf("%s:\n", ffx.description);
    printf("  20!: %20" PRIu64 ", overflow: %s\n", shriek_result, bof);

//  TODO: timings tool selector
#if defined(GETTOD_)
    double clock_count;
    clock_count =
      (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
      (double) (tv2.tv_sec  - tv1.tv_sec);
    printf("  Total time = %10.6f s\n", clock_count);
#endif

//  TODO: timings tool selector
#if defined(CLOCK_)
    double ctime_diff;
    ctime_diff = (double) (tc2 - tc1) / CLOCKS_PER_SEC;
    printf("  CPU Time   = %10.6f s\n", ctime_diff);
#endif

//  TODO: timings tool selector
#if defined(GETRUSAGE_)
    double rtval_diffu;
    double rtval_diffs;
    double rtval_diff;
    rtval_diffu =
      (double) (rusage2.ru_utime.tv_usec - rusage1.ru_utime.tv_usec) / 1000000 +
      (double) (rusage2.ru_utime.tv_sec  - rusage1.ru_utime.tv_sec);
    rtval_diffs =
      (double) (rusage2.ru_stime.tv_usec - rusage1.ru_stime.tv_usec) / 1000000 +
      (double) (rusage2.ru_stime.tv_sec  - rusage1.ru_stime.tv_sec);
    rtval_diff = rtval_diffs + rtval_diffu;

    printf("  CPU Time   = %10.6f s\n", rtval_diff);
#endif
  }

  return EXIT_SUCCESS;
}

//  MARK: - Static function implementations
/*
 *  MARK: flush_environment_loop()
 *
 *  Burn some cycles. Iteratively.
 */
static
void flush_environment_loop(size_t const max) {

  int32_t xx[max];
  for (int32_t x_ = 0; x_ < max; ++x_) {
    xx[x_] = x_;
  }

  return;
}

/*
 *  MARK: flush_environment_recurse()
 *
 *  Burn some cycles. Recursive.
 */
static
void flush_environment_recurse(size_t const max, size_t limit) {

  size_t xx;
  if (max > limit) {
    xx = limit;
    flush_environment_recurse(max, limit + 1);
  }

  return;
}
