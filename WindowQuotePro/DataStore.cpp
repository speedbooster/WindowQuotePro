// BISMILLAAHIRRAHMAANIRRAHEEM

#include "DataStore.h"

DataStore::DataStore(wxWindow* window)
{
    wxFileName oFile(GetStandardPaths().GetExecutablePath());
    oFile.SetFullName(m_strDatabaseFilePath);
    m_strDatabaseFilePath = oFile.GetAbsolutePath();
}

wxStandardPaths& DataStore::GetStandardPaths()
{
    return wxStandardPaths::Get();
}

///////////////////////////
void DataStore::GetConfig(const wxString& strConfig, std::map<wxString, wxString>& mapConfig)
{
	mapConfig.clear();
    auto it = m_mapConfig.find(strConfig);
    if (it != m_mapConfig.end())
    {
    	mapConfig = (*it).second;
    }
}

wxString DataStore::GetConfigKey(const wxString& strConfig, const wxString& strKey)
{
	return m_mapConfig[strConfig][strKey];
}

void DataStore::GetConfigKey(const wxString& strConfig, const wxString& strKey, wxString& strVal)
{
	strVal = m_mapConfig[strConfig][strKey];
}

void DataStore::SetConfig(const wxString& strConfig, const std::map<wxString, wxString>& mapConfig)
{
    m_mapConfig[strConfig] = mapConfig;
}

void DataStore::SetConfigKey(const wxString& strConfig, const wxString& strKey, const wxString& strVal)
{
    m_mapConfig[strConfig][strKey] = strVal;
}

void DataStore::LoadConfig()
{
    if(!wxFileExists(m_strConfigPath)) {
        wxTextFile file(m_strConfigPath );
        file.Create();
    }
    wxFileInputStream input(m_strConfigPath);
    wxTextInputStream text(input, wxT("\x09"), wxConvUTF8 );
    if(!input.IsOk()) {
        return;
    }
    wxString strSection = "";
    wxString strKey = "";
    wxString strValue = "";
    while(input.IsOk() && !input.Eof() )
    {
        wxString wline=text.ReadLine();
        wline = wline.Trim().Trim(false);
        if (wline == "")
        {
        	continue;
        }
        if (! (wline.Contains(":"))) // found a new config section
        {
        	strSection = wline;
        	if (m_mapConfig.find(strSection) != m_mapConfig.end())
        	{
        		wxMessageBox(Concat({"Configuration section \"", strSection, "\" already parsed. Overwriting..."}), "Warning", Msg_Warn);
        	}
        	m_mapConfig[strSection].clear();
        	continue;
        }

        wxStringTokenizer oTokenizer(wline, ":");
        if (oTokenizer.CountTokens() != 2)
        {
        	wxMessageBox(Concat({"Invalid format for configuration entry section \"", wline, "\"."}), "Warning", Msg_Warn);
        	continue;
        }
        strKey = oTokenizer.GetNextToken().Trim().Trim(false);
        strValue = oTokenizer.GetNextToken().Trim().Trim(false);
        m_mapConfig[strSection][strKey] = strValue;
    }
    // Display loaded configuration:
    wxString strMessage = "ALHAMDOLILLAAH successfully loaded configuration:\n\n";
    wxString strConfig = "";
    for (auto& it : m_mapConfig)
    {
        strConfig.Append(Concat({it.first, "\n"}));
    	for (auto& itr : it.second)
    	{
    	    strConfig.Append(Concat({"      ", itr.first, " : ", itr.second, "\n"}));
    	}
        strConfig.Append("\n");
    }
    strMessage.Append(strConfig);
    wxMessageBox(strMessage);
}

void DataStore::SaveConfig()
{
    FILE* pfile = fopen(m_strConfigPath.ToStdString().c_str(), "w");
    for (auto& it : m_mapConfig)
    {
    	fprintf(pfile, "%s\n", it.first.ToStdString().c_str());
    	for (auto& itr: it.second)
    	{
    		fprintf(pfile, "%s : %s\n", itr.first.ToStdString().c_str(), itr.second.ToStdString().c_str());
    	}
    	fprintf(pfile, "\n");
    }
    fclose(pfile);
    fprintf(stdout, "Configuration successfully saved!\n");
}
///////////////////////////

bool DataStore::GetFileContents(const wxString& strFile, wxString& strContents)
{
    strContents = "";
    if(!wxFileExists(strFile)) {
        return false;
    }
    wxFileInputStream input(strFile);
    wxTextInputStream text(input, wxT("\x09"), wxConvUTF8 );
    if(!input.IsOk()) {
        return false;
    }
    while(input.IsOk() && !input.Eof() )
    {
        if (strContents.Length() > 0)
        {
            strContents.Append("\n");
        }
        strContents.Append(text.ReadLine());
    }
    return true;
}

/*wxString DataStore::GetFilePath()
{
    return m_strDatabaseFilePath;
}

void DataStore::SetFilePath(wxString& strFilePath)
{
    m_strDatabaseFilePath = strFilePath;
}

bool DataStore::ExecuteQuery(const wxString& strQuery,
                             typDBResultSet& vecResult,
                             wxString& strMessage)
{
    vecResult.clear();
    strMessage = "";
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open(m_strDatabaseFilePath.c_str(), &db);
    if( rc )
    {
        strMessage = Concat({"Can't open database: ", sqlite3_errmsg(db)});
        //wxMessageBox(Concat({"Can't open database: ", sqlite3_errmsg(db)}));
        sqlite3_close(db);
        return false;
    }
    rc = sqlite3_exec(db, strQuery.c_str(), callback, (void*)&vecResult, &zErrMsg);
    if( rc != SQLITE_OK ){
        strMessage = Concat({"SQL error: ", (const char*)zErrMsg, "\n\nQuery: ", strQuery});
        //wxMessageBox(Concat({"SQL error: ", (const char*)zErrMsg}));
        sqlite3_free(zErrMsg);
        return false;
    }
    sqlite3_close(db);
    return true;
}

bool DataStore::ExecuteQueryGetStr(const wxString& strQuery,
                             typDBResultSet& vecResult,
                             wxString& strMessage)
{
    auto& strResult = strMessage;
    if (!ExecuteQuery(strQuery, vecResult, strMessage)) {
        return false;
    } else {
        for (auto& it : vecResult)
        {
            for (auto& itr : it)
            {
                strResult.Append(itr.first);
                strResult.Append(" : ");
                strResult.Append(itr.second);
                strResult.Append(";   ");
            }
            strResult.Append("\n");
        }
    }
    return true;
}


bool DataStore::SaveData(const wxString& strQuery)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open(m_strDatabaseFilePath.c_str(), &db);
    if( rc )
    {
        wxMessageBox(Concat({"Can't open database: ", sqlite3_errmsg(db)}));
        sqlite3_close(db);
        return false;
    }
    rc = sqlite3_exec(db, strQuery.c_str(), callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        wxMessageBox(Concat({"SQL error: ", (const char*)zErrMsg}));
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);

    return true;
}


bool DataStore::LoadData(const wxString& strQuery)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("", &db);
    if( rc ){
        wxString str = "Can't open database: ";
        str.Append(sqlite3_errmsg(db));
      wxMessageBox(str);
      sqlite3_close(db);
    }
    return true;
}

void DataStore::PrepareSearchFilters(wxString& strFilters, const DataStore::typFilters& mapSearchFields)
{
    for (auto& it : mapSearchFields)
    {
        wxString strValue = it.second.strVal;
        bool bExact = it.second.bExact;
        bool bQuotes = it.second.bQuotes;
        Append(strFilters, Concat({it.first, " ", bExact ? "=" : "LIKE", " ", bQuotes ? "'" : "", bExact ? "" : "%", strValue, bExact ? "" : "%", bQuotes ? "'" : ""}), " AND ");
    }
}

wxString DataStore::GetSearchQuery(const wxString& strTable, const wxString& strIDField, const typFilters& mapSearchFields)
{
    wxString Page_Table = strTable; // to keep nomenclature consistent with Page class
    wxString Page_Table_ID_Field = Trim(strIDField);
    wxString strFilters = "";
    PrepareSearchFilters(strFilters, mapSearchFields);
    wxString strQuery = Concat({"SELECT * FROM ", Page_Table, PrependIfNotEmpty(" WHERE ", strFilters), PrependIfNotEmpty(" ORDER BY ", Page_Table_ID_Field)});
    if (strTable == Curriculum_Table) {
            Append(strFilters, Concat({Levels_Table, ".", Levels_Table_ID_Field, " = ", Curriculum_Table, ".", Curriculum_Table_LID_Field, ""}), " AND ");
            strQuery = Concat({"SELECT ",
                        Page_Table, ".*, ",
                        Levels_Table, ".", Levels_Table_ID_Field, ", ",
                        //Levels_Table, ".", Levels_Table_Year_Field, ", ",
                        Levels_Table, ".", Levels_Table_Level_Field, "",
                        " FROM ", Page_Table, ", ", Levels_Table, PrependIfNotEmpty(" WHERE ", strFilters), PrependIfNotEmpty(" ORDER BY ", Page_Table_ID_Field)});
    }
    return strQuery;
}
*/

void DataStore::AddComboContent(sComboContents& oComboContents, const wxString& strValue, const wxString& strID, const std::map<wxString, wxString>& mapMisc)
{
    oComboContents.arrValues.Add(strValue);
    oComboContents.vecValues.push_back({strID, strValue, mapMisc});
}


DataStore::~DataStore()
{
}
