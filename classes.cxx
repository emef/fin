#include "classes.h"
#include "global.h"

/*******************************************************************
TRANSACTIONS
*******************************************************************/

transaction::transaction(mongo::BSONObj obj) {
    _date = date( (time_t)obj.getField(DATE_FIELD).Long() );
    _type = (trans_t)obj.getIntField(TYPE_FIELD);
    _name = obj.getStringField(NAME_FIELD);
    _amount = obj.getField(AMOUNT_FIELD).Long();
}

vector<transaction> transaction::all() {
    vector<transaction> ts;
    mongo::BSONObj emptyObj;

    auto_ptr<mongo::DBClientCursor> cursor = 
        db.query(DB_TRANSACTION, emptyObj);

    while( cursor->more() ) {
        mongo::BSONObj obj = cursor->next();
        ts.push_back(transaction(obj));
    }

    return ts;
}

date transaction::latest() {
    date best;
    vector<transaction> ts = transaction::all();
    vector<transaction>::iterator it;

    for ( it = ts.begin(); it < ts.end(); it++ ) {
        date cur = it->occurred();
        if (cur.time() > best.time())
            best = cur;
    }

    return best;
}

/*******************************************************************
DATES
*******************************************************************/
date::date(time_t t) {
    _time = t;
    _tm = *localtime( &_time );
}


/*******************************************************************
INPUT/OUTPUT
*******************************************************************/

ostream& operator<<(ostream& output, const transaction& t) {
    output << "{ name: " << t.name() << endl
           << "  type: " << (int)t.type() << endl
           << "  date: " << t.occurred() << endl
           << "  amount: " << to_string(t.amount()) << " }";
    return output;
}

ostream& operator<<(ostream& output, const date& t) {
    time_t rawtime = t.time();
    struct tm *timeinfo = localtime( &rawtime );
    char buffer[80];

    strftime(buffer, 80, "%x", timeinfo);
    output << buffer;
    
    return output;
}

istream& operator>>(istream& input, date& t) {

    return input;
}
