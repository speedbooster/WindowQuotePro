// BISMILLAAHIRRAHMAANIRRAHEEM

#include "Page.h"

Page::Page(wxWindow* parent, wxSharedPtr<DataStore> pDataStore, const wxString& strTitle)
    : //pPage(page),
    wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, strTitle)
{
    pPage = this;
    m_pParent = parent;
    m_pDataStore = pDataStore;
    m_strTitle = strTitle;

    m_pSizer = new wxBoxSizer(wxVERTICAL);
    m_pControlsSizer = new wxFlexGridSizer(0);
}

wxString Page::GetTitle()
{
    return m_strTitle;
}

void Page::SetRowStage(const int nRow, const wxString& strStage, const wxString& strMessage)
{
    if ((nRow >= 0) && (nRow < m_pGrid->GetNumberRows()) && (m_pGrid->GetNumberCols() > 0))
    {
        const int nStage = IntOStr(strStage);
        m_pGrid->SetCellValue(wxGridCellCoords(nRow, Grid_Stage_Col), strStage);
        switch (nStage)
        {
        case nStageNew:
            SetRowBackgroundColour(nRow, Color_New);
            break;
        case nStageIdle:
            SetRowBackgroundColour(nRow, Color_Idle);
            break;
        case nStageModified:
            SetRowBackgroundColour(nRow, Color_Modified);
            break;
        case nStageObsolete:
            SetRowBackgroundColour(nRow, Color_Obsolete);
            break;
        case nStageError:
            SetRowBackgroundColour(nRow, Color_Error);
            break;
        case nStageSaved:
            SetRowBackgroundColour(nRow, Color_Saved);
            break;
        case nStageToBeSaved:
            SetRowBackgroundColour(nRow, Color_ToBeSaved);
            break;
        default:
            SetRowBackgroundColour(nRow, Color_Default);
            break;
        }
    }
    if (strMessage != "")
    {
        SetRowMessage(nRow, strMessage);
    }
}

void Page::SetCellStage(const int nRow, const int nCol, const wxString& strStage, const wxString& strMessage)
{
    if ((nRow >= 0) && (nRow < m_pGrid->GetNumberRows()) && (nCol >= 0) && (nCol < m_pGrid->GetNumberCols()))
    {
        const int nStage = IntOStr(strStage);
        //m_pGrid->SetCellValue(wxGridCellCoords(nRow, Grid_Stage_Col), strStage);
        switch (nStage)
        {
        case nStageNew:
            SetCellBackgroundColour(nRow, nCol, Color_New);
            break;
        case nStageIdle:
            SetCellBackgroundColour(nRow, nCol, Color_Idle);
            break;
        case nStageModified:
            SetCellBackgroundColour(nRow, nCol, Color_Modified);
            break;
        case nStageObsolete:
            SetCellBackgroundColour(nRow, nCol, Color_Obsolete);
            break;
        case nStageError:
            SetCellBackgroundColour(nRow, nCol, Color_Error);
            break;
        case nStageSaved:
            SetCellBackgroundColour(nRow, nCol, Color_Saved);
            break;
        case nStageToBeSaved:
            SetCellBackgroundColour(nRow, nCol, Color_ToBeSaved);
            break;
        default:
            SetCellBackgroundColour(nRow, nCol, Color_Default);
            break;
        }
    }
    if (strMessage != "")
    {
        SetRowMessage(nRow, strMessage);
    }
}

void Page::SetRowsStage(const std::vector<int>& vecnRows, const wxString& strStage, const wxString& strMessage)
{
    for (auto& nRow : vecnRows)
    {
        if ((nRow < m_pGrid->GetNumberRows()) && (m_pGrid->GetNumberCols() > 0))
        {
            SetRowStage(nRow, strStage, strMessage);
        }
    }
}

wxString Page::GetRowStage(const int nRow)
{
    return m_pGrid->GetCellValue(nRow, Grid_Stage_Col);
}

void Page::SetRowMessage(const int nRow, const wxString& strMessage)
{
    m_pGrid->SetCellValue(nRow, Grid_Message_Col, strMessage);
}

void Page::SetRowsMessage(const std::vector<int>& vecnRows, const wxString& strMessage)
{
    for (auto& nRow : vecnRows)
    {
        if ((nRow < m_pGrid->GetNumberRows()) && (m_pGrid->GetNumberCols() > 0))
        {
            SetRowMessage(nRow, strMessage);
        }
    }
}

wxString Page::GetRowMessage(const int nRow)
{
    return m_pGrid->GetCellValue(nRow, Grid_Message_Col);
}

bool Page::IsRowValid(const int nRow) const
{
    return ((nRow >= 0) && (nRow < m_pGrid->GetNumberRows()));
}

bool Page::IsColValid(const int nCol) const
{
    return ((nCol >= 0) && (nCol < m_pGrid->GetNumberCols()));
}

bool Page::IsRowColValid(const int nRow, const int nCol) const
{
    return (IsRowValid(nRow) && IsColValid(nCol));
}

void Page::SetRowBackgroundColour(const int nRow, const wxColour& oColor)
{
    for (int i = 0; i < m_pGrid->GetNumberCols(); i++)
    {
        m_pGrid->SetCellBackgroundColour(nRow, i, oColor);
    }
}

void Page::SetColBackgroundColour(const int nCol, const wxColour& oColor)
{
    for (int i = 0; i < m_pGrid->GetNumberRows(); i++)
    {
        m_pGrid->SetCellBackgroundColour(i, nCol, oColor);
    }
}

void Page::SetCellBackgroundColour(const int nRow, const int nCol, const wxColour& oColor)
{
    if ((m_pGrid->GetNumberRows() > nRow) && (m_pGrid->GetNumberCols() > nCol))
    {
        m_pGrid->SetCellBackgroundColour(nRow, nCol, oColor);
    }
}

void Page::AlignCenter(int nRow, const std::vector<int>& vecnCol)
{
    for (auto& it : vecnCol)
    {
        wxGridCellAttrPtr pGridCellAttr = m_pGrid->GetOrCreateCellAttrPtr(nRow, it);
        int nhAlign = 0;
        int nvAlign = 0;
        pGridCellAttr->GetAlignment(&nhAlign, &nvAlign);
        pGridCellAttr->SetAlignment(wxALIGN_CENTER, nvAlign);
    }
}

void Page::AlignCenter(int nRow)
{
    for (int i = 0; i < m_pGrid->GetNumberCols(); i++)
    {
        wxGridCellAttrPtr pGridCellAttr = m_pGrid->GetOrCreateCellAttrPtr(nRow, i);
        int nhAlign = 0;
        int nvAlign = 0;
        pGridCellAttr->GetAlignment(&nhAlign, &nvAlign);
        pGridCellAttr->SetAlignment(wxALIGN_CENTER, nvAlign);
    }
}

/*Page::typFormElements& Page::GetVecFormFields()
{
    return m_vecFormElements;
}*/

void Page::ProcessFormFields()
{
    // parse columns
    for (int i = 0; i < m_vecColumns.size(); i++)
    {
        auto& it = m_vecColumns[i];
        auto ite = std::find_if(m_vecFormElements.begin(), m_vecFormElements.end(), [it] (const auto& itr) {return (itr.strName == it.oColumn.strName);});
        if (ite != m_vecFormElements.end())
        {
            wxMessageBox("Column field already exists", "Error");
            continue;
        }
        if (it.bBlank == true)
        {
            m_vecFormElements.push_back({Concat({"Gap", wxString::Format(wxT("%i"), i)}), 0L, false});
            continue;
        }
        if (it.oField.bSearchable)
        {
            wxStaticText* pStaticText = new wxStaticText(pPage, wxID_ANY, Concat({it.oField.strLabel, ":"}), wxDefaultPosition, it.oField.oLabelSize);
            m_vecFormElements.push_back({Concat({it.oColumn.strName, "Static"}), pStaticText, false});
            if (it.oField.eFieldType == typCombo)
            {
                wxComboBox* pComboBox = new wxComboBox(pPage, it.oField.nID, "", wxDefaultPosition, it.oField.oSize, 0, NULL, wxCB_READONLY);
                m_vecFormElements.push_back({it.oColumn.strName, pComboBox, true});
                if (m_mapFormFields.find(it.oColumn.strName) == m_mapFormFields.end())
                {
                    m_mapFormFields[it.oColumn.strName] = {pComboBox, eFieldTypes::typCombo};
                    //m_vecFormFields.push_back(pComboBox);
                }
            } else {
                // causes memory leak
                wxTextCtrl* pTextCtrl = new wxTextCtrl(pPage, it.oField.nID, "", wxDefaultPosition, it.oField.oSize);
                m_vecFormElements.push_back({it.oColumn.strName, pTextCtrl, true});
                //m_vecFormFields.push_back(pTextCtrl);
                if (m_mapFormFields.find(it.oColumn.strName) == m_mapFormFields.end())
                {
                    m_mapFormFields[it.oColumn.strName] = {pTextCtrl, eFieldTypes::typText};
                }
            }
        }
    }
}

void Page::Initialize()
{
    // place form controls
    int i = 0;
    for (auto& it : m_vecFormElements)
    {
        if (it.pElement != 0L)
        {
            //wxMessageBox(Concat({"", it.first, " ", wxString::Format(wxT("%i"), i)}));
            m_pControlsSizer->AddGrowableCol(i);
            m_pControlsSizer->Add(it.pElement, 0, wxEXPAND | wxTOP | wxRIGHT | wxBOTTOM | wxLEFT | wxALIGN_CENTER_VERTICAL, 3);
        }
        else
        {
            //wxMessageBox(Concat({"null", it.first, " ", wxString::Format(wxT("%i"), i)}));
            m_pControlsSizer->AddGrowableCol(i, 1);
            m_pControlsSizer->AddSpacer(it.nSize);
        }
        i = i + 1;
    }

    m_pGrid = new wxGrid(pPage, idGrid, wxDefaultPosition, wxDefaultSize);
    m_pGrid->CreateGrid(0, 0);

    m_pGrid->SetColMinimalAcceptableWidth(Grid_Minimal_Col_Size);

    m_pGrid->AppendCols(m_vecColumns.size());

    for (int i = 0; i < m_vecColumns.size(); i++)
    {
        if (i < m_pGrid->GetNumberCols())
        {
            auto& it = m_vecColumns[i];
            m_pGrid->SetColLabelValue(i, it.oColumn.strLabel);
            m_pGrid->SetColSize(i, it.oColumn.nSize);
            if (it.oColumn.bReadOnly == true)
            {
                wxGridCellAttr* oCellAttr = new wxGridCellAttr();
                oCellAttr->SetReadOnly();
                m_pGrid->SetColAttr(i, oCellAttr);
            }
            if (it.oColumn.bHidden == true)
            {
                // hide
                //continue;
                m_pGrid->HideCol(i);
            }
        }
    }
    //AlignCenter(m_pGrid, 0);
    //m_pGrid->AppendRows(3);
    m_pGrid->SetSelectionMode(wxGrid::wxGridSelectRows);
    m_pGrid->HideCellEditControl();
    //m_pGrid->SetReadOnly(0,2,true);
    m_pGrid->SetSelectionForeground(Color_Selection);

    m_pGrid->HideRowLabels();

    m_pSizer->Add(m_pControlsSizer, 0, wxEXPAND | wxTOP | wxRIGHT | wxBOTTOM | wxLEFT, 3);
    m_pSizer->Add(m_pGrid, 1, wxEXPAND | wxRIGHT | wxBOTTOM | wxLEFT, 3);
    pPage->SetSizerAndFit(m_pSizer);

    /*auto pbtnExit = FindFormElement("btnExit");
    if (pbtnExit)
    {
        Bind(wxEVT_BUTTON, Exit, this, wxID_EXIT);
    }*/
}

wxControl* Page::FindFormElement(const wxString& strField)
{
    auto itElement = std::find_if(m_vecFormElements.begin(), m_vecFormElements.end(), [strField](const auto& it) {return it.strName == strField;} );
    if (itElement == m_vecFormElements.end())
    {
        return nullptr;
    }
    return (*itElement).pElement;
}

bool Page::CheckValueExclusion(const wxString& strValue)
{
    auto itElement = std::find_if(Exclusion_Values.begin(), Exclusion_Values.end(), [strValue](const auto& it) {return it == strValue;} );
    return (itElement == Exclusion_Values.end());
}

bool Page::DBDeleteAction(const int nRow, const wxString& strID, wxString& strMessage)
{
    wxString strDBID = Trim(strID);
    if (strDBID == "")
    {
        strMessage.Append(Concat({"(Row: ", StrOInt(nRow), ") Invalid ID: ", strDBID}));
        return false;
    }
    wxString strQuery = Concat({"DELETE FROM ", Page_Table, " WHERE ", Page_Table_ID_Field, " = ", strDBID});
    //wxMessageBox(strQuery);
    wxString strQueryMessage = "";
    typDBResultSet vecResult;
    if (!(m_pDataStore->ExecuteQuery(strQuery, vecResult, strQueryMessage))) {
        QueryError(strQueryMessage, strQuery);
        return false;
    }
    return true;
}

bool Page::CheckDeletable(const int nRow, wxString& strID, wxString& strMessage)
{
    strID = GetCellValue(nRow, Grid_ID_Col);
    if (strID == "")
    {
        // this should not happen InShaaALLAAH
        return false;
    }
    wxString strQueryTable = "";
    wxString strQueryID = "";
    wxString strQueryTableIDField = "";
    wxString strQuery = "";
    wxString strQueryMessage = "";
    typDBResultSet vecResult = {};
    for (auto& it : m_vecTableIDFields)
    {
        strQueryTable = it.strTable;
        strQueryID = "";
        strQueryTableIDField = Concat({it.strTable, ".", it.strIDField});
        strQuery = m_pDataStore->GetSearchQuery(strQueryTable, strQueryID, {{strQueryTableIDField, {strID, true, false}}});
        strQueryMessage = "";
        vecResult.clear();
        //wxMessageBox(strQuery);
        if (! SearchExecute(strQuery, vecResult, strQueryMessage)) {
            QueryError(strQueryMessage, strQuery);
            return false;
        } else {
            //wxMessageBox(StringifyResult(vecResult));
            if (vecResult.size() > 0) {
                strMessage.Append(Concat({"(Row: ", StrOInt(nRow), ") Unable to delete. Entry in use in table: ", strQueryTable, "\n"}));
                return false;
            }
        }
    }
    return true;
}

bool Page::DBDelete(const int nRow, wxString& strMessage)
{
    wxString strID = "";
    if (CheckDeletable(nRow, strID, strMessage))
    {
        // perform delete from database
        if (DBDeleteAction(nRow, strID, strMessage))
        {
            return true;
        }
    }
    //wxMessageBox(strMessage, "Error", Msg_Error);
    return false;
}

void Page::Clear(wxCommandEvent& oEvent)
{
    bool bUnsaved = false;
    wxString strRows = "";
    for (int nRow = 0; nRow < GetRowsCount(); nRow++)
    {
        if ((GetRowStage(nRow) == Stage_New) || (GetRowStage(nRow) == Stage_Modified))
        {
            bUnsaved = true;
            strRows.Append(Concat({"\n", StrOInt(nRow)}));
        }
    }
    if (bUnsaved)
    {
        if (wxMessageBox(Concat({"Following rows are unsaved, are you sure you want to clear?\n", strRows}),
                        "Are you sure?",
                        wxYES_NO|wxICON_QUESTION) == wxYES)
        {
            ClearAll();
        }
    } else {
        ClearAll();
    }
}

void Page::Reset(wxCommandEvent& oEvent)
{
    for (auto& it : m_mapFormFields)
    {
        if (it.second.eFieldType == typCombo)
        {
            wxComboBox* pComboBox = static_cast<wxComboBox*>(it.second.pField);
            if (pComboBox)
            {
                if (pComboBox->GetCount() > 0)
                {
                    pComboBox->SetSelection(0);
                }
            }
        }
        else
        {
            it.second.pField->SetValue("");
        }
    }
}

void Page::Delete(wxCommandEvent& oEvent)
{
    wxString strMessage = "";
    wxString strRows = "";
    for (auto& nRow: m_pGrid->GetSelectedRows())
    {
        strRows.Append(Concat({"\n", StrOInt(nRow)}));
    }
    if (strRows == "")
    {
        return;
    }
    if (wxMessageBox(Concat({"Following rows would be permanently deleted from the database. Are you sure?\n", strRows}),
                    "Are you sure?",
                    wxYES_NO|wxICON_INFORMATION) == wxYES)
    {
        for (auto& it : m_pGrid->GetSelectedRows())
        {
            if (GetRowStage(it) == Stage_New) {
                DeleteRow(it);
            }
            else if ((GetRowStage(it) == Stage_Idle) || (GetRowStage(it) == Stage_Saved)) {
                if (DBDelete(it, strMessage))
                {
                    DeleteRow(it);
                }
            }
        }
        if (strMessage != "") {
            strMessage.Prepend("One or more entries could not be deleted:\n\n");
            wxMessageBox(strMessage, "Error", Msg_Warn);
        }
    }
    //m_pGrid->SetColFormatDate(Classes_Grid_NonHijri_Col, "%d/%m/%Y");
    //wxMessageBox(Concat({"concat: ", oFile.GetCwd()}));
}

void Page::Add(wxCommandEvent& oEvent)
{
    int nRow;
    if (AddRow(nRow))
    {
        if (IsRowValid(nRow))
        {
            wxDateTime oDateTime = wxDateTime::Now();
            AlignCenter(nRow);
            // empty would result in "" InShaaALLAAH
            //SetRowValues(0, mapRowData, Stage_New);
            SetRowValues(nRow);
        }
    }
}

bool Page::AddRow(int& nRow)
{
    nRow = m_bInsertAtStart ? 0 : m_pGrid->GetNumberRows();
    return (m_pGrid->InsertRows(nRow));
}

void Page::PrepareSearchFields()
{
    m_mapSearchFields.clear();
    wxString strValue = "";
    for (auto& it : m_mapFormFields)
    {
        strValue = it.second.pField->GetValue();
        if (CheckValueExclusion(strValue)) {
            m_mapSearchFields[it.first] = {strValue};
        }
    }
}

wxString Page::GetSearchQuery()
{
    PrepareSearchFields();
    return m_pDataStore->GetSearchQuery(Page_Table, Page_Table_ID_Field, m_mapSearchFields);
}

void Page::FillData(const typDBResultSet& vecResult)
{
    int nRow;
    for (auto& it : vecResult)
    {
        if (AddRow(nRow))
        {
            //int nRow = 0;
            AlignCenter(nRow);
            SetRowValues(nRow, it, Stage_Idle);
        }
    } // end for loop
}

void Page::SearchAction(const wxString& strQuery)
{
    ClearAll();
    wxString strMessage = "";
    typDBResultSet vecResult;
    //wxMessageBox(strQuery);
    if (SearchExecute(strQuery, vecResult, strMessage)) {
        //wxMessageBox(StringifyResult(vecResult));
        FillData(vecResult);
    }
}

void Page::Search(wxCommandEvent& oEvent)
{
    SearchAction(GetSearchQuery());
}

bool Page::SearchExecute(const wxString& strQuery, typDBResultSet& vecResult, wxString& strMessage)
{
    bool bRet = true;
    if (!(m_pDataStore->ExecuteQuery(strQuery, vecResult, strMessage))) {
        QueryError(strMessage, strQuery);
        bRet = false;
    }
    return bRet;
}

bool Page::GetRow(const int nRow, Page::sRow& oRow, wxString& strMessage, const bool bCheck)
{
    bool bRet = true;
    wxString strVal = "";
    oRow.nRow = nRow;
    oRow.strDBID = m_pGrid->GetCellValue(nRow, Grid_ID_Col);
    oRow.strStage = "";
    oRow.strDateTimeGenerated = m_pGrid->GetCellValue(nRow, Grid_DateTimeGenerated_Col);
    oRow.strDateTimeUpdated = m_pGrid->GetCellValue(nRow, Grid_DateTimeUpdated_Col);
    for (auto& it : m_mapCols)
    {
        if (it.second.bSave)
        {
            strVal = GetCellValue(nRow, it.first);
            if (strVal == "") {
                strVal = it.second.strDefault;
            }
            if ((bCheck) && (strVal == "") && (! (it.second.bNullable))) // Error
            {
                strMessage.Append(Concat({"(Row: ", StrOInt(nRow), ", Col: \"", it.second.strName, "\"): ",
                                          "Field must not be empty.\n"}));
                bRet = false;
            } else {
                oRow.mapData[it.second.strName] = strVal;
            }
        }
    }
    oRow.strNewDateTimeUpdated = "";
    return bRet;
}

bool Page::GetUnsavedRows(std::vector<Page::sRow>& vecRows, wxString& strMessage)
{
    bool bRet = true;
    vecRows.clear();
    wxString strVal = "";
    for (int i = (m_pGrid->GetNumberRows() - 1); i >= 0; i--) // reverse to set previous one first
    {
        if ((GetRowStage(i) == Stage_New) ||
            (GetRowStage(i) == Stage_Modified) ||
            (GetRowStage(i) == Stage_Error))
        {
            sRow oRow;
            if (! GetRow(i, oRow, strMessage, true))
            {
                bRet = false;
            }
/*            oRow.nRow = i;
            oRow.strDBID = m_pGrid->GetCellValue(i, Grid_ID_Col);
            oRow.strStage = "";
            oRow.strDateTime = m_pGrid->GetCellValue(i, Grid_DateTime_Col);
            oRow.strDateTimeNonHijri = m_pGrid->GetCellValue(i, Grid_DateTimeNonHijri_Col);
            for (auto& it : m_mapCols)
            {
                if (it.second.bSave)
                {
                    strVal = GetCellValue(i, it.first);
                    if (strVal == "") {
                        strVal = it.second.strDefault;
                    }
                    if ((strVal == "") && (! (it.second.bNullable))) // Error
                    {
                        strMessage.Append(Concat({"(Row: ", StrOInt(i), ", Col: \"", it.second.strName, "\"): ",
                                                  "Field must not be empty.\n"}));
                        bRet = false;
                    } else {
                        oRow.mapData[it.second.strName] = strVal;
                    }
                }
            }
            oRow.strNewDateTime = "";
            oRow.strNewDateTimeNonHijri = "";*/
            vecRows.push_back(oRow);
        }
    }
    return bRet;//vecRows;
}

bool Page::CheckRowData(sRow& itRow, wxString& strMessage)
{
    return true;
}

void Page::Save(wxCommandEvent& oEvent)
{
    //std::vector<sRow> vecRows = GetUnsavedRows();
    wxString strMessage = "";
    std::vector<sRow> vecRows;
    if (! GetUnsavedRows(vecRows, strMessage)) {
        strMessage.Prepend("One or more rows have errors. Data not saved:\n\n");
        wxMessageBox(strMessage, "Error saving data", Msg_Error);
        return;
    }
    if (!(vecRows.size() > 0))
    {
        return;
    }
    wxString strIDs = "";
    for (auto& it : vecRows)
    {
        if (it.strDBID == "")
        {
            continue;
        }
        if (strIDs != "")
        {
            strIDs.Append(", ");
        }
        strIDs.Append(it.strDBID);
    }
    typDBResultSet vecResult;
    //wxString strMessage = "";
    if (strIDs != "")
    {
        wxString strQuery = Concat({"SELECT * FROM ", Page_Table, " WHERE ", Page_Table_ID_Field, " IN (", strIDs, ")"});
        //wxMessageBox(strQuery);
        if (!(m_pDataStore->ExecuteQuery(strQuery, vecResult, strMessage))) {
            QueryError(strMessage, strQuery);
        }
    }
    for (auto& it : vecRows)
    {
        if (it.strDBID == "") // new
        {
            it.strStage = Stage_New;
        } else {
            const auto& itrRecRow = std::find_if(vecResult.begin(), vecResult.end(),
                                        [this, &it](const auto& itr) {
                                            if (itr.find(Page_Table_ID_Field) != itr.end()) {
                                                return itr.at(Page_Table_ID_Field) == it.strDBID;
                                            } else { // if somehow the db table doesnt have the column name... unlikely InShaaALLAAH
                                                return false;
                                            }
                                        }
                                    );
            if (itrRecRow == vecResult.end())
            {
                it.strStage = Stage_Error;
                strMessage = Concat({"ID not found in database."});
                //wxMessageBox(strMessage, "Error");
                SetRowStage(it.nRow, Stage_Error, strMessage);
            } else {
                //wxMessageBox(Concat({it.strDateTimeUpdated, "  ", (*itrRecRow)[Table_DateTimeUpdated_Field]}), "date mismatch");
                //wxMessageBox(StringifyResult(vecResult));
                if ((it.strDateTimeGenerated == (*itrRecRow)[Table_DateTimeGenerated_Field]) && (it.strDateTimeUpdated == (*itrRecRow)[Table_DateTimeUpdated_Field]))
                {
                    it.strStage = Stage_Modified;
                } else {
                    it.strStage = Stage_Obsolete;
                    SetRowStage(it.nRow, Stage_Obsolete, "The entry has changed meanwhile.");
                }
            }
        }
    }
    // Check days
    //? check data function
/*    for (auto& it : vecRows)
    {
        if ((it.strStage == Stage_New) || (it.strStage == Stage_Modified)) // new
        {
            Hijri oHijriDate;
            oHijriDate.SetDate(it.mapData[Classes_Table_Hijri_Field]);
            oHijriDate.DecrementHijriMonths();
            wxString strQuery = Concat({"SELECT * FROM ", Classes_Table, " WHERE ", Classes_Table_Hijri_Field, " = '", oHijriDate.GetDate(), "'"});
            //wxMessageBox(strQuery);
            if (!(m_pDataStore->ExecuteQuery(strQuery, vecResult, strMessage))) {
                QueryError(strMessage, strQuery);
            } else {
                //wxMessageBox(StringifyResult(vecResult), "Result");
                if (vecResult.size() > 0)
                {
                    wxDateTime oPrevMonthNonHijriDate;
                    oPrevMonthNonHijriDate.ParseFormat(vecResult.at(0)[Classes_Table_NonHijri_Field], "%Y/%m/%d");
                    wxDateTime oCurrMonthNonHijriDate;
                    oCurrMonthNonHijriDate.ParseFormat(it.mapData[Classes_Table_NonHijri_Field], "%Y/%m/%d");
                    wxTimeSpan oDateTimeSpan = oCurrMonthNonHijriDate - oPrevMonthNonHijriDate;
                    int nDiffDays = oDateTimeSpan.GetDays();
                    if ((nDiffDays < 29) || (nDiffDays > 30))
                    {
                        //wxMessageBox(Concat({oPrevMonthNonHijriDate.Format("%Y %m %d"), "   ", oCurrMonthNonHijriDate.Format("%Y %m %d")}));
                        strMessage = Concat({"New month starts after ", StrOInt(nDiffDays), " days.\nNew month must start after 29 or 30 days."});
                        //wxMessageBox(strMessage, "Error");
                        it.strStage = Stage_Error;
                        SetRowStage(it.nRow, Stage_Error, strMessage);
                    }
                }
            }
        }
    }
*/    wxString strResult = "";
    //wxMessageBox(StrOInt(vecRows.size()));
    for (auto& it : vecRows)
    {
        //wxMessageBox(Concat({StrOInt(it.nRow), " : ", it.strDBID, " ", it.strStage}));
        if ((it.strStage == Stage_New) || (it.strStage == Stage_Modified))
        {
            wxString strQuery = "";
            //? check data already exists
            if (it.strDBID == "") // or Stage_New
            {
                wxString strKeys = "";
                wxString strValues = "";
                wxString strFilters = "";
                for (auto& ite : it.mapData)
                {
                    if (ite.first != Page_Table_ID_Field)
                    {
                        Append(strKeys, ite.first);
                        Append(strValues, Concat({"'", ite.second, "'"}));
                        Append(strFilters, Concat({ite.first, " = '", ite.second, "'"}), " AND ");
                    }
                }
                // Check new data
                strQuery = Concat({"SELECT * FROM ", Page_Table, PrependIfNotEmpty(" WHERE ", strFilters)});
                if (!(m_pDataStore->ExecuteQuery(strQuery, vecResult, strMessage))) {
                    QueryError(strMessage, strQuery);
                } else {// check if data already exists
                    if (vecResult.size() > 0)
                    {
                        it.strStage = Stage_Error;
                        wxString strID = vecResult.at(0)[Page_Table_ID_Field];
                        strMessage = Concat({"Data already exists in database (ID: ", strID, "): \n\n", strFilters});
                        //wxMessageBox(strMessage, "Error");
                        SetRowStage(it.nRow, Stage_Error, strMessage);
                        continue;
                    }
                }
                Append(strKeys, Table_DateTimeGenerated_Field);
                it.strDateTimeGenerated = m_pDataStore->GetCurrentDateTimeStr();
                Append(strValues, Concat({"'", it.strDateTimeGenerated, "'"}));
                Append(strKeys, Table_DateTimeUpdated_Field);
                it.strNewDateTimeUpdated = m_pDataStore->GetCurrentDateTimeStr();
                Append(strValues, Concat({"'", it.strNewDateTimeUpdated, "'"}));
                strQuery = Concat({"INSERT INTO ", Page_Table, " (", strKeys, ") VALUES (", strValues, "); SELECT last_insert_rowid();"});
            } else { // existing record
                it.mapData[Table_DateTimeUpdated_Field] = m_pDataStore->GetCurrentDateTimeStr();
                wxString strUpdates = "";
                for (auto& ite : it.mapData)
                {
                    if (ite.first != Page_Table_ID_Field)
                    {
                        if (strUpdates != "")
                        {
                            strUpdates.Append(", ");
                        }
                        strUpdates.Append(Concat({ite.first, " = '", ite.second, "'"}));
                    }
                }
                strQuery = Concat({"UPDATE ", Page_Table, " SET ", strUpdates, " WHERE ", Page_Table_ID_Field, " = ", it.strDBID});
                // Update all affected dates
            }
            //wxMessageBox(strQuery);
            if (strQuery != "")
            {
                if (!(m_pDataStore->ExecuteQuery(strQuery, vecResult, strMessage))) {
                    QueryError(strMessage, strQuery);
                } else {// get returned id and update UI rows....
                    //wxMessageBox(StringifyResult(vecResult), "Result");
                    if (it.strDBID == "")
                    {
                        it.strDBID = vecResult.at(0).at(Table_Last_Insert_Value);
                        if (vecResult.size() > 0)
                        {
                            //-m_pGrid->SetCellValue(it.nRow, Grid_ID_Col, vecResult.at(0).at(Table_Last_Insert_Value));
                        }
                    }
                    // fetch data just added
                    UpdateRowData({{Page_Table_ID_Field, {it.strDBID, true, false}}}, it.nRow, Page_Table, Page_Table_ID_Field);
                    SetRowStage(it.nRow, Stage_Saved);
                }
            }
        }
    }
    bool bError = false;
    for (auto& it : vecRows)
    {
        bError |= (it.strStage == Stage_Error);
    }
    if (bError)
    {
        wxMessageBox("One or more errors occurred.", "Error");
    }
}

void Page::ClearAll()
{
    m_pGrid->ClearGrid();
    int nRowCount = m_pGrid->GetNumberRows();
    if (nRowCount > 0)
    {
        m_pGrid->DeleteRows(0, nRowCount);
    }
}

void Page::ClearRow(const int nRow, const int nCol)
{
    for (int i = nCol; i < m_pGrid->GetNumberCols(); i++) {
        SetCellValue(nRow, i, "");
    }
}

void Page::ClearRowData(const int nRow)
{
    ClearRow(nRow, nDataStartCol);
}

void Page::DeleteRow(wxCommandEvent& oEvent)
{
    sGridCellCoords oCellCoords = *((sGridCellCoords*)(oEvent.GetClientData()));
    if (GetRowStage(oCellCoords.nRow) == Stage_New) {
        DeleteRow(oCellCoords.nRow);
    }
}

void Page::DeleteRow(const int nRow)
{
    m_pGrid->DeleteRows(nRow);
}

void Page::RefreshRow(wxCommandEvent& oEvent)
{
    sGridCellCoords oCellCoords = *((sGridCellCoords*)(oEvent.GetClientData()));
    wxMessageBox(Concat({"refresh ", StrOInt(oCellCoords.nRow), " ", StrOInt(oCellCoords.nCol)}));
}

void Page::GridCellChanged(wxGridEvent& oEvent)
{
    CellChanged(oEvent.GetRow(), oEvent.GetCol());
}

void Page::CellChanged(const int nRow, const int nCol)
{
    if ((GetRowStage(nRow) != Stage_New) && (GetRowStage(nRow) != Stage_Obsolete))
    {
        SetRowStage(nRow, Stage_Modified);
    }
}

void Page::GridHover(wxMouseEvent& oEvent)
{
    wxPoint oPoint = oEvent.GetPosition();
    sGridCellCoords oCellCoords = GetGridCellCoords(oPoint);
    int nCol = oCellCoords.nCol;
    int nRow = oCellCoords.nRow;
    if (IsRowColValid(nRow, nCol))
    {
        if (GetRowStage(nRow) == Stage_Error)
        {
            wxString strTooltip = Concat({GetRowMessage(nRow)});
            m_pGrid->GetGridWindow()->SetToolTip("");
            m_pGrid->GetGridWindow()->GetToolTip()->SetDelay(nToolTipDelay);
            m_pGrid->GetGridWindow()->GetToolTip()->SetTip(strTooltip);
            return;
        }
    }
    m_pGrid->GetGridWindow()->UnsetToolTip();
}

Page::sGridCellCoords Page::GetGridCellCoords(const wxPoint& oPoint)
{
    wxPoint oPosition = m_pGrid->CalcScrolledPosition(oPoint);
    int nCol = m_pGrid->XToCol(oPosition.x);
    int nRow = m_pGrid->YToRow(oPosition.y);
    return sGridCellCoords(nRow, nCol);
}

void Page::SetRowValues(const int nRow, const typRowData& mapRowData, const wxString& strStage, const wxString& strMessage, bool bUpdateStage, const bool bReset)
{
    if (nRow < m_pGrid->GetNumberRows())
    {
        for (auto& it : m_mapCols)
        {
            if (it.first < m_pGrid->GetNumberCols())
            {
                if (mapRowData.find(it.second.strName) != mapRowData.end())
                {
                    m_pGrid->SetCellValue(wxGridCellCoords(nRow, it.first), mapRowData.at(it.second.strName));
                } else {
                    if (bReset) {
                        m_pGrid->SetCellValue(wxGridCellCoords(nRow, it.first), "");
                    }
                }
            }
        }
        if (bUpdateStage) {
            SetRowStage(nRow, strStage, strMessage);
        }
    }
}

void Page::AddAndSetRowValues(const typRowData& mapRowData, const wxString& strStage, const wxString& strMessage, const bool bUpdateStage, const bool bReset)
{
    int nRow = m_bInsertAtStart ? 0 : m_pGrid->GetNumberRows();
    if (m_pGrid->InsertRows(nRow))
    {
        if (IsRowValid(nRow))
        {
            wxDateTime oDateTime = wxDateTime::Now();
            AlignCenter(nRow);
            // empty would result in "" InShaaALLAAH
            //SetRowValues(0, mapRowData, Stage_New);
            SetRowValues(nRow, mapRowData, strStage, strMessage, bUpdateStage, bReset);
        }
    }
}

wxString Page::GetCellValue(const int nRow, const int nCol) const
{
    return IsRowColValid(nRow, nCol) ? Trim(m_pGrid->GetCellValue(nRow, nCol)) : wxString("");
}

bool Page::GetCellValue(const int nRow, const int nCol, wxString& strValue)
{
    bool bValid = IsRowColValid(nRow, nCol);
    if (bValid)
    {
        strValue = m_pGrid->GetCellValue(nRow, nCol);
    }
    return bValid;
}

bool Page::SetCellValue(const int nRow, const int nCol, const wxString& strValue)
{
    bool bValid = IsRowColValid(nRow, nCol);
    if (bValid)
    {
        m_pGrid->SetCellValue(nRow, nCol, strValue);
    }
    return bValid;
}

int Page::GetRowsCount()
{
    return m_pGrid->GetNumberRows();
}

void Page::FillComboBox(wxComboBox* pComboBox, const wxArrayString& arrItems, const wxString& strInitialItem, const int nSelection, bool bReverse)
{
    if (!pComboBox)
    {
        //return;
    }
    pComboBox->Clear();
    for (auto& it : arrItems)
    {
        if (bReverse) {
            pComboBox->Insert(it, 0);
        } else {
            pComboBox->Append(it);
        }
    }
    if (strInitialItem.Length() > 0)
    {
        pComboBox->Insert(strInitialItem, 0);
    }
    if (nSelection < pComboBox->GetCount())
    {
        pComboBox->SetSelection(nSelection);
    }
}

void Page::FillComboBox(wxComboBox* pComboBox, const DataStore::sComboContents& oItems, const wxString& strInitialItem, const int nSelection, bool bReverse)
{
    pComboBox->Clear();
    for (auto& it : oItems.vecValues)
    {
        wxStringClientData* pData = new wxStringClientData(it.strID);
        if (bReverse) {
            pComboBox->Insert(it.strValue, 0, pData);
        } else {
            pComboBox->Append(it.strValue, pData);
        }
    }
    if (strInitialItem.Length() > 0)
    {
        wxStringClientData* pData = new wxStringClientData("");
        pComboBox->Insert(strInitialItem, 0, pData);
    }
    if (nSelection < pComboBox->GetCount())
    {
        pComboBox->SetSelection(nSelection);
    }
}

void Page::UpdateNextCell(const int nRow, const int nCol, const int nNextCol, const DataStore::sComboContents oElements)
{
    wxString strValue = m_pGrid->GetCellValue(nRow, nNextCol); // original value
    GenerateComboBoxAttr(nRow, nNextCol, oElements.arrValues);
    // do not reset old value if not needed
    m_pGrid->SetCellValue(nRow, nNextCol,
                          (std::find_if(oElements.vecValues.begin(),
                                        oElements.vecValues.end(),
                                        [strValue] (const auto& it) {return (it.strValue == strValue); }) != oElements.vecValues.end())
                          ? strValue : wxString("")
                         );
}

void Page::UpdateIDCell(const int nRow, const int nIDCol, const int nValueCol, const DataStore::sComboContents& oElements)
{
    wxString strValue = m_pGrid->GetCellValue(nRow, nValueCol);
    const auto& it = std::find_if(oElements.vecValues.begin(),
                                  oElements.vecValues.end(),
                                  [strValue] (const auto& it) {return (it.strValue == strValue); });
    if (it != oElements.vecValues.end())
    {
        m_pGrid->SetCellValue(nRow, nIDCol, it->strID);
    }
}

bool Page::GetField(const int nRow, const int nCol, const int nValueCol, const DataStore::sComboContents& oElements, const wxString& strField, wxString& strFieldValue)
{
    bool bRet = false;
    strFieldValue = "";
    wxString strValue = m_pGrid->GetCellValue(nRow, nValueCol);
    const auto& it = std::find_if(oElements.vecValues.begin(),
                                  oElements.vecValues.end(),
                                  [strValue] (const auto& it) {return (it.strValue == strValue); });
    if (it != oElements.vecValues.end())
    {
        auto itr = it->mapMisc.find(strField);
        if (itr != it->mapMisc.end())
        {
            strFieldValue = itr->second;
            bRet = true;
        }
    }
    return bRet;
}

wxString Page::GetField(const int nRow, const int nCol, const int nValueCol, const DataStore::sComboContents& oElements, const wxString& strField)
{
    wxString strFieldValue = "";
    GetField(nRow, nCol, nValueCol, oElements, strField, strFieldValue);
    return strFieldValue;
}

void Page::UpdateCellField(const int nRow, const int nCol, const int nValueCol, const DataStore::sComboContents& oElements, const wxString& strField)
{
    wxString strFieldValue = "";
    if (GetField(nRow, nCol, nValueCol, oElements, strField, strFieldValue))
    {
        m_pGrid->SetCellValue(nRow, nCol, strFieldValue);
    }
}

void Page::GenerateComboBoxAttr(const int nCol, const wxArrayString& arrItems)
{
    wxGridCellAttr* pCellAttr = new wxGridCellAttr();
    pCellAttr->SetEditor(new wxGridCellChoiceEditor(arrItems));
    m_pGrid->SetColAttr(nCol, pCellAttr);
}

void Page::GenerateComboBoxAttr(const int nRow, const int nCol, const wxArrayString& arrItems)
{
    if (IsRowValid(nRow)) {
        //wxGridCellAttr* pCellAttr = new wxGridCellAttr();
        wxGridCellAttrPtr pCellAttr = m_pGrid->GetOrCreateCellAttrPtr(nRow, nCol);
        pCellAttr->SetEditor(new wxGridCellChoiceEditor(arrItems));
        //m_pGrid->SetAttr(nRow, nCol, pCellAttr);
        SetRowStage(nRow, GetRowStage(nRow));
    }
}

void Page::UpdateComboBoxCell(const int nRow, const int nCol, const wxArrayString& arrItems)
{
    //ignore//wxGridCellChoiceEditor* pGridCellChoiceEditor = static_cast<wxGridCellChoiceEditor*>(m_pGrid->GetCellAttrPtr()->GetEditorPtr().get());
    //wxGridCellChoiceEditor* pGridCellChoiceEditor = static_cast<wxGridCellChoiceEditor*>(m_pGrid->GetCellEditor(nRow, nCol));
    //pGridCellChoiceEditor->SetParameters(Concat(arrItems, ",")); // does not override combo when passing empty string
    //pGridCellChoiceEditor->DecRef();
    GenerateComboBoxAttr(nRow, nCol, arrItems);
}

void Page::UpdateRowData(const DataStore::typFilters& mapSearchFields, const int nRow, const wxString& strTable, const wxString& strIDField, const bool bReset)
{
    wxString strQueryTable = (strTable != "") ? strTable : Page_Table;
    wxString strQueryID = (strIDField != "") ? strIDField : Page_Table_ID_Field;
    wxString strQuery = m_pDataStore->GetSearchQuery(strQueryTable, strQueryID, mapSearchFields);
    wxString strMessage = "";
    typDBResultSet vecResult;
    //wxMessageBox(strQuery);
    if (bReset) ClearRowData(nRow);
    if (SearchExecute(strQuery, vecResult, strMessage)) {
        //wxMessageBox(StringifyResult(vecResult));
        if (vecResult.size() > 0) {
            auto& it = vecResult.at(0);
            SetRowValues(nRow, it, GetRowStage(nRow), "", false, bReset);
        }
    }
}

void Page::Exit(wxCommandEvent& oEvent)
{
    /*for (auto& it : m_mapFormFields)
    {
        if (it.second)
        {
            delete it.second;
        }
    }
    Close(true);*/
}

Page::~Page()
{
}
