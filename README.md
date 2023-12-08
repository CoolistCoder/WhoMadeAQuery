WhoMadeAQuery by Alec Roberts

A simple MySQL DB that uses the MySQL C++ Connector library to connect to a localhost DB.
By default, this DB uses credentials that are specific and not typically used.
This means that if you want to try this out, you will currently need to create a 
MySQL DB with the exact user as specified in the src, which I will clarify now:
User: dummyuser   Pwd: password   Connection: localhost

In addition, a db with two tables needs to be made.  Including more data on this
in a future push.

Author's Note: While I do enjoy developing MySQL stuff, SQLite might be a better
tool for projects such as this.  A proper DB is historically limited for small
devlopment, so it may be a good idea to port this code over to SQLite in the future.

Current features:
Allows the user to "login" to this localhost DB.
Allows the user to create a new "login" for the localhost DB.

Future features:
Users will be able to perform simple actions like printing out users or user history.
All actions a "logged in" user will make are logged into the second table.
