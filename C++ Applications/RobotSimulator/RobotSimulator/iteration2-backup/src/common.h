/**
 * @file common.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define NAMESPACE_BEGIN(name) namespace name {
#define NAMESPACE_END(name) }

// This should be placed in front of any variable defined but not used to
// satisfy the compiler - otherwise a warning is given.
#define __unused __attribute__((unused))
/**
 * @brief Position structor is used for representing entities' position.
 *
 */


#endif  // SRC_COMMON_H_
