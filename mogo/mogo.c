#include <bson.h>
#include <bcon.h>
#include <mongo.h>
#include "mogo.h"

typedef enum _logger_level_t
{
	LOGGER_ERROR,
	LOGGER_CRITICAL,
	LOGGER_WARNING,
	LOGGER_MESSAGE,
	LOGGER_INFO,
	LOGGER_DEBUG,
	LOGGER_TRACE,
}logger_level_t;



#define DEBUG(fmt, ...)
	fprintf(stderr, fmt, ##__VA_ARGS__)

void _logger(const char *file, const char *func,
				int *line, long level, 
				const char *fmt, ...)

#define LOG(level, fmt, ...)
	_logger(__FILE__, __func__, __LINE__,
			level, fmt, ## __VA_ARGS__)	

//process convert data to type of bson object
typedef int (*encode_fn)(const void *data, bson_t *doc);
//build id from the data, set it to doc
typedef void (*oid_fn)(const void *data, bson_t *doc);
//batch process the data
typedef void (*data_fn)(const void *data, 
					encode_fn encoder,
					oid_fn oidder,
					mongoc_bulk_operation_t *bulk);

typedef enum _mogo_batch_type_t{
	MOGO_BULK_DEV,
	MOGO_BULK_LAST,
}mogo_batch_type_t;

typedef struct _mogo_batch_t
{
	int						counter;
	pthread_mutex_t			lock;
	const char				*db_name;
	const char				*coll_name;
	const encode_fn			encoder;	
	const oid_fn			oid_setter;	
	mongo_collection_t		*coll;
	mongo_client_t			*client;
	mongo_bulk_operation_t	*bulk;
}mogo_batch_t;

struct _mogo_ctx_t{
	int					running;
	pthread_t			tid;	
	pthread_mutex_t		lock;
	pthread_cond_t		cond;
	mongo_client_pool_t *pool;
	mogo_batch_t        batches[MOG_BULK_LAST];
}mogo_ctx_t;

void mongoc_logger_wrapper(mongoc_log_level_t log_level,
							const char *log_domain,
							const char *message,
							void *user_data)
{
	switch(log_level)
	{
		case MONGOC_LOG_LEVEL_ERROR:
		case MONGOC_LOG_LEVEL_CRITICAL:
		case MONGOC_LOG_LEVEL_WARNING:
			break;
		case MONGOC_LOG_LEVEL_MESSAGE:
		case MONGOC_LOG_LEVEL_INFO:
			break;
		case MONGOC_LOG_LEVEL_DEBUG:
		case MONGOC_LOG_LEVEL_TRACE:
			break;
		default:
			break;
	}
	
}

int mogo_init(void)
{
	mongoc_log_set_handler(mongoc_logger_wrapper, NULL);
	//pthread_create();
	//pthread_cond_wait();
	return VNI_SUCCESS;
}

int mogo_end(void)
{
	return VNI_SUCCESS;
}

int mogo_set_dev(mogo_action_t act, mogo_dev_t dev)
{
	return VNI_SUCCESS;
}
