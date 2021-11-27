/***************************************************************
 * Name:      udpPlotMain.h
 * Purpose:   Defines Application Frame
 * Author:    Cedric Boudinet ()
 * Created:   2021-10-19
 * Copyright: Cedric Boudinet ()
 * License:
 **************************************************************/

#ifndef UDPPLOTMAIN_H
#define UDPPLOTMAIN_H

//(*Headers(udpPlotFrame)
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
//*)
#include <vector>
#include <mathplot.h>
#include "udpPlotWindow.h"
class udpPlotFrame: public wxFrame
{
    public:

        udpPlotFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~udpPlotFrame();
        void postInit();
    private:

        //(*Handlers(udpPlotFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnConfig(wxCommandEvent& event);
        void OnStartCaptureSelected(wxCommandEvent& event);
        void OnStopCaptureSelected(wxCommandEvent& event);
        void OnMenuItemLoadDataFormatSelected(wxCommandEvent& event);
        void OnStartStopCaptureSelected(wxCommandEvent& event);
        void OnMenuRefreshSelected(wxCommandEvent& event);
        //*)
        //(*Identifiers(udpPlotFrame)
        static const long idMenuStartStopCapture;
        static const long idMenuRefresh;
        static const long idMenuQuit;
        static const long idMenuSocket;
        static const long idMenuLoadDataFormat;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(udpPlotFrame)
        wxStatusBar* StatusBar1;
        wxMenu* Menu3;
        wxMenuItem* MenuRefresh;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItemLoadDataFormat;
        wxBoxSizer* PlotsBoxSizer;
        wxMenuItem* StartStopCapture;
        //*)
        std::vector<mpInfoLegend*> mpInfoLegends;
        std::vector<udpPlotWindow*> mpWindows;
        std::vector<mpScaleX*> mpAxes_X;
        std::vector<mpScaleY*> mpAxes_Y;
        std::vector<mpFXYVector*> mpFXYVectors;
        std::vector<double> Vector_X;
        std::vector< std::vector<double> > Vectors_Y;
        DECLARE_EVENT_TABLE()
        std::vector<const wxColour*> plotColours;
        int udpSocket;
        int capturing=0;
        void captureLoop();
        void OnUdpPlotViewChanged(wxCommandEvent&);
        void RefreshData();
};

#endif // UDPPLOTMAIN_H
