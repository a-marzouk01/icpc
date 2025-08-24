#include <bits/stdc++.h>

typedef long long ll; 

const ll MAX = 1e6 + 10;
const ll MOD = 1e9 + 7;

using namespace std;

// a function that returns a vector stating wether a number is a prime or not, note max is limited to 1e6 or vector max
vector<bool> sieve(long long n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (long long i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (long long j = i * i; j <= n; j += i)
                isPrime[j] = false;
        }
    }
    return isPrime;
}

// Linear sieve (more efficient)
vector<int> linearSieve(int n) {
    vector<int> spf(n + 1); // smalong longest prime factor
    vector<int> primes;

    for (int i = 2; i <= n; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }

        for (int j = 0; j < (int)primes.size() && primes[j] <= spf[i] && i * primes[j] <= n; j++) {
            spf[i * primes[j]] = primes[j];
        }
    }
    return primes;
}

// Segmented sieve for large ranges
vector<bool> segmentedSieve(long long L, long long R) {
    long long lim = sqrtl(R);
    vector<bool> mark(lim + 1, false);
    vector<long long> primes;

    for (long long i = 2; i <= lim; ++i) {
        if (!mark[i]) {
            primes.push_back(i);
            for (long long j = i * i; j <= lim; j += i)
                mark[j] = true;
        }
    }

    vector<bool> isPrime(R - L + 1, true);
    for (long long i : primes) {
        for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = false;
    }

    if (L == 1) isPrime[0] = false;
    return isPrime;
}

// Count primes up to n using lehmer algorithm (approximation)
long long countPrimes(long long n) {
    if (n < 2) return 0;

    long long sqrtn = sqrt(n);
    vector<bool> is_prime = sieve(sqrtn);
    vector<int> primes;
    for (int i = 2; i <= sqrtn; i++) {
        if (is_prime[i]) primes.push_back(i);
    }

    // Simple counting for demonstration
    long long count = 0;
    vector<bool> segment = segmentedSieve(2, n);
    for (bool prime : segment) {
        if (prime) count++;
    }
    return count;
}

// Check if n can be expressed as sum of two primes (Goldbach's conjecture)
pair<int, int> goldbach(int n) {
    if (n <= 2 || n % 2 != 0) return {-1, -1};

    vector<bool> is_prime = sieve(n);
    for (int i = 2; i <= n / 2; i++) {
        if (is_prime[i] && is_prime[n - i]) {
            return {i, n - i};
        }
    }
    return {-1, -1};
}

// returns a vector containing the prime factors of x
vector<long long> primefactors(ll x) {
    vector<long long> factors;
    
    while (x % 2 == 0) {
        factors.push_back(2);
        x /= 2;
    }
    
    for (long long i = 3; i * i <= x; i += 2) {
        while (x % i == 0) {
            factors.push_back(i);
            x /= i;
        }
    }
    
    if (x > 2) {
        factors.push_back(x);
    }
    
    return factors;
}

// get the divisors of a number
vector<long long> factors(ll n) {
    vector<long long> divisors;
    for (long long i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i != n / i) {
                divisors.push_back(n / i);
            }
        }
    }
    sort(divisors.begin(), divisors.end());
    return divisors;
}

// Fast prime factorization using precomputed smalong longest prime factors
vector<pair<int, int>> factorizeWithSPF(int n, const vector<int>& spf) {
    vector<pair<int, int>> factors;

    while (n > 1) {
        int p = spf[n];
        int count = 0;
        while (n % p == 0) {
            n /= p;
            count++;
        }
        factors.push_back({p, count});
    }
    return factors;
}

// Sum of divisors function
vector<long long> sigma(int n, int k = 1) {
    vector<long long> result(n + 1, 1);

    for (int i = 2; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            long long power_i = 1;
            for (int p = 0; p < k; p++) {
                power_i *= i;
            }
            result[j] += power_i;
        }
    }

    return result;
}


// Number of divisors function
vector<int> tau(int n) {
    vector<int> result(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            result[j]++;
        }
    }

    return result;
}


