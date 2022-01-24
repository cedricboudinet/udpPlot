///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/sizer.h>
#include <wx/gdicmn.h>
#include <wx/statusbr.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include <wx/spinctrl.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class udpPlotFrameBase
///////////////////////////////////////////////////////////////////////////////
class udpPlotFrameBase : public wxFrame
{
	private:

	protected:
		wxBoxSizer* PlotsBoxSizer;
		wxStatusBar* m_statusBar1;
		wxMenuBar* m_menubar1;
		wxMenu* mnuFile;
		wxMenuItem* mnuItm_startStopCapt;
		wxMenu* mnuConfig;

		// Virtual event handlers, override them in your derived class
		virtual void OnStartStopCapture( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRefresh( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuItemLoadDataFormatSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnConfig( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnConfAcq( wxCommandEvent& event ) { event.Skip(); }


	public:

		udpPlotFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("udpPlot"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~udpPlotFrameBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class AcquisitionDialog
///////////////////////////////////////////////////////////////////////////////
class AcquisitionDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText3;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrl4;
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText6;
		wxStaticText* m_staticText7;
		wxButton* m_button3;
		wxButton* m_button4;

	public:
		wxTextCtrl* bufferSizeValue;
		wxComboBox* triggerSource;
		wxSpinCtrlDouble* triggerLevel;
		wxComboBox* triggerSlope;

		AcquisitionDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("udpPlot: Acquisition configuration"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~AcquisitionDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class ConfigDialog
///////////////////////////////////////////////////////////////////////////////
class ConfigDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText2;
		wxButton* OK;
		wxButton* m_button2;

	public:
		wxTextCtrl* IP_ctrl;
		wxSpinCtrl* PORT_ctrl;

		ConfigDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("udpPlot: IP Config"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~ConfigDialog();

};

