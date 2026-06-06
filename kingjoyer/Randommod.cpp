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
    "Raibow hair"
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

void RandomMod(float vremaeffectof)
{
    extern bool randommod; // Объявляем внешнюю переменную randommod из gui.cpp
    isRandomModEnabled = randommod; // Синхронизируем флаг
    if (hair == true)
    {
        static void* pMaterial = memsearch("hair", sizeof("hair"));
        if (pMaterial) {
            change_value_hobbit<DWORD>(((char*)pMaterial) + 0x104, 0x01, 0x01);
            char* _pTint = ((char*)pMaterial) + 0x11C;
            float* pTint = (float*)_pTint;
            float tint[4];

            std::uniform_int_distribution<> distrib1(0, 255); 
            pTint[0] = distrib1(gen); 
            pTint[1] = distrib1(gen);  
            pTint[2] = distrib1(gen);  
            pTint[3] = distrib1(gen);
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