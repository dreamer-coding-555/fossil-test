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
#include "fossil/mockup/output.h"
#include <string.h>

fossil_mockup_output_t* fossil_mockup_output_create(const char *function_name) {
    fossil_mockup_output_t *output = (fossil_mockup_output_t *)malloc(sizeof(fossil_mockup_output_t));
    if (output == NULL) {
        perror("Failed to allocate memory for output mock");
        exit(EXIT_FAILURE);
    }
    output->function_name = _custom_fossil_test_strdup(function_name);
    output->captured_outputs = NULL;
    output->output_count = 0;
    output->call_count = 0;
    output->next = NULL;
    return output;
}

void fossil_mockup_output_capture(fossil_mockup_output_t *output, const char *captured_output) {
    output->call_count++;
    output->captured_outputs = (char **)realloc(output->captured_outputs, output->call_count * sizeof(char *));
    output->captured_outputs[output->call_count - 1] = _custom_fossil_test_strdup(captured_output);
    output->output_count = output->call_count;
}

bool fossil_mockup_output_verify(fossil_mockup_output_t *output, const char *expected_output, int32_t call_index) {
    if (call_index < 0 || call_index >= output->call_count) {
        fprintf(stderr, "Invalid call index %d for function '%s'\n", call_index, output->function_name);
        return false;
    }
    return strcmp(output->captured_outputs[call_index], expected_output) == 0;
}

bool fossil_mockup_output_verify_call_count(fossil_mockup_output_t *output, int32_t expected_call_count) {
    if (output->call_count != expected_call_count) {
        fprintf(stderr, "Output function '%s' was called %d times, expected %d times\n",
                output->function_name, output->call_count, expected_call_count);
        return false;
    }
    return true;
}

void fossil_mockup_output_reset(fossil_mockup_output_t *output) {
    for (int32_t i = 0; i < output->call_count; i++) {
        free(output->captured_outputs[i]);
    }
    free(output->captured_outputs);
    output->captured_outputs = NULL;
    output->call_count = 0;
    output->output_count = 0;
}

void fossil_mockup_output_erase(fossil_mockup_output_t *output) {
    fossil_mockup_output_reset(output);
    free(output->function_name);
    free(output);
}
