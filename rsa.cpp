#include "rsa.h"
#include <vector>
#include <random>
#include <chrono>
using namespace std;

constexpr int MAX16 = 65535;

// ----- Sito Eratostenesa -----
vector<bool> sieve_eratosthenes()
{
    vector<bool> is_prime(MAX16 + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int p = 2; p * p <= MAX16; ++p)
    {
        if (is_prime[p])
        {
            for (int q = p * p; q <= MAX16; q += p)
                is_prime[q] = false;
        }
    }
    return is_prime;
}

vector<int> all_primes16()
{
    vector<bool> is_prime = sieve_eratosthenes();
    vector<int> primes;

    for (int i = 2; i <= MAX16; ++i)
        if (is_prime[i])
            primes.push_back(i);

    return primes;
}

int random_prime(const vector<int>& primes)
{
    static mt19937_64 rng(
        (unsigned) chrono::high_resolution_clock::now().time_since_epoch().count()
    );
    uniform_int_distribution<size_t> dist(0, primes.size() - 1);
    return primes[dist(rng)];
}

// // ----- Potęgowanie modularne -----
// long long power_mod(long long a, long long d, long long n)
// {
//     long long result = 1;
//     a %= n;

//     while (d > 0)
//     {
//         if (d & 1)
//             result = (__int128)result * a % n;

//         a = (__int128)a * a % n;
//         d >>= 1;
//     }
//     return result;
// }

long long mul_mod(long long a, long long b, long long mod)
{
    long long result = 0;
    a %= mod;

    while (b > 0)
    {
        if (b & 1)
            result = (result + a) % mod;

        a = (a * 2) % mod;
        b >>= 1;
    }

    return result;
}

long long power_mod(long long a, long long d, long long mod)
{
    long long result = 1;
    a %= mod;

    while (d > 0)
    {
        if (d & 1)
            result = mul_mod(result, a, mod);

        a = mul_mod(a, a, mod);
        d >>= 1;
    }

    return result;
}




// // ----- Test Millera–Rabina -----
// bool miller_rabin_test(long long n, long long a, long long d, int s)
// {
//     long long x = power_mod(a, d, n);
//     if (x == 1 || x == n - 1)
//         return true;

//     for (int r = 1; r < s; r++)
//     {
//         x = (__int128)x * x % n;
//         if (x == n - 1)
//             return true;
//     }
//     return false;
// }



bool miller_rabin_test(long long n, long long a, long long d, int s)
{
    long long x = power_mod(a, d, n);

    if (x == 1 || x == n - 1)
        return true;

    for (int r = 1; r < s; r++)
    {
        x = mul_mod(x, x, n); // zamiast (__int128)x * x % n

        if (x == n - 1)
            return true;
    }

    return false;
}





bool is_probable_prime(long long n, int k)
{
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    long long d = n - 1;
    int s = 0;

    while (d % 2 == 0)
    {
        d /= 2;
        s++;
    }

    mt19937_64 gen(time(nullptr));
    uniform_int_distribution<long long> dist(2, n - 2);

    for (int i = 0; i < k; i++)
    {
        long long a = dist(gen);
        if (!miller_rabin_test(n, a, d, s))
            return false;
    }
    return true;
}

// ----- Algorytm Euklidesa -----
long long euklides(long long a, long long b, long long& x, long long& y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    long long x1, y1;
    long long g = euklides(b, a % b, x1, y1);

    x = y1;
    y = x1 - y1 * (a / b);

    return g;
}

long long mod_inverse(long long a, long long m)
{
    long long x, y;
    long long g = euklides(a, m, x, y);

    if (g != 1)
        return -1;

    return (x % m + m) % m;
}
