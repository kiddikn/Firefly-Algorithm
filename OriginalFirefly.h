/**
 * Name:original_Firefly.h
 * for Global Optimization
 */

#ifndef _INC_FA  //まだ読み込まれていなければ以下の処理をする
#define _INC_FA  //すでに読み込まれているという目印をつける
#include "MersenneTwister.h"
#include "Ackley.h"
#define MAX_FF	1000
#define MAX_D	1000
#define MAX_GEN 1000

class OriginalFirefly{
	private:
		CMersenneTwister *mersenneTwister;//メルセンヌ・ツイスタで乱数を生成
		Ackley *objFunction;              //目的関数用クラスを宣言

		//変数宣言
		int genNum;                       //現世代数
		int genMax;                       //最大世代数
		int D;                            //問題次元数
		int ffNum;                        //ホタルの数(集団サイズ)
		int trialNum;					  //評価回数

		double alpha;					  //パラメータ
		double beta0;
		double betamin;
		double gamma;
		double lambda;

		double I[MAX_FF];		             //light intensity
		double ff[MAX_FF][MAX_D];            //ホタル集合
		double bestIntensityPerGen[MAX_GEN]; //解の保存配列
		double eliteI[MAX_FF+1];             //エリート保存用の配列集合
		double eliteFF[MAX_FF+1][MAX_D];     //エリート保存
		double fftmp[MAX_D];                 //ホタル一時保存
		double ffBest[MAX_D][MAX_D];         //最適解の保存
		double ffBestValue;                  //最適解の値
		double ub;						     //上限
		double lb;						     //下限

		//Objective function
		//typedef double (*FunctionCallback)(double sol[D]);
		//double ackley(double sol[D]);
		//FunctionCallback function = &ackley;
		double getDistance(double soli[],double solj[]);
		void move(int fi,int fj);
		void rank();
		void copy(double dst[],double src[]);
		void findLimits(int k);
		double alpha_new(double alpha, int gMax);
		void save();
		double levyFlight(int gen_num);
		double sign(double target);

	public:
		OriginalFirefly(int seed,double alpha,double beta0,double gamma,int ffNum,int D,int genMax);
		void setLambda(double lambda);
		void search();
		void disp();
		int exportData(string fname);
		double getIntensity(int ffnum);
		int getTrialNum();
};
#endif //INC_FA
