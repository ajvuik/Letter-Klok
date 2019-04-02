  #include "WordClock.h"

  bool WordClock_Class::init(void){
    this->Woord[Het].Show=1;
    this->Woord[Het].Pixel=0;
    this->Woord[Het].Pixels=2;

    this->Woord[Is].Pixel=2;
    this->Woord[Is].Pixels=1;

    this->Woord[Was].Pixel=3;
    this->Woord[Was].Pixels=2;

    this->Woord[m_Tien].Pixel=5;
    this->Woord[m_Tien].Pixels=3;

    this->Woord[m_Vijf].Pixel=8;
    this->Woord[m_Vijf].Pixels=3;

    this->Woord[Kwart].Pixel=11;
    this->Woord[Kwart].Pixels=4;

    this->Woord[Voor].Pixel=15;
    this->Woord[Voor].Pixels=3;

    this->Woord[Precies].Pixel=18;
    this->Woord[Precies].Pixels=6;

    this->Woord[Over].Pixel=24;
    this->Woord[Over].Pixels=3;

    this->Woord[Half].Pixel=27;
    this->Woord[Half].Pixels=3;

    this->Woord[Elf].Pixel=30;
    this->Woord[Elf].Pixels=2;

    this->Woord[Twee].Pixel=32;
    this->Woord[Twee].Pixels=3;

    this->Woord[h_Vijf].Pixel=35;
    this->Woord[h_Vijf].Pixels=3;

    this->Woord[Een].Pixel=38;
    this->Woord[Een].Pixels=2;

    this->Woord[Vier].Pixel=40;
    this->Woord[Vier].Pixels=3;

    this->Woord[Twaalf].Pixel=43;
    this->Woord[Twaalf].Pixels=5;

    this->Woord[h_Tien].Pixel=48;
    this->Woord[h_Tien].Pixels=3;

    this->Woord[Drie].Pixel=51;
    this->Woord[Drie].Pixels=3;

    this->Woord[Negen].Pixel=54;
    this->Woord[Negen].Pixels=4;

    this->Woord[Zes].Pixel=58;
    this->Woord[Zes].Pixels=2;

    this->Woord[Acht].Pixel=60;
    this->Woord[Acht].Pixels=3;

    this->Woord[Zeven].Pixel=63;
    this->Woord[Zeven].Pixels=4;

    this->Woord[Uur].Pixel=67;
    this->Woord[Uur].Pixels=2;

    return true;
  }
