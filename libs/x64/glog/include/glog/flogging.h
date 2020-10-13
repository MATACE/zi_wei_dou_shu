/*
 * Copyright (c) 2010-2019, Flexem Technologies Inc
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
 * Neither the name of Flexem Technologies Inc nor the names of its contributors
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
#ifndef FLOGGING_H_
#define FLOGGING_H_

#include <glog/logging.h>

#define FLOG(severity) COMPACT_GOOGLE_LOG_ ## severity.stream()


///////////////////////////////////////////////////////////////
#include <stdarg.h>

enum SeverityLevel {
	FLOG_INFO = 0,
	FLOG_WARNING = 1,
	FLOG_ERROR = 2,
	FLOG_FATAL = 3
};

char buf[2048] = { 0 };

int32_t FlogInit(const char* tag, const char* log_dir, int32_t log_level)
{
	CHECK_NOTNULL(log_dir);
	google::InitGoogleLogging(tag);
	FLAGS_stderrthreshold = log_level;
	FLAGS_log_dir = log_dir;
	FLAGS_logbufsecs = 0;   // Print log in real time
	FLAGS_max_log_size = 1; // Max log size 1MB，每个日志文件大小超过1MB，会自动生成一个新的日志文件
	FLAGS_colorlogtostderr = true;

	return 0;
}

int32_t FlogStop()
{
	google::ShutdownGoogleLogging();
}

void GLogMsg(uint32_t nSeverity, const char *format, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vsprintf(buf, format, arg_ptr);
	switch (nSeverity)
	{
	case 0:
		LOG(INFO) << buf;
		break;
	case 1:
		LOG(WARNING) << buf;
		break;
	case 2:
		LOG(ERROR) << buf;
		break;
	case 3:
		LOG(FATAL) << buf;
		break;
	default:
		break;
	}
	va_end(arg_ptr);

	memset(buf, 0, 2048);
}

#endif  // FLOGGOING_H_
