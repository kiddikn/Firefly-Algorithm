/**
* Name:Ackley.h
* for Global Optimization
*/
//#ifndef _INC_FA  //�܂��ǂݍ��܂�Ă��Ȃ���Έȉ��̏���������
//#define _INC_FA  //���łɓǂݍ��܂�Ă���Ƃ����ڈ������

class Ackley{
private:
	int d;
public:
	Ackley(int D);
	void setDimension(int D);
	double evaluate(double sol[]);

};
//#endif //INC_FA
