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
#ifndef FOSSIL_TEST_ASSUME_STRING_TYPE_H
#define FOSSIL_TEST_ASSUME_STRING_TYPE_H

#include <fossil/unittest.h> // using assurt rules from Fossil Test
#include <wchar.h>
#include <string.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

// Wide char string equality check
#define ASSUME_ITS_EQUAL_WSTR(actual, expected) \
    TEST_ASSUME(wcscmp((actual), (expected)) == 0, "Expected wide string " #actual " to be equal to " #expected)

#define ASSUME_NOT_EQUAL_WSTR(actual, expected) \
    TEST_ASSUME(wcscmp((actual), (expected)) != 0, "Expected wide string " #actual " to not be equal to " #expected)

// For length comparison
#define ASSUME_ITS_LENGTH_EQUAL_WSTR(actual, expected_len) \
    TEST_ASSUME(wcslen((actual)) == (expected_len), "Expected length of wide string " #actual " to be equal to " #expected_len)

// Byte string equality check
#define ASSUME_ITS_EQUAL_BSTR(actual, expected) \
    TEST_ASSUME(strcmp((const char*)(actual), (const char*)(expected)) == 0, "Expected byte string " #actual " to be equal to " #expected)

#define ASSUME_NOT_EQUAL_BSTR(actual, expected) \
    TEST_ASSUME(strcmp((const char*)(actual), (const char*)(expected)) != 0, "Expected byte string " #actual " to not be equal to " #expected)

// For length comparison
#define ASSUME_ITS_LENGTH_EQUAL_BSTR(actual, expected_len) \
    TEST_ASSUME(strlen((const char*)(actual)) == (expected_len), "Expected length of byte string " #actual " to be equal to " #expected_len)

// Classic C string equality check
#define ASSUME_ITS_EQUAL_CSTR(actual, expected) \
    TEST_ASSUME(strcmp((actual), (expected)) == 0, "Expected C string " #actual " to be equal to " #expected)

#define ASSUME_NOT_EQUAL_CSTR(actual, expected) \
    TEST_ASSUME(strcmp((actual), (expected)) != 0, "Expected C string " #actual " to not be equal to " #expected)

// For length comparison
#define ASSUME_ITS_LENGTH_EQUAL_CSTR(actual, expected_len) \
    TEST_ASSUME(strlen((actual)) == (expected_len), "Expected length of C string " #actual " to be equal to " #expected_len)

#ifdef __cplusplus
}
#endif

#endif
