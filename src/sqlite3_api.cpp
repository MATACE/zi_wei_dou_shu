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