#include <iostream>
#include "manager.h"
#include "signer.h"
#include "user.h"
using namespace std;
int main(int argc,char**argv)
{
	string P_Ppub,R,KeySQ,blind_signature,sign;
	string s("Denis");
	Manager p;
	p.KeyGeneration(P_Ppub);
	p.Setup(s, KeySQ);
	cout<<KeySQ<<endl;
	signer a;
	a.GetEl(P_Ppub);
	a.sendR(R);
	user b;
	b.GetR(R);
	b.GetEl(P_Ppub);
	a.GetQid_Sid(KeySQ);
	b.GetQid(KeySQ);
	b.SendCBlind();
	b.sendC(blind_signature);
	a.GetC(blind_signature);
	a.Signing(sign);
	b.GetS(sign);
	b.unblinding();
	b.Verf();
	

	return 0;

}