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
    wxSharedPtr<DataStore> pDataStore(new DataStore(0L));

    WindowQuoteProFrame* pFrame = new WindowQuoteProFrame(0L, _("Window Quote Pro"), wxDefaultPosition, wxSize(500, 500), pDataStore);
    //pFrame->SetIcon(wxICON(aaaa)); // To Set App Icon
    pFrame->Show();

    return true;
}
