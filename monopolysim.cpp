//Compile and run with argument "j" to allow jail. Our precalculated probability did not include jail, though.
//This program outputs into a file called "results.txt" in the same directory as the a.out file. It cannot overwrite it, though
//so rename before running a second time!

#include <random>
#include <iostream>
#include <map>
#include <fstream>
using std::cout;
using std::endl;
using std::cerr;

int boardTiles[40];

int runSim(bool allowJail){//simulates one turn around the board
	int currentposition = 0;
	int doublecounter = 0;
	int turns = 0;
	int min = 1;
	int max = 6;
	int d1,d2;
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

	while (currentposition < 40){
		//if (allowJail && (doublecounter == 3 || currentposition == 30)){ //you are in jail!
		if(allowJail && currentposition == 30){
			cerr << "You got into jail!";
			int jailRolls = doublecounter = 0;
			currentposition = 10;
			do{
				d1 = uni(rng);
				d2 = uni(rng);
				jailRolls++;
				turns++;
			} while (jailRolls < 3 && (d1 != d2));
		}
		d1 = uni(rng);
		d2 = uni(rng);
		if (d1 == d2)
			doublecounter++;
		else
			doublecounter = 0;
		currentposition += d1+d2;
		
		boardTiles[currentposition]++;
		turns++;
	}
	return turns;
}

int main(int argc, char *argv[]){
	//std::ofstream output;
	//output.open("results.txt");
	bool allowJail = false;
	int numberofRuns = 5000000; //change this to set how many times the loop runs!

	if (argc > 1 && *argv[1] == 'j')
		allowJail = true;

	for (int i = 0; i < 40; i++)
		boardTiles[i] = 0;
	std::map<int,int> turnNumbers;
	for (int i = 0; i < 20; i++)
		turnNumbers[i] = 0;

	for(uint32_t i = 0; i < numberofRuns; i++){
		cerr <<"Simlation# "<< i << endl;	
		turnNumbers[runSim(allowJail)]++;
	}

	for (std::map<int,int>::iterator it = turnNumbers.begin(); it != turnNumbers.end(); ++it)
		cout << it->first <<": " << it->second << endl;
	cout << "The tiles were each rolled onto this many times:" << endl;
	for (int i = 0; i < 40; i++)
		cout << i << ": " << boardTiles[i] << endl;

	return 0;
}
