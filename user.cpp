#include "user.h"
using namespace std;

user::user()
{
	pairing_init_set_str(pairing, _PAIRING_PARAM_);
	element_init_G1(R, pairing);
	element_init_G1(P, pairing);
	element_init_G1(Ppub, pairing);
	element_init_G1(Qid, pairing);
	element_init_G1(S, pairing);
	element_init_Zr(c,pairing);
	element_init_Zr(a, pairing);
  element_init_Zr(b, pairing);
  element_init_G1(S1, pairing);
	element_init_Zr(c1,pairing);
	element_random(a);
	  element_random(b);
}


user::~user()
{
	element_clear(R);
	element_clear(P);
	element_clear(Ppub);
	element_clear(c);
	element_clear(S);
	element_clear(Qid);
	pairing_clear(pairing);
}
void user::GetQid(string key)
{
	helper::TakeNextElementFromString(key,Qid);
	element_printf("Qid= %B\n", Qid);
}
void user::GetR(string Rz)
{
	helper::TakeNextElementFromString(Rz,R);
	element_printf("R = %B\n", R);
}

void user::GetEl(string P_Pub)
{
  helper::TakeNextElementFromString(P_Pub,Ppub);
  helper::TakeNextElementFromString(P_Pub,P);

}

void user::SendCBlind()
{
	string mes("hello");
  element_t t1, t2, t3, t5,t6;
  element_init_G1(t1, pairing);
  element_init_G1(t2, pairing);
  element_init_Zr(t5, pairing);
  element_init_Zr(t6, pairing);
  element_init_GT(t3, pairing);
	printf("Blinding\n");
	  element_mul_zn(t1, P, a);
	  element_add(t1, R, t1);
	  element_mul_zn(t2, Qid, b);
	  element_add(t2, t2, t1);
	  pairing_apply(t3, t2, Ppub, pairing);
	   element_from_hash(t5, (char*)mes.c_str(), 6);
	   element_printf("t5 SUKAAAAAAAAAA = %B\n", t5);
	  element_mul_zn(t6, t5, t3);
	  element_add(c, t6, b);
	  printf("User sends c to signer\n");
	  element_printf("c = %B\n", c);
	  
	    
  element_clear(t1);
  element_clear(t2);
  element_clear(t3);
  element_clear(t5);
  element_clear(t6);
}
void user::unblinding()
{
	element_t t9,S_,c_;
	element_init_G1(t9, pairing);
	element_init_G1(S_, pairing);
	element_init_G1(c_, pairing);
	printf("Unblinding\n");
	element_printf("c = %B\n", c);
  element_mul_zn(t9, Ppub, a);
  element_add(S1, S, t9);
  element_printf("c = %B\n", c);
  element_printf("b = %B\n", b);
  element_sub(c1, c, b);
  element_printf("c after - = %B\n", c1);
  printf("Blind Signature of message \"Message\" is:\n");
  element_printf("S in unblinding = %B\n", S1);
  element_add(c,c,b);
  element_printf("c1 = %B\n", c1);
  element_clear(t9);
}

void user::sendgit(string &git)
{
	git=helper::sendgit(c1,S1);
	element_printf("S1 in unblinding = %B\n", S1);
    element_printf("c1 in unblinding = %B\n", c1);
}
void user::sendC(string &blind)
{
	blind=helper::blind(c);
	element_printf("CSEND = %B\n", c);
}
void user::GetS(string sig)
{
	helper::TakeNextElementFromString(sig,S);
	element_printf("S it gets = %B\n", S);
}
void user::Verf()
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