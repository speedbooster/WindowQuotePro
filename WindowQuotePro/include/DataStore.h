// BISMILLAAHIRRAHMAANIRRAHEEM

#ifndef DATASTORE_H
#define DATASTORE_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/tokenzr.h>
//#include <wx/secretstore.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
//#include <wx/html/htmprint.h>
#include <wx/textfile.h>
#include <wx/txtstrm.h>
#include <wx/wfstream.h>

#include <map>


const bool bDebug = !false;
const bool bControlsHidden = false;

const wxString strPathParameter = "%LOCAL_PATH%";

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

/*const int nDefaultFieldWidth = 200;
const wxSize oDefaultFieldSize = wxSize(200, -1);
const wxSize oDefaultTinyFieldSize = wxSize(50, -1);
const wxSize oDefaultSmallFieldSize = wxSize(80, -1);
*/
//typedef std::map<wxString, wxString> typDBResult;
//typedef std::vector<typDBResult> typDBResultSet;

class DataStore : public wxObject
{
    public:
        DataStore(wxWindow* window);
        ~DataStore();

        ///////
        //wxString GetFilePath();
        //void SetFilePath(wxString& strFilePath);
        //bool SaveData(const wxString& strQuery);
        //bool LoadData(const wxString& strQuery);
        //bool ExecuteQuery(const wxString& strQuery, typDBResultSet& vecResult, wxString& strMessage);
        //bool ExecuteQueryGetStr(const wxString& strQuery, typDBResultSet& vecResult, wxString& strMessage);
        /*struct sSearchFields {
            sSearchFields(const wxString& strVal = "", const bool bExact = false, const bool bQuotes = true)
                : strVal(strVal), bExact(bExact), bQuotes(bQuotes) {}
            wxString strVal = "";
            bool bExact = false;
            bool bQuotes = true;
        };
        // used to fill filter values for search query
        typedef std::map<wxString, sSearchFields> typFilters;
        void PrepareSearchFilters(wxString& strFilters, const typFilters& mapSearchFields);
        wxString GetSearchQuery(const wxString& strTable, const wxString& strIDField, const typFilters& mapSearchFields);*/
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
    private:
        wxString m_strDatabaseFilePath = "database.db";
        wxString m_strConfigPath = "config.txt";
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

/*static int callback(void *NotUsed, int argc, char **argv, char **azColName){
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
*/

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
