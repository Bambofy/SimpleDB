#include <sqlite3.h>

#include <thread>
#include <string>
#include <queue>
#include <string>
#include <exception>
#include <iostream>

using namespace std;

#include "SimpleDB++/All.h"

int main() {

	sdb::Database db("./testdb.db");
	sdb::Query query("SELECT * FROM USERS;");

	query.Execute(db, [](sdb::Row row) {
		const vector<const sdb::Column> columns = row.Columns();
		for (const sdb::Column& column : columns) {
			const string& columnName = column.Name();
			const char * data = column.Data();
			cout << columnName << " = " << data << endl;
		}
	});

	return 0;
}
