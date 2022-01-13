#include "wxf_gen/udpPlotBase.h"
#include <vector>
#include "udpPlotWindow.h"
#include "udpData.h"

class udpPlotFrame: public udpPlotFrameBase
{
	public:
		udpPlotFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		virtual void OnMenuQuit( wxCommandEvent& event );
		void OnMenuItemLoadDataFormatSelected(wxCommandEvent& event);
		void OnUdpPlotViewChanged(wxCommandEvent&);
		void OnConfig(wxCommandEvent& event);
		void OnStartStopCapture(wxCommandEvent&);
		void OnRefresh( wxCommandEvent& event );
	private:
		std::vector<mpInfoLegend*> mpInfoLegends;
		std::vector<udpPlotWindow*> mpWindows;
		std::vector<mpScaleX*> mpAxes_X;
		std::vector<mpScaleY*> mpAxes_Y;
		std::vector<mpFXYVector*> mpFXYVectors;
		std::vector<double> Vector_X;
		std::vector< std::vector<double> > Vectors_Y;
		std::vector<const wxColour*> plotColours;
		void postInit();
		int capturing=0;
		void captureLoop();
		int udpSocket;
		void RefreshData();
		udpData_t udpData;
		uint16_t _listenPort=43210;
		//DECLARE_EVENT_TABLE()
};
