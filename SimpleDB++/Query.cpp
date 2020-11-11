//
// MIT LICENSE
//
// Copyright (c) 2020 R.G.Bamford
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "Query.h"

sdb::Query::Query(string value)
	: value(value) {

}

void sdb::Query::Execute(sdb::Database & target, function<void(sdb::Row)> success) {
	target.Open();

	sqlite3 * db = target.Sqlite3();

	char * errMsg = nullptr;
	sqlite3_exec(db, value.c_str(), [](void * userData, int colCount, char ** rowData, char ** colNames) {
		assert(userData != nullptr);

		vector<const sdb::Column> columns;
		for (int i = 0; i < colCount; i++) {
			char * columnName = colNames[i];
			char * data = rowData[i];
			columns.push_back(Column(columnName, data));
		}

		sdb::Row row(columns);

		function<void(sdb::Row)>* callback = (function<void(sdb::Row)>*)userData;
		assert(callback != nullptr);

		(*callback)(row);

		return 0;
	}, &success, &errMsg);

	target.Close();
}

