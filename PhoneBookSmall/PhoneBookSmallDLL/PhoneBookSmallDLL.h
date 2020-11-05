// Приведенный ниже блок ifdef — это стандартный метод создания макросов, упрощающий процедуру
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа PHONEBOOKSMALLDLL_EXPORTS
// Символ, определенный в командной строке. Этот символ не должен быть определен в каком-либо проекте,
// использующем данную DLL. Благодаря этому любой другой проект, исходные файлы которого включают данный файл, видит
// функции PHONEBOOKSMALLDLL_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#ifdef PHONEBOOKSMALLDLL_EXPORTS
#define PHONEBOOKSMALLDLL_API __declspec(dllexport)
#else
#define PHONEBOOKSMALLDLL_API __declspec(dllimport)
#endif

// Этот класс экспортирован из библиотеки DLL
class PHONEBOOKSMALLDLL_API CPhoneBookSmallDLL {
public:
	CPhoneBookSmallDLL(void);
	// TODO: добавьте сюда свои методы.
};

extern PHONEBOOKSMALLDLL_API int nPhoneBookSmallDLL;

PHONEBOOKSMALLDLL_API int fnPhoneBookSmallDLL(void);
