#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Number of individuals in each generation
#define POPULATION_SIZE 100

// Valid Genes
const string GENES = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

// Target string to be generated
const string TARGET = "Я большой мальчик";

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
    Individual mate(Individual parent2);
    int cal_fitness();
};

Individual::Individual(string chromosome)
{
    this->chromosome = chromosome;
    fitness = cal_fitness();
};

// Perform mating and produce new offspring
Individual Individual::mate(Individual par2)
{
    // chromosome for offspring
    string child_chromosome = "";

    int len = chromosome.size();
    for (int i = 0; i < len; i++)
    {
        // random probability
        float p = random_num(0, 100) / 100;

        // if prob is less than 0.45, insert gene
        // from parent 1
        if (p < 0.45)
            child_chromosome += chromosome[i];

        // if prob is between 0.45 and 0.90, insert
        // gene from parent 2
        else if (p < 0.90)
            child_chromosome += par2.chromosome[i];

        // otherwise insert random gene(mutate),
        // for maintaining diversity
        else
            child_chromosome += mutated_genes();
    }

    // create new Individual(offspring) using
    // generated chromosome for offspring
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

    // create initial population  (ГЕНЕНРАЦИЯ ИСХОДНОГО ПОКОЛЕНИЯ)
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        string gnome = create_gnome();
        population.push_back(Individual(gnome));
    }

    while (!found)
    {
        // sort the population in increasing order of fitness score
        sort(population.begin(), population.end());

        // if the individual having lowest fitness score ie.
        // 0 then we know that we have reached to the target
        // and break the loop  (ПРОВЕРКА НАХОЖДЕНИЯ НУЖНОГО СЛОВА)
        if (population[0].fitness <= 0)
        {
            found = true;
            break;
        }

        // Otherwise generate new offsprings for new generation
        vector<Individual> new_generation;

        // Perform Elitism, that mean 10% of fittest population
        // goes to the next generation (СЕЛЕКЦИЯ)
        int s = (10 * POPULATION_SIZE) / 100;
        for (int i = 0; i < s; i++)
            new_generation.push_back(population[i]);

        // From 50% of fittest population, Individuals
        // will mate to produce offspring
        s = (90 * POPULATION_SIZE) / 100;
        for (int i = 0; i < s; i++)
        {
            int len = population.size();
            int r = random_num(0, 50);
            Individual parent1 = population[r];
            r = random_num(0, 50);
            Individual parent2 = population[r];
            Individual offspring = parent1.mate(parent2);
            new_generation.push_back(offspring);
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


// ис2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*#include <iostream>					// для cout и т.п.
#include <vector>					// для класса vector
#include <string>					// для класса string
#include <algorithm>					// для алгоритма сортировки
#include <time.h>					// для случайных величин
#include <math.h>					// для abs()
#include <Windows.h>

#define GA_POPSIZE		2048		// размер популяции
#define GA_MAXITER		16384		// максимальное число итераций
#define GA_ELITRATE		0.10f		// элитарность
#define GA_MUTATIONRATE	0.25f			// мутации
#define GA_MUTATION		RAND_MAX * GA_MUTATIONRATE
#define GA_TARGET		std::string("МИР")

using namespace std;

struct ga_struct
{
	string str;						// строка
	unsigned int fitness;					// пригодность
};

typedef vector<ga_struct> ga_vector;			// для краткости

void init_population(ga_vector& population,
	ga_vector& buffer)
{
	int tsize = GA_TARGET.size();
	//setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	for (int i = 0; i < GA_POPSIZE; i++) {
		ga_struct citizen;

		citizen.fitness = 0;
		citizen.str.erase();

		for (int j = 0; j < tsize; j++) 
			citizen.str += (rand() % 128) + 128;
			
		population.push_back(citizen);
	}

	buffer.resize(GA_POPSIZE);
}

void calc_fitness(ga_vector& population)
{
	string target = GA_TARGET;
	int tsize = target.size();
	unsigned int fitness;

	for (int i = 0; i < GA_POPSIZE; i++) {
		fitness = 0;
		for (int j = 0; j < tsize; j++) {
			fitness += abs(int(population[i].str[j] - target[j]));
		}

		population[i].fitness = fitness;
	}
}

bool fitness_sort(ga_struct x, ga_struct y)
{
	return (x.fitness < y.fitness);
}

inline void sort_by_fitness(ga_vector& population)
{
	sort(population.begin(), population.end(), fitness_sort);
}

void elitism(ga_vector& population,
	ga_vector& buffer, int esize)
{
	for (int i = 0; i < esize; i++) {
		buffer[i].str = population[i].str;
		buffer[i].fitness = population[i].fitness;
	}
}

void mutate(ga_struct& member)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int tsize = GA_TARGET.size();
	int ipos = rand() % tsize;
	int delta = (rand() % 128) + 32;
	//setlocale(LC_ALL, "Russian");

	member.str[ipos] = ((member.str[ipos] + delta) % 160)  ;
	//member.str[ipos] =  delta;
}

void mate(ga_vector& population, ga_vector& buffer)
{
	int esize = GA_POPSIZE * GA_ELITRATE;
	int tsize = GA_TARGET.size(), spos, i1, i2;

	elitism(population, buffer, esize);

	// Mate the rest
	for (int i = esize; i < GA_POPSIZE; i++) {
		i1 = rand() % (GA_POPSIZE / 2);
		i2 = rand() % (GA_POPSIZE / 2);
		spos = rand() % tsize;

		buffer[i].str = population[i1].str.substr(0, spos) +
			population[i2].str.substr(spos, esize - spos);

		if (rand() < GA_MUTATION) mutate(buffer[i]);
	}
}

inline void print_best(ga_vector& gav)
{
	cout << "Best: " << gav[0].str << " (" << gav[0].fitness << ")" << endl;
}

inline void swap(ga_vector*& population,
	ga_vector*& buffer)
{
	ga_vector* temp = population; population = buffer; buffer = temp;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//setlocale(LC_ALL, "Russian");

	srand(unsigned(time(NULL)));

	ga_vector pop_alpha, pop_beta;
	ga_vector* population, * buffer;

	init_population(pop_alpha, pop_beta);
	population = &pop_alpha;
	buffer = &pop_beta;

	for (int i = 0; i < GA_MAXITER; i++) {
		calc_fitness(*population);		// вычисляем пригодность
		sort_by_fitness(*population);		// сортируем популяцию
		print_best(*population);		// выводим лучшую популяцию

		if ((*population)[0].fitness == 0) break;

		mate(*population, *buffer);		// спариваем популяции
		swap(population, buffer);		// очищаем буферы
	}

	return 0;
}*/

