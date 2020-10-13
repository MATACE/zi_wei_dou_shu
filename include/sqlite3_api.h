/** 
 * @file sqlite3_api.h
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

#ifndef SQLITE3_API_H
#define SQLITE3_API_H

#include <iostream>

#include <sqlite3/sqlite3.h>
#include <glog/logging.h>

#include "os.h"
#include "sql_example_msg.h"

using namespace std;

#define DATABASH_PATH "../../database/zi_wei.db"

class Sqlite3Api
{
public:
    Sqlite3Api();
    virtual ~Sqlite3Api() = default;

    bool OpenDB(string db_path);
    bool CloseDB();
    bool NormaSqlExe(string sql_cmd);

private:
   sqlite3 *db_handle_;
};

#endif // SQLITE3_API_H
