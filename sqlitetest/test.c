#include "dataSqlite.h"

extern char* tableItems[];
int main(int argc, char* argv[])
{
    sqlite3* db;

    /*�����ݿ�*/
    DbOpen(&db, "sub-tran.db");

    /*��ʾ���ݿ������б�����*/
    DbTables(db);

    /*��ѯ���ݿ����Ƿ����ĳ�ű�*/
    int a = DbIfExist(db, "2");

    /*������*/
    DbCreateTable(db, "13");

    /*���Ƿ����*/
    a = DbRecordIfExist(db, "2", "A");

    /*����¼������, �����¼*/
    DbInsertRecord(db, "2", "AQ", tableItems[2], 1.5);


    /*����¼����, ���뵥������*/
    DbUpdateRecord(db, "2", "A", tableItems[1], 2.7);
   
    /*�õ�ȫ��ֵ*/
    double result[8];
    DbGetAllData(db, "2", "A", result);

    /*�ر�*/
    if (db)
    sqlite3_close(db);
    return 0;
}