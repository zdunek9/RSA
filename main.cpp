#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

constexpr int MAX16 = 65535;

// Sito Eratostenesa
vector<bool> sito_Eratostenesa()
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
    vector<bool> is_prime = sito_Eratostenesa();
    vector<int> primes;
    for (int i = 2; i <= MAX16; ++i)
        if (is_prime[i])
            primes.push_back(i);
    return primes;
}

int random_prime(const vector<int> &primes)
{
    static mt19937_64 rng(
        (unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<size_t> dist(0, primes.size() - 1);
    return primes[dist(rng)];
}

// Potęgowanie modularne: (a^d) % n
long long power_mod(long long a, long long d, long long n)
{
    long long result = 1;
    a = a % n;
    while (d > 0)
    {
        if (d & 1)
            result = (__int128)result * a % n;
        a = (__int128)a * a % n;
        d >>= 1;
    }
    return result;
}

// Jeden test Millera-Rabina dla danego a
bool miller_rabin_test(long long n, long long a, long long d, int s)
{
    long long x = power_mod(a, d, n);
    if (x == 1 || x == n - 1)
        return true;

    for (int r = 1; r < s; r++)
    {
        x = (__int128)x * x % n;
        if (x == n - 1)
            return true;
    }
    return false;
}
// Główna funkcja testu Millera-Rabina
bool is_probable_prime(long long n, int k = 5)
{
    if (n < 2)
        return false;
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0)
        return false;

    // n - 1 = 2^s * d
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
int main()
{
    vector<int> primes = all_primes16();
    int n = random_prime(primes);
    cout << "Wylosowana liczba: " << n << endl;
    if (is_probable_prime(n))
        cout << n << " jest prawdopodobnie liczbą pierwszą.\n";
    else
        cout << n << " jest liczbą złożoną.\n";
    return 0;
}
