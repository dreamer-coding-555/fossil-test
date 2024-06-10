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
#ifndef FSCL_XMOCK_STUB_H
#define FSCL_XMOCK_STUB_H

#include "internal.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Stub object type
typedef struct xmock_stub {
    char *function_name;
    void **return_values;
    int32_t return_count;
    int32_t call_count;
    struct xmock_stub *next; // for chaining stubs
} xmock_stub_t;

/**
 * @brief Create a new stub object.
 *
 * This function creates a new stub object for a given function name.
 *
 * @param function_name The name of the function for which the stub object is created.
 * @return A pointer to the newly created stub object.
 */
xmock_stub_t* xmock_stub_create(const char *function_name);

/**
 * @brief Set the return values for the stub.
 *
 * This function sets the return values for the stub object. The number of return values
 * and the actual values are provided as arguments.
 *
 * @param stub The stub object for which the return values are set.
 * @param count The number of return values provided.
 * @param ... The return values to be set for the stub object.
 */
void xmock_stub_set_return_values(xmock_stub_t *stub, int32_t count, ...);

/**
 * @brief Simulate calling the stub function.
 *
 * This function simulates calling the stub function and returns the result.
 *
 * @param stub The stub object to be called.
 * @return The result of calling the stub function.
 */
void* xmock_stub_call(xmock_stub_t *stub);

/**
 * @brief Verify the number of times the stub function was called.
 *
 * This function verifies if the stub function was called the expected number of times.
 *
 * @param stub The stub object to be verified.
 * @param expected_call_count The expected number of times the stub function should have been called.
 * @return true if the stub function was called the expected number of times, false otherwise.
 */
bool xmock_stub_verify_call_count(xmock_stub_t *stub, int32_t expected_call_count);

/**
 * @brief Reset the stub object for reuse.
 *
 * This function resets the stub object, clearing any recorded calls and return values,
 * so that it can be reused.
 *
 * @param stub The stub object to be reset.
 */
void xmock_stub_reset(xmock_stub_t *stub);

/**
 * @brief Erase the stub object.
 *
 * This function erases the stub object, freeing any allocated memory.
 *
 * @param stub The stub object to be erased.
 */
void xmock_stub_erase(xmock_stub_t *stub);

#ifdef __cplusplus
}
#endif

#endif
