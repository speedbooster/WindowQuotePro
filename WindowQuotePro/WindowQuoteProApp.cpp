// BISMILLAAHIRRAHMAANIRRAHEEM
/***************************************************************
 * Name:      WindowQuoteProApp.cpp
 * Purpose:   Code for Application Class
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

#include "WindowQuoteProApp.h"
#include "WindowQuoteProMain.h"

IMPLEMENT_APP(WindowQuoteProApp);

bool WindowQuoteProApp::OnInit()
{
    //wxImage::AddHandler(new wxPNGHandler);
    wxInitAllImageHandlers();
    wxSplashScreen* splash = new wxSplashScreen(wxBitmap("iconSplashScreen", wxBITMAP_TYPE_PNG_RESOURCE),
            wxSPLASH_CENTRE_ON_SCREEN | wxSPLASH_TIMEOUT,
            3000, NULL, -1, wxDefaultPosition, wxDefaultSize,
            wxBORDER_SIMPLE | wxSTAY_ON_TOP);

    wxSharedPtr<DataStore> pDataStore(new DataStore(0L));

    WindowQuoteProFrame* pFrame = new WindowQuoteProFrame(0L, _("Window Quote Pro"), wxDefaultPosition, wxSize(500, 500), pDataStore);
    SafeYield(pFrame, false);
    // To Set App Icon
#if defined(__WXMSW__)
    pFrame->SetIcon(wxICON(aaaa));
#else
    SetIcon(wxIcon("icon.ico"));
#endif // wxUSE_UNICODE
    pFrame->Show();

    return true;
}
