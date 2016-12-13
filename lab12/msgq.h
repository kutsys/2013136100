
#define KEYVAL 0627
#define MSGSIZE 64

#define PRODUCER_PUSHED 1
#define CONSUMER_PUSHED 2

//structure for Message Queue
typedef struct _Msgq {
	long msgType;
	char msgTxt[MSGSIZE];
} Msgq;
