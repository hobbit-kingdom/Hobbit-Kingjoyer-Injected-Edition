#include "gui.h"
#include "byte_functions.h"
#include "Randommod.h"
#include "memsearch.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"

#include <iostream>
#include "string"
#include <chrono>
#include <random>
#include <thread>

extern bool randommod;
extern int lang;


float timer2 = 0;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(0, 15);
int random_number = distrib(gen);
int a = 0;
bool vkl = false;
bool isRandomModEnabled = false; // Глобальный флаг включения Randommod
bool hair = false;
// Хранилище для текущего активного эффекта
static std::string currentEffect = "None";
static int currentEffectIndex = -1;

/*
// Массив с названиями эффектов (на двух языках)
const char* effectNamesRU[] = {
    (const char*)u8"Невидимый Бильбо",      // 0
    (const char*)u8"Медленный Бильбо",      // 1
    (const char*)u8"Быстрый Бильбо",        // 2
    (const char*)u8"Супербыстрый Бильбо",   // 3
    (const char*)u8"Рендер объектов",       // 4
    (const char*)u8"Высокий прыжок",        // 5
    (const char*)u8"Очень высокий прыжок",  // 6
    (const char*)u8"Широкий Бильбо",        // 7
    (const char*)u8"Режим Диабло",          // 8
    (const char*)u8"Рентген",               // 9
    (const char*)u8"Перевернутая камера",   // 10
    (const char*)u8"Вид от первого лица",   // 11
    (const char*)u8"Вид от второго лица",   // 12
    (const char*)u8"Большой Бильбо",        // 13
    (const char*)u8"Маленький Бильбо"       // 14
};
*/


const char* effectNamesEN[] = {
    "Invisible Bilbo",
    "Slow Bilbo",
    "Fast Bilbo",
    "Super Fast Bilbo",
    "Object Render",
    "High Jump",
    "Very High Jump",
    "Wide Bilbo",
    "Diablo Mode",
    "X-Ray Vision",
    "Flipped Camera",
    "First Person",
    "Second Person",
    "Big Bilbo",
    "Small Bilbo",
    "Raibow Hair"
};

// Функция для получения текущего эффекта
std::string GetCurrentRandomEffect()
{
    extern int lang; // Объявляем внешнюю переменную lang из gui.cpp
    if (currentEffectIndex >= 0 && currentEffectIndex <= 15) {
       // if (lang == 0) // RUS
          //  return effectNamesRU[currentEffectIndex];
     //   else // ENG
            return effectNamesEN[currentEffectIndex];
    }
    return currentEffect;
}

bool IsRandomModActive()
{ 
    return isRandomModEnabled;
}

// https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both#6930407
typedef struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
} hsv;

static hsv   rgb2hsv(rgb in);
static rgb   hsv2rgb(hsv in);

hsv rgb2hsv(rgb in)
{
    hsv         out;
    double      min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;                                // v
    delta = max - min;
    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0; // undefined, maybe nan?
        return out;
    }
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0              
        // s = 0, h is undefined
        out.s = 0.0;
        out.h = NAN;                            // its now undefined
        return out;
    }
    if( in.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
    else
    if( in.g >= max )
        out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
    else
        out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    return out;
}


rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;     
}

static hsv g_currentColor = { 0.f, 1.f, 1.f };

void RandomMod(float vremaeffectof)
{
    extern bool randommod; // Объявляем внешнюю переменную randommod из gui.cpp
    isRandomModEnabled = randommod; // Синхронизируем флаг
    if (1 || hair == true)
    {
        char mat_name[256] = "hair"; 
        static void* pMaterial = memsearch(mat_name, sizeof(mat_name));
        if (pMaterial) {
			g_currentColor.h += 0.66;
			if(g_currentColor.h > 360.0)
				g_currentColor.h -= 360.0;

			rgb currentColor_rgb = hsv2rgb(g_currentColor);

            change_value_hobbit<DWORD>(((char*)pMaterial) + 0x104, 0x01, 0x01);
            char* _pTint = ((char*)pMaterial) + 0x11C;
            float* pTint = (float*)_pTint;
            //float tint[4];

            //std::uniform_int_distribution<> distrib1(0, 255); 
            pTint[0] = currentColor_rgb.r * 255.0;//distrib1(gen); 
            pTint[1] = currentColor_rgb.g * 255.0;//distrib1(gen);  
            pTint[2] = currentColor_rgb.b * 255.0;//distrib1(gen);  
            pTint[3] = 255.f;//distrib1(gen);
        }
    }

    if (!randommod) {
        timer2 = 0;
        return; // Если Randommod выключен, ничего не делаем
    }

    if (vkl == false or timer2 >= vremaeffectof)
    {
        hair = false;
        // Сохраняем индекс текущего эффекта перед его сменой
        currentEffectIndex = random_number;

        if (random_number == 0) change_value_hobbit<BYTE>((LPVOID)0x00777AA0, 0x01, 0x00);  //невидимый Бильбо
        else if (random_number == 1) change_value_hobbit<WORD>((LPVOID)0x0075B852, 0x42C8, 0x4396); //медленный Бильбо
        else if (random_number == 2) change_value_hobbit<DWORD>((LPVOID)0x0075B850, 0x453B8000, 0x43960000); //быстрый Бильбо
        else if (random_number == 3) change_value_hobbit<DWORD>((LPVOID)0x0075B850, 0x461C4000, 0x43960000); //Супербыстрый Бильбо
        else if (random_number == 4)
        {
            change_value_hobbit<BYTE>((LPVOID)0x00777A8C, 0x01, 0x00); //рендер объектов
            change_value_hobbit<BYTE>((LPVOID)0x00777A98, 0x01, 0x00); //рендер ландшафта
        }
        else if (random_number == 5) change_value_hobbit<DWORD>((LPVOID)0x0075B888, 0x447A0000, 0x453B8000); //высокий прыжок
        else if (random_number == 6) change_value_hobbit<DWORD>((LPVOID)0x0075B888, 0x42C80000, 0x453B8000); //очень высокий прыжок
        else if (random_number == 7) change_value_hobbit<WORD>((LPVOID)0x0077244A, 0x4080, 0x0000); //широкий Бильбо
        else if (random_number == 8) change_value_hobbit<BYTE>((LPVOID)0x0045CA39, 0xD4, 0xD8);//типо диабло
        else if (random_number == 9) change_value_hobbit<WORD>((LPVOID)0x00772BF8, 0x0000, 0x4170); //видимость всех объектов через объекты
        else if (random_number == 10) change_value_hobbit<DWORD>((LPVOID)0x00772BF0, 0x40866666, 0x3F99999A); //перевернутая камера
        else if (random_number == 11)
        {
            change_value_hobbit<DWORD>((LPVOID)0x00772A70, 0x3F800000, 0x42C80000);
            change_value_hobbit<DWORD>((LPVOID)0x00772B38, 0x3F800000, 0x42C80000);  //первое лицо
            change_value_hobbit<DWORD>((LPVOID)0x00772B3C, 0x3F800000, 0x43960000);
        }
        else if (random_number == 12)
        {
            change_value_hobbit<DWORD>((LPVOID)0x00772A70, 0xC3960000, 0x42C80000);
            change_value_hobbit<DWORD>((LPVOID)0x00772B38, 0xC3960000, 0x42C80000);  //второе лицо
            change_value_hobbit<DWORD>((LPVOID)0x00772B3C, 0xC3960000, 0x43960000);
        }
        else if (random_number == 13) change_value_hobbit<DWORD>((LPVOID)0x006E92E8, 0x3F8CCCCD, 0x3F800000); //большой Бильбо
        else if (random_number == 14) change_value_hobbit<DWORD>((LPVOID)0x006E92E8, 0x3F666666, 0x3F800000); //маленький Бильбо
        else if (random_number == 15) hair = true;

        vkl = !vkl;
    }
    if (timer2 >= vremaeffectof) {
        timer2 = 0;
        random_number = distrib(gen);
    }
    else 
        if(read_value_hobbit<int>((LPDWORD)(0x813040)) == 1) timer2 += ImGui::GetIO().DeltaTime;
    return;
}