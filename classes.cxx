#include "classes.h"
#include "global.h"

/*******************************************************************
TRANSACTIONS
*******************************************************************/

/* constructor */
transaction::transaction(mongo::BSONObj obj) {
    mongo::BSONElement e;

    /* try getting ID */
    if ( obj.getObjectID(e) ) {
        __id = e.OID();
    }
    
    occurred = date( (time_t)obj.getField(DATE_FIELD).Long() );
    type = (trans_t)obj.getIntField(TYPE_FIELD);
    name = obj.getStringField(NAME_FIELD);
    amount = obj.getField(AMOUNT_FIELD).Long();
}

bool transaction::save() {
    mongo::BSONObjBuilder build;
    bool updating = __id.isSet();
    
    if ( !updating ) 
        build.genOID();
    else 
        build.append("_id", __id);
    
    build.append(DATE_FIELD, (long long)occurred.time());
    build.append(TYPE_FIELD, (int)type);
    build.append(NAME_FIELD, name);
    build.append(AMOUNT_FIELD, (long long)amount);

    if ( !updating ) {
        mongo::BSONObj obj = build.obj();
        mongo::BSONElement e;
        
        db.insert( DB_TRANSACTIONS, obj );

        /* update _id field on our side */
        obj.getObjectID(e);
        __id = e.OID();
    } else
        db.update( DB_TRANSACTIONS, mongo::BSONObj(), build.obj());

    return true;
}

/* static */
vector<transaction> transaction::all() {
    vector<transaction> ts;
    mongo::BSONObj emptyObj;

    auto_ptr<mongo::DBClientCursor> cursor = 
        db.query(DB_TRANSACTIONS, emptyObj);

    while( cursor->more() ) {
        mongo::BSONObj obj = cursor->next();
        ts.push_back(transaction(obj));
    }

    return ts;
}

/* static */
date transaction::latest() {
    date best(0);
    vector<transaction> ts = transaction::all();
    vector<transaction>::iterator it;

    for ( it = ts.begin(); it < ts.end(); it++ ) {
        date cur = it->occurred;
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
    output << "{";

    if ( t.has_id() ) 
        output << " _id = " << t._id().str() << endl;
 
    output << "  name: " << t.name << endl
           << "  type: " << (int)t.type << endl
           << "  date: " << t.occurred << endl
           << "  amount: " << to_string(t.amount) << " }";
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
