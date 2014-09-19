/**
* Name:Ackley.h
* for Global Optimization
*/
//#ifndef _INC_FA  //‚Ü‚¾“Ç‚İ‚Ü‚ê‚Ä‚¢‚È‚¯‚ê‚ÎˆÈ‰º‚Ìˆ—‚ğ‚·‚é
//#define _INC_FA  //‚·‚Å‚É“Ç‚İ‚Ü‚ê‚Ä‚¢‚é‚Æ‚¢‚¤–Úˆó‚ğ‚Â‚¯‚é

class Ackley{
private:
	int d;
public:
	Ackley(int D);
	void setDimension(int D);
	double evaluate(double sol[]);

};
//#endif //INC_FA
