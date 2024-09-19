

#include <iostream>
#include<cmath>
#include<thread>
#include<vector>
#include<chrono>

using namespace std;
using namespace std::chrono;

bool isPrimeSingleThread(unsigned long long num) {
    if (num <= 1) return false;
    for (unsigned long long i = 2;i <= sqrt(num);i++) {
        if (num % i == 0)return false;
    }
    return true;
}
void checkPrime(unsigned long long num, unsigned long long start, unsigned long long end, bool& isPrime) {
    for (unsigned long long i = start;i < end;i++) {
        if (num % i == 0) {
            isPrime = false;
            return;
        }
    }
}
bool isPrimeMultiThread(unsigned long long num) {
    if (num <= 1)return false;
    unsigned long long limit = sqrt(num);
    unsigned long long rangeSize = limit / 5;
    vector<thread> threads;
    bool isPrime = true;

    for (unsigned long long i = 0;i < 5;i++) {
        unsigned long long start = (i == 0) ? 2 : i * rangeSize;
        unsigned long long end = (i == 4) ? limit : (i + 1) * rangeSize;
        threads.push_back(thread(checkPrime, num, start, end, ref(isPrime)));
    }
    for (thread& t : threads) {
        t.join();
    }
    return isPrime;
}
void checkAndTime(bool (*func)(unsigned long long), unsigned long long num, const string& s) {
    auto start = high_resolution_clock::now();
    bool res = func(num);
    auto end = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(end - start);

    cout << s << " ,number: " << num << " ,is prime: " << (res ? "yes " : "no ") << " ,time: " << time.count() << endl;
}
int main()
{
    vector<unsigned long long> nums = { 5321,412321,43232171,43232174323217 };
    for (unsigned long long num : nums) {
        checkAndTime(isPrimeSingleThread, num, "single thread");
        checkAndTime(isPrimeMultiThread, num, "5 thread");

    }
    // דוגמא שכן עובדת ומראה את ההבדל: 
    /*unsigned long long num = 12963097176472289281;
    checkAndTime(isPrimeSingleThread, num, "***single thread");
    checkAndTime(isPrimeMultiThread, num, "***5 thread");*/

}
