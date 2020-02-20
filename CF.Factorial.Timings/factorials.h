//
//  factorials.h
//  CF.Factorial.Timings
//
//  Created by Alan Sampson on 2/16/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//

//  MARK: - Setup and header includes
#pragma once
#ifndef factorials_h
#define factorials_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <string.h>

//  MARK: - Definitions.
uint64_t fact_u64_iterative(uint64_t, bool *);
uint64_t fact_u64_unrolled(uint64_t, bool *);
uint64_t fact_u64_recursive(uint64_t, bool *);
uint64_t fact_u64_tabular(uint64_t, bool *);

#endif /* factorials_h */
