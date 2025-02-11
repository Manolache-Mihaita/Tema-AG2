// Tema AG2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <climits>
#include <time.h>
#include <conio.h>
#include <map>
#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>
#define PI 3.14


class WaysToChosePopulation {
public:
    virtual std::vector<double> cutfunctions(std::vector<double> vectorOfValues) = 0;
};

class RoataNorocului : public WaysToChosePopulation {
    std::vector<double> cutfunctions(std::vector<double> vectorOfValues) override{
        std::vector<double> individualData;
        std::vector<double> returnedVector;
		returnedVector.push_back(0);
        double sum = 0;
        for (auto index : vectorOfValues) {
            sum += index;
        }
        for (auto index : vectorOfValues) {
            individualData.push_back(index / sum);
        }
		unsigned int index_values=0;
        while( index_values < vectorOfValues.size()) 
        {
			returnedVector.push_back(returnedVector[index_values] + individualData[index_values]);
			index_values++;
        }

		return returnedVector;
    }
};

class RandSelect : public WaysToChosePopulation {
    std::vector<double> cutfunctions(std::vector<double> vectorOfValues) {
        // to be left to be implemented at a later date
		std::vector<double>ffsUni;
		return ffsUni;
    }
};

class Turneu : public WaysToChosePopulation {
    std::vector<double> cutfunctions(std::vector<double> vectorOfValues) {
        // to be left to be implemented at a later date
		std::vector<double>ffsUni;
		return ffsUni;
    }
};

class Elitism : public WaysToChosePopulation {
    std::vector<double> cutfunctions(std::vector<double> vectorOfValues) {
        // to be left to be implemented at a later date
		std::vector<double>ffsUni;
		return ffsUni;
    }
};

class ChoseModeToCut {
private:
    std::map<std::string, WaysToChosePopulation *> functions;

    std::map<std::string, WaysToChosePopulation *>::iterator accesFunctionWithName(std::string &functionName) {
        return functions.find(functionName);
    }

public:
    ChoseModeToCut() {
        functions.insert(std::make_pair("Roata", new RoataNorocului()));
        functions.insert(std::make_pair("Elitism", new Elitism()));
        functions.insert(std::make_pair("RandSelect", new RandSelect()));
        functions.insert(std::make_pair("Turneu", new Turneu()));
    }

    std::vector<double> execute(std::string &functionName, std::vector<double> vectorOfValues) {
        auto function = accesFunctionWithName(functionName);
        if (function != functions.end()) {
            return function->second->cutfunctions(vectorOfValues);
        } else exit(-1);
    }
};

class Function {
public:
    virtual double execute(std::vector<double> decodedValues, unsigned int number) = 0;

    virtual void initialiseInterval(std::vector<double> &interval) = 0;
};

class Rastrigin : public Function {
public:
    double execute(std::vector<double> decodedValues, unsigned int number) override {
        double functionResult = 10 * number;
        for (auto index : decodedValues) {
            functionResult += pow(index, 2) - 10 * cos(2 * PI * index);
        }
        return functionResult;
    }

    void initialiseInterval(std::vector<double> &interval) override {
        interval.push_back(-5.12);
        interval.push_back(5.12);
    }
};

class Six_Hump : public Function {
public:
    double execute(std::vector<double> decodedValues, unsigned int number) override {
        double functionRestult =
                (4 - 2.1 * pow(decodedValues[0], 2) + pow(decodedValues[0], 4 / 3)) * pow(decodedValues[0], 2) +
                decodedValues[0] * decodedValues[1] + (-4 + 4 * pow(decodedValues[1], 2)) * pow(decodedValues[1], 2);
        return functionRestult;
    }

    void initialiseInterval(std::vector<double> &interval) override {
        interval.push_back(-2);
        interval.push_back(2);
    }
};

class Griewangk : public Function {
public:
    double execute(std::vector<double> decodedValues, unsigned int number) override {
        double functionSum = 0;
        double functionProduct = 0;
        double functionResult = 0;
        unsigned int i = 1;
        for (auto index : decodedValues) {
            functionSum += pow(index, 2) / 4000;
            functionProduct += cos(index / sqrt(i));
            ++i;
        }
        functionResult = functionProduct + functionSum + 1;
        return functionResult;
    }

    void initialiseInterval(std::vector<double> &interval) override {
        interval.push_back(-600);
        interval.push_back(600);
    }
};

class Rosenbrock : public Function {
public:
    double execute(std::vector<double> decodedValues, unsigned int number) override {
        double functionResult = 0;
        for (auto index = 0; index < decodedValues.size() - 1; ++index) {
            functionResult += 100 * pow((decodedValues[index + 1] - pow(decodedValues[index], 2)), 2) +
                              pow((1 - decodedValues[index]), 2);
        }
        return functionResult;
    }

    void initialiseInterval(std::vector<double> &interval) override {
        interval.push_back(-2.048);
        interval.push_back(2.047);
    }
};
class DeJong : public Function {
public:
	double execute(std::vector<double> decodedValues, unsigned int number) override {
		double functionResult = 0;
		for (unsigned int index = 0;index < decodedValues.size(); ++index) {
			functionResult += decodedValues[index] * decodedValues[index];
		}
		return functionResult;
	}

	void initialiseInterval(std::vector<double> &interval) override {
		interval.push_back(-5.12);
		interval.push_back(5.12);
	}
};
class Schwefel : public Function {
public:
	double execute(std::vector<double> decodedValues, unsigned int number) override {
		double functionResult=0;
		for (unsigned int index = 0;index < decodedValues.size(); ++index) {
			functionResult += ((-decodedValues[index])*sin(sqrt(abs(decodedValues[index]))));
		}
		return functionResult;
	}

	void initialiseInterval(std::vector<double> &interval) override {
		interval.push_back(-500);
		interval.push_back(500);
	}
};

class FunctionSelect {
private:
    std::map<std::string, Function *> functions;

    std::map<std::string, Function *>::iterator getDesiredFunction(std::string &functionName) {
        return functions.find(functionName);
    }

    std::map<std::string, Function *> initFunctions;

    std::map<std::string, Function *>::iterator getDesiredInitialiseFunction(std::string &functionName) {
        return initFunctions.find(functionName);
    }

public:
    FunctionSelect() {
        functions.insert(std::make_pair("Rastrigin", new Rastrigin));
        functions.insert(std::make_pair("Rosenbrock", new Rosenbrock));
        functions.insert(std::make_pair("Six_Hump", new Six_Hump));
        functions.insert(std::make_pair("Griewangk", new Griewangk));
		functions.insert(std::make_pair("Schwefel", new Schwefel));
		functions.insert(std::make_pair("DeJong", new DeJong));
    }

    double execute(std::string &functionName, std::vector<double> &decodedValues, unsigned int number) {
        auto function = getDesiredFunction(functionName);
        return function->second->execute(decodedValues, number);
    }

    void initialiseInterval(std::string &functionName, std::vector<double> &interval) {
        auto function = getDesiredFunction(functionName);
        function->second->initialiseInterval(interval);
    
	}
};

class Cromozom {
private:
    std::vector<bool> cromozom;
public:
    friend class PopulationOperations;

    void randomIndivid(unsigned int numberOfBits, unsigned int numberOfIndivids) {
        for (int index = 0; index < numberOfBits * numberOfIndivids; ++index) {
            this->cromozom.push_back(rand() % 2);
        }
    }

    std::vector<int> bitsToInteger(unsigned int numberOfBits, unsigned int numberOfIndivids) {
        std::vector<int> decodedBitstring;
        for (unsigned int index = 0; index < numberOfIndivids; ++index) {
            unsigned int sum = 0;
            for (unsigned int bitIndex = 0; bitIndex < numberOfBits; ++bitIndex) {
                sum += this->cromozom[index * numberOfBits + bitIndex] * pow(2, bitIndex);
            }
            decodedBitstring.push_back(sum);
        }
        return decodedBitstring;
    }

    std::vector<double>
    integerToReal(std::vector<int> integerString, unsigned int numberOfBits, std::vector<double> interval) {
        std::vector<double> realNumers;
        for (auto index : integerString) {
            realNumers.push_back(interval[0] + index * (interval[1] - interval[0]) / (pow(2, numberOfBits) - 1));
        }
        return realNumers;
    }

    void mutateCromozom(unsigned int position) {
        this->cromozom[position] = !this->cromozom[position];
    }

    std::vector<bool> *getChromozome() {
        std::vector<bool> returnedChromozome = this->cromozom;
        return &this->cromozom;
    }

    void newChromosome(std::vector<bool> Chromosome) {
        this->cromozom = Chromosome;
    }

    double
    improveCromozom(FunctionSelect genericFunction, std::string genericFunctionName, std::vector<double> interval,
                    unsigned int numberOfBits, unsigned int numberOfIndivinds,unsigned int numberOfExecutions) {
        double currentBest = genericFunction.execute(genericFunctionName, this->integerToReal(
                this->bitsToInteger(numberOfBits, numberOfIndivinds), numberOfBits, interval), numberOfIndivinds);
        double alteredValue;
		unsigned int bestBit;
		bool local;
		unsigned int stuckCounter ;
		do {
			bestBit = UINT_MAX;
			stuckCounter = 0;
			do {
				local = false;
				currentBest = genericFunction.execute(genericFunctionName, this->integerToReal(
					this->bitsToInteger(numberOfBits, numberOfIndivinds), numberOfBits, interval), numberOfIndivinds);
				bestBit = this->bestBit(genericFunction, genericFunctionName, numberOfBits, numberOfIndivinds, interval);
				if (bestBit != UINT_MAX) {
					this->cromozom[bestBit] = !this->cromozom[bestBit];
					alteredValue = genericFunction.execute(genericFunctionName, this->integerToReal(
						this->bitsToInteger(numberOfBits, numberOfIndivinds), numberOfBits, interval), numberOfIndivinds);
					if (alteredValue > currentBest) {
						this->cromozom[bestBit] = !this->cromozom[bestBit];
						stuckCounter++;
					}
					else {
						local = true;
						currentBest = alteredValue;
					}
				}
			} while (local&&stuckCounter);
				numberOfExecutions--;
		} while (numberOfExecutions);
		return currentBest;
		}
   
	unsigned int bestBit(FunctionSelect genericFunction, std::string genericFunctionName,unsigned int numberOfBits,unsigned int numberOfIndivinds,std::vector<double>interval) {
		double currentBest;
		double alteredString;
		unsigned int bestBit = UINT_MAX;
		currentBest = genericFunction.execute(genericFunctionName, this->integerToReal(
			this->bitsToInteger(numberOfBits, numberOfIndivinds), numberOfBits, interval), numberOfIndivinds);
		for (unsigned int index = 0; index < this->cromozom.size();++index) {
			this->cromozom[index] = !this->cromozom[index];
			alteredString= genericFunction.execute(genericFunctionName, this->integerToReal(
				this->bitsToInteger(numberOfBits, numberOfIndivinds), numberOfBits, interval), numberOfIndivinds);
			this->cromozom[index] = !this->cromozom[index];
			if (alteredString < currentBest) {
				currentBest = alteredString;
				bestBit = index;
				}
		}
		return bestBit;
	}
    void replaceChromozom(std::vector<bool> bitstringToRepalceWith) {
        this->cromozom = bitstringToRepalceWith;
    }
};


class CuttingPartitions {
public :
	
};


class Population {
private:
    std::vector<Cromozom> population;
public:
    friend class PopulationOperations;

    void initializePopulation(unsigned int populationSize, unsigned int numberOfIndivids, unsigned int numberOfBits) {
        std::vector<Cromozom> popInit(populationSize);
        population = popInit;
        for (unsigned int index = 0; index < populationSize; ++index) {
            this->population[index].randomIndivid(numberOfBits, numberOfIndivids);
        }
    }

    std::vector<std::vector<double>>
    populationRealNumbers(unsigned int numberOfBits, unsigned int numberOfIndivids, std::vector<double> interval) {
        std::vector<std::vector<double>> populationInRealNumbers;
        for (auto index : population) {
            populationInRealNumbers.push_back(
                    index.integerToReal(index.bitsToInteger(numberOfBits, numberOfIndivids), numberOfBits, interval));
        }
        return populationInRealNumbers;
    }

    void mutation(unsigned int bitToMutate) {
        for (auto index : population) {
            index.mutateCromozom(bitToMutate);
        }
    }

    void crossBreeding(unsigned int numberOfIndivids, unsigned int numberOfBits) {
        Population newGeneration;
        while (this->population.size()) {
            unsigned int positionToMutate = rand() % (numberOfIndivids * numberOfBits);
        }
    }

    std::vector<Cromozom> getPopulation() {
        return this->population;
    }

    std::vector<bool> *getSpecificMember(unsigned int desiredMemberIndex) {
        return this->population[desiredMemberIndex].getChromozome();
    }

    void newGeneration(Cromozom newGenerationMember) {
        this->population.clear();
        this->population.push_back(newGenerationMember);
    }

    std::vector<double>
    improvePopulation(FunctionSelect genericFunction, std::string genericFunctionName, std::vector<double> interval,
                      unsigned int numberOfBits, unsigned int numberOFIndivids, unsigned int numberOfExecutions) {
        std::vector<double> improvedPopulation;
            for (auto index : this->population) {
                improvedPopulation.push_back(
                        index.improveCromozom(genericFunction, genericFunctionName, interval, numberOfBits,
                                              numberOFIndivids,numberOfExecutions));
            }
        return improvedPopulation;
    }

    void replacePopulation(std::vector<Cromozom> newPopulation) {
        for (unsigned int index = 0; index < this->population.size(); ++index) {
            this->population[index] = newPopulation[index];
        }
    }

    void erasePopulationMember(unsigned int index) {
    }
};

double randDoubleVal(double rM, double lM) {
    double range = lM - rM;
    double randVal = (double) rand() / (double) RAND_MAX;
    return range + randVal + rM;
}

class PopulationOperations {
	CuttingPartitions breed;
public:
    Population ReplacePopulation(Population &oldPopulation, std::vector<Cromozom> newGeneration) {
        oldPopulation.replacePopulation(newGeneration);
    }

    void mutatePopulation(Population &population, double chanceToMutate, unsigned int numberOfIndivids) {
        double randomValue = randDoubleVal(0.0, 1.0);
        if (randomValue <= chanceToMutate) {
            population.mutation(randDoubleVal(1.0, (numberOfIndivids - 1)));
        }
    }

	std::vector<Cromozom> Cut_In_X_Ways(Cromozom vector1, Cromozom vector2, std::vector<unsigned int>cutting_positions) {
		std::vector<Cromozom> returnedVector(2);
		std::sort(cutting_positions.begin(), cutting_positions.end());
		std::vector<bool>new_vector1;
		std::vector<bool>new_vector2;
		bool up = true;
		unsigned int cur_partition = 0;
		cutting_positions.push_back(vector1.cromozom.size());
		for (unsigned int ind = 0; ind < vector1.cromozom.size() ; ++ind) {
			if (ind == cutting_positions[cur_partition]) {
				cur_partition++;
				up = !up;
			}
					if (up) {
						new_vector1.push_back(vector1.cromozom[ind]);
						new_vector2.push_back(vector2.cromozom[ind]);
					}
					else {
						new_vector1.push_back(vector2.cromozom[ind]);
						new_vector2.push_back(vector1.cromozom[ind]);
					}
		}
		returnedVector[0].replaceChromozom(new_vector1);
		returnedVector[1].replaceChromozom(new_vector2);
		return returnedVector;
	}



    void breedPopulation(Population &pop, unsigned int positionToMutate, unsigned int numberOfIndivids,std::vector<double>StringProbability,double chance_for_new_cromozome) {

        Population newPopulation;
            std::vector<bool> child1;
            std::vector<bool> child2;
            Cromozom c1;
            Cromozom c2;
		std::default_random_engine generator;
		std::uniform_real_distribution<double> distribution(0, 1.0);
		while (newPopulation.population.size() < pop.population.size()) {
			std::vector<Cromozom> cr;
			double rand_pos1 = distribution(generator);
			unsigned int rand_pos1_index = 0;
			bool rand_pos1_found = false;
			double rand_pos2 = distribution(generator);
			unsigned int rand_pos2_index = 0;
			bool rand_pos2_found = false;
			unsigned int index = 1;
			while (!rand_pos1_found || !rand_pos2_found) {
				if (rand_pos1 > StringProbability[index - 1] && rand_pos1 < StringProbability[index]) {
					rand_pos1_found = true;
					rand_pos1_index = index - 1;
				}
				if (rand_pos2 > StringProbability[index - 1] && rand_pos2 < StringProbability[index]) {
					rand_pos2_found = true;
					rand_pos2_index = index - 1;
				}
				++index;
			}
			std::vector<unsigned int> pos_to_cut = { rand() % pop.population[0].cromozom.size() };
			cr=Cut_In_X_Ways(pop.population[rand_pos1_index], pop.population[rand_pos2_index],pos_to_cut);
			newPopulation.population.push_back(cr[0]);
			newPopulation.population.push_back(cr[1]);
			if (randDoubleVal(0, 1) < chance_for_new_cromozome) {
				std::vector<bool>randBoolVector(pop.population[0].cromozom.size());
				for (auto index : randBoolVector) {
					index = rand() % 2;
				}
				c1.replaceChromozom(randBoolVector);
				newPopulation.population.push_back(c1);
			}
			if (newPopulation.population.size() == pop.population.size() - 1) {
				std::vector<bool>randBoolVector(pop.population[0].cromozom.size());
				for (auto index : randBoolVector) {
					index = rand() % 2;
				}
				c1.replaceChromozom(randBoolVector);
				newPopulation.population.push_back(c1);
			}
		}
		pop = newPopulation;
    }

};

class GeneticAlgorithm {
private:
    std::string modeToCut;
    PopulationOperations q;
    Population chosenPopulation;
    FunctionSelect function;
    std::string functionName;
    std::vector<double> interval;
    unsigned int numberOfBits;
    unsigned int numberOfIndivids;
    unsigned int populationSize;
    unsigned int precision;
    unsigned int numberOfExecutions;
    unsigned int numberOfGenerations;
    double mutateChance;
	double chance_for_new_cromozome;
	std::vector<std::string> saveBaseFunctions = { "Rastrigin", "Griewangk", "Rosenbrock", "Six_Hump" ,"DeJong","Schwefel" };
public:
    friend class PopulationOperations;

    GeneticAlgorithm() {

    }
    void choseGeneticAlgorithm() {
		for (auto index : saveBaseFunctions) {
			std::cout << index << std::endl;
		}
        std::cout<< "To chose a function write it's name and press enter: ";
        bool validFunction = false;
        while (1) {
            std::string readImputString;
            std::cin >> readImputString;
            for (auto i : saveBaseFunctions) {
                if (i == readImputString) {
                    this->functionName = readImputString;
                    validFunction = true;
                    break;
                }
            }
            if (validFunction) {
                break;
            } else std::cout << "\nWrong Input!\n";
        }
        std::cout << "You chose the " << this->functionName << " function\n";
        function.initialiseInterval(this->functionName, interval);
        std::cout << "Introduce the population size(integer): ";
        std::cin >> this->populationSize;
        std::cout << "Indroduceti numarul de valori al unui singur individ: ";
        std::cin >> this->numberOfIndivids;
        std::cout << "Introduceti precizia: ";
        std::cin >> this->precision;
        std::cout << "Number Of executions for improve: ";
        std::cin >> this->numberOfExecutions;
        std::cout << std::endl;
        std::cout << "Number Of generations: ";
        std::cin >> this->numberOfGenerations;
        std::cout << "% to mutate: ";
        std::cin >> this->mutateChance;
		this->modeToCut = "Roata";
        this->numberOfBits = ceil(log2((interval[1] - interval[0]) * pow(10, precision)));
        chosenPopulation.initializePopulation(this->populationSize, this->numberOfIndivids, this->numberOfBits);
        double minValue = DBL_MAX;
        ChoseModeToCut modeToCut;
        std::string name_modeToCut = "Roata";
        std::vector<std::vector<double>> teststringsaves;
        std::vector<double> teststring;
		std::string create_file = functionName;
		create_file += ".txt";
		std::ofstream file;
		file.open(create_file.c_str(), std::ios::out | std::ios::trunc);
		file << functionName << std::endl;
        for (unsigned int generation = 0; generation < this->numberOfGenerations; generation++) {
            teststring = this->chosenPopulation.improvePopulation(this->function, this->functionName, this->interval,
                                                                  this->numberOfBits, this->numberOfIndivids,
                                                                  this->numberOfExecutions);
			
            //mode to cut,work on dis....
            std::vector<double> prob_to_be_chosen = modeToCut.execute(name_modeToCut, teststring);

            q.mutatePopulation(this->chosenPopulation, this->mutateChance, this->numberOfIndivids);
			q.breedPopulation(this->chosenPopulation, randDoubleVal(0, numberOfBits * numberOfIndivids),
				this->numberOfBits, prob_to_be_chosen,chance_for_new_cromozome);
            teststringsaves.push_back(teststring);
			file << "Generation: " << generation << std::endl;
			for (unsigned int indeX = 0; indeX < teststring.size();++indeX) {
				file << teststring[indeX] << " ";
				if (teststring[indeX] < minValue) {
					minValue = teststring[indeX];
					std::cout << "min " << minValue << " ";
				}
            }
			file << std::endl;
        }
        std::cout << "Min value:" << minValue;
		file.close();

    }
    Population getPopulation() {
        return this->chosenPopulation;
    }

};



void a() {
	std::cout << "A";
}
void b(){
	std::cout << "B";
}

int main() {





    srand(time(NULL));
	GeneticAlgorithm a;
	a.choseGeneticAlgorithm();
    return 0;
}



x=	1 2 3 | 4 5 6
y=	6 5 4 | 3 2 1 
-------------

x= 1 2 3 3 2 1
y= 6 5 4 4 5 6


