/*
 * -----------------------------------------------------------------------------
 * Copyright (C) Australian Semiconductor Technology Company (ASTC). 2010.
 * All Rights Reserved.
 *
 * This is unpublished proprietary source code of the Australian Semiconductor
 * Technology Company (ASTC).  The copyright notice does not evidence any actual
 * or intended publication of such source code.
 * -----------------------------------------------------------------------------
 */

/*
 * test.h
 * 
 * Header file for the helper class for testing.
 */
 
#ifndef __TEST_H_
#define __TEST_H_

// Test that a condition is satisfied - and log the test result.
#define TEST(cond) \
	_test_helper(cond, #cond, __FILE__, __LINE__, __FUNCTION__)

// Log a passed test.
#define PASS() _test_helper(1, "", __FILE__, __LINE__, __FUNCTION__)

// Log a failed test.
// msg is a NULL terminated char string describing the failure.
#define FAIL(msg) _test_helper(0, msg, __FILE__, __LINE__, __FUNCTION__)

// Output the test results based on _total_cnt and _fail_cnt
void print_test_results(void);

/** Test helper
 * NEVER CALL THIS. Use the test, pass and fail macros above.
 * This will ensure that the file, line and function are filled in correctly.
 * This will increment _total_cnt whenever called, and increment
 *  _fail_cnt if pass is zero.
 *
 * \param pass - indicates 1 for pass, 0 for fail
 * \param msg  - message string to print along with failure
 * \param file_name - log the file where failure occurred
 * \param line_num - log the line number where failure occurred
 * \param func_name - log the function name where failure occurred
 */
void _test_helper(int pass, const char* msg, const char* file_name,
                  int line_num, const char* func_name);

#endif /*__TEST_H_*/
