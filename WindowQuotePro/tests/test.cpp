
#include <gtest/gtest.h>
#include <TestsAssist.h>

using namespace TestsAssist;

TEST(BackendTest, TestAdd)
{
    int32_t nA = 100;
    int32_t nB = 200;

    ASSERT_EQ(Add(nA, nB), 300);
}

