#pragma once

#ifdef SDARIMLIBRARY_EXPORTS  
#define SDARIMLIBRARY_API __declspec(dllexport)   
#else  
#define SDARIMLIBRARY_API __declspec(dllimport)   
#endif  

#include <iostream>
#include <map>
#include <string>
#include <exception>
#include <vcclr.h>
using namespace std;
using namespace System;

namespace SdarimWrapper {


	extern SDARIMLIBRARY_API enum BooksNames {Error ,Bereshit, Shemot, VaYikra, BaMidbar, Devarim, Yehoshua, Shoftim, Shmuel, ShmuelA, ShmuelB, Melachim, MelachimA, MelachimB, Yisheyah, Yermiyah, Yechezchial, Treisar, Hoshea, Yoel, Amos, Ovadiyah, Yonah, Micah, Nahum, Habakkuk, Tzefaniyah, Haggai, Zechariah, Malachi, Tehilim, Mishlei, Eyov, ShirHaShirim, Ruth, Eichah, Keholet, Esther, Daniel, Ezra, Nehemiah, DivreiHaYamim, DivreiHaYamimA, DivreiHaYamimB };

	extern SDARIMLIBRARY_API class Result {
	public:
		Result(wstring book, unsigned int chapter, unsigned int phrase, wstring stratingSederComment, wstring bookComment) :book(book), chapter(chapter), phrase(phrase), stratingSederComment(stratingSederComment), bookComment(bookComment) {}
		Result() {
			book = L"";
			chapter = 0;
			phrase = 0;
			stratingSederComment = L"";
			bookComment = L"";
		}
		~Result() {}
		wstring book;
		unsigned int chapter;
		unsigned int phrase;
		wstring stratingSederComment;
		wstring bookComment;

	};



	extern SDARIMLIBRARY_API Result* change(BooksNames book, unsigned int chapter, unsigned int phrase, bool rev = false);


	extern SDARIMLIBRARY_API struct SdarimException : public exception {
	public:
		SdarimException(wstring book, unsigned int chapter, unsigned int phrase, bool rev) : chapter(chapter), phrase(phrase), book(book), rev(rev) {}
		virtual wstring explain() = 0;
	protected:
		unsigned int chapter;
		unsigned int phrase;
		wstring book;
		bool rev;

	};

	extern SDARIMLIBRARY_API struct NumOfChaptersException : SdarimException {
		NumOfChaptersException(wstring book, unsigned int chapter, unsigned int phrase, bool rev) : SdarimException(book, chapter, phrase, rev) {}
		wstring explain() override;

	};

	extern SDARIMLIBRARY_API struct NumOfPhraseException : SdarimException {
		NumOfPhraseException(wstring book, unsigned int chapter, unsigned int phrase, bool rev) : SdarimException(book, chapter, phrase, rev) {}
		wstring explain() override;
	};

	extern SDARIMLIBRARY_API struct BookException : SdarimException {
		BookException(wstring book, unsigned int chapter, unsigned int phrase, bool rev) : SdarimException(book, chapter, phrase, rev) {}
		wstring explain() override;
	};

	extern SDARIMLIBRARY_API map<BooksNames, unsigned int*> sDictionary;
	extern SDARIMLIBRARY_API map<BooksNames, unsigned int*> pDictionary;

	extern SDARIMLIBRARY_API wstring intToOtiyot(unsigned int input);
	extern SDARIMLIBRARY_API unsigned int otiyotToint(wstring input);

	/**
	* find for the seperated books (e.g Shmuel) where is the 0 location of this chapter. (e.g for Shmuel B: 31)
	*/
	extern SDARIMLIBRARY_API unsigned int bookStartAt(BooksNames book);

	/**
	* find for the seperated books (e.g Shmuel) where is the last location of this chapter. (e.g for Shmuel A: 31)
	*/
	extern SDARIMLIBRARY_API unsigned int bookEndAt(BooksNames book);



	extern SDARIMLIBRARY_API public ref class SdarimHelper
	{
	public:
		SdarimHelper() {};
		/**
		* The main function - gets book, chapter, phrase and whitch way to convert.
		* return System::String^ of the result.
		*/
		static String^ convertor(String^ book, unsigned int chapter, unsigned int phrase, bool rev, bool longVersion) {
			BooksNames name = bookName(book);
			if (name == BooksNames()) throw;
			auto ans = change(name, chapter, phrase, rev);
			String^ toReturn = gcnew String(ans->book.c_str());
			toReturn = gcnew String(ans->book.c_str());
			toReturn += L" ";
			if (!rev && bookName(gcnew String(ans->book.c_str())) == Treisar) toReturn += book + L" ";
			if(name == Eichah) toReturn += (rev) ? L"פרק " : L", קינה ";
			else if (longVersion) toReturn += (rev) ? L"פרק " : L"סדר ";
			toReturn += gcnew String(intToOtiyot(ans->chapter).c_str());
			toReturn += L" ";
			if (longVersion) toReturn += L"פסוק ";
			toReturn += gcnew String(intToOtiyot(ans->phrase).c_str());
			if (bookName(book) == Shemot && chapter == 15 && phrase == 22 && rev) toReturn += L" + ג";
			if (bookName(book) == Devarim && chapter == 5 && phrase == 15 && rev) toReturn += L" + ז";
			if (name == Tehilim) {
				toReturn += L", מזמור";
				auto Mizmor = gcnew String(ans->bookComment.c_str());
				auto splitted = Mizmor->Split(L' ');
				for (int i = 6; i < splitted->Length; i++) {
					
					toReturn += L" ";
					if (i == 8) toReturn += L"פסוק";
					else toReturn += splitted[i];
				}
			}
			return toReturn;
		}

		/**
		* This function returns the number of chapter (if (rev==true) - of Sdarim) in a book
		*/
		static int numOfChapterInBook(String^ book, bool rev) {

			BooksNames name = bookName(book);
			if (name == BooksNames()) throw;
			return (rev) ? (sDictionary[name])[0] : bookEndAt(name) - bookStartAt(name);

		}
		/**
		* This function returns the number of phrase of a Chapter (if (rev==true) - of a Seder) in a book
		*/

		static int numOfPhraseInChapter(String^ book, unsigned int chapter, bool rev) {
			BooksNames name = bookName(book);
			if (name == BooksNames()) throw;
			unsigned int numOfPhrase;
			if (!rev) {
				chapter += bookStartAt(name);
				numOfPhrase = (chapter == 1) ? (pDictionary[name])[chapter] : (pDictionary[name])[chapter] - (pDictionary[name])[chapter - 1];
			}
			else {
				numOfPhrase = (chapter == 1) ? (sDictionary[name])[chapter] : (sDictionary[name])[chapter] - (sDictionary[name])[chapter - 1];
				if ((name == Shemot && chapter == 15) || (name == Devarim && chapter == 5)) numOfPhrase--;
			}
			return numOfPhrase;
		}

		/**
		* return the gimatriya String^ value of a number. e.g - 32 to "לב".
		*/
		static String^ numToChar(unsigned int input) {
			return gcnew String(intToOtiyot(input).c_str());
		}

		/**
		* return the int value of a gimatriya. e.g - "לב" to 32.
		*/
		static unsigned int CharToNum(String^ input) {
			pin_ptr<const wchar_t> temp = PtrToStringChars(input);
			return otiyotToint(temp);
		}
	private:
		static BooksNames bookName(String^ name)
		{
			if (name == L"בראשית") return Bereshit;
			if (name == L"שמות") return Shemot;
			if (name == L"ויקרא") return VaYikra;
			if (name == L"במדבר") return BaMidbar;
			if (name == L"דברים") return Devarim;
			if (name == L"יהושע") return Yehoshua;
			if (name == L"שופטים") return Shoftim;
			if (name == L"שמואל") return Shmuel;
			if (name == L"שמואל א") return ShmuelA;
			if (name == L"שמואל ב") return ShmuelB;
			if (name == L"מלכים") return Melachim;
			if (name == L"מלכים א") return MelachimA;
			if (name == L"מלכים ב") return MelachimB;
			if (name == L"ישעיה") return Yisheyah;
			if (name == L"ירמיה") return Yermiyah;
			if (name == L"יחזקאל") return Yechezchial;
			if (name == L"תרי עשר") return Treisar;
			if (name == L"הושע") return Hoshea;
			if (name == L"יואל") return Yoel;
			if (name == L"עמוס") return Amos;
			if (name == L"עובדיה") return Ovadiyah;
			if (name == L"יונה") return Yonah;
			if (name == L"מיכה") return Micah;
			if (name == L"נחום") return Nahum;
			if (name == L"חבקוק") return Habakkuk;
			if (name == L"צפניה") return Tzefaniyah;
			if (name == L"חגי") return Haggai;
			if (name == L"זכריה") return Zechariah;
			if (name == L"מלאכי") return Malachi;
			if (name == L"תהילים") return Tehilim;
			if (name == L"משלי") return Mishlei;
			if (name == L"איוב") return Eyov;
			if (name == L"שיר השירים") return ShirHaShirim;
			if (name == L"רות") return Ruth;
			if (name == L"איכה") return Eichah;
			if (name == L"קהלת") return Keholet;
			if (name == L"אסתר") return Esther;
			if (name == L"דניאל") return Daniel;
			if (name == L"עזרא") return Ezra;
			if (name == L"נחמיה") return Nehemiah;
			if (name == L"דברי הימים") return DivreiHaYamim;
			if (name == L"דברי הימים א") return DivreiHaYamimA;
			if (name == L"דברי הימים ב") return DivreiHaYamimB;
			if (name == L"תהלים") return Tehilim;
			if (name == L"יהושוע") return Yehoshua;
			if (name == L"ישעיהו") return Yisheyah;
			if (name == L"ירמיהו") return Yermiyah;
			if (name == L"קוהלת") return Keholet;
			if (name == L"שנים עשר") return Treisar;
			return BooksNames();
		}

		// TODO: Add your methods for this class here.
	};
}