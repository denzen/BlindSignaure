# BlindSignature
ID-Based Blind Signature from Pairing  by Zangguo Zhang and Kwangjo Kim
In this lib you have three main programms: manager, that SETUP and EXTRACT keys; user. that BLIND and then UNNBLINDING signature, that signer SIGN.

	1) Function KeyGeneraton of the class manager.
	
	2) Setup of the same class.
	
	3)GetEl, class Signer, to get P and Ppub.
	
	4)GetQid_Sid to get open and secret key
	
	5) sendR to send R to user.
	
	6) GetEl to get P and Pub for user class.
	
	7)GetQid - get open signers open key
	
	8)SendCBlind - compute blinding 
	
	9)SendC - and send it to signer
	
	10) Signing - signer compute S and send it to user
	
	11)GetS - user gets S
	
	12) unblinding - user unblind the signature.
	
	13)Verf - cheking if the signature is true.
	
