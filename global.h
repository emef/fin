#pragma once
#include <mongo/client/dbclient.h>

#ifdef MAIN
#define EXTERN
#else
#define EXTERN extern
#endif


/* global db connection */
EXTERN mongo::DBClientConnection db;

/* global collection names */
#define DB_TRANSACTION "fin.transactions"

