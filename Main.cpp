#include <phpcpp.h>
#include <xapian.h>

class Error: public Php::Base, public Xapian::Error {
public:
    Error(const Xapian::Error&e):Xapian::Error(e){}
    virtual ~Error(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<Error> cError("XapianError");
        //cError.method<&Error::m>("m");
        extension.add(std::move(cError));

    }
};

class Compactor: public Php::Base {
    std::unique_ptr<Xapian::Compactor> m;
public:
    Compactor(){m=std::unique_ptr<Xapian::Compactor>(new Xapian::Compactor());}
    void add_source(Php::Parameters &params){
        //deprecated Use Database::compact(destdir[, compactor]) instead.
        m->add_source(params[0]);
    }
    void set_destdir(Php::Parameters &params){
        //deprecated Use Database::compact(destdir[, compactor]) instead.
        m->set_destdir(params[0]);
    }
    void compact(Php::Parameters &params){
        //deprecated Use Database::compact(destdir[, compactor]) instead.
        m->compact();
    }
    virtual ~Compactor(){m=NULL;}
    static void get_module_part(Php::Extension& extension){
        Php::Class<Compactor> cCompactor("XapianCompactor");
        cCompactor.method<&Compactor::add_source>("add_source");
        cCompactor.method<&Compactor::set_destdir>("set_destdir");
        cCompactor.method<&Compactor::compact>("compact");
        extension.add(std::move(cCompactor));
    }
};


class TermIterator: public Php::Base, public Xapian::TermIterator {
public:
    TermIterator():Xapian::TermIterator(){}
    TermIterator(const Xapian::TermIterator& i):Xapian::TermIterator(i){}
    Php::Value get_description(Php::Parameters &params){return Xapian::TermIterator::get_description();}
    virtual ~TermIterator(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<TermIterator> cTermIterator("XapianTermIterator");
        cTermIterator.method<&TermIterator::get_description>("get_description",{});
        extension.add(std::move(cTermIterator));
    }
};
class Stem: public Php::Base, public Xapian::Stem {
public:
    Stem(std::string lang):Xapian::Stem(lang){}
    Php::Value get_description(Php::Parameters &params){return Xapian::Stem::get_description();}
    virtual ~Stem(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<Stem> cStem("XapianStem");
        cStem.method<&Stem::get_description>("get_description",{});
        //cStem.method<&Stem::m>("m");
        extension.add(std::move(cStem));
    }
};
class Stopper: public Php::Base, public Xapian::Stopper {
    typedef Xapian::Stopper B;
public:
    Stopper():Xapian::Stopper(){}
    Php::Value get_description(Php::Parameters &params){return Xapian::Stopper::get_description();}
    Php::Value apply(Php::Parameters &params){
        B& b=*static_cast<B*>(this);
        return b(params[0].stringValue());
    }
    virtual ~Stopper(){}
    static Php::Class<Stopper>  get_module_part(Php::Extension& extension){
        Php::Class<Stopper> cStopper("XapianStopper");
        cStopper.method<&Stopper::get_description>("get_description",{});
        cStopper.method<&Stopper::apply>("apply");
        extension.add(std::move(cStopper));
        return cStopper;
    }
};
class SimpleStopper: public Php::Base, public Xapian::SimpleStopper {
    typedef Xapian::SimpleStopper B;
public:
    SimpleStopper():Xapian::SimpleStopper(){}
    //SimpleStopper(Php::Array words):Xapian::SimpleStopper(words.begin(),words.end()){}
    Php::Value get_description(Php::Parameters &params){return Xapian::SimpleStopper::get_description();}
    void add(Php::Parameters& params){B::add(params[0]);}
    Php::Value apply(Php::Parameters &params){
        B& b=*static_cast<B*>(this);
        return b(params[0].stringValue());
    }
    virtual ~SimpleStopper(){}
    static void get_module_part(Php::Extension& extension, Php::Class<::Stopper>& cStopper){
        Php::Class<SimpleStopper> cSimpleStopper("XapianSimpleStopper");
        cSimpleStopper.method<&SimpleStopper::get_description>("get_description",{});
        cSimpleStopper.method<&SimpleStopper::add>("add");
        cSimpleStopper.method<&SimpleStopper::apply>("apply");
        cSimpleStopper.extends(cStopper);
        extension.add(std::move(cSimpleStopper));
    }
};
class TermGenerator: public Php::Base, public Xapian::TermGenerator {
    typedef Xapian::TermGenerator B;
public:
    TermGenerator():Xapian::TermGenerator(){}
    TermGenerator(const Xapian::TermGenerator& tg):Xapian::TermGenerator(tg){}
    Php::Value get_description(Php::Parameters &params){return Xapian::TermGenerator::get_description();}
    void set_stemmer(Php::Parameters &params) {
        B::set_stemmer(*dynamic_cast<Xapian::Stem*>(params[0].implementation()));
    }
    void set_stopper(Php::Parameters &params) {
        B::set_stopper(dynamic_cast<Xapian::Stopper*>(params[0].implementation()));
    }
    void set_database(Php::Parameters &params) {
        B::set_database(*dynamic_cast<Xapian::WritableDatabase*>(params[0].implementation()));
    }
    void set_document(Php::Parameters &params) {
        B::set_document(*dynamic_cast<Xapian::Document*>(params[0].implementation()));
    }
    void index_text(Php::Parameters& params) {
        Xapian::termcount wdfinc=params.size()>=1 ? params[1].numericValue() : 1;
        std::string prefix = params.size()>=2 ? params[2].stringValue() : "";
        B::index_text(params[0].stringValue(),wdfinc,prefix);
    }
    virtual ~TermGenerator(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<TermGenerator> cTermGenerator("XapianTermGenerator");
        cTermGenerator.method<&TermGenerator::get_description>("get_description",{});
        cTermGenerator.method<&TermGenerator::set_stemmer>("set_stemmer");
        cTermGenerator.method<&TermGenerator::set_stopper>("set_stopper");
        cTermGenerator.method<&TermGenerator::set_database>("set_database");
        cTermGenerator.method<&TermGenerator::set_document>("set_document");
        cTermGenerator.method<&TermGenerator::index_text>("index_text");
        extension.add(std::move(cTermGenerator));
    }
};

class Document: public Php::Base, public Xapian::Document {
    typedef Xapian::Document B;
public:
    Document():Xapian::Document(){}
    Document(const Xapian::Document&d):Xapian::Document(d){}
    Php::Value get_description(Php::Parameters &params){return Xapian::Document::get_description();}
    void set_data(Php::Parameters &params){B::set_data(params[0]);}
    Php::Value get_data(Php::Parameters &params){return B::get_data();}

    virtual ~Document(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<Document> cDocument("XapianDocument");
        cDocument.method<&Document::get_description>("get_description",{});
        cDocument.method<&Document::set_data>("set_data",{});
        cDocument.method<&Document::get_data>("get_data",{});
        //cDocument.method<&Document::m>("m");
        extension.add(std::move(cDocument));
    }
};

class MSet: public Php::Base, public Xapian::MSet {
public:
    MSet():Xapian::MSet(){}
    MSet(const Xapian::MSet &m):Xapian::MSet(m){}
    Php::Value get_description(Php::Parameters &params){return Xapian::MSet::get_description();}
    virtual ~MSet(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<MSet> cMSet("XapianMSet");
        cMSet.method<&MSet::get_description>("get_description",{});
        //cMSet.method<&MSet::m>("m");
        extension.add(std::move(cMSet));
    }
};
class RSet: public Php::Base, public Xapian::RSet {
public:
    RSet():Xapian::RSet(){}
    RSet(const Xapian::RSet&r):Xapian::RSet(r){}
    Php::Value get_description(Php::Parameters &params){return Xapian::RSet::get_description();}
    virtual ~RSet(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<RSet> cRSet("XapianRSet");
        cRSet.method<&RSet::get_description>("get_description",{});
        //cRSet.method<&RSet::m>("m");
        extension.add(std::move(cRSet));
    }
};
class ESet: public Php::Base, public Xapian::ESet {
public:
    ESet():Xapian::ESet(){}
    ESet(const Xapian::ESet& e):Xapian::ESet(e){}
    Php::Value get_description(Php::Parameters &params){return Xapian::ESet::get_description();}
    virtual ~ESet(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<ESet> cESet("XapianESet");
        cESet.method<&ESet::get_description>("get_description",{});
        extension.add(std::move(cESet));
    }
};

class MatchSpy: public Php::Base, public Xapian::MatchSpy {
public:
    MatchSpy():Xapian::MatchSpy(){}
    //MatchSpy(const Xapian::MatchSpy& e):Xapian::MatchSpy(e){}
    Php::Value get_description(Php::Parameters &params){return Xapian::MatchSpy::get_description();}
    virtual ~MatchSpy(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<MatchSpy> cMatchSpy("XapianMatchSpy");
        cMatchSpy.method<&MatchSpy::get_description>("get_description",{});
        extension.add(std::move(cMatchSpy));
    }
};

class ValueCountMatchSpy: public Php::Base, public Xapian::ValueCountMatchSpy {
public:
    ValueCountMatchSpy():Xapian::ValueCountMatchSpy(){}
    //ValueCountMatchSpy(const Xapian::ValueCountMatchSpy& e):Xapian::ValueCountMatchSpy(e){}
    Php::Value get_description(Php::Parameters &params){return Xapian::ValueCountMatchSpy::get_description();}
    virtual ~ValueCountMatchSpy(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<ValueCountMatchSpy> cValueCountMatchSpy("XapianValueCountMatchSpy");
        cValueCountMatchSpy.method<&ValueCountMatchSpy::get_description>("get_description",{});
        extension.add(std::move(cValueCountMatchSpy));
    }
};

class MatchDecider: public Php::Base, public Xapian::MatchDecider {
public:
    MatchDecider():Xapian::MatchDecider(){}
    //MatchDecider(const Xapian::MatchDecider& e):Xapian::MatchDecider(e){}
    //Php::Value get_description(Php::Parameters &params){return Xapian::MatchDecider::get_description();}
    virtual ~MatchDecider(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<MatchDecider> cMatchDecider("XapianMatchDecider");
        //cMatchDecider.method<&MatchDecider::get_description>("get_description",{});
        extension.add(std::move(cMatchDecider));
    }
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
    static Php::Class<Database>  get_module_part(Php::Extension& extension){
        Php::Class<Database> cDatabase("XapianDatabase");
        cDatabase.method<&Database::close>("close");
        cDatabase.method<&Database::get_doccount>("get_doccount");
        cDatabase.method<&Database::add_database>("add_database");
        cDatabase.method<&Database::get_description>("get_description",{});
        extension.add(std::move(cDatabase));
        return cDatabase;
    }
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
    void add_document(Php::Parameters &params){Xapian::WritableDatabase::add_document(*dynamic_cast<Xapian::Document*>(params[0].implementation()));}

    static void get_module_part(Php::Extension& extension,Php::Class<::Database>& cDatabase){
        Php::Class<WritableDatabase> cWritableDatabase("XapianWritableDatabase");
        cWritableDatabase.method<&WritableDatabase::get_description>("get_description");
        cWritableDatabase.method<&WritableDatabase::begin_transaction>("begin_transaction");
        cWritableDatabase.method<&WritableDatabase::cancel_transaction>("cancel_transaction");
        cWritableDatabase.method<&WritableDatabase::commit_transaction>("commit_transaction");
        cWritableDatabase.method<&WritableDatabase::commit>("commit");
        cWritableDatabase.method<&WritableDatabase::close>("close");
        cWritableDatabase.method<&WritableDatabase::get_doccount>("get_doccount");
        cWritableDatabase.method<&WritableDatabase::add_document>("add_document");
        cWritableDatabase.extends(cDatabase);
        extension.add(std::move(cWritableDatabase));
    }
};

class Query: public Php::Base, public Xapian::Query {
public:
    Query(const Xapian::Query&e):Xapian::Query(e){}
    Query(std::string str):Xapian::Query(str){}
    virtual ~Query(){}
    Php::Value get_description(Php::Parameters &params){return Xapian::Query::get_description();}
    static void get_module_part(Php::Extension& extension){
        Php::Class<Query> cQuery("XapianQuery");
        //cQuery.method<&Query::m>("m");
        extension.add(std::move(cQuery));
    }
};

class QueryParser: public Php::Base, public Xapian::QueryParser {
public:
    QueryParser(const Xapian::QueryParser&e):Xapian::QueryParser(e){}
    virtual ~QueryParser(){}
    Php::Value get_description(Php::Parameters &params){return Xapian::QueryParser::get_description();}
    static void get_module_part(Php::Extension& extension){
        Php::Class<QueryParser> cQueryParser("XapianQueryParser");
        //cQueryParser.method<&QueryParser::m>("m");
        extension.add(std::move(cQueryParser));
    }
};

class Enquire: public Php::Base, public Xapian::Enquire {
    typedef Xapian::Enquire B;
public:
    Enquire(const Xapian::Enquire&e):Xapian::Enquire(e){}
    virtual ~Enquire(){}
    Php::Value get_description(Php::Parameters &params){return Xapian::Enquire::get_description();}
    void set_query(Php::Parameters& params){B::set_query(*dynamic_cast<Xapian::Query*>(params[0].implementation()));}
    Php::Value get_query(Php::Parameters& params){
        Query q=B::get_query();
        return Php::Object("XapianQuery",&q);
    }
    Php::Value get_mset(Php::Parameters& params){
        Xapian::doccount first=params[0].numericValue();
        Xapian::doccount maxitems=params[1].numericValue();
        Xapian::doccount checkatleast=params[2].numericValue();
        RSet* omrset = params.size()>=3 ? dynamic_cast<RSet*>(params[3].implementation()) : NULL;
        MatchDecider* mdecider = params.size()>=4 ? dynamic_cast<MatchDecider*>(params[4].implementation()) : NULL;
        MSet mset=B::get_mset(first,maxitems,checkatleast,omrset,mdecider);
        return Php::Object("XapianMSet",&mset);
    }
    static void get_module_part(Php::Extension& extension){
        Php::Class<Enquire> cEnquire("XapianEnquire");
        cEnquire.method<&Enquire::set_query>("set_query");
        cEnquire.method<&Enquire::get_query>("get_query");
        cEnquire.method<&Enquire::get_mset>("get_mset");
        extension.add(std::move(cEnquire));
    }
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
    static void get_module_part(Php::Extension& extension) {
        Php::Class<PhpXapian> Xapian("Xapian");
        Xapian.method<&PhpXapian::version_string>("version_string");
        Xapian.method<&PhpXapian::inmemory_open>("inmemory_open");
        extension.add(std::move(Xapian));

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
        PhpXapian::get_module_part(extension); 
        Error::get_module_part(extension);
        Compactor::get_module_part(extension);
        TermIterator::get_module_part(extension);
        Stem::get_module_part(extension);
        Php::Class<Stopper> cStopper = Stopper::get_module_part(extension);
        SimpleStopper::get_module_part(extension, cStopper);
        TermGenerator::get_module_part(extension);
        Document::get_module_part(extension);
        MSet::get_module_part(extension);
        RSet::get_module_part(extension);
        ESet::get_module_part(extension);
        MatchSpy::get_module_part(extension);
        ValueCountMatchSpy::get_module_part(extension);
        MatchDecider::get_module_part(extension);
        Php::Class<Database> cDatabase=Database::get_module_part(extension);
        WritableDatabase::get_module_part(extension,cDatabase);
        QueryParser::get_module_part(extension);
        Query::get_module_part(extension);
        Enquire::get_module_part(extension);
        // return the extension
        return extension;
    }
}
