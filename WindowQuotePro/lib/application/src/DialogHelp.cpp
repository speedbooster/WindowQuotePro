// BISMILLAAHIRRAHMAANIRRAHEEM

#include "DialogHelp.h"

DialogHelp::DialogHelp(wxWindow* window)
    : wxDialog(window, wxID_ANY, _("WindowQuotePro Help"), window->GetPosition() + wxPoint(
            window->GetSize().GetWidth() / 8,
            window->GetSize().GetHeight() / 16
        ), wxDefaultSize + wxSize((window->GetSize().GetWidth() - (2 * (window->GetSize().GetWidth()) / 8)), 800))
{
    wxPanel* contentsPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxDefaultSize);

    wxBoxSizer* contentsPanelSizer = new wxBoxSizer(wxVERTICAL);

    pWebView = wxWebView::New(contentsPanel, wxID_ANY);

    contentsPanelSizer->Add(pWebView, 1, wxEXPAND | wxTOP | wxRIGHT | wxBOTTOM | wxLEFT, 1);
    contentsPanel->SetSizerAndFit(contentsPanelSizer);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(contentsPanel, 1, wxEXPAND | wxALL, 1);

    this->SetSizerAndFit(mainSizer);

    SetSize(wxSize((window->GetSize().GetWidth() - (2 * (window->GetSize().GetWidth()) / 8)), 600));

    Bind(wxEVT_CLOSE_WINDOW, [=](wxCloseEvent&) { EndModal(wxID_OK); });

    pWebView->SetPage(html_help, "baseUrl");

}

DialogHelp::~DialogHelp()
{
}
