#include <iostream>
#include <fstream>
#include <string>
#include "OriginalFirefly.h"

using namespace std;


int main(){
	int length = 10;
	int FILE_EXPORT = 0;
	int seed[10] = {181,149,163,179,181,223,449,547,659,811};
	string fname = "data_a020b1r1f40d128_levy.csv";
	string fsname = "data/seedAvg/";
	fsname += fname;
	double alpha = 0.2;
	double beta0 = 1.0;
	double gamma = 1.0;
	double lambda = 1.5;
	int ffNum = 40;
	int D = 128;
	int maxGen = 15; 
	//double bestIntensityPerSeed[1000]; //各seedごとのbestを記憶
	double trialnumPerSeed[1000];		 //終了条件を満たした時の評価回数を記憶
    
	//int seed,double alpha,double beta0,double gamma,int ffNum,int D,int maxGen
    for(int i = 0;i < 10;i++){
		OriginalFirefly *ff = new OriginalFirefly(seed[i],alpha,beta0,gamma,ffNum,D,maxGen);   
		ff->setLambda(lambda);
		ff->search();
		//bestIntensityPerSeed[i] = ff->getIntensity(0);
		trialnumPerSeed[i] = ff->getTrialNum();
		cout<<trialnumPerSeed[i]<<endl;
		if(i == 9 && FILE_EXPORT == 1){
			ff->exportData(fname);
		}
	}

	if(FILE_EXPORT == 1){
		//csvファイル書き込み準備
		ofstream fs1(fsname);

		//統計データを取得する
		double sum = 0;  //合計値
		double sd = 0;   //標準偏差
		double avg = 0;  //平均値
		//平均値の取得
		for(int i = 0;i < length;i++){
			//ファイル出力
			fs1 << trialnumPerSeed[i] << endl;
			sum += trialnumPerSeed[i];
		}
		avg = sum /length;

		//標準偏差の取得
		for(int i = 0;i < length;i++){
			sd += (trialnumPerSeed[i] - avg)*(trialnumPerSeed[i] - avg);
		}
		sd = sqrt(sd/(length - 1));

		//ファイル出力
		fs1 << "" << endl;
		fs1 << "avg:," << avg << endl;
		fs1 << "SD:," << sd << endl;
		fs1 << "MAX:,"<<"=MAX(A1:A10)"<<endl;
		fs1 << "MIN:,"<<"=MIN(A1:A10)"<<endl;

		cout << "finish writing. \r"<<endl;
	}
	
    return 0;
}