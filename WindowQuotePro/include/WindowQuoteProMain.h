// BISMILLAAHIRRAHMAANIRRAHEEM
/***************************************************************
 * Name:      WindowQuoteProMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2022-10-30
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef WINDOWQUOTEPROMAIN_H
#define WINDOWQUOTEPROMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/statbmp.h>
#include <wx/msgdlg.h>

#include "WindowQuoteProApp.h"

#include "DialogHelp.h"
#include "DialogAbout.h"

#include "QuotesPage.h"


class WindowQuoteProFrame: public wxFrame
{
    public:
        WindowQuoteProFrame(wxWindow *window, const wxString& title, const wxPoint& oPosition,
                                         const wxSize& oSize, wxSharedPtr<DataStore> pDataStore);
        ~WindowQuoteProFrame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuHelp,
            idMenuAbout,
            idControlSetup,
            idControlDelete
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnHelp(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()

        wxSharedPtr<DataStore> m_pDataStore;

        void Setup(wxCommandEvent& oEvent);
        void Delete(wxCommandEvent& oEvent);


};


#endif // WINDOWQUOTEPROMAIN_H
