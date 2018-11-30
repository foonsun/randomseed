#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <openssl/rand.h>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
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
    hash_combine(hash, to_hex((char *)(seed1), sizeof(seed1)));
    hash_combine(hash, to_hex((char *)(seed2), sizeof(seed2)));
    random_roll[1] = hash % 6 + 1;
    hash_combine(hash, to_hex((char *)(seed1), sizeof(seed1)));
    hash_combine(hash, to_hex((char *)(seed2), sizeof(seed2)));
    random_roll[2] = hash % 6 + 1;
    hash_combine(hash, to_hex((char *)(seed1), sizeof(seed1)));
    hash_combine(hash, to_hex((char *)(seed2), sizeof(seed2)));
    random_roll[3] = hash % 6 + 1;
    hash_combine(hash, to_hex((char *)(seed1), sizeof(seed1)));
    hash_combine(hash, to_hex((char *)(seed2), sizeof(seed2)));
    random_roll[4] = hash % 6 + 1;
    hash_combine(hash, to_hex((char *)(seed1), sizeof(seed1)));
    hash_combine(hash, to_hex((char *)(seed2), sizeof(seed2)));
    random_roll[5] = hash % 6 + 1;

    /*
    std::ofstream outFile;
    outFile.open("bobingresult.csv", std::ios::app);
    outFile << int(random_roll[0]) << ',' << int(random_roll[1]) << ',' << int(random_roll[2]) << ',' << int(random_roll[3]) << ','
    << int(random_roll[4]) << ',' << int(random_roll[5]) << '\n';
    outFile.close();
    */
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

void compute_result(uint8_t (&random_roll)[6], int32_t (&result)[13]) {
    uint8_t one_count = 0;
    uint8_t two_count = 0;
    uint8_t three_count = 0;
    uint8_t four_count = 0;
    uint8_t five_count = 0;
    uint8_t six_count = 0;
    for(int i = 0; i < sizeof(random_roll); i++) {
        uint8_t roll_number = random_roll[i];
        switch(roll_number){
            case 1:
                one_count++;
                break;
            case 2:
                two_count++;
                break;
            case 3:
                three_count++;
                break;
            case 4:
                four_count++;
                break;
            case 5:
                five_count++;
                break;
            case 6:
                six_count++;
                break;
            default:
                printf("roll number must be between 1 and 6\n");
        }
    }
// calculate result
    if (six_count == 6 || five_count == 6 || three_count == 6 || two_count == 6) {
        //guandengqiang
        result[0]++;
    }
    else if(four_count == 6){
        //liubeihong
        result[1]++;
    }
    else if(four_count == 4 && one_count == 2){
        //CHAJINHUA;
        result[2]++;
    }
    else if(one_count == 6){
        //biandijin
        result[3]++;
    }
    else if(four_count == 5){
        //WUHONG
        result[4]++;
    }
    else if(six_count == 5 || five_count == 5 || three_count == 5 || two_count == 5 || one_count == 5){
        //WUZIDENGKE
        result[5]++;
    }
    else if(four_count == 4){
        //SIDIANHONG
        result[6]++;
    }
    else if(one_count == 1 && two_count == 1 && three_count == 1 && four_count == 1 && five_count == 1 && six_count == 1){
        //DUITANG
        result[7]++;
    }
    else if(four_count == 3){
        //SANHONG
        result[8]++;
    }
    else if(three_count == 4 || two_count == 4 || one_count == 4 || five_count == 4 || six_count == 4){
        //SIJIN
        result[9]++;
    }
    else if(four_count == 2){
        //ERJU
        result[10]++;
    }
    else if(four_count == 1){
        //YIXIU
        result[11]++;
    }
    else{
        //FAPAI
        result[12]++;
    }
}

int main(int argc, char * argv[])
{
    unsigned char *seed1 = (unsigned char *)malloc(32);
    unsigned char *seed2 = (unsigned char *)malloc(16);
    uint8_t random_roll[6] = {0};
    int one = 0;
    int two = 0;
    int three = 0;
    int four = 0;
    int five = 0;
    int six = 0;
    int result[13] = {0};
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

        compute_result(random_roll, result);

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
    printf("关灯抢: %d 六杯红: %d  插金花: %d 遍地锦: %d 五红: %d 五子登科: %d 四点红: %d 对堂: %d 三红: %d 四进: %d 二举: %d \
    一秀: %d 罚牌: %d \n",result[0],result[1],result[2],result[3],result[4],result[5],result[6],result[7],result[8],result[9],\
    result[10],result[11],result[12]);
}
