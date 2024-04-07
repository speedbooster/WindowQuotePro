// BISMILLAAHIRRAHMAANIRRAHEEM

#ifndef QUOTESPAGE_H
#define QUOTESPAGE_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "Page.h"

// Define grid columns (index and label)
static const int Quotes_Grid_Indicator_Col = Grid_Indicator_Col;
static const wxString Quotes_Grid_Indicator_Col_Str = Grid_Indicator_Col_Str;
static const int Quotes_Grid_Stage_Col = Grid_Stage_Col;
static const wxString Quotes_Grid_Stage_Col_Str = Grid_Stage_Col_Str;
static const int Quotes_Grid_Message_Col = Grid_Message_Col;
static const wxString Quotes_Grid_Message_Col_Str = Grid_Message_Col_Str;
static const int Quotes_Grid_Controls_Col = Grid_Controls_Col;
static const wxString Quotes_Grid_Controls_Col_Str = Grid_Controls_Col_Str;
static const int Quotes_Grid_ID_Col = Grid_ID_Col;
static const wxString Quotes_Grid_ID_Col_Str = Quotes_Table_ID_Field;
static const int Quotes_Grid_Name_Col = 5;
static const wxString Quotes_Grid_Name_Col_Str = Quotes_Table_Name_Field;
static const int Quotes_Grid_Customer_Col = 6;
static const wxString Quotes_Grid_Customer_Col_Str = Quotes_Table_Customer_Field;
static const int Quotes_Grid_Material_Col = 7;
static const wxString Quotes_Grid_Material_Col_Str = Quotes_Table_Material_Field;
static const int Quotes_Grid_Size_Col = 8;
static const wxString Quotes_Grid_Size_Col_Str = Quotes_Table_Size_Field;
static const int Quotes_Grid_Price_Col = 9;
static const wxString Quotes_Grid_Price_Col_Str = Quotes_Table_Price_Field;
static const int Quotes_Grid_DateTimeGenerated_Col = 10;
static const wxString Quotes_Grid_DateTimeGenerated_Col_Str = Table_DateTimeGenerated_Field;
static const int Quotes_Grid_DateTimeUpdated_Col = 11;
static const wxString Quotes_Grid_DateTimeUpdated_Col_Str = Table_DateTimeUpdated_Field;
static const int Quotes_Grid_Status_Col = 12;
static const wxString Quotes_Grid_Status_Col_Str = Table_Status_Field;

static const Page::typCols mapQuotesCols =
{
    {Quotes_Grid_Indicator_Col, {Quotes_Grid_Indicator_Col_Str}},
    {Quotes_Grid_Stage_Col, {Quotes_Grid_Stage_Col_Str}},
    {Quotes_Grid_Controls_Col, {Quotes_Grid_Controls_Col_Str}},
    {Quotes_Grid_ID_Col, {Quotes_Grid_ID_Col_Str}},
    {Quotes_Grid_Name_Col, {Quotes_Grid_Name_Col_Str, true}},
    {Quotes_Grid_Customer_Col, {Quotes_Grid_Customer_Col_Str, true}},
    {Quotes_Grid_Material_Col, {Quotes_Grid_Material_Col_Str, true}},
    {Quotes_Grid_Size_Col, {Quotes_Grid_Size_Col_Str, true}},
    {Quotes_Grid_Price_Col, {Quotes_Grid_Price_Col_Str, true}},
    {Quotes_Grid_DateTimeGenerated_Col, {Quotes_Grid_DateTimeGenerated_Col_Str}},
    {Quotes_Grid_DateTimeUpdated_Col, {Quotes_Grid_DateTimeUpdated_Col_Str}},
    {Quotes_Grid_Status_Col, {Quotes_Grid_Status_Col_Str}}
};

static const std::vector<Page::sTableIDField> vecQuotesTableIDFields =
{
};

class QuotesPage : public Page
{
    public:
        QuotesPage(wxWindow* parent, wxSharedPtr<DataStore> pDataStore, const wxString& strTitle);
        ~QuotesPage();

        void SearchQuotes(wxCommandEvent& oEvent);
        void AddQuotes(wxCommandEvent& oEvent);
        //void Save(wxCommandEvent& oEvent);
        //void DeleteQuotes(wxCommandEvent& oEvent);
        //void GenerateQuotes(wxCommandEvent& oEvent);

        //void RefreshRow(wxCommandEvent& oEvent);
        void GridCellChangedQuotes(wxGridEvent& oEvent);
        //void GridHover(wxMouseEvent& oEvent);
        void GridRightClick(wxGridEvent& oEvent);
        void GridDoubleClick(wxGridEvent& oEvent);

        void Load();
        void LoadQuotes();

        void QuotesConfigurationCellUpdated(const int nRow, bool bReset = false);
        void UpdatePrice(const int nRow);
    private:
        wxNotebookPage* pPage;
        wxSharedPtr<DataStore> m_pDataStore;

        enum
        {
            idGridQuotes = 1000,
            idGridRMenuRefresh = 999
        };


};

#endif // QUOTESPAGE_H
