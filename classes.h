#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <mongo/client/dbclient.h>
#include "money.h"


/******************************************************************
DATE
******************************************************************/

class date {
    friend ostream& operator<<(ostream& output, const date& t);
    friend istream& operator>>(istream& input, date& t);
    
    time_t _time;
    struct tm _tm;

public:

    /* constructor from time_t */
    date(time_t t = std::time(NULL));
    
    time_t time() const { return _time; }
    int day() const { return _tm.tm_mday; }
    int month() const { return _tm.tm_mon + 1; }
    int year() const { return _tm.tm_year + 1900; }
};

/******************************************************************
TRANSACTION
******************************************************************/

#define DATE_FIELD "date"
#define TYPE_FIELD "type"
#define NAME_FIELD "name"
#define AMOUNT_FIELD "amount"

enum trans_t { ATM, DEBIT, CREDIT };

class transaction {
   friend ostream& operator<<(ostream& output, const transaction& t);
    
    mongo::OID __id;
    
/* attributes */
public:
    date occurred;
    trans_t type;
    string name;
    usd amount;
    
public: 
    transaction() {}
    transaction(mongo::BSONObj obj);

    /* static methods */
    static vector<transaction> all();
    static date latest();
    
    
/* accessors */
public:
    mongo::OID _id() const { return __id; }
    
/* general instance methods */
public:
    bool has_id() const { return __id.isSet(); }
    bool save();

private:
    bool update();
    bool insert();
    
};
