#include <string>
#include "pbc.h"
#include "sha1.h"
#include "helper.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


using namespace std;
class Manager
{
	public:
		Manager();
		void KeyGeneration(string & P_Ppub1);
		void Setup(string s1, string& key);
		~Manager();
	private:
		pairing_t pairing;
		element_t P;
	    element_t s;
	    element_t Ppub;
	    element_t Qid;
	    element_t Sid;
};