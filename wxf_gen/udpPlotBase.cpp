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

	mnuConfig = new wxMenu();
	wxMenuItem* mnuItm_dataFormat;
	mnuItm_dataFormat = new wxMenuItem( mnuConfig, wxID_ANY, wxString( wxT("Load data format file") ) + wxT('\t') + wxT("alt+d"), wxEmptyString, wxITEM_NORMAL );
	mnuConfig->Append( mnuItm_dataFormat );

	wxMenuItem* mnuItm_ipport;
	mnuItm_ipport = new wxMenuItem( mnuConfig, wxID_ANY, wxString( wxT("IP/Port") ) + wxT('\t') + wxT("alt+P"), wxEmptyString, wxITEM_NORMAL );
	mnuConfig->Append( mnuItm_ipport );

	wxMenuItem* mnuItm_confAcq;
	mnuItm_confAcq = new wxMenuItem( mnuConfig, wxID_ANY, wxString( wxT("Acquisition") ) + wxT('\t') + wxT("alt+Q"), wxEmptyString, wxITEM_NORMAL );
	mnuConfig->Append( mnuItm_confAcq );

	m_menubar1->Append( mnuConfig, wxT("&Configuration") );

	this->SetMenuBar( m_menubar1 );


	this->Centre( wxBOTH );

	// Connect Events
	mnuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udpPlotFrameBase::OnStartStopCapture ), this, mnuItm_startStopCapt->GetId());
	mnuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udpPlotFrameBase::OnRefresh ), this, mnuItm_refresh->GetId());
	mnuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udpPlotFrameBase::OnMenuQuit ), this, m_menuItem2->GetId());
	mnuConfig->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udpPlotFrameBase::OnMenuItemLoadDataFormatSelected ), this, mnuItm_dataFormat->GetId());
	mnuConfig->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udpPlotFrameBase::OnConfig ), this, mnuItm_ipport->GetId());
	mnuConfig->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udpPlotFrameBase::OnConfAcq ), this, mnuItm_confAcq->GetId());
}

udpPlotFrameBase::~udpPlotFrameBase()
{
	// Disconnect Events

}

AcquisitionDialog::AcquisitionDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 3, 2, 0, 0 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Buffer size"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gSizer2->Add( m_staticText3, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	bufferSizeValue = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( bufferSizeValue, 0, wxALL, 5 );

	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Decimation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gSizer2->Add( m_staticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrl4 = new wxTextCtrl( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl4->Enable( false );

	gSizer2->Add( m_textCtrl4, 0, wxALL, 5 );

	m_button3 = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_button3, 0, wxALL, 5 );

	m_button4 = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_button4, 0, wxALL, 5 );


	this->SetSizer( gSizer2 );
	this->Layout();
	gSizer2->Fit( this );

	this->Centre( wxBOTH );
}

AcquisitionDialog::~AcquisitionDialog()
{
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
