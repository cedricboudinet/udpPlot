#include "udpPlotWindow.h"
#include <iostream>

wxDEFINE_EVENT(UDPPLOTWINDOW_VIEWCHANGED, wxCommandEvent);

//udpPlotWindow::udpPlotWindow()
udpPlotWindow::udpPlotWindow( wxWindow *parent, wxWindowID id,
            const wxPoint &pos, const wxSize &size, long flag ):
                mpWindow(parent, id, pos, size, flag )
{
    SetMargins(20,0,20,50);
    //SetMPScrollbars(1); plante
}

udpPlotWindow::~udpPlotWindow()
{
}

bool udpPlotWindow::UpdateBBox()
{
    static double m_posX_prev=0;
    static int m_scrX_prev=0;
    static double m_scaleX_prev=0;
    //printf("[mpWindow::UpdateBBox] Bounding box: Xmin = %f, Xmax = %f, Ymin = %f, YMax = %f\n", m_minX, m_maxX, m_minY, m_maxY);//<<std::endl;
    bool bl = mpWindow::UpdateBBox();
    //printf("[mpWindow::UpdateBBox] Bounding box: Xmin = %f, Xmax = %f, Ymin = %f, YMax = %f\n", m_minX, m_maxX, m_minY, m_maxY);//<<std::endl;
    if((m_posX_prev != m_posX) | (m_scaleX_prev!=m_scaleX) | (m_scrX_prev!=m_scrX))
    {
        //printf("view changed for %d: %.1f %d %.1f\n", GetId(), m_posX, m_scrX, m_scaleX);
        wxCommandEvent event(UDPPLOTWINDOW_VIEWCHANGED, GetId());
        event.SetEventObject(this);
        ProcessWindowEvent(event);
    }
    m_posX_prev = m_posX;
    m_scaleX_prev = m_scaleX;
    m_scrX_prev=m_scrX;
    return bl;
}
