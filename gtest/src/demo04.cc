#include <stdio.h>

#include "demo04.h"

// Returns the current counter value, and increments it.
int Counter::Increment() {
    return counter_++;
}

// Prints the current counter value to STDOUT.
void Counter::Print() const {
    printf("%d", counter_);
}
