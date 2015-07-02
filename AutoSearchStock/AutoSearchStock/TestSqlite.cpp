#include "sqlite3.h"


static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for( i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
};


void TestSqlite3()
{
	sqlite3 *pSQLite3 = NULL;
    char    *szErrMsg = NULL;

	int rst = sqlite3_open("d:/test.db", &pSQLite3);

	if ( rst )
    {
        printf( "Can't open database: %s\n", sqlite3_errmsg( pSQLite3 ));

        sqlite3_close( pSQLite3 );
        pSQLite3 = NULL;
    }
    else
    {
        printf("Database opened!!\n");

		printf("Create\n");
        // 테이블생성
        rst = sqlite3_exec(pSQLite3, 
            "CREATE TABLE member ( name TEXT(20), age INTEGER )",
            callback, 0, &szErrMsg);

		printf("Insert\n");
        // 데이터삽입
        rst = sqlite3_exec(pSQLite3, 
            "INSERT INTO member ( name, age ) values ( 'andy', 20 )", 
            callback, 0, &szErrMsg);

		printf("Selete\n");
        // 데이터질의
        rst = sqlite3_exec(pSQLite3, 
            "SELECT * FROM member", 
            callback, 0, &szErrMsg);


		printf("Done\n");
    }

    //객체해제
    sqlite3_free( szErrMsg );
    sqlite3_close( pSQLite3 );
}