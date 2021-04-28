#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Number of individuals in each generation
#define POPULATION_SIZE 100
#define MAX_ITERATION 100	// максимальное число итераций
#define CROSSOVER_PROB  0.7f        //Pc - вероятность кроссинговера
#define MUTATIONRATE 0.3f   //вероятность мутации РМ
// Valid Genes
const string GENES = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

// Target string to be generated
const string TARGET = "МИР";

// Function to generate random numbers in given range
int random_num(int start, int end)
{
    int range = (end - start) + 1;
    int random_int = start + (rand() % range);
    return random_int;
}

// Create random genes for mutation
char mutated_genes()
{
    int len = GENES.size();
    int r = random_num(0, len - 1);
    return GENES[r];
}

// create chromosome or string of genes
string create_gnome()
{
    int len = TARGET.size();
    string gnome = "";
    for (int i = 0; i < len; i++)
        gnome += mutated_genes();
    return gnome;
}

// Class representing individual in population
class Individual
{
public:
    string chromosome;
    int fitness;
    Individual(string chromosome);
    Individual mutate();
    int cal_fitness();
};

Individual::Individual(string chromosome)
{
    this->chromosome = chromosome;
    fitness = cal_fitness();
};

Individual Individual::mutate() {
    string child_chromosome = "";
    int len = chromosome.size();
    for (int i = 0; i < len; i++) {
        child_chromosome += mutated_genes();
    }
    return Individual(child_chromosome);
};

// Calculate fittness score, it is the number of
// characters in string which differ from target
// string.
int Individual::cal_fitness()
{
    int len = TARGET.size();
    int fitness = 0;
    for (int i = 0; i < len; i++)
    {
        if (chromosome[i] != TARGET[i])
            fitness++;
    }
    return fitness;
};

// Overloading < operator
bool operator<(const Individual& ind1, const Individual& ind2)
{
    return ind1.fitness < ind2.fitness;
}

// Driver code
int main()
{
    setlocale(LC_ALL, "Russian");
    srand((unsigned)(time(0)));

    // current generation
    int generation = 0;

    vector<Individual> population;
    bool found = false;

    // create initial population
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        string gnome = create_gnome();
        population.push_back(Individual(gnome));
    }

    while (!found && generation <MAX_ITERATION)
    {
        // sort the population in increasing order of fitness score
        sort(population.begin(), population.end());

        // if the individual having lowest fitness score ie.
        // 0 then we know that we have reached to the target
        // and break the loop
        if (population[0].fitness <= 0)
        {
            found = true;
            break;
        }

        // Otherwise generate new offsprings for new generation
        vector<Individual> new_generation;

        // Perform Elitism, that mean 10% of fittest population
        // goes to the next generation
        int s = (10 * POPULATION_SIZE) / 100;
        for (int i = 0; i < s; i++)
            new_generation.push_back(population[i]);

        // From 50% of fittest population, Individuals
        // will mate to produce offspring
        s = POPULATION_SIZE/2;
        int k = 0;
        while (k<s)
        {
            
            int i = random_num(0, s-1);
            int j = random_num(0, s-1);

            Individual parent1 = population[i];
            Individual parent2 = population[j];
            Individual offspring1 = population[i], offspring2 = population[j];
            if (CROSSOVER_PROB > (random_num(0, 100) / 100)) {
                k += 2;
                int spos = rand() % TARGET.size()+1;
                offspring1 = parent1.chromosome.substr(0, spos) 
                    + parent2.chromosome.substr(spos, TARGET.size() - spos);
                offspring2 = parent2.chromosome.substr(0, spos)
                    + parent1.chromosome.substr(spos, TARGET.size() - spos);
            }
           
            if (MUTATIONRATE> (random_num(0, 100) / 100)){
                offspring1 = population[i].mutate();
                offspring2 = population[j].mutate();
            }
            new_generation.push_back(offspring1);
            new_generation.push_back(offspring2);
        }
        population = new_generation;
        cout << "Generation: " << generation << "\t";
        cout << "String: " << population[0].chromosome << "\t";
        cout << "Fitness: " << population[0].fitness << "\n";

        generation++;
    }
    cout << "Generation: " << generation << "\t";
    cout << "String: " << population[0].chromosome << "\t";
    cout << "Fitness: " << population[0].fitness << "\n";
}
