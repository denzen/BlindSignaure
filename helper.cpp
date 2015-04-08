#include "helper.h"
using namespace std;
string helper::Hash_ID(string ID)
{
    unsigned char h[20];
    char hex[41];
    sha1::calc((void*)ID.c_str(),ID.length(),h);
    sha1::toHexString(h,hex);
    string hash(hex);
    printf("Hash= %s\n",hash.c_str());
    return hash;
}
string helper::Element_to_BASE_58(element_t elem)
{
    int len=element_length_in_bytes(elem);
    unsigned char* buf=new unsigned char[len];
    element_to_bytes(buf,elem);
    string ret=EncodeBase58(buf, len);
    delete[]buf;
    return ret;
}
string helper::P_PpubToString(element_t Ppub, element_t P)
{
  string P_Ppub;
    P_Ppub.append(Element_to_BASE_58(Ppub)+"\n");
    P_Ppub.append(Element_to_BASE_58(P)+"\n");
    
    return P_Ppub;
}
void helper::Element_from_BASE_58(element_t elem,string elem_base58)
{
    int len=elem_base58.length();
    unsigned char* buf=new unsigned char[len];
    DecodeBase58(elem_base58, buf, len);
    element_from_bytes(elem,buf);
    delete[]buf;
}
void helper::TakeNextElementFromString(string & str,element_t elem)
{
	string tmp;
	size_t pos;
    pos=str.find("\n");
	tmp=str.substr(0,pos);
	str.erase(0,pos+1);
	Element_from_BASE_58(elem,tmp);
}
string helper::Element_to_string(element_t elem)
{
	string el;
    el.append(Element_to_BASE_58(elem)+"\n");
    
    
    return el;
}
string helper::Signature_to_string(element_t c)
{
	string signature;
	Element_to_string(c);
	return signature;
}

void helper::Hash_C(element_t res,element_t t,  char* mes, int len_mes)
{
    int len1=element_length_in_bytes(t);
    int len2=len1+len_mes;
    unsigned char*buf=new unsigned char[len2];
    element_to_bytes(buf,t);
    strcpy((char*)buf+len1,mes);
    unsigned char hash[20];
    sha1::calc(buf,len2,hash);
    element_from_hash(res,(void*)hash,20);
    delete[]buf;
}
string helper::SQToString(element_t Qid, element_t Sid)
{
  string key;
    key.append(Element_to_BASE_58(Qid)+"\n");
    key.append(Element_to_BASE_58(Sid)+"\n");
    
    return key;
}
string helper::blind(element_t c)
{
  string blind;
    blind.append(Element_to_BASE_58(c)+"\n");
    
    return blind;
}
string helper::sendgit(element_t c1, element_t S1)
{
  string blind;
    blind.append(Element_to_BASE_58(c1)+"\n");
    blind.append(Element_to_BASE_58(S1)+"\n");
    

    
    return blind;
}