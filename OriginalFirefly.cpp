/**
 * Name:original_Firefly.cpp
 * for Global Optimization
 */

#include "OriginalFirefly.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <memory.h>

using namespace std;

OriginalFirefly::OriginalFirefly(int seed,double alpha,double beta0,double gamma,int ffNum,int D,int genMax){
	this->alpha = alpha;
	this->beta0 = beta0;
	//this->betamin = 0.2;
	this->gamma = gamma;
	this->ffNum = ffNum;
	this->D = D;
	this->genMax = genMax;
	this->ub = 2.0;
	this->lb = -2.0;
	this->trialNum = 0;

	//乱数生成しホタルの配列を初期化する
	mersenneTwister = new CMersenneTwister();
	mersenneTwister->init_genrand(seed);
	for(int i = 0;i < ffNum;i++){
		for(int j = 0;j < D;j++){
			double rand = (double)mersenneTwister->genrand_real1(); //rand[0,1]
			ff[i][j] = rand*abs(this->ub - this->lb) + this->lb; //scale
		}
	}
	
	//目的関数を宣言
	//TODO:引数から宣言できるようにする
	objFunction = new Ackley(D);
	for(int i = 0;i < ffNum;i++){
		I[i] = objFunction->evaluate(ff[i]);
		this->trialNum++;
        //cout << I[i] << endl;
	}

}

void OriginalFirefly::setLambda(double lambda){
	this->lambda = lambda;
}

//与えられた配列から2点間の距離を求める
double OriginalFirefly::getDistance(double soli[],double solj[]){
	double distance = 0;
	double sum = 0;
	for(int k = 0;k < this->D;k++){
		sum += (soli[k] - solj[k])*(soli[k] - solj[k]);
	}
	distance = sqrt(sum);
	return distance;
}

/**
* i番目のホタルとj番目のホタルを入れ替える
*/
void OriginalFirefly::move(int fi,int fj){
	//ff[][]
	double r = this->getDistance(ff[fi],ff[fj]);
	//double attractiveness = (this->beta0-betamin)* exp(-gamma*r*r)+betamin;
	double attractiveness = this->beta0 * exp(-gamma*r*r);
	//double scale = abs(ub - lb);
	//levy flyght
	double levy = this->levyFlight(this->genNum/1.08); //levy flightに与える値を考察する必要がある
	for(int k = 0;k < this->D;k++){
		//NOMAL version
		//double rand = mersenneTwister->genrand_real1();
		//rand = rand - (double)0.5;
		//ff[fi][k] = ff[fi][k] + attractiveness*(ff[fj][k] - ff[fi][k]) + alpha*rand;
		ff[fi][k] = ff[fi][k] + attractiveness*(ff[fj][k] - ff[fi][k]) + alpha*levy;
	}
}

double OriginalFirefly::levyFlight(int gen_num){
	double rand = (double)mersenneTwister->genrand_real1();
	rand = rand - (double)0.5;
	double levy = this->sign(rand);
	double d = 0;
	//d = gen_num / pow(rand,1/1.001);
	/*if(gen_num == 0.0){
		d = 1;
	}else{*/
		//d = pow(gen_num,-this->lambda); //bug x^y:xが0で、かつ、yが0以下の場合、定義域エラーが発生する。結果が1.#INF000になってしまう
		//以下パレート分布に従う乱数生成を追加
		d = gen_num / pow(1-rand,1/this->lambda);
		//cout << d << endl;
		//以下d = gen_num * t * sまでlevy.cから追加
		//c=>-lambda,alpha=>gen_num
		//double u, v, t, s;
		//u = M_PI * rand;
		//if (alpha == 1)		/* cauchy case */
		//{
		//	t = tan (u);
		//	return gen_num * t;
		//}

		//do
		//{
		//	v = exp(rand);
		//}
		//while (v == 0);

		//if (alpha == 2)             /* gaussian case */
		//{
		//	t = 2 * sin (u) * sqrt(v);
		//	return gen_num * t;
		//}

		///* general case */
		//t = sin(this->lambda * u) / pow(cos(u), 1 / this->lambda);
		//s = pow(cos((1 - this->lambda) * u) / v, (1 - this->lambda) / this->lambda);

		//d = gen_num * t * s;
	//}
	return levy*d;
}

//引数で与えられた数の符号を返す
double OriginalFirefly::sign(double target){
	if(target > 0){
		return 1;
	}else if(target < 0){
		return -1;
	}else{
		return 0;
	}
}

// optionally recalculate the new alpha value
double OriginalFirefly::alpha_new(double alpha, int gMax){
	double delta;			// delta parameter
	delta = pow((pow(10.0, -4.0)/0.9), 1.0/(double) gMax);
	return delta*alpha;
}


void OriginalFirefly::copy(double dst[],double src[]){
	for(int i = 0;i < this->D;i++){
		dst[i] = src[i];
	}
}


void OriginalFirefly::rank(){
	// Bubble sort
	int n = this->ffNum;
	for(int i = 0; i < n-1; i++){
		for(int j = i + 1; j < n; j++){
			if(I[i] > I[j]){
				// LightIntensityを入れ替える
				double z = I[i];
				I[i] = I[j];
				I[j] = z;
				//ホタルを入れ替える
				this->copy(fftmp,ff[i]);
				this->copy(ff[i],ff[j]);
				this->copy(ff[j],fftmp);
			}
		}
	}
	

}

void OriginalFirefly::findLimits(int k)
{
	for(int i = 0; i < D; i++){
		if(ff[k][i] < lb){
			ff[k][i] = lb;
		}
		if(ff[k][i] > ub){
			ff[k][i] = ub;
		}
	}
}


void OriginalFirefly::search(){
	this->genNum = 0;
	int terminate = 0;
	while(this->genNum < genMax){
		//alpha = alpha_new(alpha,genMax);
		for(int i = 0;i < this->ffNum;i++){
			for(int j = 0;j < this->ffNum;j++){
				if(I[i] > I[j]){
					move(i,j);
					this->findLimits(i);
					I[i] = objFunction->evaluate(ff[i]);
					this->trialNum++;
					if(I[i] <= 1e-4){
						//while文を抜ける
						terminate = 1;
					}
				}
				//if文通らなかったら評価は変化なし∴ifに入れる
				/*I[i] = objFunction->evaluate(ff[i]);
				this->trialNum++;*/
				if(terminate == 1) break;
			}
			if(terminate == 1) break;
		}
		this->rank();
        this->disp();
		this->save();
		this->genNum++;
		if(terminate == 1) break;
	}
}

void OriginalFirefly::disp(){
	cout << "gen:"<< this->genNum <<",Light Intensity:"<< this->I[0] << ",eval:"<< this->trialNum <<endl;
	/*for(int j = 0;j < ffNum;j++){
		for(int i = 0;i < D;i++){
			cout<<j<<":"<<ff[j][i] <<endl;
		}
	}*/
} 

void OriginalFirefly::save(){
	bestIntensityPerGen[this->genNum] = this->I[0];
}


int OriginalFirefly::exportData(string fname){
	string fn = "data/";
	fn += fname;
	ofstream fs1(fn);

	for(int i = 0;i < this->genMax;i++){
		fs1 << this->bestIntensityPerGen[i] << endl;
	}

	cout << "finish writing " << fn << ". \r"<<endl;
	return 0;
}

double OriginalFirefly::getIntensity(int ffnum){
	if(0 >= ffnum && ffnum <= this->ffNum){
		return this->I[ffnum];
	}else{
		return -1;
	}
}

int OriginalFirefly::getTrialNum(){
	return this->trialNum;
}

