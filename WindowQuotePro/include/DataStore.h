// BISMILLAAHIRRAHMAANIRRAHEEM

#ifndef DATASTORE_H
#define DATASTORE_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "sqlite3.h"
#include <wx/tokenzr.h>
//#include <wx/secretstore.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
//#include <wx/html/htmprint.h>
#include <wx/textfile.h>
#include <wx/txtstrm.h>
#include <wx/wfstream.h>

#include <map>

const wxString strPathParameter = "%LOCAL_PATH%";

static const wxString Config_Application = "[Application]";
static const wxString Config_Application_Debug = "Debug";
static const wxString Config_Application_DatabasePath = "DatabasePath";


//------------- Database definitions -------------//
static const wxString Database_Version = "0.1";

static const wxString Database_Table = "Database";
static const wxString Database_Table_ID_Field = "DBID";
static const wxString Database_Table_Version_Field = "Version";

static const wxString Quotes_Table = "Quotes";
static const wxString Quotes_Table_ID_Field = "QID";
static const wxString Quotes_Table_Name_Field = "Name";
static const wxString Quotes_Table_Customer_Field = "Customer";
static const wxString Quotes_Table_Material_Field = "Material";
static const wxString Quotes_Table_Size_Field = "Size";
static const wxString Quotes_Table_Price_Field = "Price";

static const wxString Table_Status_Field = "Status";
static const wxString Table_DateTimeGenerated_Field = "DateTimeGenerated";
static const wxString Table_DateTimeUpdated_Field = "DateTimeUpdated";
static const wxString Table_Last_Insert_Value = "last_insert_rowid()";
//----------- Database definitions end -----------//


//--------------- Grid definitions ---------------//
static const wxColor Color_Selection = wxColor(250, 250, 255, 1);
static const wxColor Color_New = *wxCYAN;
static const wxColor Color_Idle = *wxWHITE;
static const wxColor Color_Modified = wxColor(220, 220, 255, 1);
static const wxColor Color_Obsolete = wxColor(255, 225, 0, 1);
static const wxColor Color_Error = wxColor(255, 220, 220, 1);
static const wxColor Color_Saved = wxColor(200, 225, 200, 1);
static const wxColor Color_ToBeSaved = wxColor(220, 255, 220, 1);
static const wxColor Color_Default = *wxLIGHT_GREY;

static const wxString Stage_New = "0-NEW-";
static const wxString Stage_Idle = "1-IDLE-";
static const wxString Stage_Modified = "2-MODIFIED-";
static const wxString Stage_Obsolete = "3-OBSOLETE-";
static const wxString Stage_Error = "4-ERROR-";
static const wxString Stage_Saved = "5-SAVED-";
static const wxString Stage_ToBeSaved = "6-TO-BE-SAVED-";

static const int nStageNew = 0;
static const int nStageIdle = 1;
static const int nStageModified = 2;
static const int nStageObsolete = 3;
static const int nStageError = 4;
static const int nStageSaved = 5;
static const int nStageToBeSaved = 6;

const int nDataStartCol = 5;

const bool bDebug = !false;
const bool bStageHidden = false;
const bool bMessageHidden = false;
const bool bControlsHidden = true;
const bool bDateHidden = false;
const bool bNonHijriDateHidden = false;

//------------- Grid definitions end -------------//

static const wxString Material_Wood = "Wood";
static const wxString Material_Metal = "Metal";

static const wxString Size_S = "S";
static const wxString Size_M = "M";
static const wxString Size_L = "L";

static const std::vector<wxString> Materials = {
    Material_Wood,
    Material_Metal
};

static const std::vector<wxString> Sizes = {
    Size_S,
    Size_M,
    Size_L
};


static long nToolTipDelay = 300;

static long Msg_Info = 0x00000004|wxCENTER|wxICON_INFORMATION;
static long Msg_Warn = 0x00000004|wxCENTER|wxICON_WARNING;
static long Msg_Error = 0x00000004|wxCENTER|wxICON_ERROR;

static const wxString Combo_Empty = "";
static const wxString Combo_All = "-all-";
static const std::vector<wxString> Exclusion_Values = {
    Combo_Empty,
    Combo_All
};

const int nDefaultFieldWidth = 200;
const wxSize oDefaultFieldSize = wxSize(200, -1);
const wxSize oDefaultTinyFieldSize = wxSize(50, -1);
const wxSize oDefaultSmallFieldSize = wxSize(80, -1);

typedef std::map<wxString, wxString> typDBResult;
typedef std::vector<typDBResult> typDBResultSet;

class DataStore : public wxObject
{
    public:
        DataStore(wxWindow* window);
        ~DataStore();

        ///////
        wxString GetFilePath();
        void SetFilePath(wxString& strFilePath);
        bool SaveData(const wxString& strQuery);
        bool LoadData(const wxString& strQuery);
        bool ExecuteQuery(const wxString& strQuery, typDBResultSet& vecResult, wxString& strMessage);
        bool ExecuteQueryGetStr(const wxString& strQuery, typDBResultSet& vecResult, wxString& strMessage);
        wxString GetCurrentDateTimeStr();
        struct sSearchFields {
            sSearchFields(const wxString& strVal = "", const bool bExact = false, const bool bQuotes = true)
                : strVal(strVal), bExact(bExact), bQuotes(bQuotes) {}
            wxString strVal = "";
            bool bExact = false;
            bool bQuotes = true;
        };
        // used to fill filter values for search query
        typedef std::map<wxString, sSearchFields> typFilters;
        void PrepareSearchFilters(wxString& strFilters, const typFilters& mapSearchFields);
        wxString GetSearchQuery(const wxString& strTable, const wxString& strIDField, const typFilters& mapSearchFields);
        ///////

        wxStandardPaths& GetStandardPaths();

        struct sComboValue {
            sComboValue(const wxString& strID = "", const wxString& strValue = "", const std::map<wxString, wxString>& mapMisc = {})
            : strID(strID), strValue(strValue), mapMisc(mapMisc) {}
            wxString strID = "";
            wxString strValue = "";
            std::map<wxString, wxString> mapMisc;
        };

        struct sComboContents {
            std::vector<sComboValue> vecValues;
            wxArrayString arrValues;// = [];
        };

        void AddComboContent(sComboContents& oComboContents, const wxString& strValue = "", const wxString& strID = "", const std::map<wxString, wxString>& mapMisc = {});

        sComboContents m_oMaterials;
        void UpdateMaterials();
        sComboContents& GetMaterials();

        sComboContents m_oSizes;
        void UpdateSizes();
        sComboContents& GetSizes();

        bool CheckValueExclusion(const wxString& strValue);

        /////////
        void GetConfig(const wxString& strConfig, std::map<wxString, wxString>& mapConfig);
        wxString GetConfigKey(const wxString& strConfig, const wxString& strKey);
        void GetConfigKey(const wxString& strConfig, const wxString& strKey, wxString& strVal);
        void SetConfig(const wxString& strConfig, const std::map<wxString, wxString>& mapConfig);
        void SetConfigKey(const wxString& strConfig, const wxString& strKey, const wxString& strVal);
        void LoadConfig();
        void SaveConfig();
        /////////

        bool GetFileContents(const wxString& strFile, wxString& strContents);
        bool GetDebugMode();
    private:
        bool m_bDebug = false;
        wxString m_strDatabaseFilePath = "database1.db";
        wxString m_strConfigPath = "config.ini";
        std::map<wxString, std::map<wxString, wxString> > m_mapConfig;
};

static wxString Concat(const std::vector<wxString>& vecStrings)
{
    wxString strResult = "";
    for (auto& it : vecStrings)
    {
        strResult.Append(it);
    }
    return strResult;
}

static wxString Concat(const wxArrayString& arrStrings, const wxString& strDelimiter)
{
    wxString strResult = "";
    for (auto& it : arrStrings)
    {
        if (strResult.Length() > 0)
        {
            strResult.Append(strDelimiter);
        }
        strResult.Append(it);
    }
    return strResult;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    auto& vecResults = (*((typDBResultSet*)(NotUsed)));
    std::map<wxString, wxString> tmp;
    for( i = 0; i < argc; i++)
    {
        wxString strCol = azColName[i];// ? azColName[i] : "NULL";
        wxString strVal = argv[i] ? argv[i] : "NULL";
        tmp[strCol] = strVal;
        //wxMessageBox(Concat({azColName[i], " | ", argv[i] ? argv[i] : "NULL"}));
    }
    vecResults.push_back(tmp);
    return 0;
}

static wxString StringifyResult(typDBResultSet vecResult)
{
    wxString strRet = "";
    wxString strRow = "";
    for (auto& it : vecResult)
    {
        strRow = "";
        for (auto& itr : it)
        {
            if (strRow != "")
            {
                strRow.Append(", ");
            }
            strRow.Append(Concat({itr.first, ": ", itr.second}));
        }
        strRet.Append(Concat({strRow, "\n"}));
    }
    return strRet;
}

static wxString StrOInt(const int nNum)
{
    return wxString::Format(wxT("%i"), nNum);
}

static int IntOStr(const wxString& str)
{
    //return str.ToInt();
    return wxAtoi(str);
}

static wxString StrOFloat(const double fNum)
{
	return wxString::Format(wxT("%.2f"), fNum);
}

static float FloatOStr(const wxString& str)
{
	double fTmp = 0.0;
	if (! (str.ToDouble(&fTmp))) {
		return 0.0;
	}
	return fTmp;
}

static int ModOInt(const int nNum)
{
    return (nNum < 0) ? nNum*(-1) : nNum;
}

static double ModOFloat(const double fNum)
{
    return (fNum < 0) ? fNum*(-1) : fNum;
}

static wxString GetDateTimeStr(wxDateTime& oDateTime)
{
    return oDateTime.Format("%Y/%m/%d %H:%M:%S");
}

static wxString GetDateTimeNowStr()
{
    return wxDateTime::Now().Format("%Y/%m/%d %H:%M:%S");
}

static wxString Append(wxString& strText, const wxString& strElement, const wxString strDelimiter = ", ")
{
    if (strText != "")
    {
        strText.Append(strDelimiter);
    }
    strText.Append(strElement);
    return strText;
}

static wxString Trim(const wxString& strText)
{
    wxString str = strText;
    return str = str.Trim().Trim(false);
}

static wxString Trim(const wxString& strText, const wxString& strDelimiter)
{
    wxString strRet = strText;
    if (strDelimiter.Length() != 1)
    {
        return strRet;
    }
    if (strRet.StartsWith(strDelimiter))
    {
        strRet.Remove(0, 1);
    }
    if (strRet.EndsWith(strDelimiter))
    {
        strRet.RemoveLast(1);
    }
    return strRet;
}

static wxString PrependIfNotEmpty(const wxString& strElement, wxString& strText)
{
    wxString strRet = "";
    if (strText != "")
    {
        strRet = Concat({strElement, strText});
    }
    return strRet;
}

static wxArrayString ArrOVec(const std::vector<wxString>& vecData)
{
    wxArrayString arrData;
    for (auto& it : vecData)
    {
        arrData.Add(it);
    }
    return arrData;
}

static std::vector<wxString> VecOArr(const wxArrayString& arrData)
{
    std::vector<wxString> vecData;
    for (auto& it : arrData)
    {
        vecData.push_back(it);
    }
    return vecData;
}

static void QueryError(const wxString& strMessage = "", const wxString& strQuery = "")
{
    wxMessageBox(Concat({strMessage, "\n\nQuery: ", strQuery}), "SQL query execution error", Msg_Error);
}

#endif // DATASTORE_H
