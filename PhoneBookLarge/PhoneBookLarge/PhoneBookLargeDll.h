
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

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
	virtual std::vector<PhonebookRecord*> GetNext()=0;
	virtual std::vector<PhonebookRecord*> SearchNext(PhonebookRecord searchParam)=0;
	virtual void ReturnToPrevious()=0;
	virtual void InitPhoneBook() = 0;
};

class PhoneBook :public IPhoneBook {

public:
	void InitPhoneBook();
	std::vector<PhonebookRecord*> GetPhoneBook();
	std::vector<PhonebookRecord*> Search(PhonebookRecord searchParam);
	std::vector<PhonebookRecord*> GetNext();
	std::vector<PhonebookRecord*> SearchNext(PhonebookRecord searchParam);
	void ReturnToPrevious();


private:
	HANDLE hSrcFile;
	DWORD dwFileSize;
	HANDLE hMapObject;
	LPVOID lpvFilePointer;
	DWORD offset;

	std::vector<DWORD> cachedOffsets;
	SYSTEM_INFO sysinfo;

	TCHAR currentDirectory[1024];
	LPVOID SetFilePointer(HANDLE hMap, LPVOID prevFilePointer, DWORD offset);
	std::wstring ReadLine(DWORD* offset);
	wchar_t ReadSymbol(DWORD* offset);
	BYTE ReadByte(DWORD offset);
	PhonebookRecord* ParseLine(std::wstring line);
};

extern "C"
{
	PHONEBOOKLARGEDLL_API IPhoneBook* _cdecl CreatePhoneBookObject();
};

typedef IPhoneBook* (*PHONE_BOOK) ();