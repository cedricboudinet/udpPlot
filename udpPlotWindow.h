#ifndef UDPPLOTWINDOW_H
#define UDPPLOTWINDOW_H

#include <mathplot.h>
wxDECLARE_EVENT(UDPPLOTWINDOW_VIEWCHANGED, wxCommandEvent);

class udpPlotWindow : public mpWindow
{
    public:
        udpPlotWindow( wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long flag );
        //udpPlotWindow();
        virtual ~udpPlotWindow();
        virtual bool UpdateBBox() override;
    protected:

    private:
};

#endif // UDPPLOTWINDOW_H
