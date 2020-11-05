// PhoneBookSmallDLL.cpp : Определяет экспортируемые функции для DLL.
//

#include "pch.h"
#include "framework.h"
#include "PhoneBookSmallDLL.h"


// Пример экспортированной переменной
PHONEBOOKSMALLDLL_API int nPhoneBookSmallDLL=0;

// Пример экспортированной функции.
PHONEBOOKSMALLDLL_API int fnPhoneBookSmallDLL(void)
{
    return 0;
}

// Конструктор для экспортированного класса.
CPhoneBookSmallDLL::CPhoneBookSmallDLL()
{
    return;
}
