/*int callback(void *data, int argc, char **argv, char **azColName){
    for(int i = 0; i < argc;i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

void Connect_to_DB(){
    sqlite3 *db;
    char *errMsg = 0;
    int rc = sqlite3_open("test.db", &db);

    const char *sql = "CREATE TABLE IF NOT EXISTS client(IP TEXT);";
    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK){
        sqlite3_free(errMsg);
    }
    sqlite3_close(db);

}

*/
