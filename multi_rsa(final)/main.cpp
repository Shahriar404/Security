#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>
#include <assert.h>

using namespace std;

int main()
{

    int PRIMESIZE;
    mpz_t p; mpz_init(p);
    mpz_t q; mpz_init(q);
    mpz_t n;
    mpz_init(n);
    mpz_t d1; mpz_init(d1);
    mpz_t e1; mpz_init(e1);
    mpz_t d2; mpz_init(d2);
    mpz_t e2; mpz_init(e2);
    mpz_t d3; mpz_init(d3);
    mpz_t e3; mpz_init(e3);
    mpz_t phi;
    mpz_init(phi);
    mpz_t tmp1;
    mpz_init(tmp1);
    mpz_t tmp2;
    mpz_init(tmp2);
    mpz_t msg;
    mpz_init(msg);
    mpz_t cip1; mpz_init(cip1);
    mpz_t dcr1; mpz_init(dcr1);
    mpz_t cip2; mpz_init(cip2);
    mpz_t dcr2; mpz_init(dcr2);
    mpz_t cip3; mpz_init(cip3);
    mpz_t dcr3; mpz_init(dcr3);

    cout<<"Enter No of bits for P and Q: ";
    cin>>PRIMESIZE;

    //P Q
    char* p_str = new char[PRIMESIZE+1];
    char* q_str = new char[PRIMESIZE+1];



    p_str[0] = '1';
    q_str[0] = '1';

    for(int i=1; i<PRIMESIZE; i++)
        p_str[i] = char((rand()%2)+48);

    for(int i=1; i<PRIMESIZE; i++)
        q_str[i] = char((rand()%2)+48);

    p_str[PRIMESIZE] = '\0';
    q_str[PRIMESIZE] = '\0';
    mpz_set_str(p,p_str,2);
    mpz_set_str(q,q_str,2);
    mpz_nextprime(p,p);
    mpz_nextprime(q,q);

    mpz_mul(n, p, q);

    mpz_sub_ui(tmp1, p, 1);
    mpz_sub_ui(tmp2, q, 1);
    mpz_mul(phi, tmp1, tmp2);

    mpz_set_ui(msg, 1122334455);

    mpz_init_set_ui(e1, 2);
    while(1){
        mpz_gcd(tmp1, e1, phi);
        if(! mpz_cmp_ui(tmp1, 1))
            break;
        mpz_nextprime(e1,e1);
    }
    mpz_invert(d1, e1, phi);
    mpz_powm(cip1, msg, e1, n);

    // e2 d2
    mpz_nextprime(e2,e1);
    while(1){
        mpz_gcd(tmp1, e2, phi);
        if(! mpz_cmp_ui(tmp1, 1))
            break;
        mpz_nextprime(e2,e2);
    }
    mpz_invert(d2, e2, phi);
    mpz_powm(cip2, cip1, e2, n);

    // e3 d3
    mpz_nextprime(e3,e3);
    while(1){
        mpz_gcd(tmp1, e3, phi);
        if(! mpz_cmp_ui(tmp1, 1))
            break;
        mpz_nextprime(e3,e3);
    }
    mpz_invert(d3, e3, phi);
    mpz_powm(cip3, cip2, e3, n);


    cout << "e and d" << endl;
    cout <<  mpz_out_str(stdout,10,e1) << " " << mpz_out_str(stdout,10,d1) << endl;
    cout <<  mpz_out_str(stdout,10,e2) << " " << mpz_out_str(stdout,10,d2) << endl;
    cout <<  mpz_out_str(stdout,10,e3) << " " << mpz_out_str(stdout,10,d3) << endl;


    //decrypt a message

    mpz_powm(dcr1, cip3, d1, n);
    mpz_powm(dcr2, dcr1, d2, n);
    mpz_powm(dcr3, dcr2, d3, n);

    cout << endl;
    cout << "Original message: ";
    mpz_out_str(stdout,10,msg);
    cout << endl;
    cout << "encrypted message for party 1: "; mpz_out_str(stdout,10,cip1); cout << endl;
    cout << "encrypted message for party 2: "; mpz_out_str(stdout,10,cip2); cout << endl;
    cout << "encrypted message for party 3: "; mpz_out_str(stdout,10,cip3); cout << endl;
    cout << "decrypted message for party 1: "; mpz_out_str(stdout,10,dcr1); cout << endl;
    cout << "decrypted message for party 2: "; mpz_out_str(stdout,10,dcr2); cout << endl;
    cout << "decrypted message for party 3: "; mpz_out_str(stdout,10,dcr3); cout << endl;
    return 0;
}
