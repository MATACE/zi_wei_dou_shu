/** 
 * @file sqlite3_api.cpp
 * @author HXQ(huangxinquan@matace.cn)
 * @brief
 * @version 1.0
 * @date 2020-9-2
 * 
 * @copyright
 * Copyright (c) 2019-2020, the copyright holders HXQ(huangxinquan@matace.cn)
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided that
 * the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 * 
 * Neither the name of the copyright holders HXQ(huangxinquan@matace.cn) nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS
 * LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */ 

#include "sqlite3_api.h"

static int callback(void* data, int columen_count, char** column_value, char** column_name)
{
    for (int i = 0; i < columen_count; ++i) {
        LOG(INFO) << column_name[i] << " = " << (column_value[i] ? column_value[i] : "NULL");
    }
    LOG(INFO) << "";
}

Sqlite3Api::Sqlite3Api()
{ 
    db_handle_ = nullptr;
}

/**
 * @brief Open the sqlite3 database for get database handle.
 * 
 * @param db_path 
 * @return int 
 */
bool Sqlite3Api::OpenDB(string db_path)
{
    LOG(INFO) << db_path;
    if (db_handle_ != nullptr) {
        LOG(ERROR) << "SQL: Database path not free.";
        return false;
    }

    int ret = 0;
    ret = sqlite3_open(db_path.c_str(), &db_handle_);
    if (ret) {
        LOG(ERROR) << "SQL: sqlite3_open " << db_path << " failed, error msg: " << sqlite3_errmsg(db_handle_);
        return false;
    } else {
        DEBUG_INFO("Open database: " << db_path << " successful");
        return true;
    }
}

/**
 * @brief Close the database.
 * 
 * @param db_handle 
 * @return true 
 * @return false 
 */
bool Sqlite3Api::CloseDB()
{
    if (db_handle_ == nullptr) {
        LOG(ERROR) << "The database not open.";
        return false;
    }

    sqlite3_close(db_handle_);
    db_handle_ = nullptr;
    return true;
}

bool Sqlite3Api::NormaSqlExe(string sql_cmd)
{   
    if (db_handle_ == nullptr) {
        LOG(ERROR) << "Data base is null";
        return false;
    }
    
    char *z_err_msg = nullptr;
    int ret = 0;
    
    sqlite3_exec(db_handle_, sql_cmd.c_str(), callback, NULL, &z_err_msg);
    if (ret != SQLITE_OK) {
        LOG(ERROR) << "SQL: sqlite3 exe failed." << z_err_msg;
        sqlite3_free(z_err_msg);
        return false;
    } else {
        DEBUG_INFO("SQL: exe " << sql_cmd << "successful");
        return true;
    }
}

bool Sqlite3Api::QuickSqlExeExample()
{
    if (db_handle_ == nullptr) {
        LOG(ERROR) << "Data base is null";
        return false;
    }
    
    int ret = 0;

    // The life cycle of a statement object goes through the following process:
    // 1.Create this object using: sqlite3_prepare_v2()

    // 2.Bind a value to the host parameters: sqlite3_bind_*()
    // sqlite3 offer ? to be the not be sure value
    // sql msg: insert into table values(?,?,?)
    // first ?: sqlite3_bind_int(stmt, 1, value)
    // second ?: sqlite3_bind_double(stmt, 2, value)
    // three ?: sqlite3_bind_text(stmt, 3, value)

    // 3.This sql is executed one or more times by calling sqlite3_step()

    // 4.Reset the statement using sqlite3reset() and then go back to Step 2. Do this 0 or more times

    // NOTE: The 3 step and 4 step can exchange, please read as flower example.

    // 5.Destroy this object using SQlite3_finalize()

    // The operation reason please visit https://www.cnblogs.com/rainbowzc/p/6444389.html.
    
    // Begin use business
    sqlite3_exec(db_handle_, "begin;", NULL, NULL, NULL);
    // Set write synchronous mode: FULL | NORMA | OFF
    sqlite3_exec(db_handle_, "PRAGMA synchronous = OFF; ", NULL, NULL, NULL);
    // Create execute peraper
    sqlite3_stmt *stmt;
    string sql_msg = "insert into table values(?, ?, ?, ?)";  
    sqlite3_prepare_v2(db_handle_, sql_msg.c_str(), sql_msg.size(), &stmt, NULL);  
    
    int n_count = 64;
    for(int i = 0; i < n_count; ++i)  
    {         
        sqlite3_reset(stmt);
        // SQLITE_API int sqlite3_bind_int(sqlite3_stmt *p, int i, int iValue)
        // p: The sqlite3_stmt object
        // i: Which ? (When the ? is more)
        // iValue: The value
        sqlite3_bind_int(stmt, 1, i);  
        sqlite3_bind_int(stmt, 2, i * 2);  
        sqlite3_bind_int(stmt, 3, i / 2);  
        sqlite3_bind_double(stmt, 4, i * i);  
    }
    // Free execute peraper
    sqlite3_finalize(stmt);
    // End use business
    sqlite3_exec(db_handle_, "commit;", NULL, NULL, NULL);  
    
}