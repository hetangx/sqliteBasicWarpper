#include "dataSqlite.h"

extern char* tableItems[];
int main(int argc, char* argv[])
{
    sqlite3* db;

    /*打开数据库*/
    DbOpen(&db, "sub-tran.db");

    /*显示数据库中所有表名字*/
    DbTables(db);

    /*查询数据库中是否存在某张表*/
    int a = DbIfExist(db, "2");

    /*创建表*/
    DbCreateTable(db, "13");

    /*项是否存在*/
    a = DbRecordIfExist(db, "2", "A");

    /*若记录不存在, 插入记录*/
    DbInsertRecord(db, "2", "AQ", tableItems[2], 1.5);


    /*若记录存在, 插入单个数据*/
    DbUpdateRecord(db, "2", "A", tableItems[1], 2.7);
   
    /*得到全部值*/
    double result[8];
    DbGetAllData(db, "2", "A", result);

    /*关闭*/
    if (db)
    sqlite3_close(db);
    return 0;
}