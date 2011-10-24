#include <cstdlib>
#include <iostream>
#include <mongo/client/dbclient.h>
#include "classes.h"

#define MAIN
#include "global.h"

bool connect_db() {
    try {
        db.connect("localhost");
        cerr << "connected ok" << endl;
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

    vector<transaction> ts = transaction::all();
    vector<transaction>::iterator it;
    for ( it = ts.begin(); it < ts.end(); it++ ) {
        cout << *it << endl;
    }

    cout << endl << "latest transaction: " << transaction::latest() << endl;
    
    return 0;
}
