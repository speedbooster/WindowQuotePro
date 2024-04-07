// BISMILLAAHIRRAHMAANIRRAHEEM

#ifndef PAGE_H
#define PAGE_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <set>

#include <wx/notebook.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/dateevt.h>
//#include <wx/ctrlsub.h>
#include <wx/html/htmlwin.h>


#include "DataStore.h"

#include <wx/event.h>


// Standard column indices and their default column sizes
static const int Grid_Minimal_Col_Size = 5;

static const int Grid_Indicator_Col = 0;
static const int Grid_Indicator_Col_Size = Grid_Minimal_Col_Size;
static const wxString Grid_Indicator_Col_Str = "Indicator";
static const int Grid_Stage_Col = 1;
static const int Grid_Stage_Col_Size = 60;
static const wxString Grid_Stage_Col_Str = "Stage";
static const int Grid_Message_Col = 2;
static const int Grid_Message_Col_Size = 50;
static const wxString Grid_Message_Col_Str = "Message";
static const int Grid_Controls_Col = 3;
static const int Grid_Controls_Col_Size = 60;
static const wxString Grid_Controls_Col_Str = "Controls";
static const int Grid_Amount_Col_Size = 70;
static const int Grid_Name_Col_Size = 230;
static const int Grid_ID_Col = 4;
static const int Grid_ID_Col_Size = 30;
static const int Grid_DateTime_Col_Size = 150;
static const int Grid_Date_Col_Size = 70;
static const int Grid_Time_Col_Size = 70;
static const int Grid_Status_Col_Size = 120;


class Page : public wxWindow
{
    public:
        Page(wxWindow* parent, wxSharedPtr<DataStore> pDataStore, const wxString& strTitle);
        ~Page();

        wxString GetTitle();

        void Search(wxCommandEvent& oEvent);
        void Add(wxCommandEvent& oEvent);
        void Save(wxCommandEvent& oEvent);
        void Delete(wxCommandEvent& oEvent);
        void Clear(wxCommandEvent& oEvent);
        void Reset(wxCommandEvent& oEvent);

        bool AddRow(int& nRow);


        struct sRow;
        virtual bool CheckRowData(sRow& itRow, wxString& strMessage);
        void RefreshRow(wxCommandEvent& oEvent);
        void DeleteRow(wxCommandEvent& oEvent);
        void GridCellChanged(wxGridEvent& oEvent);
        void GridHover(wxMouseEvent& oEvent);
        void GridRightClick(wxGridEvent& oEvent);
        void CellChanged(const int nRow, const int nCol);
        void DeleteRow(const int nRow);
        bool DBDeleteAction(const int nRow, const wxString& strID, wxString& strMessage);
        virtual bool CheckDeletable(const int nRow, wxString& strID, wxString& strMessage);
        virtual bool DBDelete(const int nRow, wxString& strMessage);

        void PrepareSearchFields();
        wxString GetSearchQuery();
        void SearchAction(const wxString& strQuery);
        bool SearchExecute(const wxString& strQuery, typDBResultSet& vecResult, wxString& strMessage);
        void FillData(const typDBResultSet& vecResult);

        enum eFieldTypes
        {
            typStatic,
            typText,
            typCombo,
            typCheck,
            typButton
        };
        struct sFormElements {
            sFormElements(const wxString& strName = "", wxControl* pElement = nullptr, const bool bSearchable = false, int nSize = 0)
                : strName(strName), pElement(pElement), bSearchable(bSearchable), nSize(nSize) {}
            wxString strName = "";
            wxControl* pElement = nullptr;
            bool bSearchable = false;
            int nSize = 0; // spacer size
        };
        typedef std::vector<sFormElements> typFormElements;

        struct sColumn {
            sColumn(const wxString& strName = "", const wxString& strLabel = "", const int nSize = 200, const bool bReadOnly = false, const bool bHidden = false)
                : strName(strName), strLabel(strLabel), nSize(nSize), bReadOnly(bReadOnly), bHidden(bHidden) {}
            wxString strName = ""; // in db
            wxString strLabel = ""; // in table
            int nSize = 100; // table column width
            // edit control type
            bool bReadOnly = false;
            bool bHidden = false;
        };
        struct sField {
            sField(const wxString& strLabel = "", const bool bSearchable = false, const wxSize& oLabelSize = oDefaultFieldSize,
                   const wxSize& oSize = oDefaultFieldSize, const eFieldTypes& eFieldType = typText,
                   const wxWindowID& nID = wxID_ANY)
                : strLabel(strLabel), bSearchable(bSearchable), oLabelSize(oLabelSize), oSize(oSize), eFieldType(eFieldType),
                  nID(nID) {}
            wxString strLabel = "";
            bool bSearchable = false;
            wxSize oLabelSize = oDefaultFieldSize;
            wxSize oSize = oDefaultFieldSize;
            eFieldTypes eFieldType = typText;
            wxWindowID nID = wxID_ANY;
            bool bValid = false; // is field form pointer valid?
            wxTextEntry* pField = nullptr; // field form pointer
        };
        struct sColumnDetails {
            sColumnDetails(const sColumn& oColumn = {}, const sField& oField = {}, const bool bBlank = false)
                : oColumn(oColumn), oField(oField), bBlank(bBlank)
                {}
            sColumn oColumn;
            sField oField;
            bool bBlank = false; // gap
          //  int nSize = 0;
        };
        std::vector<sColumnDetails> m_vecColumns;

        struct sGridCellCoords {
            sGridCellCoords(const int nRow = 0, const int nCol = 0)
            : nRow(nRow), nCol(nCol) {}
            int nRow = 0;
            int nCol = 0;
        };

        typedef typDBResult typRowData;

        struct sRow {
            int nRow = -1;
            wxString strDBID = "-1";
            wxString strStage = "";
            wxString strDateTimeGenerated = "";
            wxString strDateTimeUpdated = "";
            wxString strNewDateTimeUpdated = "";
            typRowData mapData;
        };

        struct sTableIDField {
            sTableIDField(const wxString& strTable, const wxString& strIDField)
                : strTable(strTable), strIDField(strIDField) {}
            wxString strTable = "";
            wxString strIDField = "";
        };
        std::vector<sTableIDField> m_vecTableIDFields;

        wxString Page_Table = "";
        wxString Page_Table_ID_Field = "";
        int Grid_DateTimeGenerated_Col = 0;
        int Grid_DateTimeUpdated_Col = 0;

        // name, pointer, use for search?
        typFormElements m_vecFormElements; // contains column and fields generation information

        // separate from form elements because form elements contain static text etc
        // and form fields contain text entry to read value
        struct sFormField {
            sFormField(wxTextEntry* pField = nullptr, const eFieldTypes& eFieldType = typText)
                : pField(pField), eFieldType(eFieldType) {}
            wxTextEntry* pField = nullptr;
            eFieldTypes eFieldType = typText;
        };
        std::map<wxString, sFormField> m_mapFormFields; // contains field pointers

        DataStore::typFilters m_mapSearchFields;

        std::vector<std::vector<wxString>> m_vecTable;

        wxGrid* m_pGrid;
        void Initialize();
        void ProcessFormFields();
        bool m_bInsertAtStart = true;

        wxControl* FindFormElement(const wxString& strField);
        bool CheckValueExclusion(const wxString& strValue);
        void AlignCenter(const int nRow, const std::vector<int>& nCol);
        void AlignCenter(const int nRow);
        void SetRowBackgroundColour(const int nRow = 0, const wxColour& oColor = Color_New);
        void SetColBackgroundColour(const int nCol = 0, const wxColour& oColor = Color_New);
        void SetCellBackgroundColour(const int nRow = 0, const int nCol = 0, const wxColour& oColor = Color_New);
        void SetRowStage(const int nRow = 0, const wxString& strStage = Stage_New, const wxString& strMessage = "");
        void SetRowsStage(const std::vector<int>& vecnRows, const wxString& strStage = Stage_New, const wxString& strMessage = "");
        void SetCellStage(const int nRow = 0, const int nCol = 0, const wxString& strStage = Stage_New, const wxString& strMessage = "");
        wxString GetRowStage(const int nRow = 0);
        void SetRowMessage(const int nRow = 0, const wxString& strMessage = "");
        void SetRowsMessage(const std::vector<int>& vecnRows, const wxString& strMessage = "");
        bool IsRowValid(const int nRow = 0) const;
        bool IsColValid(const int nCol = 0) const;
        bool IsRowColValid(const int nRow = 0, const int nCol = 0) const;
        wxString GetCellValue(const int nRow = 0, const int nCol = 0) const;
        bool GetCellValue(const int nRow, const int nCol, wxString& strValue);
        bool SetCellValue(const int nRow = 0, const int nCol = 0, const wxString& strValue = "");
        int GetRowsCount();

        sGridCellCoords GetGridCellCoords(const wxPoint& oPoint);

        wxString GetRowMessage(const int nRow = 0);
        void ClearAll();
        void ClearRow(const int nRow, const int nCol = 0);
        void ClearRowData(const int nRow);
        void Exit(wxCommandEvent& oEvent);

        //typedef std::map<wxString, wxString> typRowData;
        //typedef typDBResult typRowData;

        // to contain column index to db column name mapping with save flag
        struct sCols {
            sCols(const wxString& strName = "", const bool bSave = false, const bool bNullable = false, const wxString& strDefault = "")
            : strName(strName), bSave(bSave), bNullable(bNullable), strDefault(strDefault)
            {}
            wxString strName = "";
            bool bSave = false;
            bool bNullable = false;
            wxString strDefault = "";
        };
        typedef std::map<int, sCols> typCols;
        typCols m_mapCols;

        bool GetRow(const int nRow, sRow& oRow, wxString& strMessage, const bool bCheck = true);
        bool GetUnsavedRows(std::vector<sRow>&, wxString& strMessage, const bool bStage = false);
        void SetRowValues(const int nRow = 0, const typRowData& mapRowData = typRowData(), const wxString& strStage = Stage_New, const wxString& strMessage = "", const bool bUpdateStage = true, const bool bReset = true);
        void AddAndSetRowValues(const typRowData& mapRowData = typRowData(), const wxString& strStage = Stage_New, const wxString& strMessage = "", const bool bUpdateStage = true, const bool bReset = true);

        // search field combo boxes
        void FillComboBox(wxComboBox* pComboBox, const wxArrayString& arrItems, const wxString& strInitialItem = "", const int nSelection = 0, bool bReverse = false);
        void FillComboBox(wxComboBox* pComboBox, const DataStore::sComboContents& oItems, const wxString& strInitialItem = "", const int nSelection = 0, bool bReverse = false);
        // grid cell combo boxes
        void GenerateComboBoxAttr(const int nCol, const wxArrayString& arrItems);
        void GenerateComboBoxAttr(const int nRow, const int nCol, const wxArrayString& arrItems);
        void UpdateNextCell(const int nRow, const int nCol, const int nNextCol, const DataStore::sComboContents oElements);
        void UpdateIDCell(const int nRow, const int nIDCol, const int nValueCol, const DataStore::sComboContents& oElements);
        bool GetField(const int nRow, const int nCol, const int nValueCol, const DataStore::sComboContents& oElements, const wxString& strField, wxString& strFieldValue);
        wxString GetField(const int nRow, const int nCol, const int nValueCol, const DataStore::sComboContents& oElements, const wxString& strField);
        void UpdateCellField(const int nRow, const int nCol, const int nValueCol, const DataStore::sComboContents& oElements, const wxString& strField);
        void UpdateComboBoxCell(const int nRow, const int nCol, const wxArrayString& arrItems);
        void UpdateRowData(const DataStore::typFilters& mapSearchFields, const int nRow, const wxString& strTable = "", const wxString& strIDField = "", const bool bReset = true);
    private:
        wxWindow* pPage;
        wxWindow* m_pParent;
        wxSharedPtr<DataStore> m_pDataStore;
        wxString m_strTitle = "";

        wxBoxSizer* m_pSizer;
        wxFlexGridSizer* m_pControlsSizer;
        wxNotebook* pNotebook;

        enum
        {
            idGrid = 1000
        };
    protected:
        bool bDebug = !false;
        bool bStageHidden = !false;
        bool bMessageHidden = !false;
        bool bControlsHidden = true;
        bool bDateHidden = false;
        bool bNonHijriDateHidden = false;
};


#endif // PAGE_H
