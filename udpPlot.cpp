#include "udpPlot.h"
#include <iostream>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <thread>
#include <netinet/in.h>
#include <algorithm>
udpPlotFrame::udpPlotFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
	udpPlotFrameBase(parent, id, title, pos, size, style)
{
	postInit();
}

void udpPlotFrame::OnMenuQuit( wxCommandEvent& event )
{
	std::cout<<"adios"<<std::endl;
	this->Destroy();
}

void udpPlotFrame::OnMenuItemLoadDataFormatSelected(wxCommandEvent& event)
{
	wxFileDialog
		openFileDialog(this, _("Load data format file"), "", "",
				"udpPlot data config files (*.json)|*.json", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	// proceed loading the file chosen by the user;
	// this can be done with e.g. wxWidgets input streams:
	Json::Value root;
	std::ifstream ifs;
	ifs.open(openFileDialog.GetPath());

	Json::CharReaderBuilder builder;
	JSONCPP_STRING errs;
	if (!parseFromStream(builder, ifs, &root, &errs)) {
		std::cout << errs << std::endl;
		wxMessageBox(std::string("Parsing config failed with error:\n")+errs, "Error", wxICON_ERROR);
		return;
	}
	////suppressing old layout
	/*for(std::vector<mpWindow*>::iterator mpw_it=mpWindows.begin(); mpw_it!=mpWindows.end();mpw_it++)// [](mpWindow* & mpw)
	  { //suppressing old layout
	  PlotsBoxSizer->Remove((wxWindow*)*mpw_it);
	  };*/
	for(size_t ip=0;ip<mpWindows.size();ip++)
	{
		PlotsBoxSizer->Remove(0);//berk
		delete mpWindows[ip];
		// mpAxes_X, mpAxes_Y and mpInfoLegends[ip] delete with mpWindow
	}
	mpWindows.resize(0);
	mpFXYVectors.resize(0);
	mpAxes_X.resize(0);
	mpAxes_Y.resize(0);
	mpInfoLegends.resize(0);
	for(size_t ic=0;ic<mpFXYVectors.size();ic++)
	{
		delete mpFXYVectors[0];
	}
	mpFXYVectors.resize(0);
	size_t nbGraph=root["graph"]["count"].asInt();
	int nbCurves=root["curves"]["count"].asInt();
	//populating window
	for(size_t i=0; i<nbGraph;i++)
	{
		//mpWindow * mpw = new mpWindow(this, ID_MATHPLOT1, wxDefaultPosition, wxSize(600,400), wxRAISED_BORDER|wxTAB_TRAVERSAL);
		udpPlotWindow * mpw = new udpPlotWindow(this, wxID_ANY, wxDefaultPosition, wxSize(600,400), wxRAISED_BORDER|wxTAB_TRAVERSAL);
		mpWindows.push_back(mpw);
		Bind(UDPPLOTWINDOW_VIEWCHANGED, &udpPlotFrame::OnUdpPlotViewChanged, this, mpw->GetId());
		PlotsBoxSizer->Add(mpw, 1, wxALL|wxEXPAND, 5);
		mpScaleX * xAxis = new mpScaleX(_("X"), mpALIGN_BOTTOM, false, mpX_NORMAL);
		mpw->AddLayer(xAxis);
		mpAxes_X.push_back(xAxis);
		mpScaleY * yAxis = new mpScaleY(_("Y"), mpALIGN_LEFT, false);
		mpw->AddLayer(yAxis);
		mpAxes_Y.push_back(yAxis);
		mpInfoLegend * leg = new mpInfoLegend(wxRect(0,0,40,40), wxTRANSPARENT_BRUSH); //&hatch2));
		mpw->AddLayer( leg);
		leg->SetVisible(true);
		mpInfoLegends.push_back(leg); //ah?
		mpw->UpdateAll();
		mpw->Fit();
	}
	std::cout<<"nb graphs:"<<nbGraph<<std::endl;
	std::cout<<"nb curves:"<<nbCurves<<std::endl;
	std::cout<<"Curves defs"<<std::endl;
	Vectors_Y.resize(nbCurves);
	for(int i=0;i<nbCurves;i++)
	{
		std::string name=root["curves"]["defs"][i]["Name"].asString();
		int dest=root["curves"]["defs"][i]["graph"].asInt();
		std::cout<<"name:"<<name<<" dest:"<<dest<<std::endl;
		mpFXYVector * FXYvector = new mpFXYVector(_(name), 0);
		wxPen   Vector1_PEN(*plotColours[i%plotColours.size()]);
		FXYvector->ShowName(false);
		FXYvector->SetPen(Vector1_PEN);
		FXYvector->SetContinuity(true);
		mpWindows[dest]->AddLayer(FXYvector);
		mpFXYVectors.push_back(FXYvector);
	}
	PlotsBoxSizer->Layout();
}
void udpPlotFrame::OnUdpPlotViewChanged(wxCommandEvent& event)
{
	static int blocked=0;
	if(blocked==1) return;
	blocked=1;
	//printf("event recv %d\n", event.GetId());
	udpPlotWindow * mpw = (udpPlotWindow*) event.GetEventObject();
	double m_posX=mpw->GetPosX();
	double m_scaleX=mpw->GetScaleX();
	int mpwid=event.GetId();
	//printf("event recv %d new coord: %f %d %f\n", event.GetId(), m_posX, m_scrX, m_scaleX);
	for(size_t iWin=0; iWin<mpWindows.size();iWin++)
	{
		if(mpwid!= mpWindows[iWin]->GetId())
		{
			mpWindows[iWin]->SetScaleX(m_scaleX);
			mpWindows[iWin]->SetPosX(m_posX);

		}
	}
	blocked=0;
}

void udpPlotFrame::postInit()
{
	plotColours.push_back(wxBLUE);
	plotColours.push_back(wxRED);
	plotColours.push_back(wxGREEN);
	plotColours.push_back(wxCYAN);
	plotColours.push_back(wxLIGHT_GREY);
	plotColours.push_back(wxYELLOW);

}

void udpPlotFrame::OnConfig(wxCommandEvent& event)
{
	ConfigDialog * dlg=new ConfigDialog(this, wxID_ANY);
	dlg->PORT_ctrl->SetValue(_listenPort);
	if(dlg->ShowModal()==wxID_OK)
	{
		_listenPort = dlg->PORT_ctrl->GetValue();
	}
	dlg->Destroy();
}

void udpPlotFrame::OnStartStopCapture(wxCommandEvent& event)
{
    if(capturing==0)
    {
        printf("starting capture\n");
        //captureLoop();
        mnuItm_startStopCapt->SetItemLabel("Stop capture\tAlt-A");
        capturing=1;
        std::thread * t =new std::thread(&udpPlotFrame::captureLoop, this);
        (void)t;
    }
    else
    {
        capturing=0;
        mnuItm_startStopCapt->SetItemLabel("Start capture\tAlt-A");
    }

}
void udpPlotFrame::captureLoop()
{

    udpSocket = socket(AF_INET, SOCK_DGRAM, 0); //IPPROTO_UDP);
    sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY; // listenning address
    addr.sin_port = htons(_listenPort); // port number with network byte order
    addr.sin_family = AF_INET; // IPv4
    int res = bind(udpSocket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    if(res!=0)
    {
     //   exit(-1); //TODO: error message
     wxMessageBox("Bind failed");
     return;
    }
    //sockaddr_in from;
    //socklen_t fromlen = sizeof(from);
    printf("Waiting for data\n");
    //int ret = recvfrom(udpSocket, (char*)buffer,2*sizeof(float), 0, reinterpret_cast<sockaddr*>(&from), &fromlen);
    size_t nbBytes = mpFXYVectors.size()*sizeof(double);
    size_t nbCurves = mpFXYVectors.size();
	double * buffer = new double[nbCurves];
	udpData.reinit(nbCurves);
    while(capturing==1)
    { //data collection
        int ret = recv(udpSocket, (char*)buffer, nbBytes, 0);//, reinterpret_cast<sockaddr*>(&from), &fromlen);
        if (ret <= 0)
            printf("error !!!\n");
        else
        {
		udpData.push_back(buffer);
        }
    }
	delete [] buffer;
    //graph update
    RefreshData();
    close(udpSocket);
}

void udpPlotFrame::RefreshData()
{
	//todo: populate Vector_X and Vector_Y from udpData
	udpData.getData(Vector_X, Vectors_Y);
    size_t nbCurves = mpFXYVectors.size();
    for(size_t icurve=0;icurve<nbCurves;icurve++)
    {
        mpFXYVectors[icurve]->SetData(Vector_X, Vectors_Y[icurve]);
    }

    std::for_each(mpWindows.begin(), mpWindows.end(), [](udpPlotWindow* & mpw)
    //for(auto_ptr mpw = mpWindows.begin(); mpw!=mpWindows.end(); mpw++)
    {
        mpw->UpdateAll();
        mpw->Fit();
    });
}

void udpPlotFrame::OnRefresh(wxCommandEvent& event)
{
    RefreshData();
}
