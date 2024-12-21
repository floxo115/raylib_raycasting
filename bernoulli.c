#include "bernoulli.h"
#include <stdio.h>
#include <stdlib.h> // For rand()
#include <time.h>   // For seeding rand()

// Function to generate a Bernoulli random variable
int bernoulli(double p) {
    // Validate that the probability is in the range [0, 1]
    if (p < 0.0 || p > 1.0) {
        fprintf(stderr, "Error: Probability must be between 0 and 1.\n");
        exit(EXIT_FAILURE);
    }

    // Generate a random number in the range [0, 1]
    double random_value = (double) rand() / RAND_MAX;

    // Return 1 with probability p, 0 otherwise
    return random_value < p ? 1 : 0;
}
