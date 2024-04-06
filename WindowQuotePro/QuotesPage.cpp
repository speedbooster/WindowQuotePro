// BISMILLAAHIRRAHMAANIRRAHEEM

#include "QuotesPage.h"

QuotesPage::QuotesPage(wxWindow* parent, wxSharedPtr<DataStore> pDataStore, const wxString& strTitle)
    :
    Page(parent, pDataStore, strTitle)
{
    pPage = this;
    m_pDataStore = pDataStore;

    Page_Table = Quotes_Table;
    Page_Table_ID_Field = Quotes_Table_ID_Field;
    Grid_DateTimeGenerated_Col = Quotes_Grid_DateTimeGenerated_Col;
    Grid_DateTimeUpdated_Col = Quotes_Grid_DateTimeUpdated_Col;
    m_mapCols = mapQuotesCols;
    m_vecTableIDFields = vecQuotesTableIDFields;

    // column name, field label, display label, column size, field size ...// type attributes etc
    m_vecColumns.push_back({{Quotes_Grid_Indicator_Col_Str, "", Grid_Indicator_Col_Size, true}, {}});
    m_vecColumns.push_back({{Quotes_Grid_Stage_Col_Str, "Stage", Grid_Stage_Col_Size, true, bStageHidden}, {}});
    m_vecColumns.push_back({{Quotes_Grid_Message_Col_Str, "Message", Grid_Message_Col_Size, true, bMessageHidden}, {}});
    m_vecColumns.push_back({{Quotes_Grid_Controls_Col_Str, "Controls", Grid_Controls_Col_Size, true, bControlsHidden}, {}});
    m_vecColumns.push_back({{Quotes_Grid_ID_Col_Str, "ID", Grid_ID_Col_Size, true}, {"ID"}});
    m_vecColumns.push_back({{Quotes_Grid_Name_Col_Str, "Name", 200}, {"Name", true, wxDefaultSize, oDefaultFieldSize}});
    m_vecColumns.push_back({{Quotes_Grid_Customer_Col_Str, "Customer", 250}, {"Customer", true, wxDefaultSize, oDefaultFieldSize}});
    m_vecColumns.push_back({{Quotes_Grid_Material_Col_Str, "Material", 80}, {"Material", true, wxDefaultSize, oDefaultTinyFieldSize, typCombo}});
    m_vecColumns.push_back({{Quotes_Grid_Size_Col_Str, "Size", 80}, {"Size", true, wxDefaultSize, oDefaultTinyFieldSize, typCombo}});
    m_vecColumns.push_back({{Quotes_Grid_Price_Col_Str, "Price", Grid_Amount_Col_Size, true}, {"Price", true, wxDefaultSize, oDefaultSmallFieldSize}});
    m_vecColumns.push_back({{Quotes_Grid_DateTimeGenerated_Col_Str, "Generated", Grid_DateTime_Col_Size, true}, {}});
    m_vecColumns.push_back({{Quotes_Grid_DateTimeUpdated_Col_Str, "Updated", Grid_DateTime_Col_Size, true}, {}});
    m_vecColumns.push_back({{Quotes_Grid_Status_Col_Str, "Status", Grid_Status_Col_Size, true, !bDebug}, {}});


    m_vecFormElements.push_back({"btnReset", new wxButton(pPage, wxID_RESET, _("Reset"), wxDefaultPosition, oDefaultTinyFieldSize), false});

    ProcessFormFields();

    m_vecFormElements.push_back({"btnSearch", new wxButton(pPage, wxID_FIND, _("Search"), wxDefaultPosition, wxDefaultSize), false});
    m_vecFormElements.push_back({"btnClear", new wxButton(pPage, wxID_CLEAR, _("Clear"), wxDefaultPosition, oDefaultTinyFieldSize), false});
    m_vecFormElements.push_back({"Gap", 0L, false});
    m_vecFormElements.push_back({"btnAdd", new wxButton(pPage, wxID_ADD, _("Add"), wxDefaultPosition, oDefaultTinyFieldSize), false});
    m_vecFormElements.push_back({"btnSave", new wxButton(pPage, wxID_SAVE, _("Save"), wxDefaultPosition, oDefaultTinyFieldSize), false});
    m_vecFormElements.push_back({"btnDelete", new wxButton(pPage, wxID_DELETE, _("Delete"), wxDefaultPosition, oDefaultTinyFieldSize), false});

    Initialize();

    Load();

    auto pbtnReset = FindFormElement("btnReset");
    if (pbtnReset)
    {
        pbtnReset->SetToolTip("Reset search fields");
        Bind(wxEVT_BUTTON, &QuotesPage::Reset, this, wxID_RESET);
    }
    auto pbtnSearch = FindFormElement("btnSearch");
    if (pbtnSearch)
    {
        pbtnSearch->SetToolTip("Search quotes");
        Bind(wxEVT_BUTTON, &QuotesPage::SearchQuotes, this, wxID_FIND);
    }
    auto pbtnClear = FindFormElement("btnClear");
    if (pbtnClear)
    {
        pbtnClear->SetToolTip("Clear quotes view");
        Bind(wxEVT_BUTTON, &QuotesPage::Clear, this, wxID_CLEAR);
    }
    auto pbtnAdd = FindFormElement("btnAdd");
    if (pbtnAdd)
    {
        pbtnAdd->SetToolTip("Add a new quote entry");
        Bind(wxEVT_BUTTON, &QuotesPage::AddQuotes, this, wxID_ADD);
    }
    auto pbtnSave = FindFormElement("btnSave");
    if (pbtnSave)
    {
        pbtnSave->SetToolTip("Save changes");
        Bind(wxEVT_BUTTON, &QuotesPage::Save, this, wxID_SAVE);
    }
    auto pbtnDelete = FindFormElement("btnDelete");
    if (pbtnDelete)
    {
        pbtnDelete->SetToolTip("Delete selected quotes");
        Bind(wxEVT_BUTTON, &QuotesPage::Delete, this, wxID_DELETE);
    }

    Bind(wxEVT_GRID_CELL_CHANGED, &QuotesPage::GridCellChangedQuotes, this);
    Bind(wxEVT_GRID_CELL_RIGHT_CLICK, &QuotesPage::GridRightClick, this);
    Bind(wxEVT_GRID_CELL_LEFT_DCLICK, &QuotesPage::GridDoubleClick, this);

    m_pGrid->GetGridWindow()->Bind(wxEVT_MOTION, &QuotesPage::GridHover, this);

    Bind(wxEVT_MENU, &QuotesPage::RefreshRow, this, idGridRMenuRefresh);
}

void QuotesPage::Load()
{
    wxComboBox* pMaterialCombo = static_cast<wxComboBox*>(m_mapFormFields.at(Quotes_Grid_Material_Col_Str).pField);
    wxComboBox* pSizeCombo = static_cast<wxComboBox*>(m_mapFormFields.at(Quotes_Grid_Size_Col_Str).pField);

    if (pMaterialCombo)
    {
        FillComboBox(pMaterialCombo, m_pDataStore->GetMaterials(), Combo_All);//, 1, true);
    }
    if (pSizeCombo)
    {
        FillComboBox(pSizeCombo, m_pDataStore->GetSizes(), Combo_All);
    }

    // reverse insert
    GenerateComboBoxAttr(Quotes_Grid_Material_Col, m_pDataStore->GetMaterials().arrValues);
    GenerateComboBoxAttr(Quotes_Grid_Size_Col, m_pDataStore->GetSizes().arrValues);
}

void QuotesPage::SearchQuotes(wxCommandEvent& oEvent)
{
    PrepareSearchFields();
    SearchAction(GetSearchQuery());
}

void QuotesPage::GridCellChangedQuotes(wxGridEvent& oEvent)
{
    int nCol = oEvent.GetCol();
    int nRow = oEvent.GetRow();
    GridCellChanged(oEvent);
    if (nRow < m_pGrid->GetNumberRows())
    {
        if (nCol == Quotes_Grid_Material_Col)
        {
            UpdatePrice(nRow);
        }
        if (nCol == Quotes_Grid_Size_Col)
        {
            UpdatePrice(nRow);
        }
    }
}

void QuotesPage::GridRightClick(wxGridEvent& oEvent)
{
    wxPoint oPoint = oEvent.GetPosition();
    int nCol = oEvent.GetCol();
    int nRow = oEvent.GetRow();
    wxString strTitle = IsRowColValid(nRow, nCol) ? Concat({"ID: ", m_pGrid->GetCellValue(nRow, Quotes_Grid_ID_Col)}) : wxString("");
}

void QuotesPage::GridDoubleClick(wxGridEvent& oEvent)
{
    int nCol = oEvent.GetCol();
    int nRow = oEvent.GetRow();
    if (
            (nCol == Quotes_Grid_Price_Col)
        )
    {
        UpdatePrice(nRow);
    }
}

void QuotesPage::UpdatePrice(const int nRow)
{
    // Get price InShaaALLAAH
    if (IsRowValid(nRow))
    {
        int nPrice = -1;
        wxString strMaterial = GetCellValue(nRow, Quotes_Grid_Material_Col);
        wxString strSize = GetCellValue(nRow, Quotes_Grid_Size_Col);
        if (strMaterial == Material_Wood)
        {
            if (strSize == Size_S)
            {
                nPrice = 10;
            }
            else if (strSize == Size_M)
            {
                nPrice = 30;
            }
            else if (strSize == Size_L)
            {
                nPrice = 50;
            }
        }
        else if (strMaterial == Material_Metal)
        {
            if (strSize == Size_S)
            {
                nPrice = 20;
            }
            else if (strSize == Size_M)
            {
                nPrice = 40;
            }
            else if (strSize == Size_L)
            {
                nPrice = 70;
            }
        }
        SetCellValue(nRow, Quotes_Grid_Price_Col, (nPrice >= 0) ? StrOInt(nPrice) : wxString(""));
    }
}

void QuotesPage::AddQuotes(wxCommandEvent& oEvent)
{
    Load();
    Add(oEvent);
    GenerateComboBoxAttr(0, Quotes_Grid_Material_Col, m_pDataStore->GetMaterials().arrValues);
    GenerateComboBoxAttr(0, Quotes_Grid_Size_Col, m_pDataStore->GetSizes().arrValues);
    SetRowStage(0, Stage_New); // Re apply due to combo override above

    //wxGridCellAttrPtr pCellAttr = m_pGrid->GetOrCreateCellAttrPtr(0, Quotes_Grid_SID_Col);
    //pCellAttr->SetReadOnly(false);
}

QuotesPage::~QuotesPage()
{
}
