#include "stdafx.h"
#include <string>
#include "CppUnitTest.h"
#include "../srt-validation/src/include/Subtitle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PopulateVectorValidSubsUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Subtitle sub[10000000];
			for (unsigned i = 0; i < 10000000; i++) {
				std::vector<std::string> curSub;
				std::stringstream id(i);
				std::string sID;
				id >> sID;
				curSub.push_back(sID);
				curSub.push_back("00:00.000 --> 00:00.000");
				int bound = rand() % 42;
				std::string line;
				for (int i = 0; i < bound; i++) {
					line[i] += rand() % ('a' - 'z') + 'a';
				}
				sub[i] = Subtitle(curSub);
			}
		}

	};
}