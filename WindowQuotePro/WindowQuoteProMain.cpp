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

    bool bDisplayDebugControls = !bDebug;

    wxPanel* controlsPanel;
    if (bDisplayDebugControls)
    {
        controlsPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(10, 25));
        controlsPanel->SetBackgroundColour(wxColor(100, 100, 250));
    }
    wxPanel* contentsPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(10, 100));
    contentsPanel->SetBackgroundColour(wxColor(100, 255, 100));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    if (bDisplayDebugControls)
    {
        mainSizer->Add(controlsPanel, 0, wxEXPAND | wxTOP | wxRIGHT | wxLEFT, 1);
    }

    mainSizer->Add(contentsPanel, 1, wxEXPAND | wxALL, 1);

    this->SetSizerAndFit(mainSizer);

//#if wxUSE_MENUS
    // create a menu bar
    wxMenuBar* mainMenuBar = new wxMenuBar();

    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
    mainMenuBar->Append(fileMenu, _("&File"));

    wxMenu* settingsMenu = new wxMenu(_T(""));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuAbout, _("&About\tF1"), _("Show info about this application"));
    mainMenuBar->Append(helpMenu, _("&Help"));

    SetMenuBar(mainMenuBar);
//#endif // wxUSE_MENUS

//#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    //SetStatusText(wxbuildinfo(short_f), 0);
    SetStatusText(_("WindowQuotePro"), 1);
//#endif // wxUSE_STATUSBAR

    if (bDisplayDebugControls)
    {
        wxButton* oSetupButton = new wxButton(controlsPanel, idControlSetup, _("Setup"), wxDefaultPosition + wxPoint(100, 0), wxDefaultSize);
        wxButton* oDeleteButton = new wxButton(controlsPanel, idControlDelete, _("Delete"), wxDefaultPosition + wxPoint(200, 0), wxDefaultSize);
    }

    if (bDisplayDebugControls)
    {
        Bind(wxEVT_BUTTON, &WindowQuoteProFrame::Setup, this, idControlSetup);
        Bind(wxEVT_BUTTON, &WindowQuoteProFrame::Delete, this, idControlDelete);
    }

    this->SetMinSize(wxSize(500, 400));

    Maximize();
}

void WindowQuoteProFrame::Setup(wxCommandEvent& oEvent)
{

}

void WindowQuoteProFrame::Delete(wxCommandEvent& oEvent)
{

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
    wxMessageBox("BISMILLAAHIRRAHMAANIRRAHEEM", "");
}

