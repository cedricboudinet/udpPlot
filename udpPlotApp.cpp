/***************************************************************
 * Name:      udpPlotApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Cedric Boudinet ()
 * Created:   2021-10-19
 * Copyright: Cedric Boudinet ()
 * License:
 **************************************************************/

#include "udpPlotApp.h"

//(*AppHeaders
#include "udpPlotMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(udpPlotApp);

bool udpPlotApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	udpPlotFrame* Frame = new udpPlotFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}

