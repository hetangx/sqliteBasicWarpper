#pragma once
#ifndef DATASQLITE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"

/*������*/
void DbCreateTable(sqlite3* db, char* substationid);

/*���Ƿ����, ������վID�ͱ�ѹ��ID, ����int
1 - ����
0 - ������
-1 - ����*/
int DbRecordIfExist(sqlite3* db, char* substationid, char* transformerid);

/*����¼������, �����¼
DbInsertRecord(db, "2", "AQ", tableItems[2], 1.5);
char* tableItems[8] = {
"TRANSFORMERID","UB","THDUA","THDUB","THDUC","THDIA","THDIB","THDIC"
};
*/
void DbInsertRecord(sqlite3* db, char* substationid, char* transformerid, char* item, double valueToInsert);

/*����¼����, ���µ�������
DbUpdateRecord(db, "2", "A", "UB", 2.7);
*/
void DbUpdateRecord(sqlite3* db, char* substationid, char* transformerid, char* item, double valueToInsert);

/*�õ�ȫ��ֵ
 double result[8];
 DbGetAllData(db, "2", "A", result);
    SELECT * FROM SID2 WHERE TRANSFORMERID="B";
*/
void DbGetAllData(sqlite3* db, char* substationid, char* transformerid, double allData[]);

/*��ѯ���ݿ����Ƿ����ĳ�ű�dbΪָ��sqlite3��ָ��, substationidΪ���վID, ����int
1 - ����
0 - ������
-1 - �������д���*/
int DbIfExist(sqlite3* db, char* substationid);

/*OpenDB, �����ݿ�, �÷�:
    sqlite3* db;
    char* filename = "dbname.db";
    OpenDB(&db, filename);
* ������ӡ����Ļ��
*/
void DbOpen(sqlite3** db, char* filename);

/*��ʾ������������*/
void DbTables(sqlite3* db);








#endif // !DATASQLITE_H
