#include "mydb.h"
#include <QString>
MyDB* MyDB::instance = nullptr;

// Constructor
MyDB::MyDB()
{
    init(); // Initialize the database connection
}

// Method to initialize the database
void MyDB::init()
{
    // Add the database connection
    db = QSqlDatabase::addDatabase("QSQLITE", "Data");
    QString path_to_database = QString(PROJECT) + "/databaseforDAS.sqlite";
    db.setDatabaseName(path_to_database);

    // Check if the database file exists
    if (QFile::exists(path_to_database)) {
        qDebug() << "DB file exists";
    } else {
        qDebug() << "DB file doesn't exist";
    }

    // Attempt to open the database
    if (!db.open()) {
        qDebug() << "Database Error: " << db.lastError().text(); // Output error if failed to open
    } else {
        qDebug() << "Database loaded successfully!"; // Successful connection message
    }
}

// Singleton access method
MyDB* MyDB::getInstance()
{
    qDebug() << "in MyDB::getInstance()";

    if (instance == nullptr) {
        instance = new MyDB(); // Create a new instance if it doesn't exist
    }

    return instance; // Return the singleton instance
}

// Method to get the QSqlDatabase instance
QSqlDatabase MyDB::getDBInstance()
{
    return db; // Return the database instance
}

// Reset the singleton instance
void MyDB::ResetInstance()
{
    delete instance; // Delete existing instance
    instance = nullptr; // Reset instance pointer
}

// Destructor
MyDB::~MyDB()
{
    if (db.isOpen()) {
        db.close(); // Close the database connection if it is open
        qDebug() << "Database closed."; // Log that the database was closed
    }
}
