#ifndef __MOGO_H__
#define __MOGO_H__

typedef enum _mogo_action_t{
	MOGO_NOTHING,
	MOGO_INSERT,
	MOGO_UPDATE,
	MOGO_DELETE,	
	MOGO_DONE,
}mogo_action_t;

typedef enum _dev_type_t{
	MOGO_UNKNOW,
	MOGO_VSM,
	MOGO_CSP,
	MOGO_CAM,
	MOGO_AP,
	MOGO_LAST,
}dev_type_t;

typedef struct _mogo_common{
	int				admin_id;
	int				state;
	char			mac[18];	//format: xx:xx:xx:xx:xx:xx or xxxxxxxxxxxx
	time_t			boot_time;	
	time_t		    conn_time;	
	time_t			last_time;
	time_t			offl_time;
	struct in_addr	publ_ip;
	struct in_addr	priv_ip;
	struct in6_addr publ_ip6;
	struct in6_addr priv_ip6;
}mogo_common;

typedef struct _mogo_dev{
	mogo_common comm;
}mogo_dev;

/*typedef struct _mog_sta{
	mog_common comm;	
}mog_sta;*/

//public
int mogo_init(void);
int mogo_end(void);

int mogo_set_dev(mogo_action_t act, mogo_dev dev); 

#endif
