#include "pch.h"
#include "DBManager.h"
#include <sqlext.h> 

DBManager::DBManager()
{
    SQLHENV henv{};
    SQLHDBC hdbc{};
    SQLHSTMT hstmt{};
    SQLRETURN retcode{};

    // 환경 핸들 할당
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
    {
        // 버전 맞추기
        retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            // 연결 핸들 할당
            retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);

            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
            {
                SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

                // DB 연결
                retcode = SQLConnectW(hdbc, (SQLWCHAR*)L"B1A2", SQL_NTS, (SQLWCHAR*)NULL, 0, (SQLWCHAR*)NULL, 0);

                // 명령 핸들 할당
                if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
                {
                    std::cout << "DataBase Connected\n";
                }
            }
        }
    }

    SQLDisconnect(hdbc);                
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);
}

DBManager::~DBManager()
{
}

void DBManager::Update()
{

}