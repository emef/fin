#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <mongo/client/dbclient.h>
#include "money.h"

#define DATE_FIELD "date"
#define TYPE_FIELD "type"
#define NAME_FIELD "name"
#define AMOUNT_FIELD "amount"

class date {
    friend ostream& operator<<(ostream& output, const date& t);
    friend istream& operator>>(istream& input, date& t);
    
    time_t _time;
    struct tm _tm;

public:

    /* constructor from time_t */
    date() {};
    date(time_t t);
    
    time_t time() const { return _time; }
    int day() const { return _tm.tm_mday; }
    int month() const { return _tm.tm_mon + 1; }
    int year() const { return _tm.tm_year + 1900; }
};

enum trans_t { ATM, DEBIT, CREDIT };

class transaction {
   friend ostream& operator<<(ostream& output, const transaction& t);
    
    date _date;
    trans_t _type;
    string _name;
    usd _amount;
    
public: 

    /* constructor from BSON obj */
    transaction(mongo::BSONObj obj);

    static vector<transaction> all();
    static date latest();
    
    
    
/* accessors */
public:
    date occurred() const { return _date; }
    trans_t type() const { return _type; }
    string name() const { return _name; }
    usd amount() const { return _amount; }
    
    
};
