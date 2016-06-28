#include <bson.h>
#include <bcon.h>
#include <mongo.h>
#include "mogo.h"

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

static int _dev_encoder(const void *data, bson_t *doc);
static void _dev_oid_setter(const void *data, bson_t *doc);

struct _mogo_ctx_t{
	int					running;
	pthread_t			tid;	
	pthread_mutex_t		lock;
	pthread_cond_t		cond;
	mongo_client_pool_t *pool;
	mogo_batch_t        batches[MOG_BULK_LAST];
}mogo_ctx_t;

static mogo_ctx_t mogo_ctx_ = {
	.running		= 0,
	.lock			= PTHREAD_MUTEX_INITIALIZER,
	.cond			= PTHREAD_COND_INITIALIZER,
	.pool			= NULL,
	.batches		= {
			[MOGO_BULK_DEV]		= {
					0,
					PTHREAD_MUTEX_INITIALIZER,
					"status",
					"dev",
					_dev_encoder,
					_dev_oid_setter,
			},
	}, 
};

static void _dev_oid_setter(const void *data, bson_t *doc)
{
	return
}
static int _dev_encoder(const void *data, bson_t *doc)
{
	return VNI_SUCCESS;
}
static int _add_data(const void *data, encode_fn encoder,
					oid_fn oidder, mongoc_bulk_operation_t *bulk)
{
	return VNI_SUCCCESS;
}
static int _del_data(const void *data, encode_fn encoder,
					oid_fn oidder, mongoc_bulk_operation_t *bulk)
{
	return VNI_SUCCCESS;
}

static void mongoc_logger_wrapper(mongoc_log_level_t log_level,
							const char *log_domain,
							const char *message,
							void *user_data)
{
	int level = LOGGER_DEBUG;
	switch(log_level)
	{
		case MONGOC_LOG_LEVEL_ERROR:
		case MONGOC_LOG_LEVEL_CRITICAL:
		case MONGOC_LOG_LEVEL_WARNING:
			level = LOGGER_ERROR;
			break;
		case MONGOC_LOG_LEVEL_MESSAGE:
		case MONGOC_LOG_LEVEL_INFO:
			level = LOGGER_INFO;
			break;
		case MONGOC_LOG_LEVEL_DEBUG:
		case MONGOC_LOG_LEVEL_TRACE:
			level = LOGGER_DEBUG;
			break;
		default:
			break;
	}

	LOG(level, "MOGO:%s, %s", log_domain, message);
}

int mogo_init(void)
{
	//log handler from mongoc information
	mongoc_log_set_handler(mongoc_logger_wrapper, NULL);
	//mongo init
	mongoc_init();
	
	//pthread_create();
	//pthread_cond_wait();
	return VNI_SUCCESS;
}

int mogo_end(void)
{
	
	mongoc_cleanup();
	return VNI_SUCCESS;
}

int mogo_set_dev(mogo_action_t act, mogo_dev_t dev)
{
	return VNI_SUCCESS;
}
