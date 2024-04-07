// BISMILLAAHIRRAHMAANIRRAHEEM

#include "DialogAbout.h"

DialogAbout::DialogAbout(wxWindow* window)
    : wxDialog(window, wxID_ANY, _("About WindowQuotePro"), window->GetPosition() + wxPoint(
            window->GetSize().GetWidth() / 4,
            window->GetSize().GetHeight() / 4
        ), wxDefaultSize)
{
    wxPanel* contentsPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxDefaultSize);

    SetSize(wxSize(900, 600));

    wxPanel* pAppInfoPanel = new wxPanel(contentsPanel, wxID_ANY);
    //pBoxPanel->SetBackgroundColour(wxColor(200, 100, 100));

    wxStaticBitmap* pImage = new wxStaticBitmap(pAppInfoPanel, wxID_ANY, static_cast<wxFrame*>(this->GetParent())->GetIcon(), wxDefaultPosition, wxSize(80, 80));

    wxPanel* pAppInfoTextPanel = new wxPanel(pAppInfoPanel, wxID_ANY);
    wxStaticText* pAppInfoText = new wxStaticText(pAppInfoTextPanel, wxID_ANY,
        _(
            Concat({
                "WindowQuotePro (64-bit) ",
                wxString(AppVersion),
                "\n"
            })
        ), wxDefaultPosition, wxDefaultSize
    );
    wxHyperlinkCtrl* pAppMailLink = new wxHyperlinkCtrl(pAppInfoTextPanel, wxID_ANY,
        "\x00\xA9mailto:MBk@MuhammadBilalKhan.com", "mailto:MBk@MuhammadBilalKhan.com", wxDefaultPosition, wxDefaultSize
    );
    wxHyperlinkCtrl* pAppWebsiteLink = new wxHyperlinkCtrl(pAppInfoTextPanel, wxID_ANY,
        "http://www.MuhammadBilalKhan.com/", "http://www.MuhammadBilalKhan.com/", wxDefaultPosition, wxDefaultSize
    );
    wxBoxSizer* pAppInfoSizer = new wxBoxSizer(wxVERTICAL);
    pAppInfoSizer->Add(pAppInfoText, 0, wxEXPAND | wxTOP | wxRIGHT | wxBOTTOM | wxLEFT, 1);
    pAppInfoSizer->Add(pAppMailLink, 0, wxALIGN_LEFT, 1);
    pAppInfoSizer->Add(pAppWebsiteLink, 0, wxALIGN_LEFT, 1);
    pAppInfoTextPanel->SetSizerAndFit(pAppInfoSizer);

    wxStaticBoxSizer* pAppInfoPanelBoxSizer = new wxStaticBoxSizer(wxVERTICAL, contentsPanel, "");
    pAppInfoPanelBoxSizer->Add(pAppInfoPanel, 0, wxEXPAND | wxTOP | wxRIGHT | wxBOTTOM | wxLEFT, 1);

    wxBoxSizer* pAppInfoContentsSizer = new wxBoxSizer(wxHORIZONTAL);

    pAppInfoContentsSizer->AddSpacer(50);
    pAppInfoContentsSizer->Add(pImage, 1, wxEXPAND | wxRIGHT | wxBOTTOM | wxLEFT, 1);
    pAppInfoContentsSizer->AddSpacer(50);
    pAppInfoContentsSizer->Add(pAppInfoTextPanel, 0, wxEXPAND | wxRIGHT | wxBOTTOM | wxLEFT, 1);
    pAppInfoContentsSizer->AddSpacer(5);

    pAppInfoPanel->SetSizerAndFit(pAppInfoContentsSizer);


    wxStaticBoxSizer* pAppCopyBoxSizer = new wxStaticBoxSizer(wxVERTICAL, contentsPanel, "");
    wxStaticText* pAppCopyText = new wxStaticText(contentsPanel, wxID_ANY,
        _(
            Concat({
                L"Based on: C++, wxWidgets 3.2, SQLite 3, CMake"
            })
        ), wxDefaultPosition, wxDefaultSize
    );
    pAppCopyBoxSizer->Add(pAppCopyText, 0, wxEXPAND | wxTOP | wxRIGHT | wxBOTTOM | wxLEFT, 10);
    pAppCopyBoxSizer->AddSpacer(10);


    wxStaticBoxSizer* pAppControlsBoxSizer = new wxStaticBoxSizer(wxVERTICAL, contentsPanel, "");

    wxPanel* pAppControlsPanel = new wxPanel(contentsPanel, wxID_ANY);
    wxButton* pButton = new wxButton(pAppControlsPanel, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize);

    pAppControlsBoxSizer->Add(pAppControlsPanel, 0, wxEXPAND | wxTOP | wxRIGHT | wxBOTTOM | wxLEFT, 1);

    wxBoxSizer* pAppControlsContentsSizer = new wxBoxSizer(wxHORIZONTAL);

    pAppControlsContentsSizer->AddStretchSpacer();
    pAppControlsContentsSizer->Add(pButton, 0, wxEXPAND | wxRIGHT | wxBOTTOM | wxLEFT, 1);
    pAppControlsContentsSizer->AddStretchSpacer();

    pAppControlsPanel->SetSizerAndFit(pAppControlsContentsSizer);

    wxBoxSizer* contentsPanelSizer = new wxBoxSizer(wxVERTICAL);

    contentsPanelSizer->Add(pAppInfoPanelBoxSizer, 0, wxEXPAND | wxTOP | wxRIGHT | wxBOTTOM | wxLEFT, 1);
    contentsPanelSizer->Add(pAppCopyBoxSizer, 0, wxEXPAND | wxTOP | wxRIGHT | wxBOTTOM | wxLEFT, 1);
    contentsPanelSizer->Add(pAppControlsBoxSizer, 0, wxEXPAND | wxTOP | wxRIGHT | wxBOTTOM | wxLEFT, 1);

    contentsPanel->SetSizerAndFit(contentsPanelSizer);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(contentsPanel, 1, wxEXPAND | wxALL, 3);

    this->SetSizerAndFit(mainSizer);

    Bind(wxEVT_CLOSE_WINDOW, [=](wxCloseEvent&) { EndModal(wxID_OK); });
    Bind(wxEVT_BUTTON, &DialogAbout::OnClose, this, wxID_OK);
}

void DialogAbout::OnClose(wxCommandEvent& oEvent)
{
    EndModal(wxID_OK);
}

DialogAbout::~DialogAbout()
{
}
