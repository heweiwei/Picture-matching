#ifndef _JADO_H_
#define _JADO_H_
#include <afx.h>

#pragma warning(disable: 4146)

#ifndef ADO_IMPORT_DEFINE
#define ADO_IMPORT_DEFINE
#import "msado15.dll" no_namespace rename("EOF","rsEOF")
#endif

typedef _ConnectionPtr CONNECTION;
typedef _RecordsetPtr RECORDSET;
typedef SYSTEMTIME DBDATETIME;

#define GTF(x,y) JAdo::GetTextFiledVal(x,y)
#define GIF(x,y) JAdo::GetIntegerFiledVal(x,y)
#define GDF(x,y) JAdo::GetDoubleFieldVal(x,y)
#define GDTF(x,y) JAdo::GetDateTimeFieldVal(x,y)
#define DTV(x) JAdo::GetDateTimeText(x)

class JAdo  
{
public:
	JAdo();
	virtual ~JAdo();

public:
	static double GetDoubleFieldVal(RECORDSET rs,CString fieldName);
	static int GetIntegerFiledVal(RECORDSET rs,CString fieldName);
	static CString GetTextFiledVal(RECORDSET rs,CString fieldName);
	static DBDATETIME GetDateTimeFieldVal(RECORDSET rs,CString fieldName);
	static CString GetDateTimeText(DBDATETIME dt);

	HRESULT Connect(CString str);
	HRESULT Connect(int dbtype,CString server,CString db,CString user,CString pass,CString port);
	HRESULT Close();

	HRESULT BeginTrans();
	HRESULT CommitTrans();
	HRESULT RollbackTrans();

	RECORDSET JExecuteWithRecordset(CString sql, long option=adCmdUnknown);
	LONG JExecuteWithoutRecordset(CString sql, long option=adCmdUnknown);
private:
	CONNECTION m_ado;
	bool m_isConnected;
	void Release();
	inline void TEST(HRESULT x) {if FAILED(x) _com_issue_error(x);}
	inline void ReportComErr(_com_error& e,CString sql)
	{
		char msg[256]={0};
		char comerrno[12]={0};
		sprintf(comerrno,"%d",e.Error());
		CString desc = e.Description().operator char*();
	}

	inline static void TRIM(CString& str)
	{
		CString tmp = str;
		tmp.TrimLeft();
		tmp.TrimRight();
		str = tmp;
	}
};

#endif /* _JADO_H_ */