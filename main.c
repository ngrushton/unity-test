#include <stdio.h>
#include "Unity/src/unity.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

static bool parse(const char *str, char *val1_string, char *val2_string, char *val3_string) {

    const int tokens = sscanf(str, "parse val1=%63s val2=%63s val3=%63s\r\n", val1_string, val2_string, val3_string);

    if (tokens != 3) {
        return false;
    }
    else
    {
        return true;
    }
}

static void check_parse(const char *input, const char *exp_val1, const char *exp_val2, const char *exp_val3) {

    char val1[64];
    char val2[64];
    char val3[64];
    const bool parsed = parse(input, val1, val2, val3);

    printf("Val1: %s\r\n", val1);
    printf("Val1: %s\r\n", val2);
    printf("Val2: %s\r\n", val3);

    TEST_ASSERT(parsed);
    TEST_ASSERT_EQUAL_STRING(exp_val1, val1);
    TEST_ASSERT_EQUAL_STRING(exp_val2, val2);
    TEST_ASSERT_EQUAL_STRING(exp_val3, val3);
}

static void test_parsing() {
    printf("\nTEST 1\n");
    check_parse("parse val1=Test val2=1234522 val3=we987y9A&Y)*&\r\n", "Test", "1234522", "we987y9A&Y)*&");
    printf("\nTEST 2\n");
    check_parse("parse val1=Liverpool val2=Premier-League val3=Champions\r\n", "Liverpool", "Premier-League", "Champions");
}

 int main() {
     UNITY_BEGIN();
     RUN_TEST(test_parsing);
     return UNITY_END();
 }