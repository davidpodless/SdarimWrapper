// SdarimLibrary.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "SdarimLibrary.h"
namespace SdarimWrapper {
	static Result* ChapterToSeder(BooksNames book, unsigned int chapter, unsigned int phrase);
	static Result* SederToChapter(BooksNames book, unsigned int chapter, unsigned int phrase);
	static unsigned int FindChapterInIndex(unsigned int* index, unsigned int value);
	int binarySearch(unsigned int* arr, unsigned int value);


	static BooksNames findChapterBook(BooksNames book, unsigned int chapter);

	static BooksNames FindSederBook(BooksNames book);

	static wstring getBookName(BooksNames book);


	static void isValidInput(BooksNames bookName, unsigned int chapter, unsigned int phrase, bool rev = false);

	static wstring startingSederCommentFunc(BooksNames book, unsigned int chapter, unsigned int phrase);

	static wstring bookCommentFunc(BooksNames book, unsigned int chapter, unsigned int phrase);




	wstring NumOfPhraseException::explain() {
		/*wstring toReturn = L"בספר ";
		toReturn += book;
		switch (rev)
		{
		case false:
		toReturn = L"בפרק";
		break;
		case true:
		toReturn = L"בסדר";
		break;
		}
		toReturn += chapter;
		;
		toReturn += L" יש ";
		toReturn += phrase;
		toReturn += L"פסוקים";
		return toReturn;*/ return L"Error in phrase";
	}


	wstring NumOfChaptersException::explain() {
		/*wstring toReturn = L"בספר ";
		toReturn += book;
		toReturn += L" יש ";
		toReturn += chapter;
		switch (rev)
		{
		case false:
		toReturn += L"פרקים";
		break;
		case true:
		toReturn += L"סדרים";
		break;
		}

		return toReturn;*/ return L"Error in chapter";
	}

	wstring BookException::explain() {
		/*wstring toReturn = L"הספר ";
		toReturn += book;
		toReturn += L" לא קיים בחלוקה המבוקשת";
		return toReturn;*/ return L"Error in book";
	}

	unsigned int sBereshit[] = { 43, 34, 77, 106, 146, 184, 198, 223, 267, 299, 337, 361, 382, 398, 425, 458, 496, 514, 548, 592, 633, 659, 677, 728, 755, 783, 826, 852, 876, 931, 978, 1020, 1084, 1120, 1150, 1196, 1233, 1270, 1304, 1342, 1414, 1452, 1474, 1533 };
	unsigned int sShemot[] = { 29, 47, 86, 124, 160, 197, 245, 274, 312, 335, 371, 418, 442, 467, 499, 542, 602, 660, 700, 730, 756, 801, 847, 885, 917, 987, 1069, 1118, 1161, 1210 };
	unsigned int sVaYikra[] = { 23, 50, 122, 172, 239, 252, 299, 335, 366, 398, 423, 447, 490, 506, 536, 558, 600, 640, 671, 737, 758, 781, 825, 859 };
	unsigned int sBaMidbar[] = { 32, 54, 88, 155, 198, 240, 293, 335, 384, 435, 442, 471, 514, 549, 590, 640, 677, 720, 772, 821, 867, 876, 936, 964, 998, 1044, 1060, 1084, 1114, 1156, 1212, 1249, 1288 };
	unsigned int sDevarim[] = { 27, 47, 76, 105, 152, 194, 227, 262, 291, 322, 364, 395, 430, 464, 482, 541, 580, 613, 625, 648, 671, 716, 793, 823, 846, 863, 915, 956 };

	unsigned int sYehoshua[] = { 14, 48, 82, 124, 183, 220, 254, 303, 350, 427, 469, 520, 570, 606, 656 };
	unsigned int sShoftim[] = { 14, 42, 89, 144, 184, 212, 251, 302, 351, 398, 442, 489, 534, 571, 618 };
	unsigned int sShmuel[] = { 34, 37, 83, 132, 180, 229, 269, 318, 364, 400, 442, 477, 521, 559, 602, 647, 682, 718, 754, 791, 844, 890, 930, 984, 1040, 1087, 1130, 1177, 1214, 1257, 1293, 1338, 1375, 1441, 1506 };
	unsigned int sMelachim[] = { 35, 47, 97, 146, 191, 237, 278, 325, 370, 418, 457, 497, 539, 580, 623, 662, 703, 750, 805, 849, 912, 980, 1006, 1052, 1091, 1135, 1177, 1215, 1266, 1313, 1363, 1389, 1430, 1473, 1503, 1536 };
	unsigned int sYermiyah[] = { 31, 59, 112, 144, 195, 252, 317, 368, 417, 456, 488, 543, 584, 626, 654, 695, 729, 777, 806, 844, 886, 921, 956, 994, 1040, 1083, 1125, 1182, 1224, 1275, 1324, 1364 };
	unsigned int sYechezchial[] = { 29, 49, 99, 140, 169, 210, 267, 311, 357, 393, 431, 471, 527, 569, 615, 655, 705, 739, 784, 831, 874, 919, 960, 1005, 1057, 1100, 1134, 1180, 1226, 1273 };
	unsigned int sYisheyah[] = { 26, 81, 117, 181, 231, 275, 319, 374, 420, 463, 509, 561, 622, 675, 717, 766, 823, 884, 923, 961, 1007, 1048, 1098, 1145, 1197, 1250, 1291 };
	unsigned int sTreisar[] = { 21, 74, 142, 192, 243, 294, 342, 384, 436, 485, 530, 589, 637, 693, 745, 783, 829, 866, 904, 951, 994, 1050 };

	unsigned int sRuth[] = { 1, 85 };
	unsigned int sTehilim[] = { 19, 133, 262, 392, 514, 636, 754, 877, 1008, 1131, 1265, 1389, 1516, 1636, 1774, 1927, 2094, 2256, 2401, 2527 };
	unsigned int sEyov[] = { 8, 108, 257, 399, 549, 676, 813, 958, 1070 };
	unsigned int sMishlei[] = { 8, 134, 248, 375, 510, 635, 725, 811, 915 };
	unsigned int sKeholet[] = { 4, 56, 114, 166, 222 };
	unsigned int sShirHaShirim[] = { 1, 117 };
	unsigned int sEichah[] = { 5, 22, 44, 110, 132, 154 };
	unsigned int sDaniel[] = { 7, 55, 99, 148, 177, 254, 298, 357 };
	unsigned int sEsther[] = { 5, 26, 52, 101, 130, 167 };
	unsigned int sEzra[] = { 10, 93, 152, 219, 290, 348, 399, 485, 531, 633, 685 };
	unsigned int sDivreiHaYamim[] = { 25, 142, 250, 362, 429, 508, 604, 668, 731, 830, 901, 963, 1030, 1083, 1136, 1197, 1253, 1308, 1365, 1415, 1482, 1550, 1612, 1683, 1720, 1765 };


	unsigned int  pBereshit[] = { 50, 31, 56, 80, 106, 138, 160, 184, 206, 235, 267, 299, 319, 337, 361, 382, 398, 425, 458, 496, 514, 548, 572, 592, 659, 693, 728, 774, 796, 831, 874, 929, 961, 981, 1012, 1041, 1084, 1120, 1150, 1173, 1196, 1253, 1291, 1325, 1359, 1387, 1421, 1452, 1474, 1507, 1533 };
	unsigned int  pShemot[] = { 40, 22, 47, 69, 100, 123, 153, 182, 210, 245, 274, 284, 335, 357, 388, 415, 451, 467, 494, 519, 542, 579, 609, 642, 660, 700, 737, 758, 801, 847, 885, 903, 938, 961, 996, 1031, 1069, 1098, 1129, 1172, 1210 };
	unsigned int  pVaYikra[] = { 27, 17, 33, 50, 85, 111, 134, 172, 208, 232, 252, 299, 307, 366, 423, 456, 490, 506, 536, 573, 600, 624, 657, 701, 724, 779, 825, 859 };
	unsigned int  pBaMidbar[] = { 36, 54, 88, 139, 188, 219, 246, 335, 361, 384, 420, 455, 471, 504, 549, 590, 625, 653, 685, 707, 736, 771, 812, 842, 867, 885, 950, 973, 1004, 1043, 1060, 1114, 1156, 1212, 1241, 1275, 1288 };
	unsigned int  pDevarim[] = { 34, 46, 83, 112, 161, 191, 216, 242, 262, 291, 313, 345, 376, 395, 424, 447, 469, 489, 511, 532, 552, 575, 604, 630, 652, 671, 690, 716, 785, 813, 833, 863, 915, 944, 956 };

	unsigned int  pYehoshua[] = { 24, 18, 42, 59, 83, 98, 125, 151, 186, 213, 256, 279, 303, 336, 351, 414, 424, 442, 470, 521, 530, 573, 607, 623, 656 };
	unsigned int  pShoftim[] = { 21, 36, 59, 90, 114, 145, 185, 210, 245, 302, 320, 360, 375, 400, 420, 440, 471, 484, 515, 545, 593, 618 };
	unsigned int  pShmuel[] = { 55, 28, 64, 85, 107, 119, 140, 157, 179, 206, 233, 248, 273, 296, 348, 383, 406, 464, 494, 518, 560, 576, 599, 628, 650, 694, 719, 731, 756, 767, 798, 811, 838, 870, 909, 921, 946, 969, 998, 1016, 1029, 1048, 1075, 1106, 1145, 1178, 1215, 1238, 1267, 1299, 1343, 1369, 1391, 1442, 1481, 1506 };
	unsigned int  pMelachim[] = { 47, 53, 99, 127, 147, 179, 217, 268, 334, 362, 391, 434, 467, 501, 532, 566, 600, 624, 670, 691, 734, 763, 817, 835, 860, 887, 931, 958, 991, 1011, 1040, 1077, 1113, 1133, 1155, 1180, 1209, 1247, 1267, 1308, 1345, 1382, 1403, 1429, 1449, 1486, 1506, 1536 };
	unsigned int  pYisheyah[] = { 66, 31, 53, 79, 85, 115, 128, 153, 176, 196, 230, 246, 252, 274, 306, 315, 329, 343, 350, 375, 381, 398, 423, 441, 464, 476, 497, 510, 539, 563, 596, 605, 625, 649, 666, 676, 698, 736, 758, 766, 797, 826, 851, 879, 907, 932, 945, 960, 982, 1008, 1019, 1042, 1057, 1069, 1086, 1099, 1111, 1132, 1146, 1167, 1189, 1200, 1212, 1231, 1242, 1267, 1291 };
	unsigned int  pYermiyah[] = { 52, 19, 56, 81, 112, 143, 173, 207, 230, 255, 280, 303, 320, 347, 369, 390, 411, 438, 461, 476, 494, 508, 538, 578, 588, 626, 650, 672, 689, 721, 746, 785, 829, 855, 877, 896, 928, 949, 977, 995, 1011, 1029, 1051, 1064, 1094, 1099, 1127, 1134, 1181, 1220, 1266, 1330, 1364 };
	unsigned int  pYechezchial[] = { 48, 28, 38, 65, 82, 99, 113, 140, 158, 169, 191, 216, 244, 267, 290, 298, 361, 385, 417, 431, 475, 512, 543, 592, 619, 636, 657, 693, 719, 740, 766, 784, 816, 849, 880, 895, 933, 961, 984, 1013, 1062, 1088, 1108, 1135, 1166, 1191, 1215, 1238, 1273 };
	unsigned int  pTreisar[] = { 67, 9, 34, 39, 58, 73, 84, 100, 114, 131, 146, 157, 172, 187, 197, 217, 244, 249, 270, 285, 301, 316, 329, 356, 370, 387, 401, 416, 437, 453, 464, 474, 485, 501, 514, 526, 540, 554, 570, 590, 604, 618, 637, 654, 674, 693, 711, 726, 746, 761, 784, 801, 818, 828, 842, 853, 868, 882, 905, 922, 934, 951, 965, 974, 995, 1009, 1026, 1050 };

	unsigned int  pTehilim[] = { 150, 6, 18, 27, 36, 49, 60, 78, 88, 109, 127, 134, 143, 149, 156, 161, 172, 187, 238, 253, 263, 277, 309, 315, 325, 347, 359, 373, 382, 393, 406, 431, 442, 464, 487, 515, 528, 568, 591, 605, 623, 637, 649, 654, 681, 699, 711, 721, 736, 757, 780, 801, 812, 819, 828, 852, 866, 878, 890, 908, 922, 931, 944, 956, 967, 981, 1001, 1009, 1045, 1082, 1088, 1112, 1132, 1160, 1183, 1194, 1207, 1228, 1300, 1313, 1333, 1350, 1358, 1377, 1390, 1404, 1421, 1428, 1447, 1500, 1517, 1533, 1549, 1554, 1577, 1588, 1601, 1613, 1622, 1631, 1636, 1644, 1673, 1695, 1730, 1775, 1823, 1866, 1880, 1911, 1918, 1928, 1938, 1947, 1955, 1973, 1992, 1994, 2023, 2199, 2206, 2214, 2223, 2227, 2235, 2240, 2246, 2251, 2257, 2265, 2273, 2276, 2294, 2297, 2300, 2321, 2347, 2356, 2364, 2388, 2402, 2412, 2420, 2432, 2447, 2468, 2478, 2498, 2512, 2521, 2527 };
	unsigned int  pMishlei[] = { 31, 33, 55, 90, 117, 140, 175, 202, 238, 256, 288, 319, 347, 372, 407, 440, 473, 501, 525, 554, 584, 615, 644, 679, 713, 741, 769, 796, 824, 851, 884, 915 };
	unsigned int  pEyov[] = { 42, 22, 35, 61, 82, 109, 139, 160, 182, 217, 239, 259, 284, 312, 334, 369, 391, 407, 428, 457, 486, 520, 550, 567, 592, 598, 612, 635, 663, 688, 719, 759, 781, 814, 851, 867, 900, 924, 965, 995, 1027, 1053, 1070 };
	unsigned int  pShirHaShirim[] = { 8, 17, 34, 45, 61, 77, 89, 103, 117 };
	unsigned int  pRuth[] = { 4, 22, 45, 63, 85 };
	unsigned int  pEichah[] = { 5, 22, 44, 110, 132, 154 };
	unsigned int  pKeholet[] = { 12, 18, 44, 66, 83, 102, 114, 143, 160, 178, 198, 208, 222 };
	unsigned int  pEsther[] = { 10, 22, 45, 60, 77, 91, 105, 115, 132, 164, 167 };
	unsigned int  pDaniel[] = { 12, 21, 70, 103, 137, 167, 196, 224, 251, 278, 299, 344, 357 };
	unsigned int  pEzra[] = { 23, 11, 81, 94, 118, 135, 157, 185, 221, 236, 280, 291, 311, 349, 366, 385, 404, 476, 494, 531, 571, 607, 654, 685 };
	unsigned int  pDivreiHaYamim[] = { 65, 54, 109, 133, 176, 217, 283, 323, 363, 407, 421, 468, 509, 523, 540, 569, 612, 639, 656, 675, 683, 713, 732, 764, 795, 826, 858, 892, 913, 943, 961, 978, 995, 1017, 1031, 1073, 1095, 1113, 1144, 1163, 1186, 1202, 1225, 1239, 1258, 1272, 1291, 1325, 1336, 1373, 1393, 1405, 1426, 1453, 1481, 1504, 1513, 1540, 1576, 1603, 1624, 1657, 1682, 1715, 1742, 1765 };



	map<BooksNames, unsigned int*> pDictionary = {
		{ Bereshit, pBereshit },
		{ Shemot, pShemot },
		{ VaYikra, pVaYikra },
		{ BaMidbar, pBaMidbar },
		{ Devarim, pDevarim },
		{ Yehoshua, pYehoshua },
		{ Shoftim, pShoftim },
		{ Shmuel, pShmuel },
		{ ShmuelA, pShmuel },
		{ ShmuelB, pShmuel },
		{ Melachim, pMelachim },
		{ MelachimA, pMelachim },
		{ MelachimB, pMelachim },
		{ Yisheyah, pYisheyah },
		{ Yermiyah, pYermiyah },
		{ Yechezchial, pYechezchial },
		{ Treisar, pTreisar },
		{ Hoshea, pTreisar },
		{ Yoel, pTreisar },
		{ Amos, pTreisar },
		{ Ovadiyah, pTreisar },
		{ Yonah, pTreisar },
		{ Micah, pTreisar },
		{ Nahum, pTreisar },
		{ Habakkuk, pTreisar },
		{ Tzefaniyah, pTreisar },
		{ Haggai, pTreisar },
		{ Zechariah, pTreisar },
		{ Malachi, pTreisar },
		{ Tehilim, pTehilim },
		{ Mishlei, pMishlei },
		{ Eyov, pEyov },
		{ ShirHaShirim, pShirHaShirim },
		{ Ruth, pRuth },
		{ Eichah, pEichah },
		{ Keholet, pKeholet },
		{ Esther, pEsther },
		{ Daniel, pDaniel },
		{ Ezra, pEzra },
		{ Nehemiah, pEzra },
		{ DivreiHaYamim, pDivreiHaYamim },
		{ DivreiHaYamimA, pDivreiHaYamim },
		{ DivreiHaYamimB, pDivreiHaYamim }
	};
	map<BooksNames, unsigned int*> sDictionary = {
		{ Bereshit, sBereshit },
		{ Shemot, sShemot },
		{ VaYikra, sVaYikra },
		{ BaMidbar, sBaMidbar },
		{ Devarim, sDevarim },
		{ Yehoshua, sYehoshua },
		{ Shoftim, sShoftim },
		{ Shmuel, sShmuel },
		{ ShmuelA, sShmuel },
		{ ShmuelB, sShmuel },
		{ Melachim, sMelachim },
		{ MelachimA, sMelachim },
		{ MelachimB, sMelachim },
		{ Yisheyah, sYisheyah },
		{ Yermiyah, sYermiyah },
		{ Yechezchial, sYechezchial },
		{ Treisar, sTreisar },
		{ Hoshea, sTreisar },
		{ Yoel, sTreisar },
		{ Amos, sTreisar },
		{ Ovadiyah, sTreisar },
		{ Yonah, sTreisar },
		{ Micah, sTreisar },
		{ Nahum, sTreisar },
		{ Habakkuk, sTreisar },
		{ Tzefaniyah, sTreisar },
		{ Haggai, sTreisar },
		{ Zechariah, sTreisar },
		{ Malachi, sTreisar },
		{ Tehilim, sTehilim },
		{ Mishlei, sMishlei },
		{ Eyov, sEyov },
		{ ShirHaShirim, sShirHaShirim },
		{ Ruth, sRuth },
		{ Eichah, sEichah },
		{ Keholet, sKeholet },
		{ Esther, sEsther },
		{ Daniel, sDaniel },
		{ Ezra, sEzra },
		{ Nehemiah, sEzra },
		{ DivreiHaYamim, sDivreiHaYamim },
		{ DivreiHaYamimA, sDivreiHaYamim },
		{ DivreiHaYamimB, sDivreiHaYamim }

	};

	Result* change(BooksNames book, unsigned int chapter, unsigned int phrase, bool rev) {
		try {
			switch (rev) {
			case false:
				isValidInput(book, chapter, phrase);
				return ChapterToSeder(book, chapter, phrase);
				break;
			case true:
				isValidInput(book, chapter, phrase, true);
				return SederToChapter(book, chapter, phrase);
				break;
			}
			return nullptr;
		}
		catch (SdarimException* s) { throw s; }
	}

	static Result* ChapterToSeder(BooksNames book, unsigned int chapter, unsigned int phrase) {
		chapter += bookStartAt(book);
		unsigned int phraseInBook = (chapter == 1) ? phrase : (pDictionary[book])[chapter - 1] + phrase;
		unsigned int chapterToReturn = FindChapterInIndex(sDictionary[book], phraseInBook);
		unsigned int phraseToReturn = (chapterToReturn == 1) ? phraseInBook : phraseInBook - (sDictionary[book])[chapterToReturn - 1];
		if ((book == Shemot && chapter == 20 && phrase >= 3) || (book == Devarim && chapter == 5 && phrase >= 7)) phraseToReturn--;
		book = FindSederBook(book);
		wstring bookNameToReturn = getBookName(book);
		wstring stratingSederComment = startingSederCommentFunc(book, chapterToReturn, phraseToReturn);
		wstring bookComment = bookCommentFunc(book, chapter, phrase);
		Result* toReturn = new Result(bookNameToReturn, chapterToReturn, phraseToReturn, stratingSederComment, bookComment);
		/*toReturn->book = bookNameToReturn;
		toReturn->chapter = chapterToReturn;
		toReturn->phrase = phraseToReturn;
		toReturn->stratingSederComment = stratingSederComment;
		toReturn->bookComment = bookComment;*/
		return toReturn;

	}

	static Result* SederToChapter(BooksNames book, unsigned int chapter, unsigned int phrase) {

		unsigned int phraseInBook = (chapter == 1) ? phrase : (sDictionary[book])[chapter - 1] + phrase;
		unsigned int chapterToReturn = FindChapterInIndex(pDictionary[book], phraseInBook);
		unsigned int phraseToReturn = (chapterToReturn == 1) ? phraseInBook : phraseInBook - (pDictionary[book])[chapterToReturn - 1];
		if ((book == Shemot && chapter == 15 && phrase >= 23) || (book == Devarim && chapter == 5 && phrase >= 16)) phraseToReturn++;
		wstring stratingSederComment = startingSederCommentFunc(book, chapter, phrase);
		wstring bookComment = bookCommentFunc(book, chapterToReturn, phraseToReturn);
		book = findChapterBook(book, chapterToReturn);
		wstring bookNameToReturn = getBookName(book);
		Result* toReturn = new Result(bookNameToReturn, chapterToReturn - bookStartAt(book), phraseToReturn, stratingSederComment, bookComment);
		return toReturn;

	}

	unsigned int FindChapterInIndex(unsigned int* index, unsigned int value)
	{
		auto chapter = binarySearch(index, value);
		if (chapter != -1) return (unsigned int)chapter;
		else exit(1); //TODO - raise error
	}


	// A iterative binary search function. It returns location of x in
	// given array arr[l..r] if present, otherwise -1
	int binarySearch(unsigned int* arr, unsigned int value)
	{
		int toReturn = 0, m = -1;
		int l = 1, r = arr[0];
		while (l <= r)
		{
			m = l + (r - l) / 2;

			// Check if x is present at mid
			if (arr[m] == value) {
				return m;
			}

			// If x greater, ignore left half  
			else if (arr[m] < value) {
				l = m + 1;
			}

			// If x is smaller, ignore right half 
			else {
				toReturn = m;
				r = m - 1;
			}
			if (m == 0) break;
		}

		return toReturn;
	}


	unsigned int bookStartAt(BooksNames book)
	{
		switch (book)
		{
		case ShmuelB:
			return 31;
		case MelachimB:
			return 22;
		case Yoel:
			return 14;
		case Amos:
			return 18;
		case Ovadiyah:
			return 27;
		case Yonah:
			return 28;
		case Micah:
			return 32;
		case Nahum:
			return 39;
		case Habakkuk:
			return 42;
		case Tzefaniyah:
			return 45;
		case Haggai:
			return 48;
		case Zechariah:
			return 50;
		case Malachi:
			return 64;
		case Nehemiah:
			return 10;
		case DivreiHaYamimB:
			return 29;
		default:
			return 0;
		}
	}

	unsigned int bookEndAt(BooksNames book)
	{
		switch (book)
		{
		case ShmuelA:
			return 31;
		case MelachimA:
			return 22;
		case Hoshea:
			return 14;
		case Yoel:
			return 18;
		case Amos:
			return 27;
		case Ovadiyah:
			return 28;
		case Yonah:
			return 32;
		case Micah:
			return 39;
		case Nahum:
			return 42;
		case Habakkuk:
			return 45;
		case Tzefaniyah:
			return 48;
		case Haggai:
			return 50;
		case Zechariah:
			return 64;
		case Ezra:
			return 10;
		case DivreiHaYamimA:
			return 29;
		default:
			return (pDictionary[book])[0];
		}
	}

	BooksNames findChapterBook(BooksNames book, unsigned int chapter)
	{
		switch (book) {
		case Shmuel:
			if (chapter > 31) return ShmuelB;
			else return ShmuelA;
		case Melachim:
			if (chapter > 22) return MelachimB;
			else return MelachimA;
		case Treisar:
			if (chapter <= 14) return Hoshea;
			else if (chapter <= 18) return Yoel;
			else if (chapter <= 27) return Amos;
			else if (chapter <= 28) return Ovadiyah;
			else if (chapter <= 32) return Yonah;
			else if (chapter <= 39) return Micah;
			else if (chapter <= 42) return Nahum;
			else if (chapter <= 45) return Habakkuk;
			else if (chapter <= 48) return Tzefaniyah;
			else if (chapter <= 50) return Haggai;
			else if (chapter <= 64) return Zechariah;
			else return Malachi;
		case Ezra:
			if (chapter > 10) return Nehemiah;
			else return Ezra;
		case DivreiHaYamim:
			if (chapter > 29) return DivreiHaYamimB;
			else return DivreiHaYamimA;
		default:
			return book;
		}
	}

	static wstring getBookName(BooksNames book) {
		switch (book)
		{
		case Bereshit:
			return L"בראשית";
			break;
		case Shemot:
			return L"שמות";
			break;
		case VaYikra:
			return L"ויקרא";
			break;
		case BaMidbar:
			return L"במדבר";
			break;
		case Devarim:
			return L"דברים";
			break;
		case Yehoshua:
			return L"יהושע";
			break;
		case Shoftim:
			return L"שופטים";
			break;
		case Shmuel:
			return L"שמואל";
			break;
		case ShmuelA:
			return L"שמואל א";
			break;
		case ShmuelB:
			return L"שמואל ב";
			break;
		case Melachim:
			return L"מלכים";
			break;
		case MelachimA:
			return L"מלכים א";
			break;
		case MelachimB:
			return L"מלכים ב";
			break;
		case Yisheyah:
			return L"ישעיה";
			break;
		case Yermiyah:
			return L"ירמיה";
			break;
		case Yechezchial:
			return L"יחזקאל";
			break;
		case Treisar:
			return L"תרי עשר";
			break;
		case Hoshea:
			return L"הושע";
			break;
		case Yoel:
			return L"יואל";
			break;
		case Amos:
			return L"עמוס";
			break;
		case Ovadiyah:
			return L"עובדיה";
			break;
		case Yonah:
			return L"יונה";
			break;
		case Micah:
			return L"מיכה";
			break;
		case Nahum:
			return L"נחום";
			break;
		case Habakkuk:
			return L"חבקוק";
			break;
		case Tzefaniyah:
			return L"צפניה";
			break;
		case Haggai:
			return L"חגי";
			break;
		case Zechariah:
			return L"זכריה";
			break;
		case Malachi:
			return L"מלאכי";
			break;
		case Tehilim:
			return L"תהלים";
			break;
		case Mishlei:
			return L"משלי";
			break;
		case Eyov:
			return L"איוב";
			break;
		case ShirHaShirim:
			return L"שיר השירים";
			break;
		case Ruth:
			return L"רות";
			break;
		case Eichah:
			return L"איכה";
			break;
		case Keholet:
			return L"קהלת";
			break;
		case Esther:
			return L"אסתר";
			break;
		case Daniel:
			return L"דניאל";
			break;
		case Ezra:
			return L"עזרא";
			break;
		case Nehemiah:
			return L"נחמיה";
			break;
		case DivreiHaYamim:
			return L"דברי הימים";
			break;
		case DivreiHaYamimA:
			return L"דברי הימים א";
			break;
		case DivreiHaYamimB:
			return L"דברי הימים ב";
			break;
		default:
			return NULL;
			break;
		}
	}

	void isValidInput(BooksNames bookName, unsigned int chapter, unsigned int phrase, bool rev)
	{
		unsigned int* book;
		switch (rev) {
		case false:
			if (bookName == Shmuel || bookName == Melachim || bookName == Treisar || bookName == DivreiHaYamim) throw new BookException(getBookName(bookName), chapter, phrase, rev);
			book = pDictionary[bookName];
			break;
		default:
			if (bookName == ShmuelA || bookName == MelachimA || bookName == ShmuelB || bookName == MelachimB || bookName == DivreiHaYamimA || bookName == DivreiHaYamimB || bookName == Nehemiah || bookName == Hoshea || bookName == Yoel || bookName == Amos || bookName == Ovadiyah || bookName == Yonah || bookName == Micah || bookName == Nahum || bookName == Habakkuk || bookName == Tzefaniyah || bookName == Haggai || bookName == Zechariah || bookName == Malachi) throw new BookException(getBookName(bookName), chapter, phrase, rev);
			book = sDictionary[bookName];
			break;

		}
		chapter += bookStartAt(bookName);
		if (book[0] >= chapter) {
			unsigned int phraseInChapter = (chapter == 1) ? book[chapter] : book[chapter] - book[chapter - 1];
			if (phraseInChapter >= phrase) {
				return;
			}
			else {
				//ERROE - there is no such phrase!
				throw new NumOfPhraseException(getBookName(bookName), chapter, phrase, rev);
			}
		}
		else {
			//ERROR - there is no such chapter!
			throw new NumOfChaptersException(getBookName(bookName), chapter, phrase, rev);

		}
	}

	wstring startingSederCommentFunc(BooksNames book, unsigned int chapter, unsigned int phrase)
	{

		switch (book) {
		case Bereshit:
			if (chapter == 24) return  L"סדר כד בבראשית פותח\nויהי\nכי-זקן יצחק";
			if (chapter == 38) return L"סדר לח בבראשית פותח\nויאמר אלהם יוסף\nביום השלישי";
			goto NOTHING;
		case Shemot:
			if (chapter == 10) return L"סדר י בשמות פותח\nוידבר ה\n:אל-משה לאמר\nקדש -לי\n.כל-בכור";
			goto NOTHING;
		case VaYikra:
			if (chapter == 20) return L"סדר כ בויקרא פותח\nוכי-תמכרו ממכר\n.לעמיתך";
			goto NOTHING;
		case Devarim:
			if (chapter == 12) return L"סדר יב בדברים פותח\nבנים אתם\n.'לה' א";
			goto NOTHING;
		case Yehoshua:
			if (chapter == 3) return L"סדר ג ביהושע פותח\nלמען\nדעת\nכל-עמי הארץ\n.'את-יד ה";
			if (chapter == 11) return L"סדר יא ביהושע פותח\nוצלע\nהאלף\n.והיבוסי היא ירושלם";
			goto NOTHING;
		case Shmuel:
			if (chapter == 25) return L"סדר כה בשמואל פותח\nחזק ונתחזק\nבעד עמנו\nובעד\n.'ערי א";
			goto NOTHING;
		case Melachim:
			if (chapter == 18) return L"סדר יח במלכים פותח\n'ויהי דבר - ה\nאל-אליהו התשבי\n:לאמר";
			goto NOTHING;
		case Yermiyah:
			if (chapter == 4) return L"סדר ד  בירמיה פותח\nהנוה והמענגה\n:דמיתי בת - ציון";
			if (chapter == 10) return L"סדר י  בירמיה פותח\n'הקשיבה ה\n.אלי";
			goto NOTHING;
		case Yechezchial:
			if (chapter == 27) return L"סדר כז ביחזקאל פותח\n.ויכלו את-הימים";
			if (chapter == 29) return L"סדר כט ביחזקאל פותח\nועל-הנחל יעלה\n| על-שפתו מזה\n| ומזה\n.כל-עץ-מאכל";
			goto NOTHING;
		case Yisheyah:
			if (chapter == 11) return L"סדר יא בישעיה פותח\n| והיה \nביום ההוא\nיתקע\n.בשופר גדול";
			goto NOTHING;
		case Tehilim:
			if (chapter == 7) return L"סדר ז  בתהלים פותח\nכי -נפשו\n.בחייו יברך";
			if (chapter == 17) return L"סדר יז בתהלים פותח\nטוב -לי\nתורת -פיך\nמאלפי\n:זהב וכסף";
			goto NOTHING;
		case Eyov:
			if (chapter == 2) return L"סדר ב  באיוב פותח\nהנה-זאת חקרנוה\n.כן-היא";
			if (chapter == 5) return L"סדר ה  באיוב פותח\nימלט אי - נקי\nונמלט\n:בבר כפיך";
			if (chapter == 6) return L"סדר ו  באיוב פותח\nצדק לבשתי\n.וילבשני";
			if (chapter == 7) return L"סדר ז  באיוב פותח\nאם -אין\n.אתה שמע-לי";
			if (chapter == 8) return L"סדר ח  באיוב פותח\nהתשלח ברקים וילכו\n:ויאמרו לך הננו";
			goto NOTHING;
		case Mishlei:
			if (chapter == 2) return L"סדר ב  במשלי פותח\nיהי-מקורך ברוך\nושמח\n:מאשת נעוריך";
			if (chapter == 3) return L"סדר ג  במשלי פותח\nכי -בי\nירבו ימיך\nויוסיפו לך\n:שנות חיים";
			if (chapter == 6) return L"סדר ו  במשלי פותח\nלהודיעך קשט\n.אמרי אמת";
			goto NOTHING;
		case DivreiHaYamim:
			if (chapter == 19) return L"סדר יט בדברי הימים פותח\nותשקט מלכות יהושפט\nוינח לו אלהיו מסביב";
			goto NOTHING;
		NOTHING:
		default:
			return L"";
			break;

		}
	}

	wstring bookCommentFunc(BooksNames book, unsigned int chapter, unsigned int phrase)
	{

		switch (book) {
		case Tehilim:
		{
			wstring toReturn = L"";
			toReturn += L"הפסוק המבוקש נמצא בספר ";
			if (chapter <= 41) toReturn += L"ראשון";
			else if (chapter <= 72) toReturn += L"שני";
			else if (chapter <= 89) toReturn += L"שלישי";
			else if (chapter <= 106) toReturn += L"רביעי";
			else toReturn += L"חמישי";
			toReturn += L" במזמור ";
			unsigned int mizmor;
			unsigned int pasuk;
			mizmor = chapter;
			pasuk = phrase;
			if (chapter < 10);
			else if (chapter == 10) {
				mizmor--;
				pasuk += 21;
			}
			else if (chapter <= 114) mizmor--;
			else if (chapter == 115) {
				mizmor -= 2;
				pasuk += 8;
			}
			else if (chapter == 116) mizmor -= 2;
			else if (chapter == 117) {
				mizmor -= 3;
				pasuk += 19;
			}
			else mizmor -= 3;
			toReturn += intToOtiyot(mizmor);
			toReturn += L" שלנו בפסוק ";
			toReturn += intToOtiyot(pasuk);
			return toReturn;
		}
		break;
		case Eichah:
			return L" מספרי הפסוקים במגילת איכה בספרים המודפסים הם נכונים. ";
			break;
		case Ruth:
			return L" במגילת רות אין חלוקה לסדרים. הפסוקים נספרו בתוך כל המגילה. ";
			break;
		case ShirHaShirim:
			return L" במגילת שיר השירים אין חלוקה לסדרים. הפסוקים נספרו בתוך כל המגילה. ";
			break;
			//TODO - Bereshit.
			/*case Bereshit:
			{
			unsigned int;
			if (chapter == 31 && phrase == 55)
			}*/
		default:
			return L" גם הרעיון ... להוסיף את מספרי הסדרים החסרים בכל המהדורות ראוי לברכה, והרי הם והם הפרקים שלנו הידועים לנו מפי הקבלה.  הרב צבי פסח פראנק זצ'ל     ";
			break;
		}

	}

	wstring intToOtiyot(unsigned int input)
	{
		wstring toReturn = L"";
		if (input / 100 == 1) toReturn += L"ק";
		input = input % 100;
		if (input == 15) {
			toReturn += L"טו";
			return toReturn;
		}
		if (input == 16) {
			toReturn += L"טז";
			return toReturn;
		}
		switch (input / 10) {
		case 1:
			toReturn += L"י";
			break;
		case 2:
			toReturn += L"כ";
			break;
		case 3:
			toReturn += L"ל";
			break;
		case 4:
			toReturn += L"מ";
			break;
		case 5:
			toReturn += L"נ";
			break;
		case 6:
			toReturn += L"ס";
			break;
		case 7:
			toReturn += L"ע";
			break;
		case 8:
			toReturn += L"פ";
			break;
		case 9:
			toReturn += L"צ";
			break;
		default:
			break;
		}
		input = input % 10;
		switch (input) {
		case 1:
			toReturn += L"א";
			break;
		case 2:
			toReturn += L"ב";
			break;
		case 3:
			toReturn += L"ג";
			break;
		case 4:
			toReturn += L"ד";
			break;
		case 5:
			toReturn += L"ה";
			break;
		case 6:
			toReturn += L"ו";
			break;
		case 7:
			toReturn += L"ז";
			break;
		case 8:
			toReturn += L"ח";
			break;
		case 9:
			toReturn += L"ט";
			break;
		default:
			break;
		}
		return toReturn;
	}

	unsigned int otiyotToint(wstring input)
	{
		unsigned int toReturn = 0;
		for (int i = 0; i < input.length(); i++) {
			switch (input[i]) {
			case L'א':
				toReturn += 1;
				break;
			case L'ב':
				toReturn += 2;
				break;
			case L'ג':
				toReturn += 3;
				break;
			case L'ד':
				toReturn += 4;
				break;
			case L'ה':
				toReturn += 5;
				break;
			case L'ו':
				toReturn += 6;
				break;
			case L'ז':
				toReturn += 7;
				break;
			case L'ח':
				toReturn += 8;
				break;
			case L'ט':
				toReturn += 9;
				break;
			case L'י':
				toReturn += 10;
				break;
			case L'כ':
				toReturn += 20;
				break;
			case L'ל':
				toReturn += 30;
				break;
			case L'מ':
				toReturn += 40;
				break;
			case L'נ':
				toReturn += 50;
				break;
			case L'ס':
				toReturn += 60;
				break;
			case L'ע':
				toReturn += 70;
				break;
			case L'פ':
				toReturn += 80;
				break;
			case L'צ':
				toReturn += 90;
				break;
			case L'ק':
				toReturn += 100;
				break;
			default:
				//TODO - Error, unfamiliar wchar
				break;

			}
		}
		return toReturn;
	}


	BooksNames FindSederBook(BooksNames book) {
		switch (book) {
		case ShmuelA:
		case ShmuelB:
			return Shmuel;
		case MelachimA:
		case MelachimB:
			return Melachim;
		case Hoshea: case Yoel: case Amos: case Ovadiyah: case Yonah: case Micah: case Nahum: case Habakkuk: case Tzefaniyah: case Haggai: case Zechariah: case Malachi:
			return Treisar;
		case Nehemiah: return Ezra;
		case DivreiHaYamimA: case DivreiHaYamimB: return DivreiHaYamim;
		default: return book;
		}
	}
}