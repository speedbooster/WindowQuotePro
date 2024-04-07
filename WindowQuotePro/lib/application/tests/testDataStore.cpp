
#include <gtest/gtest.h>
#include <DataStore.h>

#include <wx/app.h>

TEST(ApplicationDataStore, TestGrid)
{
    wxDisableAsserts();
    wxSharedPtr<DataStore> pDataStore(new DataStore(0L));
    ASSERT_EQ(pDataStore->GetMaterials().vecValues.size(), 2);
}
