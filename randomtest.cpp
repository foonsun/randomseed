#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <openssl/rand.h>
#include <limits>
//
// Created by 乔晓峰 on 2018/11/28.
//

// copied from boost https://www.boost.org/
template <class T>
inline void hash_combine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

std::string to_hex(const char* d, uint32_t s) {
    std::string r;
    const char* to_hex = "0123456789abcdef";
    uint8_t* c = (uint8_t*)d;
    for (uint32_t i = 0; i < s; ++i)
        (r += to_hex[(c[i] >> 4)]) += to_hex[(c[i] & 0x0f)];
    return r;
}

uint8_t compute_random_roll(unsigned char* seed1, unsigned char* seed2, uint8_t (&random_roll)[6]) {
    size_t hash = 0;
    hash_combine(hash, to_hex((char *)seed1, sizeof(seed1)));
    hash_combine(hash, to_hex((char *)seed2, sizeof(seed2)));

    random_roll[0] = hash % 6 + 1;
    random_roll[1] = (hash >> 1) % 6 + 1;
    random_roll[2] = (hash >> 2) % 6 + 1;
    random_roll[3] = (hash >> 3) % 6 + 1;
    random_roll[4] = (hash >> 4) % 6 + 1;
    random_roll[5] = (hash >> 5) % 6 + 1;
    return 0;
}

bool GetRandomSeed(unsigned char &rnd, int num){
    int chunk=num;
    int r;
    r = RAND_bytes((unsigned char *)&rnd, chunk);
    if(r <= 0 ){
        return false;
    }else{
        return true;
    }

}

int main(int argc, char * argv[])
{
    unsigned char *seed1 = (unsigned char *)malloc(32);
    unsigned char *seed2 = (unsigned char *)malloc(16);
    uint8_t random_roll[6] = {};
    int one = 0;
    int two = 0;
    int three = 0;
    int four = 0;
    int five = 0;
    int six = 0;
    int count = 100000000;
    for(int index = 0; index<count; index++) {
        if (GetRandomSeed(*seed1, 32)) {
            /*
            unsigned char *p = seed1;

            for(int count=0; count<32 ; count++)
            {
                printf("%02X",*(p+count));
            }
            printf("\n");
             */
        }

        if (GetRandomSeed(*seed2, 16)) {
            /*
            unsigned char *p = seed2;
            for(int count=0; count<16 ; count++)
            {
                printf("%02X",*(p+count));
            }
            */
        }
        compute_random_roll((seed1), (seed2), random_roll);

        for (int i = 0; i < 6; i++) {
            int number = random_roll[i];
            switch (number) {
                case 1:
                    one++;
                    break;
                case 2:
                    two++;
                    break;
                case 3:
                    three++;
                    break;
                case 4:
                    four++;
                    break;
                case 5:
                    five++;
                    break;
                case 6:
                    six++;
                    break;
                default:
                    printf("num must be 1-6\n");
                    break;
            }
        }
    }
    printf("one:%d two:%d three:%d four:%d five:%d six:%d total count:%d \n", one, two, three, four, five, six, count);
}
