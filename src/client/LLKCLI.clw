; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLLKBgReady
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "LLKCLI.h"

ClassCount=9
Class1=CLLKCLIApp
Class2=CLLKCLIDlg
Class3=CAboutDlg

ResourceCount=9
Resource1=IDD_CHANGEPWD
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CLLKGame
Resource4=IDD_LLKCLI_LOGIN
Class5=CLLKHome
Resource5=IDD_GAMEHOME
Class6=CLLKBgReady
Resource6=IDD_ADDUSER
Class7=CLLKReg
Resource7=IDD_READYBG
Class8=CLLKChangePwd
Resource8=IDD_LLK_GAME
Class9=Scorelist
Resource9=IDD_SCORE_LIST

[CLS:CLLKCLIApp]
Type=0
HeaderFile=LLKCLI.h
ImplementationFile=LLKCLI.cpp
Filter=N
LastObject=CLLKCLIApp

[CLS:CLLKCLIDlg]
Type=0
HeaderFile=LLKCLIDlg.h
ImplementationFile=LLKCLIDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CLLKCLIDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=LLKCLIDlg.h
ImplementationFile=LLKCLIDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_LLK_GAME]
Type=1
Class=CLLKGame
ControlCount=1
Control1=IDC_NUMBER,edit,1476466817

[CLS:CLLKGame]
Type=0
HeaderFile=LLKGame.h
ImplementationFile=LLKGame.cpp
BaseClass=CDialog
Filter=D
LastObject=CLLKGame
VirtualFilter=dWC

[DLG:IDD_GAMEHOME]
Type=1
Class=CLLKHome
ControlCount=0

[CLS:CLLKHome]
Type=0
HeaderFile=LLKHome.h
ImplementationFile=LLKHome.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_READYBG]
Type=1
Class=CLLKBgReady
ControlCount=5
Control1=IDC_START,button,1342242827
Control2=IDC_TEST,button,1342242827
Control3=IDC_CANCEL,button,1073807371
Control4=IDC_EDIT_OUT,edit,1478557764
Control5=IDC_EDIT_ENTER,edit,1350631552

[CLS:CLLKBgReady]
Type=0
HeaderFile=LLKBgReady.h
ImplementationFile=LLKBgReady.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_OUT

[DLG:IDD_LLKCLI_LOGIN]
Type=1
Class=CLLKCLIDlg
ControlCount=8
Control1=IDC_BTN_TEST,button,1342275595
Control2=IDC_OUT,button,1342275595
Control3=IDC_USER,edit,1350639744
Control4=IDC_PWD,edit,1350631584
Control5=IDC_ChangePwd,button,1342275595
Control6=IDC_EXPAND,button,1342275595
Control7=IDC_STATIC,static,1342177294
Control8=IDC_GIF_ANIMATION,static,1342308352

[DLG:IDD_ADDUSER]
Type=1
Class=CLLKReg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NAME,static,1342308352
Control4=IDC_EDIT_NAME,edit,1350631552
Control5=IDC_PWD,static,1342308352
Control6=IDC_EDIT_PWD,edit,1350631584
Control7=IDC_SEX,static,1342308352
Control8=IDC_RADIO_MALE,button,1342308361
Control9=IDC_RADIO_FEMALE,button,1342177289
Control10=IDC_EDIT_REPWD,edit,1350631584
Control11=IDC_PWD2,static,1342308352

[CLS:CLLKReg]
Type=0
HeaderFile=LLKReg.h
ImplementationFile=LLKReg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_NAME

[DLG:IDD_CHANGEPWD]
Type=1
Class=CLLKChangePwd
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_PWDOLD,static,1342308352
Control4=IDC_PWDNEW,static,1342308352
Control5=IDC_PWDTWICE,static,1342308352
Control6=IDC_EDIT_PWD,edit,1350631584
Control7=IDC_EDIT_REPWD,edit,1350631584
Control8=IDC_EDIT_REPWD2,edit,1350631584
Control9=IDC_NAME,static,1342308352
Control10=IDC_EDIT_USER,edit,1350631552

[CLS:CLLKChangePwd]
Type=0
HeaderFile=LLKChangePwd.h
ImplementationFile=LLKChangePwd.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_SCORE_LIST]
Type=1
Class=Scorelist
ControlCount=1
Control1=IDC_CANCEL,button,1342242827

[CLS:Scorelist]
Type=0
HeaderFile=Scorelist.h
ImplementationFile=Scorelist.cpp
BaseClass=CDialog
Filter=D
LastObject=Scorelist
VirtualFilter=dWC

