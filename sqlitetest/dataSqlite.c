#include "dataSqlite.h"

char* tableItems[8] = {
"TRANSFORMERID","UB","THDUA","THDUB","THDUC","THDIA","THDIB","THDIC"
};

/*sqlite DB�ص���������ʾ���صļ�ֵ��*/
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}
/*sqlite DB�ص�����������һ��ָ��, ָ��double���飬���ڱ��淵��ֵ*/
int callbackGetData(void* dataArray, int argc, char** argv, char** azColName) {
    int i;
    double* result = dataArray;
    for (i = 0; i < argc; i++) {
        if (argv[i])
        {
            *result = (double)atof(argv[i]);
        }
        else
        {
            *result = 0;
        }
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        result++;
    }
    printf("\n");
    return 0;
}

/*sqlite DB�ص���������ӡ���б������*/
int callbackShowAllTable(void* outMessage, int argc, char** argv, char** ColName) {
    // 1. ��ʾ����
    if (argc == 1)
    {
        printf("%s\n", argv[0]);
    }
    else
    {
        printf("SELECT tables name wrong, find code error\n");
        return -1;
    }
    return 0;
}

/*sqlite DB�ص�����������int ������Ϊ����ֵ��
1 - ����
0 - ������*/
int callbackIfTableExist(void* outMessage, int argc, char** argv, char** ColName)
{
    *(int*)outMessage = (int)atoi(argv[0]);
    return 0;
}

/*OpenDB, �����ݿ�, �÷�:
    sqlite3* db;
    char* filename = "dbname.db";
    OpenDB(&db, filename);
* ������ӡ����Ļ��
*/
void DbOpen(sqlite3** db, char* filename)
{
    int rc;
    rc = sqlite3_open(filename, db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
        exit(0);
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }
}

/*��ʾ������������*/
void DbTables(sqlite3* db)
{
    int rc;
    char* zErrMsg = 0;
    char* sqlAllTableName = " SELECT name FROM sqlite_master WHERE type='table' ORDER BY name;";

    rc = sqlite3_exec(db, sqlAllTableName, callbackShowAllTable, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Table showed successfully\n");
    }
}

/*��ѯ���ݿ����Ƿ����ĳ�ű�dbΪָ��sqlite3��ָ��, substationidΪ���վID, ����int
1 - ����
0 - ������
-1 - �������д���*/
int DbIfExist(sqlite3* db, char* substationid)
{
    int rc;
    char* zErrMsg = 0;
    char sqlIfExist[1024];
    sprintf_s(sqlIfExist, 1024, "select count(*) as c from sqlite_master where type ='table' and name ='SID%s'; ", substationid);

    int ifExist = -1;
    rc = sqlite3_exec(db, sqlIfExist, callbackIfTableExist, &ifExist, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    if (ifExist == 1)
    {
        printf("Table %s exist\n", substationid);
        // ������
    }
    else
    {
        printf("table %s null\n", substationid);
        // ������
    }
    return ifExist;
}

/*������*/
void DbCreateTable(sqlite3* db, char* substationid)
{
    int rc;
    char* zErrMsg = 0;

    char sqlCreateTable[1024];
    sprintf_s(sqlCreateTable, 1024, "CREATE TABLE SID%s(TRANSFORMERID TEXT PRIMARY KEY NOT NULL,UB REAL,THDUA REAL,THDUB REAL,THDUC REAL,THDIA REAL,THDIB REAL,THDIC REAL);", substationid);
    rc = sqlite3_exec(db, sqlCreateTable, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Table created successfully\n");
    }
}

/*���Ƿ����, ������վID�ͱ�ѹ��ID, ����int
1 - ����
0 - ������
-1 - ����*/
int DbRecordIfExist(sqlite3* db, char* substationid, char* transformerid)
{
    int rc;
    char* zErrMsg = 0;
    char sqlRecordIfExist[1024];
    sprintf_s(sqlRecordIfExist, 1024, "select count(*) from SID%s where TRANSFORMERID='%s';", substationid, transformerid);

    int ifTableExist = -1;
    rc = sqlite3_exec(db, sqlRecordIfExist, callbackIfTableExist, &ifTableExist, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    if (ifTableExist == 1)
    {
        printf("Record %s exist\n", transformerid);
    }
    else
    {
        printf("table %s null\n", transformerid);
    }
    return ifTableExist;
}

// һ���¼�������


/*����¼������, �����¼
DbInsertRecord(db, "2", "AQ", tableItems[2], 1.5);
char* tableItems[8] = {
"TRANSFORMERID","UB","THDUA","THDUB","THDUC","THDIA","THDIB","THDIC"
};
*/
void DbInsertRecord(sqlite3* db, char* substationid, char* transformerid, char* item, double valueToInsert)
{

    int rc;
    char* zErrMsg = 0;

    char sqlInsertRecord[1024];
    sprintf_s(sqlInsertRecord, 1024, "INSERT INTO SID%s(TRANSFORMERID,%s) VALUES (\"%s\", %.4f);", substationid, item, transformerid, valueToInsert);
    rc = sqlite3_exec(db, sqlInsertRecord, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Insert record successfully\n");
    }
}

/*����¼����, ���µ�������
DbUpdateRecord(db, "2", "A", "UB", 2.7);
*/
void DbUpdateRecord(sqlite3* db, char* substationid, char* transformerid, char* item, double valueToInsert)
{
    int rc;
    char* zErrMsg = 0;
    char sqlUpdateRecord[1024];

    // UPDATE SID2 SET THDUA=2.5 WHERE TRANSFORMERID="B";
    sprintf_s(sqlUpdateRecord, 1024, "UPDATE SID%s SET %s=%.4f WHERE TRANSFORMERID=\"%s\";", substationid, item, valueToInsert, transformerid);
    rc = sqlite3_exec(db, sqlUpdateRecord, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Update record successfully\n");
    }
}

/*�õ�ȫ��ֵ
 double result[8];
 DbGetAllData(db, "2", "A", result);
    SELECT * FROM SID2 WHERE TRANSFORMERID="B";
*/
void DbGetAllData(sqlite3* db, char* substationid, char* transformerid, double allData[])
{
    int rc;
    char* zErrMsg = 0;
    char sqlGetAllData[1024];

    sprintf_s(sqlGetAllData, 1024, "SELECT * FROM SID%s WHERE TRANSFORMERID=\"%s\";", substationid, transformerid);
    rc = sqlite3_exec(db, sqlGetAllData, callbackGetData, (void*)allData, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Insert single record successfully\n");
    }
}