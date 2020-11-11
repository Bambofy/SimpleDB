#include <sqlite3.h>

#include <thread>
#include <string>
#include <queue>
#include <string>
#include <exception>
#include <iostream>

using namespace std;

#include "SimpleDB++/All.h"

void CreateTable(sdb::Database& db) {
	sdb::Query query("CREATE TABLE USERS(Name TEXT, Level INTEGER)");

	query.Execute(db, [](sdb::Row row) {});
}

void Insert(sdb::Database& db) {
	sdb::Query query("INSERT INTO USERS VALasdaUES ('test', 1);");

	query.Execute(db, [](sdb::Row row){});
}

void Select(sdb::Database& db) {
	sdb::Query query("SELECT * FROM USERS;");

	query.Execute(db, [](sdb::Row row) {
		const vector<const sdb::Column> columns = row.Columns();
		for (const sdb::Column & column : columns) {
			const string & columnName = column.Name();
			const char * data = column.Data();
			cout << columnName << " = " << data << endl;
		}
	});
}

int main() {

	sdb::Database db("./testdb.db");
	CreateTable(db);
	Insert(db);
	Select(db);
	return 0;
}
