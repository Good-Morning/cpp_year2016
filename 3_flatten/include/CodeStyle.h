#define LOWER_CAMEL_CASE 0
#define CAMEL_CASE 1


#if LOWER_CAMEL_CASE 1

#define GET get
#define IS_READY isReady
#define WAIT wait

#define GET_FUTURE getFuture
#define SET set
#define SET_EXCEPTION setException

#define FLATTEN flatten

#elif CAMEL_CASE 1

#define GET Get
#define IS_READY IsReady
#define WAIT Wait

#define GET_FUTURE GetFuture
#define SET Set
#define SET_EXCEPTION SetException

#define FLATTEN Flatten

#else

#error No code style was set

#endif
