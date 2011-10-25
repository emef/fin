#include <cstdlib>
#include <iostream>
#include <mongo/client/dbclient.h>
#include "classes.h"

#define MAIN
#include "global.h"

bool connect_db() {
    try {
        db.connect("localhost");
        return true;
    } catch( mongo::DBException &e ) {
        cerr << "caught " << e.what() << endl;
        return false;
    }   
}

int main() {

    if ( !connect_db() ) {
        exit(1);
    }

    /* insert new transaction */
    transaction t;
    t.name = "transaction added from c++";
    t.amount = 175000000;
    t.type = DEBIT;
        t.save();

    vector<transaction> ts = transaction::all();
    vector<transaction>::iterator it;
    for ( it = ts.begin(); it < ts.end(); it++ ) {
        cout << *it << endl;
    }

    cout << endl << "latest transaction: " << transaction::latest() << endl;
    
    return 0;
}
