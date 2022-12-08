#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *message;
} test_struct;

static void func () {
    printf ("%s", test->message)
}

int main () {
    test_struct test;
    test.message = "testing";

    func ()

    return 0;
}