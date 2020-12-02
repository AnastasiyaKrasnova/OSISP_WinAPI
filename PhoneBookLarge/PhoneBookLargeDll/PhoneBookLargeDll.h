#include "framework.h"

#ifdef PHONEBOOKLARGEDLL_EXPORTS
#define PHONEBOOKLARGEDLL_API __declspec(dllexport)
#else
#define PHONEBOOKLARGEDLL_API __declspec(dllimport)
#endif

struct PhonebookRecord
{
	wchar_t telephone[20];
	wchar_t lastName[20];
	wchar_t firstName[20];
	wchar_t fatherName[20];
	wchar_t street[20];
	wchar_t house[10];
	wchar_t flat[10];
};

class IPhoneBook {
public:
	virtual ~IPhoneBook() { ; }
	virtual std::vector<PhonebookRecord*> Search(PhonebookRecord searchParam) = 0;
	virtual std::vector<PhonebookRecord*> GetPhoneBook() = 0;
	virtual std::vector<PhonebookRecord*> SearchFrom(PhonebookRecord searchParam)=0;
	virtual void PrevPage()=0;
	virtual void InitPhoneBook() = 0;
	virtual void DestroyPhoneBook() = 0;
};

class PhoneBook :public IPhoneBook {

private:
	std::vector<DWORD> offsetStack;
	TCHAR currentDirectory[1024];

	SYSTEM_INFO sysinfo;
	HANDLE dbFile;
	DWORD fileSize;
	HANDLE hMapObject;
	HANDLE hFilePointer;
	DWORD offset;

	HANDLE SetFilePointer(HANDLE hMap, HANDLE prevFilePointer, DWORD offset);
	BYTE ReadByte(DWORD offset);
	wchar_t ReadEncoding(DWORD* offset);
	std::wstring ReadLine(DWORD* offset);
	PhonebookRecord* ParseLine(std::wstring line);

public:
	void InitPhoneBook();
	void DestroyPhoneBook();
	std::vector<PhonebookRecord*> GetPhoneBook();
	std::vector<PhonebookRecord*> Search(PhonebookRecord searchParam);
	std::vector<PhonebookRecord*> SearchFrom(PhonebookRecord searchParam);
	void PrevPage();
};

extern "C"
{
	PHONEBOOKLARGEDLL_API IPhoneBook* _cdecl CreatePhoneBookObject();
};

typedef IPhoneBook* (*PHONE_BOOK) ();