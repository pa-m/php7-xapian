#include <phpcpp.h>
#include <xapian.h>

class Error: public Php::Base, public Xapian::Error {
public:
    Error(const Xapian::Error&e):Xapian::Error(e){}
    virtual ~Error(){}
};

class Compactor: public Php::Base {
    std::unique_ptr<Xapian::Compactor> m;
public:
    Compactor(){m=std::unique_ptr<Xapian::Compactor>(new Xapian::Compactor());}
    void add_source(Php::Parameters &params){
        m->add_source(params[0]);
    }
    void set_destdir(Php::Parameters &params){
        m->set_destdir(params[0]);
    }
    void compact(Php::Parameters &params){
        m->compact();
    }
    virtual ~Compactor(){m=NULL;}
};


class TermIterator: public Php::Base, public Xapian::TermIterator {
public:
    TermIterator():Xapian::TermIterator(){}
    TermIterator(const Xapian::TermIterator& i):Xapian::TermIterator(i){}
    Php::Value get_description(Php::Parameters &params){return Xapian::TermIterator::get_description();}
    virtual ~TermIterator(){}
};

class TermGenerator: public Php::Base, public Xapian::TermGenerator {
public:
    TermGenerator():Xapian::TermGenerator(){}
    TermGenerator(const Xapian::TermGenerator& tg):Xapian::TermGenerator(tg){}
    Php::Value get_description(Php::Parameters &params){return Xapian::TermGenerator::get_description();}
    virtual ~TermGenerator(){}
};

class Document: public Php::Base, public Xapian::Document {
public:
    Document():Xapian::Document(){}
    Document(const Xapian::Document&d):Xapian::Document(d){}
    Php::Value get_description(Php::Parameters &params){return Xapian::Document::get_description();}

    virtual ~Document(){}
};

class MSet: public Php::Base, public Xapian::MSet {
public:
    MSet():Xapian::MSet(){}
    MSet(const Xapian::MSet &m):Xapian::MSet(m){}
    Php::Value get_description(Php::Parameters &params){return Xapian::MSet::get_description();}
    virtual ~MSet(){}
};
class RSet: public Php::Base, public Xapian::RSet {
public:
    RSet():Xapian::RSet(){}
    RSet(const Xapian::RSet&r):Xapian::RSet(r){}
    Php::Value get_description(Php::Parameters &params){return Xapian::RSet::get_description();}
    virtual ~RSet(){}
};
class ESet: public Php::Base, public Xapian::ESet {
public:
    ESet():Xapian::ESet(){}
    ESet(const Xapian::ESet& e):Xapian::ESet(e){}
    Php::Value get_description(Php::Parameters &params){return Xapian::ESet::get_description();}
    virtual ~ESet(){}
};

class Database: public Php::Base, public Xapian::Database {
public:
    Database():Xapian::Database(){}
    Database(const Xapian::Database&d):Xapian::Database(d){}
    virtual ~Database(){}
    void close(Php::Parameters &params){ Xapian::Database::close();}
    Php::Value get_doccount(Php::Parameters &params){ return (int64_t)Xapian::Database::get_doccount();}
    void add_database(Php::Parameters &params){
        Database*db=dynamic_cast<Database*>(params[0].implementation());
        Xapian::Database::add_database(*db);
    }
    Php::Value get_description(Php::Parameters &params){return Xapian::Database::get_description();}
};

class WritableDatabase: public Php::Base, public Xapian::WritableDatabase {

public:
    WritableDatabase():Xapian::WritableDatabase(){}
    WritableDatabase(const Xapian::WritableDatabase&d):Xapian::WritableDatabase(d){}
    virtual ~WritableDatabase(){}
    void begin_transaction(Php::Parameters &params){ static_cast<Xapian::WritableDatabase*>(this)->begin_transaction();}
    void cancel_transaction(Php::Parameters &params){ static_cast<Xapian::WritableDatabase*>(this)->cancel_transaction();}
    void commit_transaction(Php::Parameters &params){ static_cast<Xapian::WritableDatabase*>(this)->commit_transaction();}
    void commit(Php::Parameters &params){ static_cast<Xapian::WritableDatabase*>(this)->commit();}
    void close(Php::Parameters &params){ Xapian::WritableDatabase::close();}
    Php::Value get_doccount(Php::Parameters &params){ return (int64_t)Xapian::WritableDatabase::get_doccount();}
    Php::Value get_description(Php::Parameters &params){return Xapian::WritableDatabase::get_description();}

};

class Enquire: public Php::Base, public Xapian::Enquire {
public:
    Enquire(const Xapian::Enquire&e):Xapian::Enquire(e){}
    virtual ~Enquire(){}
    Php::Value get_description(Php::Parameters &params){return Xapian::Enquire::get_description();}
};


class PhpXapian : public Php::Base {
    public:
     PhpXapian()=default;
     virtual ~PhpXapian()=default;
     
    static Php::Value version_string(Php::Parameters &params)
    {
        // @todo add implementation
        return Xapian::version_string();
    }
    static Php::Value inmemory_open(Php::Parameters &params){
        Xapian::WritableDatabase db(std::string(),Xapian::DB_BACKEND_INMEMORY);
        return Php::Object("XapianWritableDatabase",new WritableDatabase(db));
    }
};
/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {

    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("xapian", "1.4.0");

        // @todo    add your own functions, classes, namespaces to the extension
        Php::Class<PhpXapian> Xapian("Xapian");
        Xapian.method<&PhpXapian::version_string>("version_string");
        Xapian.method<&PhpXapian::inmemory_open>("inmemory_open");
        extension.add(std::move(Xapian));

        Php::Class<Error> cError("XapianError");
        //cError.method<&Error::m>("m");
        extension.add(std::move(cError));
        Php::Class<Compactor> cCompactor("XapianCompactor");
        cCompactor.method<&Compactor::add_source>("add_source");
        cCompactor.method<&Compactor::set_destdir>("set_destdir");
        cCompactor.method<&Compactor::compact>("compact");
        extension.add(std::move(cCompactor));

        Php::Class<TermIterator> cTermIterator("XapianTermIterator");
        cTermIterator.method<&TermIterator::get_description>("get_description",{});
        extension.add(std::move(cTermIterator));
        Php::Class<TermGenerator> cTermGenerator("XapianTermGenerator");
        cTermGenerator.method<&TermGenerator::get_description>("get_description",{});
        //cTermGenerator.method<&TermGenerator::m>("m");
        extension.add(std::move(cTermGenerator));

        Php::Class<Document> cDocument("XapianDocument");
        cDocument.method<&Document::get_description>("get_description",{});
        //cDocument.method<&Document::m>("m");
        extension.add(std::move(cDocument));

        Php::Class<MSet> cMSet("XapianMSet");
        cMSet.method<&MSet::get_description>("get_description",{});
        //cMSet.method<&MSet::m>("m");
        extension.add(std::move(cMSet));

        Php::Class<RSet> cRSet("XapianRSet");
        cRSet.method<&RSet::get_description>("get_description",{});
        //cRSet.method<&RSet::m>("m");
        extension.add(std::move(cRSet));

        Php::Class<ESet> cESet("XapianESet");
        cESet.method<&ESet::get_description>("get_description",{});
        extension.add(std::move(cESet));

        Php::Class<Database> cDatabase("XapianDatabase");
        cDatabase.method<&Database::close>("close");
        cDatabase.method<&Database::get_doccount>("get_doccount");
        cDatabase.method<&Database::add_database>("add_database");
        cDatabase.method<&Database::get_description>("get_description",{});
        extension.add(std::move(cDatabase));

        Php::Class<WritableDatabase> cWritableDatabase("XapianWritableDatabase");
        cWritableDatabase.method<&WritableDatabase::get_description>("get_description");
        cWritableDatabase.method<&WritableDatabase::begin_transaction>("begin_transaction");
        cWritableDatabase.method<&WritableDatabase::cancel_transaction>("cancel_transaction");
        cWritableDatabase.method<&WritableDatabase::commit_transaction>("commit_transaction");
        cWritableDatabase.method<&WritableDatabase::commit>("commit");
        cWritableDatabase.method<&WritableDatabase::close>("close");
        cWritableDatabase.method<&WritableDatabase::get_doccount>("get_doccount");
        cWritableDatabase.extends(cDatabase);
        extension.add(std::move(cWritableDatabase));
        Php::Class<Enquire> cEnquire("XapianEnquire");
        //cEnquire.method<&Enquire::m>("m");
        extension.add(std::move(cEnquire));


        // return the extension
        return extension;
    }
}
