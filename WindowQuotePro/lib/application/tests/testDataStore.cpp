
#include <gtest/gtest.h>
#include <DataStore.h>

TEST(UIComponentsTestDataStore, TestGrid)
{
    wxSharedPtr<DataStore> pDataStore(new DataStore(0L));

    EXPECT_EQ(, 0x05);
}
