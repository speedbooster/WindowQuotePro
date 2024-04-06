// BISMILLAAHIRRAHMAANIRRAHEEM
/***************************************************************
 * Name:      WindowQuoteProMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2022-10-30
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "WindowQuoteProMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(WindowQuoteProFrame, wxFrame)
    EVT_CLOSE(WindowQuoteProFrame::OnClose)
    EVT_MENU(idMenuQuit, WindowQuoteProFrame::OnQuit)
    EVT_MENU(idMenuAbout, WindowQuoteProFrame::OnAbout)
    EVT_MENU(idMenuHelp, WindowQuoteProFrame::OnHelp)
END_EVENT_TABLE()

WindowQuoteProFrame::WindowQuoteProFrame(wxWindow *window, const wxString& title, const wxPoint& oPosition,
                                         const wxSize& oSize, wxSharedPtr<DataStore> pDataStore)
    : wxFrame(window, -1, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE)
{
#if defined(__WXMSW__)
    SetIcon(wxIcon("aaaa"));
#else
    SetIcon(wxIcon("icon.ico"));
#endif // wxUSE_UNICODE

    m_pDataStore = pDataStore;

    bool bDisplayDebugControls = m_pDataStore->GetDebugMode();

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL); // to contain controlsPanel and contentsPanel InShaaALLAAH

    wxPanel* controlsPanel;
    if (bDisplayDebugControls)
    {
        controlsPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(10, 25));
        controlsPanel->SetBackgroundColour(wxColor(100, 100, 250));

        wxButton* oSetupButton = new wxButton(controlsPanel, idControlSetup, _("Setup"), wxDefaultPosition + wxPoint(0, 0), wxDefaultSize);
        wxButton* oDeleteButton = new wxButton(controlsPanel, idControlDelete, _("Delete"), wxDefaultPosition + wxPoint(100, 0), wxDefaultSize);

        Bind(wxEVT_BUTTON, &WindowQuoteProFrame::Setup, this, idControlSetup);
        Bind(wxEVT_BUTTON, &WindowQuoteProFrame::Delete, this, idControlDelete);

        mainSizer->Add(controlsPanel, 0, wxEXPAND | wxTOP | wxRIGHT | wxLEFT, 1);
    }

    wxPanel* contentsPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(10, 100));
    contentsPanel->SetBackgroundColour(wxColor(100, 255, 100));

    // Add Quotes page
    wxBoxSizer* contentsSizer = new wxBoxSizer(wxVERTICAL); // to contain Page InShaaALLAAH
    wxWindow* pQuotesWindow = new QuotesPage(contentsPanel, pDataStore, "Quotes");
    contentsSizer->Add(pQuotesWindow, 1, wxEXPAND, 1);
    contentsPanel->SetSizerAndFit(contentsSizer);

    mainSizer->Add(contentsPanel, 1, wxEXPAND | wxALL, 1);

    this->SetSizerAndFit(mainSizer);



    // create a menu bar
    wxMenuBar* mainMenuBar = new wxMenuBar();

    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
    mainMenuBar->Append(fileMenu, _("&File"));

    wxMenu* settingsMenu = new wxMenu(_T(""));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuHelp, _("&Help\tF1"), _("Application usage documentation"));
    helpMenu->Append(idMenuAbout, _("&About"), _("Show info about this application"));
    mainMenuBar->Append(helpMenu, _("&Help"));

    SetMenuBar(mainMenuBar);

    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    //SetStatusText(wxbuildinfo(short_f), 0);
    SetStatusText(_("WindowQuotePro"), 1);

    this->SetMinSize(wxSize(500, 400));

    Maximize();
}

void WindowQuoteProFrame::Setup(wxCommandEvent& oEvent)
{
    // check if table exists
    typDBResultSet vecResult;
    wxString strMessage = "";
    wxString strErrorMessage = "";
    std::vector<wxString> vecQueries = {
            Concat({
                "CREATE TABLE ", Database_Table, " (",
                    Database_Table_ID_Field, " INTEGER PRIMARY KEY ASC, ",
                    Database_Table_Version_Field, " TEXT, ",
                    Table_Status_Field, " TEXT, ",
                    Table_DateTimeGenerated_Field, " TEXT, ",
                    Table_DateTimeUpdated_Field, " TEXT"
                ");"
            }),
            Concat({
                "CREATE TABLE ", Quotes_Table, " (",
                    Quotes_Table_ID_Field, " INTEGER PRIMARY KEY ASC, ",
                    Quotes_Table_Name_Field, " TEXT, ",
                    Quotes_Table_Customer_Field, " TEXT, ",
                    Quotes_Table_Material_Field, " TEXT, ",
                    Quotes_Table_Size_Field, " TEXT, ",
                    Quotes_Table_Price_Field, " TEXT, ",
                    Table_Status_Field, " TEXT, ",
                    Table_DateTimeGenerated_Field, " TEXT, ",
                    Table_DateTimeUpdated_Field, " TEXT"
                ");"
            }),
            Concat({
                "INSERT INTO ", Database_Table, " (",
                    Database_Table_Version_Field,
                ") VALUES (",
                    Database_Version,
                "); SELECT ", Table_Last_Insert_Value, ";"
            })
    };

    for (auto& it : vecQueries)
    {
        if (!(m_pDataStore->ExecuteQuery(it, vecResult, strMessage)))
        {
            strErrorMessage.Append(strMessage);
        }
    }
    if (strErrorMessage.Length() > 0) {
        wxMessageBox(strErrorMessage);
    } else {
        wxMessageBox("ALHAMDOLILLAAH, database setup successful.", "BISMILLAAHIRRAHMAANIRRAHEEM");
    }
}

void WindowQuoteProFrame::Delete(wxCommandEvent& oEvent)
{
    // check if table exists
    wxString strQuery = Concat({
        "DROP TABLE ", Database_Table , ";",
        "DROP TABLE ", Quotes_Table , ";"
    });
    typDBResultSet vecResult;
    wxString strMessage = "";
    if (!(m_pDataStore->ExecuteQueryGetStr(strQuery, vecResult, strMessage))) {
        QueryError(strMessage, strQuery);
    } else {
        wxMessageBox(Concat({"ALHAMDOLILLAAH, tables dropped successfully.", "\n\n", strMessage}));
    }
}

WindowQuoteProFrame::~WindowQuoteProFrame()
{
}

void WindowQuoteProFrame::OnClose(wxCloseEvent &event)
{
    //Close(true);
    Destroy();
}

void WindowQuoteProFrame::OnQuit(wxCommandEvent &event)
{
    Close(true);
}

void WindowQuoteProFrame::OnAbout(wxCommandEvent& event)
{
    //wxMessageBox("BISMILLAAHIRRAHMAANIRRAHEEM", "");
    DialogAbout* pDialogAbout = new DialogAbout(this);
    pDialogAbout->ShowModal();
    pDialogAbout->Destroy();
}

void WindowQuoteProFrame::OnHelp(wxCommandEvent& event)
{
    DialogHelp* pDialogHelp = new DialogHelp(this);
    pDialogHelp->ShowModal();
    pDialogHelp->Destroy();
}

