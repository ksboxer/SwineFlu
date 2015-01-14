#include "stdafx.h"
#include "CppUnitTest.h"
#include "Networking.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SwineNetworking;

namespace TestNetwoking
{		
	TEST_CLASS(TestNetworking)
	{
	public:
		TEST_METHOD(TestNetworking1)
		{
			Assert::AreEqual(true, true, L"Yay");
		}

	};
}