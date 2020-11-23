#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#ifdef PHONEBOOKSMALLDLL_EXPORTS
#define PHONEBOOKSMALLDLL_API __declspec(dllexport)
#else
#define PHONEBOOKSMALLDLL_API __declspec(dllimport)
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


struct TreeNode
{
	std::vector<PhonebookRecord*> data;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;

	TreeNode(PhonebookRecord* value, TreeNode* parent)
	{
		this->left = this->right = nullptr;
		this->data.push_back(value);
		this->parent = parent;
	}
};

class IPhoneBook {
public:
	virtual ~IPhoneBook() { ; }
	virtual std::vector<PhonebookRecord*> Search(PhonebookRecord searchParam) = 0;;
	virtual std::vector<PhonebookRecord*> GetPhonebook() = 0;;
	virtual void InitPhoneBook() = 0;
};


class PhoneBook:public IPhoneBook {

public:
	std::vector<PhonebookRecord*> GetPhonebook();
	void InitPhoneBook();
	std::vector<PhonebookRecord*> Search(PhonebookRecord searchParam);

private:
	std::vector<PhonebookRecord*> smallPhoneBook;
	std::vector<PhonebookRecord*> ReadFromDBFile(std::wstring filePath);
	void CreateIndex(std::vector<PhonebookRecord*> phoneBook);
	std::vector<PhonebookRecord*> IntersectResult(std::vector<PhonebookRecord*> first, std::vector<PhonebookRecord*> second);
	PhonebookRecord* ParseLine(std::wstring line);
};


template <typename T>
class Indexer {
public:
	
	TreeNode* root = nullptr;
    Indexer(std::vector<PhonebookRecord*> phoneBook, int offset);
	std::vector<PhonebookRecord*> Search(TreeNode* ptr, T value);
	TreeNode* Insert(TreeNode* ptr, PhonebookRecord* value);

private:
	std::wstring ToString(T value);
	int offset;	
};

extern "C"
{
	PHONEBOOKSMALLDLL_API IPhoneBook* _cdecl CreatePhoneBookObject();
};

typedef IPhoneBook* (*PHONE_BOOK) ();