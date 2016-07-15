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
    std::shared_ptr<Xapian::Compactor> m;
public:
    Compactor(){m.reset(new Xapian::Compactor());}
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
    typedef Xapian::TermIterator B;
public:
    TermIterator():Xapian::TermIterator(){}
    TermIterator(const Xapian::TermIterator& i):Xapian::TermIterator(i){}
    Php::Value get_description(Php::Parameters &params){return Xapian::TermIterator::get_description();}
    Php::Value get_term(Php::Parameters &params){return (std::string)*(*static_cast<Xapian::TermIterator*>(this));}
    void next(Php::Parameters& params){(*static_cast<Xapian::TermIterator*>(this))++;}
    Php::Value equals(Php::Parameters& params){
        TermIterator *other=dynamic_cast<TermIterator*>(params[0].implementation());
        return *static_cast<Xapian::TermIterator*>(this)==*static_cast<Xapian::TermIterator*>(other);
    }
    Php::Value get_termfreq(Php::Parameters& params){return (int32_t)B::get_termfreq();}
    Php::Value get_wdf(Php::Parameters& params){return (int32_t)B::get_wdf();}

    virtual ~TermIterator(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<TermIterator> cTermIterator("XapianTermIterator");
        cTermIterator.method<&TermIterator::get_description>("get_description",{});
        cTermIterator.method<&TermIterator::get_term>("get_term",{});
        cTermIterator.method<&TermIterator::next>("next",{});
        cTermIterator.method<&TermIterator::equals>("equals",{Php::ByVal("other","XapianTermIterator")});
        cTermIterator.method<&TermIterator::get_termfreq>("get_termfreq",{});
        cTermIterator.method<&TermIterator::get_wdf>("get_wdf",{});
        extension.add(std::move(cTermIterator));
    }
};

class ValueIterator: public Php::Base, public Xapian::ValueIterator {
    typedef Xapian::ValueIterator B;
public:
    ValueIterator():Xapian::ValueIterator(){}
    ValueIterator(const Xapian::ValueIterator& i):Xapian::ValueIterator(i){}
    Php::Value get_description(Php::Parameters &params){return Xapian::ValueIterator::get_description();}
    Php::Value get_value(Php::Parameters &params){
        return **this;
    }
    void next(Php::Parameters& params){(*static_cast<Xapian::ValueIterator*>(this))++;}
    Php::Value equals(Php::Parameters& params){
        ValueIterator *other=dynamic_cast<ValueIterator*>(params[0].implementation());
        return *static_cast<Xapian::ValueIterator*>(this)==*static_cast<Xapian::ValueIterator*>(other);
    }
    Php::Value get_valueno(Php::Parameters& params){return (int32_t)B::get_valueno();}

    virtual ~ValueIterator(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<ValueIterator> cValueIterator("XapianValueIterator");
        cValueIterator.method<&ValueIterator::get_description>("get_description",{});
        cValueIterator.method<&ValueIterator::get_value>("get_value",{});
        cValueIterator.method<&ValueIterator::next>("next",{});
        cValueIterator.method<&ValueIterator::equals>("equals",{Php::ByVal("other","XapianValueIterator")});
        cValueIterator.method<&ValueIterator::get_valueno>("get_valueno",{});
        extension.add(std::move(cValueIterator));
    }
};
class Stem: public Php::Base {
    Xapian::Stem m;
public:
    Xapian::Stem get_xapian_stem(){return m;}
    Stem(){}
    void __construct(Php::Parameters& params){
        if(params.size()>0) m=Xapian::Stem(params[0].stringValue());
    }
    Php::Value get_description(Php::Parameters &params){return m.get_description();}
    virtual ~Stem(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<Stem> cStem("XapianStem");
        cStem.method<&Stem::__construct>("__construct",{});
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

        Xapian::TermGenerator::set_stemmer(dynamic_cast<Stem*>(params[0].implementation())->get_xapian_stem());
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
        Xapian::termcount wdfinc=params.size()>1 ? params[1].numericValue() : 1;
        std::string prefix = params.size()>2 ? params[2].stringValue() : "";
        B::index_text(params[0].stringValue(),wdfinc,prefix);
    }
    virtual ~TermGenerator(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<TermGenerator> cTermGenerator("XapianTermGenerator");
        cTermGenerator.method<&TermGenerator::get_description>("get_description",{});
        cTermGenerator.method<&TermGenerator::set_stemmer>("set_stemmer",{Php::ByVal("stem","XapianStem")});
        cTermGenerator.method<&TermGenerator::set_stopper>("set_stopper",{Php::ByVal("stopper",Php::Type::Object)});
        cTermGenerator.method<&TermGenerator::set_database>("set_database",{Php::ByVal("database","XapianWritableDatabase")});
        cTermGenerator.method<&TermGenerator::set_document>("set_document",{Php::ByVal("document","XapianDocument")});
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
    void add_value(Php::Parameters &params){
        B::add_value(params[0].numericValue(),params[1].stringValue());
    }
    Php::Value get_value(Php::Parameters& params) {
        return Php::Value(B::get_value(params[0].numericValue()));
    }
    void remove_value(Php::Parameters& params) {
        B::remove_value(params[0].numericValue());
    }
    void clear_values(Php::Parameters& params){
        B::clear_values();
    }
    void set_data(Php::Parameters &params){B::set_data(params[0]);}
    Php::Value get_data(Php::Parameters &params){return B::get_data();}
    Php::Value termlist_count(Php::Parameters &params){return (int32_t)B::termlist_count();}
    Php::Value termlist_begin(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::termlist_begin()));}
    Php::Value termlist_end(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::termlist_end()));}
    Php::Value values_count(Php::Parameters &params){return (int32_t)B::values_count();}
    Php::Value values_begin(Php::Parameters &params){return Php::Object("XapianValueIterator",new ValueIterator(B::values_begin()));}
    Php::Value values_end(Php::Parameters &params){return Php::Object("XapianValueIterator",new ValueIterator(B::values_end()));}

    virtual ~Document(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<Document> cDocument("XapianDocument");
        cDocument.method<&Document::get_description>("get_description",{});
        cDocument.method<&Document::add_value>("add_value",{Php::ByVal("slot",Php::Type::Numeric),Php::ByVal("value",Php::Type::String)});
        cDocument.method<&Document::get_value>("get_value",{Php::ByVal("slot",Php::Type::Numeric)});
        cDocument.method<&Document::remove_value>("remove_value",{Php::ByVal("slot",Php::Type::Numeric)});
        cDocument.method<&Document::clear_values>("clear_values",{});
        cDocument.method<&Document::set_data>("set_data",{Php::ByVal("data",Php::Type::String)});
        cDocument.method<&Document::get_data>("get_data",{});
        cDocument.method<&Document::termlist_count>("termlist_count",{});
        cDocument.method<&Document::termlist_begin>("termlist_begin",{});
        cDocument.method<&Document::termlist_end>("termlist_end",{});
        cDocument.method<&Document::values_count>("values_count",{});
        cDocument.method<&Document::values_begin>("values_begin",{});
        cDocument.method<&Document::values_end>("values_end",{});
        //cDocument.method<&Document::m>("m");
        extension.add(std::move(cDocument));
    }
};


class MSetIterator: public Php::Base, public Xapian::MSetIterator {
    typedef Xapian::MSetIterator B;
public:
    MSetIterator():Xapian::MSetIterator(){}
    MSetIterator(const Xapian::MSetIterator &m):Xapian::MSetIterator(m){}
    Php::Value get_description(Php::Parameters &params){return Xapian::MSetIterator::get_description();}
    Php::Value equals(Php::Parameters& params){
        MSetIterator*other=dynamic_cast<MSetIterator*>(params[0].implementation());
        return *static_cast<Xapian::MSetIterator*>(this)==*static_cast<Xapian::MSetIterator*>(other);
    }
    void next(Php::Parameters& params){(*static_cast<Xapian::MSetIterator*>(this))++;}
    Php::Value get_docid(Php::Parameters& params){return (int32_t)*(*(B*)this);}
    Php::Value get_document(Php::Parameters& params){return Php::Object("XapianDocument",new Document(B::get_document()));}
    Php::Value get_weight(Php::Parameters& params){return (double)B::get_weight();}
    virtual ~MSetIterator(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<MSetIterator> cMSetIterator("XapianMSetIterator");
        cMSetIterator.method<&MSetIterator::get_description>("get_description",{});
        cMSetIterator.method<&MSetIterator::equals>("equals",{Php::ByVal("other","XapianMSetIterator")});
        cMSetIterator.method<&MSetIterator::next>("next",{});
        cMSetIterator.method<&MSetIterator::get_docid>("get_docid",{});
        cMSetIterator.method<&MSetIterator::get_document>("get_document",{});
        cMSetIterator.method<&MSetIterator::get_weight>("get_weight",{});
        extension.add(std::move(cMSetIterator));
    }
};

class MSet: public Php::Base, public Xapian::MSet {
public:
    MSet():Xapian::MSet(){}
    MSet(const Xapian::MSet &m):Xapian::MSet(m){}
    Php::Value get_description(Php::Parameters &params){return Xapian::MSet::get_description();}
    Php::Value size(Php::Parameters &params){return Php::Value((int32_t)Xapian::MSet::size());}
    Php::Value begin(Php::Parameters &params){return Php::Object("XapianMSetIterator",new MSetIterator(Xapian::MSet::begin()));}
    Php::Value end(Php::Parameters &params){return Php::Object("XapianMSetIterator",new MSetIterator(Xapian::MSet::end()));}
    virtual ~MSet(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<MSet> cMSet("XapianMSet");
        cMSet.method<&MSet::get_description>("get_description",{});
        cMSet.method<&MSet::size>("size");
        cMSet.method<&MSet::begin>("begin");
        cMSet.method<&MSet::end>("end");
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

class Parameters:public Php::Parameters {
public:
    Parameters(Php::Base*object):Php::Parameters(object){}
};

class MatchSpy: public Php::Base, public Xapian::MatchSpy {
public:
    
    MatchSpy():Xapian::MatchSpy(){
        
    }
    //MatchSpy(const Xapian::MatchSpy& e):Xapian::MatchSpy(e){}
    Php::Value get_description(Php::Parameters &params){return Xapian::MatchSpy::get_description();}
    virtual ~MatchSpy(){}
    void __construct(Php::Parameters &params){}
    void apply(Php::Parameters &params){}
    virtual void    operator() (const Xapian::Document &doc, double wt){
        Php::Array fn({this,"apply"});
        fn(Php::Object("XapianDocument",new Document(doc)), Php::Value(wt));
    }
    static void get_module_part(Php::Extension& extension){
        Php::Class<MatchSpy> cMatchSpy("XapianMatchSpy");
        cMatchSpy.method<&MatchSpy::__construct>("__construct",{});
        cMatchSpy.method<&MatchSpy::get_description>("get_description",{});
        cMatchSpy.method<&MatchSpy::apply>("apply",{Php::ByVal("doc"),Php::ByVal("wt")});
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
    void __construct(Php::Parameters &params){}
    Php::Value apply(Php::Parameters &params){return true;}
    virtual bool    operator() (const Xapian::Document &doc) const{
        Php::Array fn({this,"apply"});
        return fn(Php::Object("XapianDocument",new Document(doc))).boolValue();
    }
    virtual ~MatchDecider(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<MatchDecider> cMatchDecider("XapianMatchDecider");
        cMatchDecider.method<&MatchDecider::__construct>("__construct");
        cMatchDecider.method<&MatchDecider::apply>("apply",{Php::ByVal("doc")});
        extension.add(std::move(cMatchDecider));
    }
};


class Database: public Php::Base, public Xapian::Database {
    typedef Xapian::Database B;
public:
    Database():B(){}
    Database(const B&d):B(d){}
    Database(std::string path,int flags):B(path,flags){}
    void close(Php::Parameters &params){ B::close();}
    Php::Value get_doccount(Php::Parameters &params){ return (int64_t)B::get_doccount();}
    void add_database(Php::Parameters &params){
        Database*db=dynamic_cast<Database*>(params[0].implementation());
        B::add_database(*db);
    }
    Php::Value get_description(Php::Parameters &params){return B::get_description();}
    virtual ~Database(){}
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
    typedef Xapian::WritableDatabase B;
    std::shared_ptr<B> m;
public:
    WritableDatabase():B(){}
    WritableDatabase(const B&d):B(d){}
    /*WritableDatabase(std::string path,int flags):B(path,flags){
        Php::out << "WritableDatabase(std::string path,int flags)\n" << std::flush;
    }*/
    void __construct(Php::Parameters& params){
        if(params.size()>0){
            if(params[0].isObject()){
                *this = *dynamic_cast<WritableDatabase*>(params[0].implementation());
                return;    
            }
            std::string path = params[0].stringValue();
            int action=params.size()>1 ? params[1].numericValue() : 0;
            //Php::out << "WritableDatabase path=" << path << ", action=" << action << "\n" << std::flush;
            *this = B(path,action);
        }
    }    
    virtual ~WritableDatabase(){}
    void begin_transaction(Php::Parameters &params){ B::begin_transaction();}
    void cancel_transaction(Php::Parameters &params){ B::cancel_transaction();}
    void commit_transaction(Php::Parameters &params){ B::commit_transaction();}
    void commit(Php::Parameters &params){ B::commit();}
    void close(Php::Parameters &params){ B::close();}
    Php::Value get_doccount(Php::Parameters &params){ return (int64_t)B::get_doccount();}
    Php::Value get_description(Php::Parameters &params){return B::get_description();}
    void add_document(Php::Parameters &params){B::add_document(*dynamic_cast<Xapian::Document*>(params[0].implementation()));}

    static void get_module_part(Php::Extension& extension,Php::Class<::Database>& cDatabase){
        Php::Class<WritableDatabase> cWritableDatabase("XapianWritableDatabase");
        cWritableDatabase.method<&WritableDatabase::__construct>("__construct");
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
        cQuery.method<&Query::get_description>("get_description");
        extension.add(std::move(cQuery));
    }
};

class QueryParser: public Php::Base, public Xapian::QueryParser {
    typedef Xapian::QueryParser B;
public:
    QueryParser():Xapian::QueryParser(){}
    QueryParser(const Xapian::QueryParser&e):Xapian::QueryParser(e){}
    Php::Value get_description(Php::Parameters &params){return Xapian::QueryParser::get_description();}
    Php::Value parse_query(Php::Parameters& params){
        unsigned flags = params.size()>1 ? params[1].numericValue() : B::FLAG_DEFAULT;
        std::string prefix = params.size()>2 ? params[2].stringValue() : "";
        Query q=B::parse_query(params[0].stringValue(), flags, prefix);
        return Php::Object("XapianQuery", new Query(q));
    }
    Php::Value get_corrected_query_string(Php::Parameters& params){
        return B::get_corrected_query_string();
    }
    virtual ~QueryParser(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<QueryParser> cQueryParser("XapianQueryParser");
        cQueryParser.method<&QueryParser::parse_query>("parse_query");
        cQueryParser.method<&QueryParser::get_corrected_query_string>("get_corrected_query_string");
        extension.add(std::move(cQueryParser));
    }
};

class Enquire: public Php::Base {
protected:
    typedef Xapian::Enquire B;
    std::shared_ptr<Xapian::Enquire> m;
public:
    //Enquire(Database*db){m.reset(new Xapian::Enquire(*db));}
    Enquire(){}
    void __construct(Php::Parameters& params){
        if(params.size()<1) throw Php::Exception("Enquire ctor requires 1 arg");
        Enquire *enq = dynamic_cast<Enquire*>(params[0].implementation());
        if(enq) {
            m.reset(new Xapian::Enquire(*(enq->m)));
            return;
        }
        Database *db = dynamic_cast<Database*>(params[0].implementation());
        if(db) {
            m.reset(new Xapian::Enquire(*db));
            return;
        }
        WritableDatabase *wdb = dynamic_cast<WritableDatabase*>(params[0].implementation());
        if(wdb) {
            m.reset(new Xapian::Enquire(*wdb));
            return;
        }
        throw Php::Exception("Enquire ctor invalid arg");
    }

    virtual ~Enquire(){}
    Php::Value get_description(Php::Parameters &params){return m ? m->get_description():"null";}
    void set_query(Php::Parameters& params){m->set_query(*dynamic_cast<Xapian::Query*>(params[0].implementation()));}
    Php::Value get_query(Php::Parameters& params){
        Xapian::Query xq = m->get_query();
        return Php::Object("XapianQuery",new Query(xq));
    }
    Php::Value get_mset(Php::Parameters& params){
        if(params.size()<3) throw new Php::Exception("get_mset must have 3-5 args");
        //Php::out << "get_mset\n"<<std::flush;
        Xapian::doccount first=params[0].numericValue();
        Xapian::doccount maxitems=params[1].numericValue();
        Xapian::doccount checkatleast=params[2].numericValue();
        RSet* omrset = params.size()>3 ? dynamic_cast<RSet*>(params[3].implementation()) : NULL;
        MatchDecider* mdecider = params.size()>4 ? dynamic_cast<MatchDecider*>(params[4].implementation()) : NULL;
        Xapian::MSet mset=m->get_mset(first,maxitems,checkatleast,omrset,mdecider);
        //Php::out <<"mset size:"<<(((Xapian::MSet)mset).size())<<std::endl<<std::flush;
        return Php::Object("XapianMSet",new MSet(mset));
    }
    void add_matchspy(Php::Parameters& params){m->add_matchspy(dynamic_cast<MatchSpy*>(params[0].implementation()));}
    void clear_matchspies(Php::Parameters& params){m->clear_matchspies();}
    static void get_module_part(Php::Extension& extension){
        Php::Class<Enquire> cEnquire("XapianEnquire");
        cEnquire.method<&Enquire::__construct>("__construct");
        cEnquire.method<&Enquire::set_query>("set_query",{Php::ByVal("query","XapianQuery")});
        cEnquire.method<&Enquire::get_query>("get_query",{});
        cEnquire.method<&Enquire::get_mset>("get_mset");
        cEnquire.method<&Enquire::add_matchspy>("add_matchspy",{Php::ByVal("matchspy",Php::Type::Object)});
        cEnquire.method<&Enquire::clear_matchspies>("clear_matchspies");
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
        Xapian.constant("DB_CREATE_OR_OPEN", (int32_t)0x00);//    Create database if it doesn't already exist. 
        Xapian.constant("DB_CREATE_OR_OVERWRITE", (int32_t)0x01);//    Create database if it doesn't already exist, or overwrite if it does. 
        Xapian.constant("DB_CREATE", (int32_t)0x02);//    Create a new database. 
        Xapian.constant("DB_OPEN", (int32_t)0x03);//    Open an existing database. 
        Xapian.constant("DB_NO_SYNC", (int32_t)0x04);//    Don't attempt to ensure changes have hit disk. 
        Xapian.constant("DB_FULL_SYNC", (int32_t)0x08);//    Try to ensure changes are really written to disk. 
        Xapian.constant("DB_DANGEROUS", (int32_t)0x10);//    Update the database in-place. 
        Xapian.constant("DB_NO_TERMLIST", (int32_t)0x20);//    When creating a database, don't create a termlist table. 
        Xapian.constant("DB_RETRY_LOCK", (int32_t)0x40);//    If the database is already locked, retry the lock. 
        Xapian.constant("DB_BACKEND_GLASS", (int32_t)0x100);//    Use the glass backend. 
        Xapian.constant("DB_BACKEND_CHERT", (int32_t)0x200);//    Use the chert backend. 
        Xapian.constant("DB_BACKEND_STUB", (int32_t)0x300);//    Open a stub database file. 
        Xapian.constant("DB_BACKEND_INMEMORY", (int32_t)0x400);//    Use the "in memory" backend. 
        Xapian.constant("DBCHECK_SHORT_TREE", (int32_t)1);//    Show a short-format display of the B-tree contents. 
        Xapian.constant("DBCHECK_FULL_TREE", (int32_t)2);//    Show a full display of the B-tree contents. 
        Xapian.constant("DBCHECK_SHOW_FREELIST", (int32_t)4);//    Show the bitmap for the B-tree. 
        Xapian.constant("DBCHECK_SHOW_STATS", (int32_t)8);//    Show statistics for the B-tree. 
        Xapian.constant("DBCHECK_FIX", (int32_t)16);//    Fix problems. 
        Xapian.constant("DBCOMPACT_NO_RENUMBER", (int32_t)4);//    Use the same document ids in the output as in the input(s). 
        Xapian.constant("DBCOMPACT_MULTIPASS", (int32_t)8);//    If merging more than 3 databases, merge the postlists in multiple passes. 
        Xapian.constant("DBCOMPACT_SINGLE_FILE", (int32_t)16);//    Produce a single-file database. 
        Xapian.constant("BAD_VALUENO", (int32_t)0xffffffff);//    Reserved value to indicate "no valueno". 


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
        ValueIterator::get_module_part(extension);
        Stem::get_module_part(extension);
        Php::Class<Stopper> cStopper = Stopper::get_module_part(extension);
        SimpleStopper::get_module_part(extension, cStopper);
        TermGenerator::get_module_part(extension);
        Document::get_module_part(extension);
        MSet::get_module_part(extension);
        MSetIterator::get_module_part(extension);
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
