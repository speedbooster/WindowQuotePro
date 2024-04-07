// BISMILLAAHIRRAHMAANIRRAHEEM

#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/hyperlink.h>

#include "DataStore.h"

class DialogAbout : public wxDialog
{
    public:
        DialogAbout(wxWindow* window);
        ~DialogAbout();
    private:
        void OnClose(wxCommandEvent& oEvent);
};

#endif // DIALOGABOUT_H
