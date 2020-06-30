#include <stdio.h>
#include "Unity/src/unity.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

static bool config_parse(const char *str, char *key_string, char *value_string, char *request_string) {

    const int tokens = sscanf(str, "set-config key=%63s value=%63s request=%63s\r\n", key_string, value_string, request_string);

    if (tokens != 3) {
        return false;
    }
    else
    {
        return true;
    }
}

static void check_config_parse(const char *input, const char *exp_key, const char *exp_val, const char *exp_req) {
    // int bytes = -1;

    char key[64];
    char val[64];
    char req[64];
    const bool parsed = config_parse(input, key, val, req);

    printf("Key: %s\r\n", key);
    printf("Value: %s\r\n", val);
    printf("Req: %s\r\n", req);

    TEST_ASSERT(parsed);
    TEST_ASSERT_EQUAL_STRING(exp_key, key);
    TEST_ASSERT_EQUAL_STRING(exp_val, val);
    TEST_ASSERT_EQUAL_STRING(exp_req, req);
}

static void test_config_parsing() {
    printf("\nTEST 1\n");
    check_config_parse("set-config key=api.token value=12 request=25465\r\n", "api.token", "12", "25465");
    printf("\nTEST 2\n");
    check_config_parse("set-config key=api.token value=wfjjbihfd238rrwdf request=12345\r\n", "api.token", "wfjjbihfd238rrwdf", "12345");
}

 int main() {
     UNITY_BEGIN();
     RUN_TEST(test_config_parsing);
     return UNITY_END();
 }