///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "udpPlotBase.h"

///////////////////////////////////////////////////////////////////////////

udpPlotFrameBase::udpPlotFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	PlotsBoxSizer = new wxBoxSizer( wxVERTICAL );


	this->SetSizer( PlotsBoxSizer );
	this->Layout();
	m_statusBar1 = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
	m_menubar1 = new wxMenuBar( 0 );
	mnuFile = new wxMenu();
	mnuItm_startStopCapt = new wxMenuItem( mnuFile, wxID_ANY, wxString( wxT("Start capture") ) + wxT('\t') + wxT("alt+A"), wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( mnuItm_startStopCapt );

	wxMenuItem* mnuItm_refresh;
	mnuItm_refresh = new wxMenuItem( mnuFile, wxID_ANY, wxString( wxT("Refresh") ) + wxT('\t') + wxT("alt+r"), wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( mnuItm_refresh );

	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem( mnuFile, wxID_ANY, wxString( wxT("Quit") ) + wxT('\t') + wxT("alt+q"), wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( m_menuItem2 );

	m_menubar1->Append( mnuFile, wxT("&File") );

	m_menu2 = new wxMenu();
	wxMenuItem* mnuItm_dataFormat;
	mnuItm_dataFormat = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("Load data format file") ) + wxT('\t') + wxT("alt+d"), wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( mnuItm_dataFormat );

	wxMenuItem* mnuItm_ipport;
	mnuItm_ipport = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("IP/Port") ) + wxT('\t') + wxT("alt+P"), wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( mnuItm_ipport );

	m_menubar1->Append( m_menu2, wxT("&Configuration") );

	this->SetMenuBar( m_menubar1 );


	this->Centre( wxBOTH );

	// Connect Events
	mnuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udpPlotFrameBase::OnStartStopCapture ), this, mnuItm_startStopCapt->GetId());
	mnuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udpPlotFrameBase::OnRefresh ), this, mnuItm_refresh->GetId());
	mnuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udpPlotFrameBase::OnMenuQuit ), this, m_menuItem2->GetId());
	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udpPlotFrameBase::OnMenuItemLoadDataFormatSelected ), this, mnuItm_dataFormat->GetId());
	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udpPlotFrameBase::OnConfig ), this, mnuItm_ipport->GetId());
}

udpPlotFrameBase::~udpPlotFrameBase()
{
	// Disconnect Events

}

ConfigDialog::ConfigDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 3, 2, 0, 0 );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Listen IP"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticText1->Wrap( -1 );
	gSizer1->Add( m_staticText1, 1, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	IP_ctrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( IP_ctrl, 0, wxALL, 5 );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Port"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticText2->Wrap( -1 );
	gSizer1->Add( m_staticText2, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	PORT_ctrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	PORT_ctrl->SetValidator( wxGenericValidator( &port_value ) );

	gSizer1->Add( PORT_ctrl, 0, wxALL, 5 );

	OK = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( OK, 0, wxALIGN_CENTER|wxALL, 5 );

	m_button2 = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_button2, 0, wxALIGN_CENTER|wxALL, 5 );


	this->SetSizer( gSizer1 );
	this->Layout();
	gSizer1->Fit( this );

	this->Centre( wxBOTH );
}

ConfigDialog::~ConfigDialog()
{
}
