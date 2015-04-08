#include <string>
#include "pbc.h"
#include "sha1.h"
#include "helper.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define _PAIRING_PARAM_ "type a\n\
q 8780710799663312522437781984754049815806883199414208211028653399266475630880222957078625179422662221423155858769582317459277713367317481324925129998224791\n\
h 12016012264891146079388821366740534204802954401251311822919615131047207289359704531102844802183906537786776\n\
r 730750818665451621361119245571504901405976559617\n\
exp2 159\n\
exp1 107\n\
sign1 1\n\
sign0 1"
using namespace std;

class user
{
public:
	user();
	void GetR(string Rz);
	void GetEl(string P_Pub);
	void GetQid(string key);
	void SendCBlind();
	void sendC(string &blind);
	void GetS(string sig);
	void unblinding();
	void Verf();
	void sendgit(string &git);
	~user();
private:
	pairing_t pairing;
	element_t P;
	element_t R;
	element_t Ppub;
	element_t c;
	element_t Qid;
	element_t S;
	element_t a;
	element_t b;
	element_t S1;
	element_t c1;
};