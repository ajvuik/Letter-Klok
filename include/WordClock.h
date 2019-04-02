
#ifndef WORDCLOCK_H
#define WORDCLOCK_H
#include <Arduino.h>


#define Het     0
#define Is      1
#define Was     2

#define m_Vijf  3
#define m_Tien  4

#define Kwart   5
#define Voor    6

#define Over    7
#define Precies 8

#define Half    9
#define Elf     10

#define h_Vijf  11
#define Twee    12

#define Een     13
#define Vier    14

#define h_Tien  15
#define Twaalf  16

#define Drie    17
#define Negen   18

#define Acht    19
#define Zes     20

#define Zeven   21
#define Uur     22

typedef struct{
    uint8_t Show;
    uint8_t Pixel;
    uint8_t Pixels;
}Pixel_Struct;

/*typedef struct{
    Pixel_Struct Woord[23];
    uint8_t Update;
}LetterClock_Struct;
*/

class WordClock_Class{
  public:
    Pixel_Struct Woord[23];
    uint8_t Update;
    bool init(void);
};

#endif //WORDCLOCK_H
