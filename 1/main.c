#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
//shitcode one love, so it dream(sleap)
void block_(char*string,unsigned char*result,unsigned char*result1,unsigned long * counter)
{
 while(*string)
 {
  for(unsigned short i = 8;i--;)
  {
   *result^=(*string^*(string+1) & 0xFF);
   string+=2;
   *counter+=2;
  }
  *result1+=*result;
 }

}

void first(char*string)
{
 unsigned char result __attribute__((aligned(8)));
 unsigned char result1 __attribute__((aligned(8)));
 unsigned long counter_string_size=0;
 block_(string,&result,&result1,&counter_string_size);
 result=(result|result1) & 0xFF;
 *string++=result;
for(counter_string_size;counter_string_size--;)
  *string++=0;
*string='\0';
}

void second(char*string)
{
char hash[SHA512_DIGEST_LENGTH];
SHA512(string, strlen(string) - 1, hash);
for(unsigned short i =0;hash[i];i++)
 *string++=hash[i++];
*string++='\0';
}

void final(unsigned char*string)
{
 first(string);
 second(string);
 char tmp[strlen(string)];
 unsigned short counter=0;
while(*string)
{
 tmp[counter++]=(*string % 16)+'0';
 *string= *string/16;
 *string++;
}
tmp[counter++]='\0';
for(counter;counter--;)
 *string--=tmp[counter];
}

void main(void)
{
unsigned char * buffer = strdup("Test String");
first(buffer);
second(buffer);
final(buffer);
printf("Result: %s\n",buffer);
}
