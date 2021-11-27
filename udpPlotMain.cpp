/***************************************************************
 * Name:      udpPlotMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Cedric Boudinet ()
 * Created:   2021-10-19
 * Copyright: Cedric Boudinet ()
 * License:
 **************************************************************/

#include "udpPlotMain.h"
#include <wx/msgdlg.h>
#include "ConfigDialog.h"

#include <netinet/in.h>
#include <jsoncpp/json/json.h>
#include <wx/filedlg.h>
#include <fstream>
#include <algorithm>
#include <thread>
//(*InternalHeaders(udpPlotFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(udpPlotFrame)
const long udpPlotFrame::idMenuStartStopCapture = wxNewId();
const long udpPlotFrame::idMenuRefresh = wxNewId();
const long udpPlotFrame::idMenuQuit = wxNewId();
const long udpPlotFrame::idMenuSocket = wxNewId();
const long udpPlotFrame::idMenuLoadDataFormat = wxNewId();
const long udpPlotFrame::idMenuAbout = wxNewId();
const long udpPlotFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(udpPlotFrame,wxFrame)
    //(*EventTable(udpPlotFrame)
    //*)
END_EVENT_TABLE()

udpPlotFrame::udpPlotFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(udpPlotFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, _("udpPlot"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(800,600));
    SetMinSize(wxSize(800,600));
    PlotsBoxSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(PlotsBoxSizer);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    StartStopCapture = new wxMenuItem(Menu1, idMenuStartStopCapture, _("Start Capture\tAlt-A"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(StartStopCapture);
    MenuRefresh = new wxMenuItem(Menu1, idMenuRefresh, _("Refresh\tAlt-R"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuRefresh);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu3, idMenuSocket, _("Port/IP\tAlt-P"), _("IP and port configuration"), wxITEM_NORMAL);
    Menu3->Append(MenuItem3);
    MenuItemLoadDataFormat = new wxMenuItem(Menu3, idMenuLoadDataFormat, _("Load data format file ...\tAlt-D"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItemLoadDataFormat);
    MenuBar1->Append(Menu3, _("&Configuration"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    SetSizer(PlotsBoxSizer);
    Layout();

    Connect(idMenuStartStopCapture,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&udpPlotFrame::OnStartStopCaptureSelected);
    Connect(idMenuRefresh,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&udpPlotFrame::OnMenuRefreshSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&udpPlotFrame::OnQuit);
    Connect(idMenuSocket,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&udpPlotFrame::OnConfig);
    Connect(idMenuLoadDataFormat,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&udpPlotFrame::OnMenuItemLoadDataFormatSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&udpPlotFrame::OnAbout);
    //*)
    postInit();
}

udpPlotFrame::~udpPlotFrame()
{
    //(*Destroy(udpPlotFrame)
    //*)
}

void udpPlotFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void udpPlotFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void udpPlotFrame::OnConfig(wxCommandEvent& event)
{
    ConfigDialog * dlg=new ConfigDialog(this, wxID_ANY);
    if(dlg->ShowModal()==wxID_OK)
    {
        std::cout<<"validated"<<std::endl;
        std::cout<<"Listen IP="<<dlg->IP_ctrl->GetValue()<<" ";
        std::cout<<"Port="<<dlg->PORT_ctrl->GetValue()<<std::endl;
    }
    std::cout<<"ended"<<std::endl;
    dlg->Destroy();
}

void udpPlotFrame::postInit()
{
    plotColours.push_back(wxBLUE);
    plotColours.push_back(wxRED);
    plotColours.push_back(wxGREEN);
}

void udpPlotFrame::OnStartStopCaptureSelected(wxCommandEvent& event)
{
    if(capturing==0)
    {
        printf("starting capture\n");
        //captureLoop();
        StartStopCapture->SetItemLabel("Stop capture\tAlt-A");
        capturing=1;
        std::thread * t =new std::thread(&udpPlotFrame::captureLoop, this);
        (void)t;
    }
    else
    {
        capturing=0;
        StartStopCapture->SetItemLabel("Start capture\tAlt-A");
    }

}

void udpPlotFrame::captureLoop()
{

    udpSocket = socket(AF_INET, SOCK_DGRAM, 0); //IPPROTO_UDP);
    sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY; // permet d'écouter sur toutes les interfaces locales
    addr.sin_port = htons(43210); // toujours penser à traduire le port en endianess réseau
    addr.sin_family = AF_INET; // notre adresse est IPv4
    int res = bind(udpSocket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    if(res!=0)
    {
     //   exit(-1); //TODO: error message
     wxMessageBox("Bind failed");
     return;
    }
    double buffer[2];
    //sockaddr_in from;
    //socklen_t fromlen = sizeof(from);
    printf("Waiting for data\n");
    //int ret = recvfrom(udpSocket, (char*)buffer,2*sizeof(float), 0, reinterpret_cast<sockaddr*>(&from), &fromlen);
    size_t nbBytes = mpFXYVectors.size()*sizeof(double);
    size_t nbCurves = mpFXYVectors.size();
    Vector_X.resize(0);
    for(size_t icurve=0;icurve<nbCurves;icurve++)
    {
        Vectors_Y[icurve].resize(0);
    }
    //for(size_t iPoint=0;iPoint<50; iPoint++)
    size_t iPoint=0;
    while(capturing==1)
    { //data collection
        int ret = recv(udpSocket, (char*)buffer, nbBytes, 0);//, reinterpret_cast<sockaddr*>(&from), &fromlen);
        if (ret <= 0)
            printf("error !!!\n");
        else
//        printf("%.3f %.3f %.3f\n", buffer[0], buffer[1], buffer[2]);
        {
            //printf("%.3f %.3f %.3f\n", buffer[0], buffer[1], buffer[2]);
            for(size_t icurve=0;icurve<nbCurves;icurve++)
            {
                Vectors_Y[icurve].push_back(buffer[icurve]);
            }
            Vector_X.push_back(iPoint);
/*            Vector1_X[i]=buffer[0];
            Vector1_Y[i]=buffer[1];
            Vector2_X[i]=buffer[0];
            Vector2_Y[i]=buffer[2];*/
            iPoint++;
        }
    }
    //graph update
    RefreshData();
    close(udpSocket);
}

void udpPlotFrame::RefreshData()
{
    size_t nbCurves = mpFXYVectors.size();
    for(size_t icurve=0;icurve<nbCurves;icurve++)
    {
        mpFXYVectors[icurve]->SetData(Vector_X, Vectors_Y[icurve]);
    }

    //Vector1->SetData(Vector1_X, Vector1_Y);
    //Vector2->SetData(Vector2_X, Vector2_Y);
    std::for_each(mpWindows.begin(), mpWindows.end(), [](udpPlotWindow* & mpw)
    //for(auto_ptr mpw = mpWindows.begin(); mpw!=mpWindows.end(); mpw++)
    {
        mpw->UpdateAll();
        mpw->Fit();
    });
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
         //TODO: parse error message
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
        wxPen   Vector1_PEN(*plotColours[i%3]);//alors la c'est plus complique parce qu'il faut les compter par graph
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

void udpPlotFrame::OnMenuRefreshSelected(wxCommandEvent& event)
{
    RefreshData();
}
