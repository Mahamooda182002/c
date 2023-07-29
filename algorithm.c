#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POPULATION_SIZE 10
#define GENERATIONS 100
#define MUTATION_RATE 0.1

// Function to evaluate the fitness of an individual
double evaluateFitness(double x) {
    return -x * x + 4 * x;
}

// Function to generate a random number within a specified range
double randomDouble(double min, double max) {
    return min + (max - min) * ((double)rand() / (double)RAND_MAX);
}

// Function to perform mutation on an individual
void mutate(double *x) {
    if (rand() < MUTATION_RATE * RAND_MAX) {
        *x = randomDouble(0, 4); // Change the value randomly within the range [0, 4]
    }
}

int main() {
    srand(time(0)); // Seed the random number generator

    double population[POPULATION_SIZE];

    // Initialize the population with random values within the range [0, 4]
    for (int i = 0; i < POPULATION_SIZE; i++) {
        population[i] = randomDouble(0, 4);
    }

    // Main evolution loop
    for (int generation = 0; generation < GENERATIONS; generation++) {
        // Evaluate the fitness of each individual
        double fitness[POPULATION_SIZE];
        for (int i = 0; i < POPULATION_SIZE; i++) {
            fitness[i] = evaluateFitness(population[i]);
        }

        // Find the best individual in this generation
        double best_fitness = fitness[0];
        double best_individual = population[0];
        for (int i = 1; i < POPULATION_SIZE; i++) {
            if (fitness[i] > best_fitness) {
                best_fitness = fitness[i];
                best_individual = population[i];
            }
        }

        printf("Generation %d: Best individual: x = %lf, fitness = %lf\n", generation, best_individual, best_fitness);

        // Create the next generation using crossover and mutation
        double next_population[POPULATION_SIZE];
        for (int i = 0; i < POPULATION_SIZE; i++) {
            // Select two parents based on fitness (simple tournament selection in this case)
            int parent1 = rand() % POPULATION_SIZE;
            int parent2 = rand() % POPULATION_SIZE;

            if (fitness[parent1] > fitness[parent2]) {
                next_population[i] = population[parent1];
            } else {
                next_population[i] = population[parent2];
            }

            // Perform mutation on the new individual
            mutate(&next_population[i]);
        }

        // Replace the old population with the new one
        for (int i = 0; i < POPULATION_SIZE; i++) {
            population[i] = next_population[i];
        }
    }

    return 0;
}
