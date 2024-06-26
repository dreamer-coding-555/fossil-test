/*
==============================================================================
Author: Michael Gene Brockus (Dreamer)
Email: michaelbrockus@gmail.com
Organization: Fossil Logic
Description: 
    This file is part of the Fossil Logic project, where innovation meets
    excellence in software development. Michael Gene Brockus, also known as
    "Dreamer," is a dedicated contributor to this project. For any inquiries,
    feel free to contact Michael at michaelbrockus@gmail.com.
==============================================================================
*/
#ifndef FOSSIL_MOCK_INTERNAL_H
#define FOSSIL_MOCK_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "fossil/_common/common.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef bool (*fossil_mockup_comparator_t)(void *expected, void *actual);

// Mock object type
typedef struct mockup {
    char *function_name;
    void **expected_args;
    fossil_mockup_comparator_t *comparators;
    void **actual_args;
    int32_t num_args;
    void **return_values;
    int32_t return_count;
    int32_t call_count;
    bool called;
    struct mockup *next; // for chaining mocks
} fossil_mockup_t;

// Create a new mock object
/**
 * @brief Creates a new mock object with the specified function name and number of arguments.
 * 
 * @param function_name The name of the function being mocked.
 * @param num_args      The number of arguments expected by the function being mocked.
 * @return A pointer to the newly created mock object.
 */
fossil_mockup_t* fossil_mockup_create(const char *function_name, int32_t num_args);

// Set expected arguments for the mock
/**
 * @brief Sets the expected arguments for the specified mock object.
 * 
 * @param mock The mock object for which to set the expected arguments.
 * @param ...  The expected arguments in the format: arg1, arg2, ...
 */
void fossil_mockup_set_expected_args(fossil_mockup_t *mock, ...);

// Set a custom comparator for an argument
/**
 * @brief Sets a custom comparator for the specified argument of the mock object.
 * 
 * @param mock       The mock object for which to set the custom comparator.
 * @param arg_index  The index of the argument for which to set the custom comparator.
 * @param comparator The custom comparator function.
 */
void fossil_mockup_set_comparator(fossil_mockup_t *mock, int32_t arg_index, fossil_mockup_comparator_t comparator);

// Set the return values for the mock
/**
 * @brief Sets the return values for the specified mock object.
 * 
 * @param mock  The mock object for which to set the return values.
 * @param count The number of return values.
 * @param ...   The return values in the format: value1, value2, ...
 */
void fossil_mockup_set_return_values(fossil_mockup_t *mock, int32_t count, ...);

// Simulate calling the mock function
/**
 * @brief Simulates calling the specified mock object with the given arguments.
 * 
 * @param mock The mock object to call.
 * @param ...  The arguments to pass to the mock function.
 * @return The return value of the mock function.
 */
void* fossil_mockup_call(fossil_mockup_t *mock, ...);

// Verify that the mock was called with the expected arguments
/**
 * @brief Verifies that the specified mock object was called with the expected arguments.
 * 
 * @param mock The mock object to verify.
 * @return true if the mock was called with the expected arguments, false otherwise.
 */
bool fossil_mockup_verify(fossil_mockup_t *mock);

// Verify the number of times the mock function was called
/**
 * @brief Verifies the number of times the specified mock object was called.
 * 
 * @param mock               The mock object to verify.
 * @param expected_call_count The expected number of times the mock function should have been called.
 * @return true if the mock was called the expected number of times, false otherwise.
 */
bool fossil_mockup_verify_call_count(fossil_mockup_t *mock, int32_t expected_call_count);

// Reset the mock object for reuse
/**
 * @brief Resets the specified mock object for reuse.
 * 
 * @param mock The mock object to reset.
 */
void fossil_mockup_reset(fossil_mockup_t *mock);

// Erase the mock object
/**
 * @brief Erases the specified mock object.
 * 
 * @param mock The mock object to erase.
 */
void fossil_mockup_erase(fossil_mockup_t *mock);

// Built-in comparators for common data types
/**
 * @brief Comparator function for comparing two int32_t values.
 * 
 * @param expected The expected int32_t value.
 * @param actual   The actual int32_t value.
 * @return true if the values are equal, false otherwise.
 */
bool fossil_mockup_i32_comparator(void *expected, void *actual);

/**
 * @brief Comparator function for comparing two C-style strings.
 * 
 * @param expected The expected C-style string.
 * @param actual   The actual C-style string.
 * @return true if the strings are equal, false otherwise.
 */
bool fossil_mockup_cstr_comparator(void *expected, void *actual);

/**
 * @brief Comparator function for comparing two pointers.
 * 
 * @param expected The expected pointer.
 * @param actual   The actual pointer.
 * @return true if the pointers are equal, false otherwise.
 */
bool fossil_mockup_ptr_comparator(void *expected, void *actual);

/**
 * @brief Comparator function for comparing two pointers.
 * 
 * @param expected The expected pointer.
 * @param actual   The actual pointer.
 * @return true if the pointers are equal, false otherwise.
 */
void fossil_mockup_log(const char *format, ...);

/**
 * @def _FOSSIL_MOCK_FUNC
 * @brief Macro for creating a mock function with the specified return type, name, and parameters.
 * 
 * This macro simplifies the creation of mock functions by defining a function with the given return
 * type, name, and parameters. The function name will be prefixed with "fossil_mockup_" to clearly indicate
 * that it is a mock function.
 * 
 * @param return_type   The return type of the mock function.
 * @param name          The name of the mock function.
 * @param ...           The parameters of the mock function in the format: (type1 param1, type2 param2, ...).
 * @return The return type specified for the mock function.
 */
#define _FOSSIL_MOCK_FUNC(return_type, name, ...) \
    return_type fossil_mockup_##name(__VA_ARGS__)

/**
 * @def _FOSSIL_MOCK_ALIAS
 * @brief Macro for creating a type alias based on an existing type.
 * 
 * This macro creates a type alias for a given existing type.
 * 
 * @param new_type       The name of the new type alias.
 * @param existing_type  The existing type to create an alias for.
 */
#define _FOSSIL_MOCK_ALIAS(new_type, existing_type) \
    typedef existing_type fossil_mockup_##new_type##_type; \
    fossil_mockup_##new_type##_type fossil_mockup_##new_type(void)

/**
 * @def _FOSSIL_MOCK_STRUCT
 * @brief Macro for creating a mock struct with the specified name and members.
 * 
 * This macro simplifies the creation of mock structs by defining a struct with the given name
 * and members.
 * 
 * @param name  The name of the mock struct.
 * @param ...   The members of the mock struct in the format: type1 member1; type2 member2; ...
 */
#define _FOSSIL_MOCK_STRUCT(name, ...) \
    typedef struct { \
        __VA_ARGS__ \
    } fossil_mockup_##name;

#ifdef __cplusplus
}
#endif

#endif
