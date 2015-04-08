#include "signer.h"
using namespace std;

signer::signer()
{
	pairing_init_set_str(pairing, _PAIRING_PARAM_);
	element_init_G1(R, pairing);
	element_init_G1(P, pairing);
	element_init_G1(Qid, pairing);
	element_init_Zr(c,pairing);
	element_init_Zr(c1,pairing);
  element_init_G1(Sid, pairing);
  element_init_G1(S, pairing);
  element_init_G1(S1, pairing);
	element_init_G1(Ppub, pairing);
	element_init_Zr(r, pairing);
	element_random(r);
}
void signer::GetC(string blsignature)
{
	helper::TakeNextElementFromString(blsignature,c);
	element_printf("c= %B\n", c);
}
void signer::GetQid_Sid(string key)
{
	helper::TakeNextElementFromString(key,Qid);
	helper::TakeNextElementFromString(key,Sid);
	element_printf("Qid= %B\n", Qid);
	element_printf("Sid= %B\n", Sid);
}	
void signer::GetGit(string git)
{
	helper::TakeNextElementFromString(git,c1);
	helper::TakeNextElementFromString(git,S1);
	element_printf("c1= %B\n", c1);
	element_printf("S1= %B\n", S1);
}	

void signer::GetEl(string P_Pub)
{
  helper::TakeNextElementFromString(P_Pub,Ppub);
  helper::TakeNextElementFromString(P_Pub,P);
  element_printf("P = %B\n", P);
  element_printf("Ppub = %B\n", Ppub);
}
void signer::sendR(string &Rz)
{
	element_mul_zn(R, P, r);
  	printf("Signer sends R = rP to user\n");
  	element_printf("R = %B\n", R);
  	Rz=helper::Element_to_string(R);
}
void signer::Signing(string &sig)
{
	element_t t7, t8;
	element_init_G1(t7, pairing);
  element_init_G1(t8, pairing);
  element_printf("r = %B\n", r);
	printf("Signing\n");
  element_mul_zn(t7, Ppub, r);
  element_mul_zn(t8, Sid, c);
  element_add(S, t8, t7);
  printf("Signer sends S\n");
  element_printf("Sig = %B\n", S);
  sig=helper::Element_to_string(S);
  element_clear(t7);
  element_clear(t8);
}
signer::~signer()
{
	element_clear(R);
	element_clear(P);
	element_clear(Ppub);
	element_clear(Sid);
	element_clear(S);
	element_clear(c);
	element_clear(Qid);
	element_clear(r);
	pairing_clear(pairing);
}

void signer::Verfi()
{
	element_printf("S in verf = %B\n", S);
	string mes("hello");
	element_t  negc, t5,
     t10, t11, t12, t14;
     mpz_t t13;
  	mpz_init(t13);
  
  
  element_init_Zr(negc, pairing);
  element_init_Zr(t5, pairing);
  element_init_Zr(t14, pairing);
  element_init_GT(t10, pairing);
  element_init_GT(t11, pairing);
  element_init_GT(t12, pairing);
  printf("VERIFICATION\n");
  pairing_apply(t10, Qid, Ppub, pairing);
  element_printf("t10 = %B\n", t10);
  element_neg(negc, c);
  element_printf("neg = %B\n", negc);
  element_pow_zn(t10, t10, negc);
  element_printf("t10 = %B\n", t10);
  pairing_apply(t11, S, P, pairing);
  element_printf("t11 = %B\n", t11);
  element_mul(t12, t11, t10);
  element_printf("t12 = %B\n", t12);
  element_to_mpz(t13, t12);
  element_from_hash(t5, (char*)mes.c_str(), 6);
  element_printf("t5 = %B\n", t5);
  element_mul_mpz(t14, t5, t13);
  element_printf("c1 = %B\n", c);
  element_printf("H(m, [e(S1, P)][e(Qid, Ppub)^(-c1)]) = %B\n", t14);

  if (!element_cmp(t14, c)) printf("Signature is valid\n");
  else printf("Signature is invalid\n");
}