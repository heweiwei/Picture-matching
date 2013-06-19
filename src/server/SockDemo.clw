; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSockThd
LastTemplate=CWinThread
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SockDemo.h"

ClassCount=5
Class1=CSockDemoApp
Class2=CSockDemoDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CSockThd
Resource3=IDD_SOCKDEMO_DIALOG

[CLS:CSockDemoApp]
Type=0
HeaderFile=SockDemo.h
ImplementationFile=SockDemo.cpp
Filter=N

[CLS:CSockDemoDlg]
Type=0
HeaderFile=SockDemoDlg.h
ImplementationFile=SockDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=SockDemoDlg.h
ImplementationFile=SockDemoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SOCKDEMO_DIALOG]
Type=1
Class=CSockDemoDlg
ControlCount=1
Control1=IDC_BTN_START_SRV,button,1342242816

[CLS:CSockThd]
Type=0
HeaderFile=SockThd.h
ImplementationFile=SockThd.cpp
BaseClass=CWinThread
Filter=N
VirtualFilter=TC

