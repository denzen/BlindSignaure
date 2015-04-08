#include "manager.h"

using namespace std;
Manager::Manager()
{
	pairing_init_set_str(pairing, _PAIRING_PARAM_);
	element_init_G1(P, pairing);
  	element_init_G1(Ppub, pairing);
  	element_init_Zr(s, pairing);
    element_init_G1(Qid, pairing);
    element_init_G1(Sid, pairing);
}
Manager::~Manager()
{
	element_clear(P);
	element_clear(Ppub);
	element_clear(s);
	pairing_clear(pairing);
}
void Manager::KeyGeneration(string & P_Ppub1)
{
	printf("Zhang and Kim ID-based Blind Signature scheme\n");
  printf("SETUP\n");
  element_random(P);
  element_random(s);
  element_mul_zn(Ppub, P, s);
  element_printf("P = %B\n", P);
  element_printf("s = %B\n", s);
  element_printf("Ppub = %B\n", Ppub);
  P_Ppub1=helper::P_PpubToString(Ppub,P);
}

void Manager::Setup(string s1, string& key)
{
  
  printf("EXTRACT\n");
  string ha=helper::Hash_ID(s1);
  element_from_hash(Qid, (void*)ha.c_str(), ha.length());
  element_mul_zn(Sid, Qid, s);
  element_printf("Sid = %B\n", Sid);
  element_printf("Qid = %B\n", Qid);
  key=helper::SQToString(Qid, Sid);
}

