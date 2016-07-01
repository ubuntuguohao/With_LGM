#include <stdarg.h>
#include <time.h>

const char *g_level[LOGGER_NUM] = {
	"ERROR",
	"CRITICAL",
	"WARNING",
	"MESSAGE",
	"INFO",
	"DEBUG",
	"TRACE"
}

int snprintf_wapper(char *buf, size_t *size, const char *fmt, ...)
{
	va_list args;
	int _wr_bytes = -1;

	if(NULL == buf || NULL == fmt
		|| 0 >= size)
	{
		return -1;	
	}

	va_start(args, fmt);
	_wr_bytes = vsnprintf(buf, size, fmt, args);
	va_end(args);

	if(_wr_bytes >= size)	
	{
		_wr_bytes = size - 1;
	}
	
	buf += _wr_bytes;
	*size -= _wr_bytes;

	return _wr_bytes;	
}

int _logger_head_handler(char *buf, const char *file, 
					const char *func, int line, long level)
{	
	char time_buf[LGM_LOG_TIME_SIZE] = {0};
	time_t ts = NULL;	

	time(&ts);
	ctime_r(&ts, time_buf);

	return snprintf(buf, LGM_LOG_LINE_SIZE, "%s|%s|%s:%d|%s",
			time_buf, g_level[level], file, line, func);		
	
}

void _logger(const char *file, const char *func,
			int line, long level, cosnt char *fmt, ## __VA_ARGS__)
{
	if(NULL == fmt 
		|| LOGGER_ERROR > level 
		|| LOGGER_NUM < level)
	{
		return;
	}

	char buf[LGM_LOG_BUF] = {0};
	int _wr_bytes = -1;
		
	_wr_bytes = _logger_head_handler(buf, file, func, line, level);
	if(_wr_bytes <= 0)
	{
		return;
	}
	
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf + _wr_bytes, 
			LGM_LOG_BUF - size, fmt, args);				
	va_end(args);
	
	P(buf);

}
