#ifndef __LGM_LOG_H__
#define __LGM_LOG_H__ 

#define LGM_LOG_BUF 65536
#define LGM_LOG_LINE_SIZE 256
#define LGM_LOG_TIME_SIZE 128

typedef enum {
	LOGGER_ERROR,
	LOGGER_CRITICAl,
	LOGGER_WARNING,
	LOGGER_MESSAGE,
	LOGGER_INFO,
	LOGGER_DEBUG,
	LOGGER_TRACE,
	LOGGER_NUM,
}logger_level_t;

#define P(fmt, ...)
	fprintf(stdout, fmt, ## __VA_ARGS__)

#define E(fmt, ...)
	fprintf(stderr, fmt, ## __VA_ARGS__)

void  _logger(const char *file, const char *func,
		int line, long level, const char *fmt, ...);

#define LOG(level, fmt, ...)
	_logger(__FILE__, __func__, __LINE__,
			level, fmt, ## __VA_ARGS__)

#endif
