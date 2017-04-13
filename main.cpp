#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;
};

class MyFrame : public wxFrame {
public:
  MyFrame();
  void OnClick(wxCommandEvent& event);
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
  MyFrame* frame= new MyFrame();
  frame -> Show();
    return true;
}


MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, wxT("RunScript test"), wxDefaultPosition, wxSize(400,300))
{
  wxPanel *panel = new wxPanel( this, wxID_ANY );
  wxBoxSizer* box = new wxBoxSizer( wxVERTICAL );

  wxButton *button = new wxButton( panel, wxID_ANY, wxT("Run") );
  wxTextCtrl* text = new wxTextCtrl( panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
  
  button -> SetFocus();
  
  box -> Add( text, 1, wxEXPAND | wxALL, 5);  
  box -> Add( button, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

  panel -> SetSizer( box );
  panel -> Layout();
  box -> Fit ( panel );

  Centre( wxBOTH );
  
  Connect( wxID_ANY, wxEVT_COMMAND_BUTTON_CLICKED,
	  wxCommandEventHandler(MyFrame::OnClick) );
  
}

void MyFrame::OnClick(wxCommandEvent& WXUNUSED(event))
{
}
