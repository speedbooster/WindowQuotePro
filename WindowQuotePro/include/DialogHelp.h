// BISMILLAAHIRRAHMAANIRRAHEEM

#ifndef DIALOGHELP_H
#define DIALOGHELP_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/hyperlink.h>

#include "DataStore.h"
#include <wx/html/htmlwin.h>
#include <wx/webview.h>

static const wxString html_help = L""
L"<html>"
L"  <head>"
L"      <style>"
L"          body { font-family: Calibri }"
L"          h2 { color: #111111; }"
L"          h3 { color: #222222; }"
L"          h4 { color: #333333; }"
L"          h5 { color: #444444; }"
L"          p { color: #555555; }"
L"          .warning { color: #ff5555; font-weight: bold; }"
L"      </style>"
L"  </head>"
L"  <body>"
L"      <h1>BISMILLAAHIRRAHMAANIRRAHEEM</h1>"
L"      <h2>IN THE NAME OF ALLAAH, THE MOST BENEFICENT, THE MOST MERCIFUL</h2>"
L"      <h3>Introduction</h3>"
L"      <p>"
L"          <strong>WindowQuotePro</strong> is an application to generate quotes for Window panels"
L"      </p>"
L"      <h3>Requirements and dependencies</h3>"
L"      <p>"
L"          <strong>WindowQuotePro</strong> is based on <strong>SQLite</strong> database"
L"      </p>"
L"      <h3>Database Setup</h3>"
L"      <p>"
L"          <strong>WindowQuotePro</strong> is shipped with a ready to use blank database file <em>database.db</em><br />"
L"          However, if a reset to the database is desired, open <em>config.ini</em> and set <em>Debug</em> to <em>1</em>. Save <em>config.ini</em>.<br />"
L"          Now launch the <strong>WindowQuotePro</strong> and use the <em>Setup</em> and <em>Delete</em> controls at the top to reset the database file to a blank database. <span class=\"warning\">Warning: All data would be permanently lost.</span><br />"
L"          After a new database is setup, reset the <em>Debug</em> flag in <em>config.ini</em> to <em>0</em>.<br />"
L"      </p>"
L"      <h3>Usage</h3>"
L"      <h4>View/ Search quotes</h4>"
L"      <p>"
L"          Type and/ or select a search criteria in the search fields at the top of the application view in <strong>WindowQuotePro</strong> to fetch quote records from the database.<br />"
L"          Click <em>Reset</em> to reset the fields. Once the fields are reset, a search would return all the database records.<br />"
L"          Click <em>Search</em> to search the database for the field values.<br />"
L"          Click <em>Clear</em> to remove all records from the application view table. Records stored in the database are <strong>not</strong> affected.<br />"
L"      </p>"
L"      <h4>Add a new quote</h4>"
L"      <p>"
L"          To add a new quote, click the <em>Add</em> button at the top right corner of the application view. A new (highlighted) row is added in the table view.<br />"
L"          Enter the following information in the corresponding columns of the newly added row:<br />"
L"          <dl>"
L"              <dt><strong>Name:</strong></dt>"
L"              <dd><dd>Name of quote</dd>"
L"              <dt><strong>Customer:</strong></dt>"
L"              <dd>Customer name</dd>"
L"              <dt><strong>Material:</strong></dt>"
L"              <dd>Window panel material</dd>"
L"              <dt><strong>Size:</strong></dt>"
L"              <dd>Window panel size</strong></dd>"
L"          </dl>"
L"          Upon changing any of the <<em>Material</em> or <em>Size</em> properties, a new <strong>Price</strong> value is generated.<br />"
L"          Click <em>Save</em> to permanently store the quote record in the database.<br />"
L"      </p>"
L"      <h4>Delete a quote</h4>"
L"      <p>"
L"          To delete a quote permanently from the database, <em>Search</em> the quote to be visible in the table view.<br />"
L"          Click to select the quote to be marked for deletion.<br />"
L"          Click <em>Delete</em> in the top right corner of the application view to delete the selected quote from the database. <span class=\"warning\">Warning: This deletion is permanent.</span><br />"
L"      </p>"
L"  </body>"
L"</html>"
L"";

class DialogHelp : public wxDialog
{
    public:
        DialogHelp(wxWindow* window);
        ~DialogHelp();
    private:
        wxHtmlWindow* pHtmlWindow;
        wxWebView* pWebView;
};

#endif // DIALOGHELP_H
