/**
* Name:Ackley.h
* for Global Optimization
*/
//#ifndef _INC_FA  //まだ読み込まれていなければ以下の処理をする
//#define _INC_FA  //すでに読み込まれているという目印をつける

class Ackley{
private:
	int d;
public:
	Ackley(int D);
	void setDimension(int D);
	double evaluate(double sol[]);

};
//#endif //INC_FA
