#include "pch.h"
#include "DBManager.h"
#include "ExpOver.h"
#include "Global.h"

DBManager::DBManager()
{
    SQLRETURN retcode;

    // 환경 핸들 할당
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_henv);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
    {
        // 버전 맞추기
        retcode = SQLSetEnvAttr(_henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            // 연결 핸들 할당
            retcode = SQLAllocHandle(SQL_HANDLE_DBC, _henv, &_hdbc);

            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
            {
                SQLSetConnectAttr(_hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

                // DB 연결
                retcode = SQLConnectW(_hdbc, (SQLWCHAR*)L"B1A2", SQL_NTS, (SQLWCHAR*)NULL, 0, (SQLWCHAR*)NULL, 0);

                if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
                {
                    // 명령 핸들 할당
                    retcode = SQLAllocHandle(SQL_HANDLE_STMT, _hdbc, &_hstmt);

                    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
                        std::cout << "DataBase Connected\n";
                }
            }
        }
    }
}

DBManager::~DBManager()
{
    SQLFreeHandle(SQL_HANDLE_STMT, _hstmt);
    SQLDisconnect(_hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC, _hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, _henv);
}

void DBManager::Update()
{
    _mutex.lock();
    if (!_workList.empty())
    {
		DBWork work = _workList.front();
        _workList.pop_front();
        _mutex.unlock();

        switch (work.type)
        {
        case DBType::ExistID:
            ProcessExistID(work);
            break;
		}

        return;
    }
    _mutex.unlock();
}

void DBManager::AddWork(DBWork work)
{
    _mutex.lock();
    _workList.push_back(work);
    _mutex.unlock();
}

void DBManager::ProcessExistID(DBWork work)
{
    SQLRETURN retcode;

    wchar_t szSql[256];
    swprintf_s(szSql, L"{CALL ExistID('%s')}", work.loginID.data());
    retcode = SQLExecDirect(_hstmt, (SQLWCHAR*)szSql, SQL_NTS);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
    {
        wchar_t id[20];
        SQLLEN idLen = 0;

        SQLBindCol(_hstmt, 1, SQL_C_WCHAR, id, sizeof(id), &idLen);

        ExpOver* over = new ExpOver(IOType::DB);
        over->_dbType = DBType::ExistID;

        if (SQLFetch(_hstmt) == SQL_SUCCESS)
            over->_dbResult = true;
        else
            over->_dbResult = false;

        PostQueuedCompletionStatus(g_network->GetIOCP(), 0, static_cast<ULONG_PTR>(work.id), &over->_over);
    }

    SQLFreeStmt(_hstmt, SQL_CLOSE);
    SQLFreeStmt(_hstmt, SQL_UNBIND);
}