//#include<iostream>
//#include <stdlib.h>
//#include<stdio.h>
#include <gmp.h>
#include<set>
#include <sstream>
//#include <string>
//#include<cmath>
//#include <unistd.h>
#include <fcntl.h>
#include <bits/stdc++.h>

using namespace std;
void get_random_n_bits(mpz_t r, size_t bits)
{
    size_t size = (size_t) ceilf(bits/8);
    char *buffer = (char*) malloc(sizeof(char)*size);
    int prg = open("/dev/random", O_RDONLY);
    read(prg, buffer, size);
    close(prg);
    mpz_import (r, size,1,sizeof(char), 0,0, buffer);
    free(buffer);
}

mpz_t p,d,E2,generator,R,C1,C2,msg,de_msg,temp1,temp2,one,output,t1;
mpz_in()
{
    mpz_init(p);
    mpz_init(d);
    mpz_init(E2);
    mpz_init(generator);

    mpz_init(C1);
    mpz_init(C2);
    mpz_init(msg);
    mpz_init(de_msg);
    mpz_init(temp1);
    mpz_init(temp2);
    mpz_init(one);
    mpz_init(output);
    mpz_init(t1);
}

int prime_num()
{
    mpz_in();
    int PRIMESIZE;
    cout<<"Enter No of bits for P: ";
    cin>>PRIMESIZE;

    char* p_str = new char[PRIMESIZE+1];

    p_str[0] = '1';

    for(int i=1; i<PRIMESIZE; i++)
    {
        p_str[i] = char((rand()%2)+48);

    }
    p_str[PRIMESIZE] = '\0';

    mpz_set_str(p,p_str,2);

    mpz_nextprime(p,p);
    printf("prime number = [%s]\n", mpz_get_str(NULL,10,p));



    do
    {
        get_random_n_bits(generator,mpz_sizeinbase(p,2));
        mpz_nextprime(generator,generator);
    }
    while (mpz_cmp(generator,p)>=0);

    printf("generator number = [%s]\n", mpz_get_str(NULL,10,generator));

    do
    {
        printf("Enter a private number: ");
        char dd[1024];
        cin>>dd;
        mpz_set_ui(d,0);
        mpz_set_str(d,dd,10);
    }
    while(!(mpz_cmp(d, p) < 0) );



    printf("private number = [%s]\n", mpz_get_str(NULL,10,d));
    mpz_set_ui(one,1);

    mpz_powm(E2,generator,d,p);

    do
    {
        printf("Enter a random number: ");
        char RR[1024];
        cin>>RR;
        mpz_set_str(R,RR,10);
    }
    while(!(mpz_cmp(R, p) < 0) );


    mpz_powm(C1,generator,R,p);

    do
    {
        printf ("Enter your msg: ");
        char msg2[1024];
        cin>>msg2;
        mpz_set_str(msg,msg2,10);
    }
    while(!(mpz_cmp(msg, p) < 0) );

    printf("Original Message = [%s]\n", mpz_get_str(NULL,10,msg));

    mpz_powm(temp1,E2,R,p);
    mpz_mul(temp2,msg,temp1);
    mpz_powm(C2,temp2,one,p);

    printf("Encrypt Message [Y1] = [%s]\n\n", mpz_get_str(NULL,10,temp1));
    printf("Encrypt Message [Y2] = [%s]\n", mpz_get_str(NULL,10,C2));

    mpz_powm(C1, C1, d, p);
    mpz_invert(C1, C1, p);
    mpz_mul(de_msg, C2, C1);
    mpz_mod(de_msg, de_msg, p);
    printf("Decrypt msg = [%s]\n", mpz_get_str(NULL,10,de_msg));

}

int main()
{
    prime_num();
}
