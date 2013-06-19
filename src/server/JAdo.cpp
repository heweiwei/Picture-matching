#include "JAdo.h"

JAdo::JAdo()
{
	::CoInitialize(NULL);
	m_isConnected = false;
	TEST(m_ado.CreateInstance(__uuidof(Connection)));
	m_ado->ConnectionTimeout = 5;
}

JAdo::~JAdo()
{
	Release();
	::CoUninitialize();
}

HRESULT JAdo::Connect(CString str)
{
	Close();
	HRESULT hr = 0;
	_bstr_t b(str);
	if (!m_isConnected)
	{
		try
		{
			hr = m_ado->Open(b,"","",adModeUnknown);
			if (SUCCEEDED(hr))
			{
				m_isConnected = true;
				m_ado->CommandTimeout = 60;
			}
			else
				m_isConnected = false;
		}
		catch (_com_error& e)
		{
			ReportComErr(e, "Connect Failed");
			hr = -1;
			m_isConnected = false;
		}
		catch (...)
		{
			hr = -1;
			m_isConnected = false;
		}
	}
	
	return hr;

}

HRESULT JAdo::Connect(int dbtype,CString server,CString db,CString user,CString pass,CString port)
{
	CString tmp = "";
	switch (dbtype)
	{
	case 0://如果是SQL SERVER服务器
		tmp = "Provider=SQLOLEDB.1;User ID=";
		tmp += user;
		tmp += ";PassWord=";
		tmp += pass;
		tmp += ";Initial Catalog=";
		tmp += db;
		tmp += ";Data Source=";
		tmp += server;
		tmp += ";";
		break;
	case 1://如果是ACCESS数据库
		tmp = "Provider=Microsoft.Jet.OLEDB.4.0;Password=";
		tmp += pass;
		tmp += ";User ID=";
		tmp += user;
		tmp += ";Data Source=";
		tmp += server;
		tmp += ";Persist Security Info=True";
		break;
	case 3://如果是IBM DB2 V8.1
		tmp = "Provider=IBMDADB2.1;Password=";
		tmp += pass;
		tmp += ";User ID=";
		tmp += user;
		tmp += ";Data Source=";
		tmp += db;
		tmp += ";Location=";
		tmp += server;
		tmp += ";Persist Security Info=True";
		break;
	case 4://如果是SYBASE 12.5
		   tmp = "Provider=Sybase.ASEOLEDBProvider.2;Password=@Password;\
				User ID=@UserID;Initial Catalog=@DBName;Server Name=@ServerName;\
				Server Port Address=@ServerPort;Persist Security Info=True;Select Method=Cursor";
		   tmp.Replace("@Password",pass);
		   tmp.Replace("@UserID",user);
		   tmp.Replace("@DBName",db);
		   tmp.Replace("@ServerName",server);
		   tmp.Replace("@ServerPort",port);
		   break;
	default:
		break;
	}
	return Connect(tmp);
}

HRESULT JAdo::Close()
{
	HRESULT hr = 0;
	try
	{
		hr = m_ado->Close();
		m_isConnected = false;
	}
	catch (_com_error& e)
	{
		ReportComErr(e, "Close Failed");
	}

	return hr;
}

HRESULT JAdo::BeginTrans()
{
	HRESULT hr = -1;
	if (m_isConnected)
		hr = m_ado->BeginTrans();
	
	return hr;
}

HRESULT JAdo::CommitTrans()
{
	HRESULT hr = -1;
	if (m_isConnected)
		hr = m_ado->CommitTrans();
	
	return hr;
}

HRESULT JAdo::RollbackTrans()
{
	HRESULT hr = -1;
	if (m_isConnected)
		hr = m_ado->RollbackTrans();
	
	return hr;
}

RECORDSET JAdo::JExecuteWithRecordset(CString sql, long option/* =adCmdUnknown */)
{
	RECORDSET rs = NULL;
	try
	{
		if (!m_isConnected)
			return NULL;
	//	TEST(rs.CreateInstance(__uuidof(Recordset)));
		//rs->PutCursorLocation(adUseClient);
		VARIANT var;
		var.vt = VT_I4;
		_bstr_t bsql(sql);
		rs = m_ado->Execute(bsql,&var,option);
	}
	catch (_com_error& e)
	{
		ReportComErr(e,sql);
		HRESULT hr = e.Error();
		if (hr == adErrObjectNotSet)
			m_isConnected = false;
		return NULL;
	}
	
	return rs;
}

LONG JAdo::JExecuteWithoutRecordset(CString sql, long option/* =adCmdUnknown */)
{
	try
	{
		if (!m_isConnected)
			return 0;
		VARIANT var;
		var.vt = VT_I4;
		_bstr_t bsql(sql);
		m_ado->Execute(bsql,&var,option);
		LONG ret = var.lVal;
		return ret;
	}
	catch (_com_error& e)
	{
		ReportComErr(e,sql);
		HRESULT hr = e.Error();
		if (hr == adErrObjectNotSet)
			m_isConnected = false;
		return -1;
	}
	
	return 0;
}

void JAdo::Release()
{
	
	if (m_ado != NULL)
	{
		if (m_isConnected)
		{
			Close();
		}
		m_ado.Release();
		m_ado = NULL;
	}
}

CString JAdo::GetTextFiledVal(RECORDSET rs, CString fieldName)
{
	_variant_t v;
	v = rs->GetFields()->GetItem((LPCTSTR)fieldName)->GetValue();
	CString tmp = "";
	if (v.vt == VT_BSTR)
	{
		tmp = (char*)v.operator _bstr_t().operator char*();
		TRIM(tmp);
	}
	
	return tmp;
}

int JAdo::GetIntegerFiledVal(RECORDSET rs, CString fieldName)
{
	_variant_t v;
	v = rs->GetFields()->GetItem((LPCTSTR)fieldName)->GetValue();
	int ret = 0;
	
	switch (v.vt)
	{
	case VT_I2:{ret = v.iVal;break;}
	case VT_I4:{ret = v.lVal;break;}
	case VT_INT:{ret = v.intVal;break;}
	case VT_UINT:{ret = v.uintVal;break;}
	case VT_UI2:{ret = v.uiVal;break;}
	case VT_UI4:{ret = v.ulVal;break;}
	default:break;
	}
	
	return ret;
}

double JAdo::GetDoubleFieldVal(RECORDSET rs, CString fieldName)
{
	_variant_t v;
	double ret = 0;
	v = rs->GetFields()->GetItem((LPCTSTR)fieldName)->GetValue();
	switch (v.vt)
	{
	case VT_R4:{ret = v.fltVal;break;}
	case VT_R8:{ret = v.dblVal;break;}
	case VT_DECIMAL:{VarR8FromDec(&v.decVal, &ret);break;}
	default:break;
	}
	
	return ret;
}

DBDATETIME JAdo::GetDateTimeFieldVal(RECORDSET rs, CString fieldName)
{
	_variant_t v;
	DBDATETIME ret;
	memset(&ret, 0, sizeof(ret));
	v = rs->GetFields()->GetItem((LPCTSTR)fieldName)->GetValue();
	switch (v.vt)
	{
	case VT_DATE:{VariantTimeToSystemTime(v.date,&ret);break;}
	default:break;
	}
	
	return ret;
}

CString JAdo::GetDateTimeText(DBDATETIME dt)
{
	CString tmp = "";
	char buf[64] = {0};
	sprintf(buf,"%04d-%02d-%02d %02d:%02d:%02d",dt.wYear,dt.wMonth,dt.wDay,dt.wHour,dt.wMinute,dt.wSecond);
	tmp = buf;
	return tmp;
}