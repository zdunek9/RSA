#ifndef RSA_H
#define RSA_H

#include <boost/multiprecision/cpp_int.hpp>
#include <vector>
using BigInt = boost::multiprecision::cpp_int;

// Deklaracja globalnego generatora
#include <boost/random.hpp>
//1024
typedef boost::random::independent_bits_engine<boost::random::mt19937, 1024, BigInt> generator_type;
//2048
// typedef boost::random::independent_bits_engine<boost::random::mt19937, 2048, BigInt> generator_type;
extern generator_type gen;

// Funkcje RSA
BigInt power_mod(BigInt a, BigInt d, BigInt n);
bool is_probable_prime(BigInt n, int k = 5);
BigInt get_random_prime_1024();
BigInt euklides(BigInt a, BigInt b, BigInt& x, BigInt& y);
BigInt mod_inverse(BigInt a, BigInt m);
BigInt RSA_encrypt(const BigInt& m, const BigInt& e, const BigInt& n);
BigInt RSA_decrypt(const BigInt& c, const BigInt& d, const BigInt& n);
void test_euklides();
#endif // RSA_H
