#include <wx/wx.h>
#include <wx/image.h>
#include "udpPlot.h"


class udpPlotApp: public wxApp {
public:
    bool OnInit();
};

IMPLEMENT_APP(udpPlotApp)

bool udpPlotApp::OnInit()
{
    wxInitAllImageHandlers();
    udpPlotFrame* frame = new udpPlotFrame(NULL, wxID_ANY, "Udp Plot");
    SetTopWindow(frame);
    frame->Show();
    return true;
}
