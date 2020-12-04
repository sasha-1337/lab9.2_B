#include "pch.h"
#include "CppUnitTest.h"
#include "../lab9.2_B/lab9_2_B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest92B
{
	TEST_CLASS(UnitTest92B)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int t;
			int mark_1 = 5, mark_2 = 4, mark_3 = 3;
			const int N = 1;
			t = midMark(N, mark_1, mark_2, mark_3);
			Assert::AreEqual(t, 4);
		}
	};
}
