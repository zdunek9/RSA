#include "rsa.h"
#include <boost/random.hpp>
#include <boost/random/uniform_int_distribution.hpp> // naprawa dla dist
#include <chrono>
#include <ctime>
#include <iostream>

using namespace std;
using namespace boost::random;

// Generator globalny
// 1024
typedef independent_bits_engine<mt19937, 1024, BigInt> generator_type;
// 2048
// typedef independent_bits_engine<mt19937, 2048, BigInt> generator_type;
generator_type gen(clock());

// Potęgowanie modularne: (a^d) % n
BigInt power_mod(BigInt a, BigInt d, BigInt n)
{
    BigInt result = 1;
    a = a % n;
    while (d > 0)
    {
        if ((d & 1))
            result = result * a % n;
        a = a * a % n;
        d >>= 1;
    }
    return result;
}

bool miller_rabin_test(BigInt n, BigInt a, BigInt d, int s)
{
    BigInt x = power_mod(a, d, n);
    if (x == 1 || x == n - 1)
        return true;

    for (int r = 1; r < s; r++)
    {
        x = x * x % n;
        if (x == n - 1)
            return true;
    }
    return false;
}

bool is_probable_prime(BigInt n, int k)
{
    if (n < 2)
        return false;
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0)
        return false;

    BigInt d = n - 1;
    int s = 0;
    while (d % 2 == 0)
    {
        d /= 2;
        s++;
    }

    // jawna ścieżka do uniform_int_distribution
    boost::random::uniform_int_distribution<BigInt> dist(2, n - 2);

    for (int i = 0; i < k; i++)
    {
        BigInt a = dist(gen);
        if (!miller_rabin_test(n, a, d, s))
            return false;
    }
    return true;
}

BigInt get_random_prime_1024()
{
    BigInt n;
    while (true)
    {
        n = gen();
        // 1024
        bit_set(n, 1023);
        // 2048
        //  bit_set(n, 2047);
        bit_set(n, 0);

        if (is_probable_prime(n, 20))
        {
            return n;
        }
    }
}

BigInt euklides(BigInt a, BigInt b, BigInt &x, BigInt &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    BigInt x1, y1;
    BigInt g = euklides(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

BigInt mod_inverse(BigInt a, BigInt m)
{
    BigInt x, y;
    BigInt g = euklides(a, m, x, y);
    if (g != 1)
        return -1;
    return (x % m + m) % m;
}

// Szyfrowanie: c = m^e mod n
BigInt RSA_encrypt(const BigInt &m, const BigInt &e, const BigInt &n)
{
    if (m >= n)
    {
        cerr << "Blad: wiadomosc m musi byc mniejsza od n!" << endl;
        return -1;
    }
    return power_mod(m, e, n);
}

// Odszyfrowanie: m = c^d mod n
BigInt RSA_decrypt(const BigInt &c, const BigInt &d, const BigInt &n)
{
    if (c >= n)
    {
        cerr << "Blad: szyfrogram c musi byc mniejszy od n!" << endl;
        return -1;
    }
    return power_mod(c, d, n);
}
