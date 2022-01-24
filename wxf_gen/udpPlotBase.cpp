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

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 2, 2, 0, 0 );

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


	bSizer4->Add( gSizer2, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Trigger") ), wxVERTICAL );

	wxGridSizer* gSizer4;
	gSizer4 = new wxGridSizer( 3, 2, 0, 0 );

	m_staticText5 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Source"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	gSizer4->Add( m_staticText5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	triggerSource = new wxComboBox( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	triggerSource->SetSelection( 0 );
	gSizer4->Add( triggerSource, 1, wxALL|wxEXPAND, 5 );

	m_staticText6 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Level"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	gSizer4->Add( m_staticText6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	triggerLevel = new wxSpinCtrlDouble( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -1e+06, 1e+06, 0, 1 );
	triggerLevel->SetDigits( 6 );
	gSizer4->Add( triggerLevel, 1, wxALL, 5 );

	m_staticText7 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Slope"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	gSizer4->Add( m_staticText7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	triggerSlope = new wxComboBox( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	triggerSlope->Append( wxT("Rising") );
	triggerSlope->Append( wxT("Falling") );
	triggerSlope->Append( wxT("Both") );
	triggerSlope->SetSelection( 0 );
	gSizer4->Add( triggerSlope, 0, wxALL|wxEXPAND, 5 );


	sbSizer1->Add( gSizer4, 1, wxEXPAND, 5 );


	bSizer4->Add( sbSizer1, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );


	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );

	m_button3 = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_button3, 0, wxALL, 5 );


	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );

	m_button4 = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_button4, 0, wxALL, 5 );


	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer4->Add( bSizer5, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer4 );
	this->Layout();
	bSizer4->Fit( this );

	this->Centre( wxBOTH );
}

AcquisitionDialog::~AcquisitionDialog()
{
}

ConfigDialog::ConfigDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Listen IP"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticText1->Wrap( -1 );
	fgSizer3->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );

	IP_ctrl = new wxTextCtrl( this, wxID_ANY, wxT("0.0.0.0"), wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !IP_ctrl->HasFlag( wxTE_MULTILINE ) )
	{
	IP_ctrl->SetMaxLength( 15 );
	}
	#else
	IP_ctrl->SetMaxLength( 15 );
	#endif
	IP_ctrl->Enable( false );

	fgSizer3->Add( IP_ctrl, 1, wxALL|wxEXPAND, 5 );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Port"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticText2->Wrap( -1 );
	fgSizer3->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );

	PORT_ctrl = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 65535, 0 );
	fgSizer3->Add( PORT_ctrl, 1, wxALL|wxEXPAND, 5 );


	bSizer2->Add( fgSizer3, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );


	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );

	OK = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( OK, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );

	m_button2 = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button2, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer2->Add( bSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );


	this->SetSizer( bSizer2 );
	this->Layout();
	bSizer2->Fit( this );

	this->Centre( wxBOTH );
}

ConfigDialog::~ConfigDialog()
{
}
