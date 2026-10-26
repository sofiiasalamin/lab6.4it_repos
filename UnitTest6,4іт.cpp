#include "pch.h"
#include "CppUnitTest.h"
#include "../6,4іт/6,4іт.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    static const double EPS = 1e-9;

   
    static void AssertArrayEqual(const double* expected, const double* actual, int n)
    {
        for (int i = 0; i < n; i++)
            Assert::AreEqual(expected[i], actual[i], EPS);
    }

    
    TEST_CLASS(CreateTests)
    {
    public:
        TEST_METHOD(AllocatesAndFillsWithinRange)
        {
            double* a = NULL;
            const int n = 500;
            Create(a, n, -10, 10);

            Assert::IsNotNull(a);
            for (int i = 0; i < n; i++)
            {
                Assert::IsTrue(a[i] >= -10 - EPS);
                Assert::IsTrue(a[i] <= 10 + EPS);
            }
            delete[] a;
        }

        TEST_METHOD(EqualBoundsGiveConstantValue)
        {
            double* a = NULL;
            Create(a, 10, 3, 3);

            for (int i = 0; i < 10; i++)
                Assert::AreEqual(3.0, a[i], EPS);
            delete[] a;
        }
    };
    
        
    TEST_CLASS(MoveZerosFirstTests)
    {
    public:
        TEST_METHOD(ZerosInMiddle_OrderPreserved)
        {
            double a[] = { 1, 0, 2, 0, 3 };
            double e[] = { 0, 0, 1, 2, 3 };
            MoveZerosFirst(a, 5);
            AssertArrayEqual(e, a, 5);
        }

       
        TEST_METHOD(NegativeAndPositiveMixed_OrderPreserved)
        {
            double a[] = { -1, 0, 3, 0, -2, 0, 4 };
            double e[] = { 0, 0, 0, -1, 3, -2, 4 };
            MoveZerosFirst(a, 7);
            AssertArrayEqual(e, a, 7);
        }

        TEST_METHOD(ElementCountIsPreserved)
        {
            double a[] = { 0, 1, 0, 2, 0, 3, 0 };
            MoveZerosFirst(a, 7);

            int zeros = 0;
            for (int i = 0; i < 7; i++)
                if (a[i] == 0) zeros++;
            Assert::AreEqual(4, zeros);
            Assert::AreEqual(0.0, a[3], EPS);
            Assert::AreEqual(1.0, a[4], EPS);
            Assert::AreEqual(2.0, a[5], EPS);
            Assert::AreEqual(3.0, a[6], EPS);
        }
    };
}
