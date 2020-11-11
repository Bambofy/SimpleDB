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

#include "Database.h"

sdb::Database::Database(string filepath) : filepath(filepath) {
}

void sdb::Database::Open() {
	assert(!open);
	int rc = sqlite3_open(filepath.c_str(), &db);
	if (rc) {
		sqlite3_close(db);
		throw CouldNotOpenDatabase();
	}
	open = true;
	assert(open);
}

void sdb::Database::Close() {
	assert(open);
	sqlite3_close(db);
	open = false;
	assert(!open);
}

sqlite3 * sdb::Database::Sqlite3() const {
	assert(open);
	return db;
}
