#ifndef _HELPER_
#define _HELPER_
#include <string>
#include "pbc.h"
#include "sha1.h"
#include "base58.h"
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
class helper
{
public:
	helper();
	static string P_PpubToString(element_t Ppub, element_t P);
	static string Element_to_BASE_58(element_t elem);
	static string Hash_ID(string ID);
	static void Element_from_BASE_58(element_t elem,string elem_base58);
	static void TakeNextElementFromString(string & str,element_t elem);
	static string Element_to_string(element_t elem);
	static string Signature_to_string(element_t c);
	static void Hash_C(element_t res,element_t t, char* mes, int len_mes);
	static string SQToString(element_t Qid, element_t Sid);
	static string blind(element_t c);
	static string sendgit(element_t c1, element_t S1);
	~helper();
	
};
#endif