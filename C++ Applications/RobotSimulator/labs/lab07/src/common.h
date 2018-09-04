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
/**
 * @brief It defines the Macros that will be used in the Project.
 */
#define NAMESPACE_BEGIN(name) namespace name {
#define NAMESPACE_END(name) }

/* This should be placed in front of any variable defined but not used to
 * satisfy the compiler - otherwise a warning is given.
 */
#define __unused __attribute__((unused))

#endif /* SRC_COMMON_H_ */
