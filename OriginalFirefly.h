/**
 * Name:original_Firefly.h
 * for Global Optimization
 */

#ifndef _INC_FA  //�܂��ǂݍ��܂�Ă��Ȃ���Έȉ��̏���������
#define _INC_FA  //���łɓǂݍ��܂�Ă���Ƃ����ڈ������
#include "MersenneTwister.h"
#include "Ackley.h"
#define MAX_FF	1000
#define MAX_D	1000
#define MAX_GEN 1000

class OriginalFirefly{
	private:
		CMersenneTwister *mersenneTwister;//�����Z���k�E�c�C�X�^�ŗ����𐶐�
		Ackley *objFunction;              //�ړI�֐��p�N���X��錾

		//�ϐ��錾
		int genNum;                       //�����㐔
		int genMax;                       //�ő吢�㐔
		int D;                            //��莟����
		int ffNum;                        //�z�^���̐�(�W�c�T�C�Y)
		int trialNum;					  //�]����

		double alpha;					  //�p�����[�^
		double beta0;
		double betamin;
		double gamma;
		double lambda;

		double I[MAX_FF];		             //light intensity
		double ff[MAX_FF][MAX_D];            //�z�^���W��
		double bestIntensityPerGen[MAX_GEN]; //���̕ۑ��z��
		double eliteI[MAX_FF+1];             //�G���[�g�ۑ��p�̔z��W��
		double eliteFF[MAX_FF+1][MAX_D];     //�G���[�g�ۑ�
		double fftmp[MAX_D];                 //�z�^���ꎞ�ۑ�
		double ffBest[MAX_D][MAX_D];         //�œK���̕ۑ�
		double ffBestValue;                  //�œK���̒l
		double ub;						     //���
		double lb;						     //����

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
