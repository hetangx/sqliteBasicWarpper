#pragma once
#ifndef DATASQLITE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"

/*创建表*/
void DbCreateTable(sqlite3* db, char* substationid);

/*项是否存在, 传入变电站ID和变压器ID, 返回int
1 - 存在
0 - 不存在
-1 - 出错*/
int DbRecordIfExist(sqlite3* db, char* substationid, char* transformerid);

/*若记录不存在, 插入记录
DbInsertRecord(db, "2", "AQ", tableItems[2], 1.5);
char* tableItems[8] = {
"TRANSFORMERID","UB","THDUA","THDUB","THDUC","THDIA","THDIB","THDIC"
};
*/
void DbInsertRecord(sqlite3* db, char* substationid, char* transformerid, char* item, double valueToInsert);

/*若记录存在, 更新单个数据
DbUpdateRecord(db, "2", "A", "UB", 2.7);
*/
void DbUpdateRecord(sqlite3* db, char* substationid, char* transformerid, char* item, double valueToInsert);

/*得到全部值
 double result[8];
 DbGetAllData(db, "2", "A", result);
    SELECT * FROM SID2 WHERE TRANSFORMERID="B";
*/
void DbGetAllData(sqlite3* db, char* substationid, char* transformerid, double allData[]);

/*查询数据库中是否存在某张表，db为指向sqlite3的指针, substationid为变电站ID, 返回int
1 - 存在
0 - 不存在
-1 - 程序运行错误*/
int DbIfExist(sqlite3* db, char* substationid);

/*OpenDB, 打开数据库, 用法:
    sqlite3* db;
    char* filename = "dbname.db";
    OpenDB(&db, filename);
* 结果会打印在屏幕中
*/
void DbOpen(sqlite3** db, char* filename);

/*显示表中所有名字*/
void DbTables(sqlite3* db);








#endif // !DATASQLITE_H
