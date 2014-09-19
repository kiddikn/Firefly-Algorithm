/**
 * Name:Ackley.cpp
 * for Global Optimization
 */
#define _USE_MATH_DEFINES
#include "Ackley.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <memory.h>

using namespace std;

Ackley::Ackley(int D){
	this->d = D;
}

void Ackley::setDimension(int D){
	this->d = D;
}

double Ackley::evaluate(double sol[]){
    //for(int i = 0;i < d;i++)cout << sol[i] << endl;
	double fitness = 20.0 + exp(1.0);
    //æ“ª‚Ì®-20exp(..)‚ğŒvZ
	double first = 0;
	double froot = 0;
	double sum = 0;
	for(int i = 0;i < this->d;i++){
		sum += sol[i] * sol[i];
	}
	froot = sqrt(((double)1/d)*sum);
	first = -20*exp(((double)-1/5)*froot);

	//Ÿ‚Ì®-exp(..cos)‚ğŒvZ
	double second = 0;
	double sroot = 0;
	sum = 0;
	for(int i = 0;i < this->d;i++){
		sum += cos(2*M_PI*sol[i]);
	}
	second = -exp(((double)1/d)*sum);
	//‡Œv‚·‚é
	fitness += (first + second);
	return fitness;
	
	////costŠÖ”
	//double sum = 0.0;
	//for(int i=0;i<this->d;i++){
	//	sum += (sol[i]-1)*(sol[i]-1);
	//}
	//return sum;

}
