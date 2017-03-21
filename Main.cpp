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

class Weight: public Php::Base {
    typedef Xapian::Weight B;
public:
    virtual Xapian::Weight*getWeight() {return NULL;}
    static Php::Class<Weight> get_module_part(Php::Extension& extension){
        Php::Class<Weight> cWeight("XapianWeight");
        extension.add(std::move(cWeight));
        return cWeight;
    }
};

class BM25Weight: public Weight {
    typedef Xapian::BM25Weight B;
    std::shared_ptr<B> m;
public:
    BM25Weight(){m.reset(new B(1.,0.,1.,0.5,0.5));}
    BM25Weight(double k1,double k2,double k3,double b,double min_normlen){m.reset(new B(k1,k2,k3,b,min_normlen));}
    BM25Weight(const BM25Weight&other){m=other.m;}
    virtual ~BM25Weight(){m.reset();}
    virtual Xapian::Weight*getWeight(){return m.get();}
    void __construct(Php::Parameters &params) {
        *this=BM25Weight((double)params[0],(double)params[1],(double)params[2],(double)params[3],(double)params[4]);
    }
    static void get_module_part(Php::Extension& extension, Php::Class<Weight>cWeight){
        Php::Class<BM25Weight> cBM25Weight("XapianBM25Weight");
        cBM25Weight.method<&BM25Weight::__construct>("__construct",{Php::ByVal("k1",Php::Type::Float),Php::ByVal("k2",Php::Type::Float),Php::ByVal("k3",Php::Type::Float),Php::ByVal("b",Php::Type::Float),Php::ByVal("min_normlen",Php::Type::Float)});
        cBM25Weight.extends(cWeight);
        extension.add(std::move(cBM25Weight));
    }
};

class BM25PlusWeight: public Weight {
    typedef Xapian::BM25PlusWeight B;
    std::shared_ptr<B> m;
public:
    BM25PlusWeight(){m.reset(new B(1.,0.,1.,0.5,0.5,1.));}
    BM25PlusWeight(double k1,double k2,double k3,double b,double min_normlen,double delta){m.reset(new B(k1,k2,k3,b,min_normlen,delta));}
    BM25PlusWeight(const BM25PlusWeight&other){m=other.m;}
    virtual ~BM25PlusWeight(){m.reset();}
    virtual Xapian::Weight*getWeight(){return m.get();}
    void __construct(Php::Parameters &params) {
        *this=BM25PlusWeight((double)params[0],(double)params[1],(double)params[2],(double)params[3],(double)params[4],(double)params[5]);
    }
    static void get_module_part(Php::Extension& extension, Php::Class<Weight>cWeight){
        Php::Class<BM25PlusWeight> cBM25PlusWeight("XapianBM25PlusWeight");
        cBM25PlusWeight.method<&BM25PlusWeight::__construct>("__construct",{Php::ByVal("k1",Php::Type::Float),Php::ByVal("k2",Php::Type::Float),Php::ByVal("k3",Php::Type::Float),Php::ByVal("b",Php::Type::Float),Php::ByVal("min_normlen",Php::Type::Float),Php::ByVal("delta",Php::Type::Float)});
        cBM25PlusWeight.extends(cWeight);
        extension.add(std::move(cBM25PlusWeight));
    }
};

class BoolWeight: public Weight {
    typedef Xapian::BoolWeight B;
    std::shared_ptr<B> m;
public:
    BoolWeight(){m.reset(new B());}
    BoolWeight(const BoolWeight&other){m=other.m;}
    virtual ~BoolWeight(){m.reset();}
    virtual Xapian::Weight*getWeight(){return m.get();}
    void __construct(Php::Parameters &params) {
        *this=BoolWeight();
    }
    static void get_module_part(Php::Extension& extension, Php::Class<Weight>cWeight){
        Php::Class<BoolWeight> cBoolWeight("XapianBoolWeight");
        cBoolWeight.method<&BoolWeight::__construct>("__construct",{});
        cBoolWeight.extends(cWeight);
        extension.add(std::move(cBoolWeight));
    }
};

class TradWeight: public Weight {
    typedef Xapian::TradWeight B;
    std::shared_ptr<B> m;
public:
    TradWeight(){m.reset(new B(1.));}
    TradWeight(double k){m.reset(new B(k));}
    TradWeight(const TradWeight&other){m=other.m;}
    virtual ~TradWeight(){m.reset();}
    virtual Xapian::Weight*getWeight(){return m.get();}
    void __construct(Php::Parameters &params) {
        *this=TradWeight((double)params[0]);
    }
    static void get_module_part(Php::Extension& extension, Php::Class<Weight>cWeight){
        Php::Class<TradWeight> cTradWeight("XapianTradWeight");
        cTradWeight.method<&TradWeight::__construct>("__construct",{Php::ByVal("k",Php::Type::Float)});
        cTradWeight.extends(cWeight);
        extension.add(std::move(cTradWeight));
    }
};

class BB2Weight: public Weight {
    typedef Xapian::BB2Weight B;
    std::shared_ptr<B> m;
public:
    BB2Weight(){m.reset(new B(1.));}
    BB2Weight(double k){m.reset(new B(k));}
    BB2Weight(const BB2Weight&other){m=other.m;}
    virtual ~BB2Weight(){m.reset();}
    virtual Xapian::Weight*getWeight(){return m.get();}
    void __construct(Php::Parameters &params) {
        *this=BB2Weight((double)params[0]);
    }
    static void get_module_part(Php::Extension& extension, Php::Class<Weight>cWeight){
        Php::Class<BB2Weight> cBB2Weight("XapianBB2Weight");
        cBB2Weight.method<&BB2Weight::__construct>("__construct",{Php::ByVal("k",Php::Type::Float)});
        cBB2Weight.extends(cWeight);
        extension.add(std::move(cBB2Weight));
    }
};

class CoordWeight: public Weight {
    typedef Xapian::CoordWeight B;
    std::shared_ptr<B> m;
public:
    CoordWeight(){m.reset(new B());}
    CoordWeight(const CoordWeight&other){m=other.m;}
    virtual ~CoordWeight(){m.reset();}
    virtual Xapian::Weight*getWeight(){return m.get();}
    void __construct(Php::Parameters &params) {
        *this=CoordWeight();
    }
    static void get_module_part(Php::Extension& extension, Php::Class<Weight>cWeight){
        Php::Class<CoordWeight> cCoordWeight("XapianCoordWeight");
        cCoordWeight.method<&CoordWeight::__construct>("__construct",{});
        cCoordWeight.extends(cWeight);
        extension.add(std::move(cCoordWeight));
    }
};

class Compactor: public Php::Base {
    typedef Xapian::Compactor B;
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
    void set_compaction_level(Php::Parameters & params){m->set_compaction_level((B::compaction_level)params[0].numericValue());}
    virtual ~Compactor(){m=NULL;}
    static void get_module_part(Php::Extension& extension){
        Php::Class<Compactor> cCompactor("XapianCompactor");
        cCompactor.method<&Compactor::add_source>("add_source");
        cCompactor.method<&Compactor::set_destdir>("set_destdir");
        cCompactor.method<&Compactor::compact>("compact");
        cCompactor.method<&Compactor::set_compaction_level>("set_compaction_level",{Php::ByVal("compaction",Php::Type::Numeric)});
        cCompactor.constant("STANDARD",B::STANDARD);
        cCompactor.constant("FULL",B::FULL);
        cCompactor.constant("FULLER",B::FULLER);
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

class PositionIterator: public Php::Base, public Xapian::PositionIterator {
    typedef Xapian::PositionIterator B;
public:
    PositionIterator():Xapian::PositionIterator(){}
    PositionIterator(const B& i):B(i){}
    Php::Value get_description(Php::Parameters &params){return B::get_description();}
    Php::Value get_termpos(Php::Parameters &params){return (int32_t)**this; }
    void skip_to(Php::Parameters &params){B::skip_to(params[0].numericValue());}
    void next(Php::Parameters& params){(*static_cast<B*>(this))++;}
    Php::Value equals(Php::Parameters& params){
        PositionIterator *other=dynamic_cast<PositionIterator*>(params[0].implementation());
        return *static_cast<B*>(this)==*static_cast<B*>(other);
    }

    virtual ~PositionIterator(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<PositionIterator> cPositionIterator("XapianPositionIterator");
        cPositionIterator.method<&PositionIterator::get_description>("get_description",{});
        cPositionIterator.method<&PositionIterator::get_termpos>("get_termpos",{});
        cPositionIterator.method<&PositionIterator::skip_to>("skip_to",{Php::ByVal("termpos",Php::Type::Numeric)});
        cPositionIterator.method<&PositionIterator::next>("next",{});
        cPositionIterator.method<&PositionIterator::equals>("equals",{Php::ByVal("other","XapianPositionIterator")});
        extension.add(std::move(cPositionIterator));
    }
};

class PostingIterator: public Php::Base, public Xapian::PostingIterator {
    typedef Xapian::PostingIterator B;
public:
    PostingIterator():Xapian::PostingIterator(){}
    PostingIterator(const B& i):B(i){}
    Php::Value get_description(Php::Parameters &params){return B::get_description();}
    Php::Value get_docid(Php::Parameters &params){return (int32_t)**this; }
    Php::Value get_wdf(Php::Parameters &params){return (int32_t)B::get_wdf(); }
    Php::Value get_doclength(Php::Parameters &params){return (int32_t)B::get_doclength(); }
    Php::Value get_unique_terms(Php::Parameters &params){return (int32_t)B::get_unique_terms(); }
    Php::Value positionlist_begin(Php::Parameters &params){return Php::Object("XapianPositionIterator",new PositionIterator(B::positionlist_begin()));}
    Php::Value positionlist_end(Php::Parameters &params){return Php::Object("XapianPositionIterator",new PositionIterator(B::positionlist_end()));}
    void skip_to(Php::Parameters &params){B::skip_to(params[0].numericValue());}
    void next(Php::Parameters& params){(*static_cast<B*>(this))++;}
    Php::Value equals(Php::Parameters& params){
        PostingIterator *other=dynamic_cast<PostingIterator*>(params[0].implementation());
        return *static_cast<B*>(this)==*static_cast<B*>(other);
    }

    virtual ~PostingIterator(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<PostingIterator> cPostingIterator("XapianPostingIterator");
        cPostingIterator.method<&PostingIterator::get_description>("get_description",{});
        cPostingIterator.method<&PostingIterator::get_docid>("get_docid",{});
        cPostingIterator.method<&PostingIterator::get_wdf>("get_wdf",{});
        cPostingIterator.method<&PostingIterator::get_doclength>("get_doclength",{});
        cPostingIterator.method<&PostingIterator::get_unique_terms>("get_unique_terms",{});
        cPostingIterator.method<&PostingIterator::positionlist_begin>("positionlist_begin",{});
        cPostingIterator.method<&PostingIterator::positionlist_end>("positionlist_end",{});
        cPostingIterator.method<&PostingIterator::skip_to>("skip_to",{Php::ByVal("did",Php::Type::Numeric)});
        cPostingIterator.method<&PostingIterator::next>("next",{});
        cPostingIterator.method<&PostingIterator::equals>("equals",{Php::ByVal("other","XapianPostingIterator")});
        extension.add(std::move(cPostingIterator));
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
    Stopper():B(){}
    Php::Value get_description(Php::Parameters &params){return B::get_description();}
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
    SimpleStopper():B(){}
    //SimpleStopper(Php::Array words):Xapian::SimpleStopper(words.begin(),words.end()){}
    Php::Value get_description(Php::Parameters &params){return B::get_description();}
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
    Php::Value set_flags(Php::Parameters& params) { return B::set_flags(params[0].numericValue(),params.size()<2 ? 0: params[1].numericValue());}
    virtual ~TermGenerator(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<TermGenerator> cTermGenerator("XapianTermGenerator");
        cTermGenerator.method<&TermGenerator::get_description>("get_description",{});
        cTermGenerator.method<&TermGenerator::set_stemmer>("set_stemmer",{Php::ByVal("stem","XapianStem")});
        cTermGenerator.method<&TermGenerator::set_stopper>("set_stopper",{Php::ByVal("stopper",Php::Type::Object)});
        cTermGenerator.method<&TermGenerator::set_database>("set_database",{Php::ByVal("database","XapianWritableDatabase")});
        cTermGenerator.method<&TermGenerator::set_document>("set_document",{Php::ByVal("document","XapianDocument")});
        cTermGenerator.method<&TermGenerator::index_text>("index_text");
        cTermGenerator.method<&TermGenerator::set_flags>("set_flags",{Php::ByVal("flags",Php::Type::Numeric)});
        cTermGenerator.constant("FLAG_SPELLING",B::FLAG_SPELLING);
        cTermGenerator.constant("STEM_NONE",B::STEM_NONE); 
        cTermGenerator.constant("STEM_SOME",B::STEM_SOME); 
        cTermGenerator.constant("STEM_ALL",B::STEM_ALL);
        cTermGenerator.constant("STEM_ALL_Z",B::STEM_ALL_Z);
        cTermGenerator.constant("STOP_NONE",B::STOP_NONE);
        cTermGenerator.constant("STOP_ALL",B::STOP_ALL);
        cTermGenerator.constant("STOP_STEMMED",B::STOP_STEMMED);
        extension.add(std::move(cTermGenerator));
    }
};

class Document: public Php::Base, public Xapian::Document {
    typedef Xapian::Document B;
public:
    Document():Xapian::Document(){}
    Document(const Xapian::Document&d):Xapian::Document(d){}
    void __construct(Php::Parameters &params){*this=params.size()==0? B():*(B*)params[0].implementation();}
    Php::Value get_value(Php::Parameters& params) {
        return Php::Value(B::get_value(params[0].numericValue()));
    }
    void add_value(Php::Parameters &params){
        B::add_value(params[0].numericValue(),params[1].stringValue());
    }
    void remove_value(Php::Parameters& params) {
        B::remove_value(params[0].numericValue());
    }
    void clear_values(Php::Parameters& params){
        B::clear_values();
    }
    Php::Value get_data(Php::Parameters &params){return B::get_data();}
    void set_data(Php::Parameters &params){B::set_data(params[0]);}
    void add_posting(Php::Parameters &params){B::add_posting(params[0].stringValue(),params[1].numericValue(),params.size()<3 ? 1 : params[2].numericValue());}
    void add_term(Php::Parameters &params){B::add_term(params[0].stringValue(),params.size()<2 ? 1 : params[1].numericValue());}
    void add_boolean_term(Php::Parameters &params){B::add_boolean_term(params[0].stringValue());}
    void remove_posting(Php::Parameters &params){B::remove_posting(params[0].stringValue(),params[1].numericValue(),params.size()<3 ? 1 : params[2].numericValue());}
    void remove_term(Php::Parameters &params){B::remove_term(params[0].stringValue());}
    void clear_terms(Php::Parameters &params){B::clear_terms();}
    Php::Value termlist_count(Php::Parameters &params){return (int32_t)B::termlist_count();}
    Php::Value termlist_begin(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::termlist_begin()));}
    Php::Value termlist_end(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::termlist_end()));}
    Php::Value values_count(Php::Parameters &params){return (int32_t)B::values_count();}
    Php::Value values_begin(Php::Parameters &params){return Php::Object("XapianValueIterator",new ValueIterator(B::values_begin()));}
    Php::Value values_end(Php::Parameters &params){return Php::Object("XapianValueIterator",new ValueIterator(B::values_end()));}
    Php::Value get_docid(Php::Parameters &params){return (int32_t)B::get_docid();}
    Php::Value serialise(Php::Parameters &params){return B::serialise();}
    Php::Value get_description(Php::Parameters &params){return B::get_description();}
    static Php::Value Document_get_value(Php::Parameters& params){
        B*doc = dynamic_cast<B*>(params[0].implementation());
        return doc ? doc->get_value(params[1].numericValue()):"";
    }
    virtual ~Document(){}


    static void get_module_part(Php::Extension& extension){
        Php::Class<Document> cDocument("XapianDocument");
        cDocument.method<&Document::__construct>("__construct",{Php::ByVal("doc","XapianDocument",false)});
        cDocument.method<&Document::get_value>("get_value",{Php::ByVal("slot",Php::Type::Numeric)});
        cDocument.method<&Document::add_value>("add_value",{Php::ByVal("slot",Php::Type::Numeric),Php::ByVal("value",Php::Type::String)});
        cDocument.method<&Document::remove_value>("remove_value",{Php::ByVal("slot",Php::Type::Numeric)});
        cDocument.method<&Document::clear_values>("clear_values",{});
        cDocument.method<&Document::get_data>("get_data",{});
        cDocument.method<&Document::set_data>("set_data",{Php::ByVal("data",Php::Type::String)});
        cDocument.method<&Document::add_posting>("add_posting",{Php::ByVal("tname",Php::Type::String),Php::ByVal("tpos",Php::Type::Numeric),Php::ByVal("wdfinc",Php::Type::Numeric,false)});
        cDocument.method<&Document::add_term>("add_term",{Php::ByVal("term",Php::Type::String),Php::ByVal("wdfinc",Php::Type::Numeric,false)});
        cDocument.method<&Document::add_boolean_term>("add_boolean_term",{Php::ByVal("term",Php::Type::String)});
        cDocument.method<&Document::remove_posting>("remove_posting",{Php::ByVal("tname",Php::Type::String),Php::ByVal("tpos",Php::Type::Numeric),Php::ByVal("wdfdec",Php::Type::Numeric,false)});
        cDocument.method<&Document::remove_term>("remove_term",{Php::ByVal("term",Php::Type::String)});
        cDocument.method<&Document::clear_terms>("clear_terms",{});
        cDocument.method<&Document::termlist_count>("termlist_count",{});
        cDocument.method<&Document::termlist_begin>("termlist_begin",{});
        cDocument.method<&Document::termlist_end>("termlist_end",{});
        cDocument.method<&Document::values_count>("values_count",{});
        cDocument.method<&Document::values_begin>("values_begin",{});
        cDocument.method<&Document::values_end>("values_end",{});
        cDocument.method<&Document::get_docid>("get_docid",{});
        cDocument.method<&Document::serialise>("serialise",{});
        cDocument.method<&Document::get_description>("get_description",{});

        extension.add("Document_get_value",Document_get_value,{Php::ByVal("doc","XapianDocument"),Php::ByVal("slot",Php::Type::Numeric)}); 
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
    Php::Value get_rank(Php::Parameters& params){return (int32_t)B::get_rank();}
    Php::Value get_percent(Php::Parameters& params){return (int32_t)B::get_percent();}
    virtual ~MSetIterator(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<MSetIterator> cMSetIterator("XapianMSetIterator");
        cMSetIterator.method<&MSetIterator::get_description>("get_description",{});
        cMSetIterator.method<&MSetIterator::equals>("equals",{Php::ByVal("other","XapianMSetIterator")});
        cMSetIterator.method<&MSetIterator::next>("next",{});
        cMSetIterator.method<&MSetIterator::get_docid>("get_docid",{});
        cMSetIterator.method<&MSetIterator::get_document>("get_document",{});
        cMSetIterator.method<&MSetIterator::get_weight>("get_weight",{});
        cMSetIterator.method<&MSetIterator::get_rank>("get_rank",{});
        cMSetIterator.method<&MSetIterator::get_percent>("get_percent",{});
        extension.add(std::move(cMSetIterator));
    }
};

class MSet: public Php::Base, public Xapian::MSet {
    typedef Xapian::MSet B;
public:
    MSet():Xapian::MSet(){}
    MSet(const Xapian::MSet &m):Xapian::MSet(m){}
    Php::Value get_description(Php::Parameters &params){return Xapian::MSet::get_description();}
    Php::Value size(Php::Parameters &params){return Php::Value((int32_t)Xapian::MSet::size());}
    Php::Value get_matches_estimated(Php::Parameters &params){return Php::Value((int32_t)Xapian::MSet::get_matches_estimated());}
    Php::Value begin(Php::Parameters &params){return Php::Object("XapianMSetIterator",new MSetIterator(Xapian::MSet::begin()));}
    Php::Value end(Php::Parameters &params){return Php::Object("XapianMSetIterator",new MSetIterator(Xapian::MSet::end()));}
    Php::Value is_empty(Php::Parameters& params){return B::empty();}
    virtual ~MSet(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<MSet> cMSet("XapianMSet");
        cMSet.method<&MSet::get_description>("get_description",{});
        cMSet.method<&MSet::size>("size",{});
        cMSet.method<&MSet::get_matches_estimated>("get_matches_estimated",{});
        cMSet.method<&MSet::begin>("begin",{});
        cMSet.method<&MSet::end>("end",{});
        cMSet.method<&MSet::is_empty>("is_empty",{});
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

class ESetIterator: public Php::Base, public Xapian::ESetIterator {
    typedef Xapian::ESetIterator B;
public:
    ESetIterator():Xapian::ESetIterator(){}
    ESetIterator(const Xapian::ESetIterator& e):Xapian::ESetIterator(e){}
    Php::Value get_description(Php::Parameters &params){return Xapian::ESetIterator::get_description();}
    Php::Value get_weight(Php::Parameters &params){return Xapian::ESetIterator::get_weight();}
    Php::Value get_term(Php::Parameters &params){return **this;}
    Php::Value equals(Php::Parameters &params){
        return *(B*)this==*(B*)dynamic_cast<ESetIterator*>(params[0].implementation());
    }
    void next(Php::Parameters& params){(*this)++;}
    virtual ~ESetIterator(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<ESetIterator> cESetIterator("XapianESetIterator");
        cESetIterator.method<&ESetIterator::get_description>("get_description",{});
        cESetIterator.method<&ESetIterator::get_weight>("get_weight",{});
        cESetIterator.method<&ESetIterator::get_term>("get_term",{});
        cESetIterator.method<&ESetIterator::equals>("equals",{});
        cESetIterator.method<&ESetIterator::next>("next",{});
        extension.add(std::move(cESetIterator));
    }
};

class ESet: public Php::Base, public Xapian::ESet {
public:
    ESet():Xapian::ESet(){}
    ESet(const Xapian::ESet& e):Xapian::ESet(e){}
    Php::Value size(Php::Parameters &params){return (int32_t)Xapian::ESet::size();}
    Php::Value get_description(Php::Parameters &params){return Xapian::ESet::get_description();}
    Php::Value begin(Php::Parameters &params){return Php::Object("XapianESetIterator",new ESetIterator(Xapian::ESet::begin()));}
    Php::Value end(Php::Parameters &params){return Php::Object("XapianESetIterator",new ESetIterator(Xapian::ESet::end()));}

    virtual ~ESet(){}

    static void get_module_part(Php::Extension& extension){
        Php::Class<ESet> cESet("XapianESet");
        cESet.method<&ESet::get_description>("get_description",{});
        cESet.method<&ESet::size>("size",{});
        cESet.method<&ESet::begin>("begin",{});
        cESet.method<&ESet::end>("end",{});
        extension.add(std::move(cESet));
    }
};


class Parameters:public Php::Parameters {
public:
    Parameters(Php::Base*object):Php::Parameters(object){}
};

class MatchSpy: public Php::Base {
public:
    
    MatchSpy(){
        
    }
    //MatchSpy(const Xapian::MatchSpy& e):Xapian::MatchSpy(e){}
    Php::Value get_description(Php::Parameters &params){return "MatchSpy";}
    virtual ~MatchSpy(){}
    virtual Xapian::MatchSpy*getMatchSpy() {return NULL;}
    void __construct(Php::Parameters &params){}
    void apply(Php::Parameters &params){}
    virtual void    operator() (const Xapian::Document &doc, double wt){
        Php::Array fn({this,"apply"});
        fn(Php::Object("XapianDocument",new Document(doc)), Php::Value(wt));
    }
    static Php::Class<MatchSpy> get_module_part(Php::Extension& extension){
        Php::Class<MatchSpy> cMatchSpy("XapianMatchSpy");
        cMatchSpy.method<&MatchSpy::__construct>("__construct",{});
        cMatchSpy.method<&MatchSpy::get_description>("get_description",{});
        cMatchSpy.method<&MatchSpy::apply>("apply",{Php::ByVal("doc"),Php::ByVal("wt")});
        extension.add(std::move(cMatchSpy));
        return cMatchSpy;
    }
};

class ValueCountMatchSpy: public MatchSpy {
    typedef Xapian::ValueCountMatchSpy B;
    Xapian::valueno slot;
    std::shared_ptr<B> m;
public:
    ValueCountMatchSpy():slot(Xapian::BAD_VALUENO){m.reset(new B(slot));}
    ValueCountMatchSpy(Xapian::valueno _slot):slot(_slot){m.reset(new B(_slot));}
    virtual ~ValueCountMatchSpy(){m.reset();}
    virtual Xapian::MatchSpy*getMatchSpy() {return m.get();}
    void __construct(Php::Parameters &params){
        m.reset(new B((Xapian::valueno)params[0].numericValue()));
    }
    Php::Value get_description(Php::Parameters &params){return m->get_description();}
    Php::Value get_total(Php::Parameters& params){
        return (int32_t)m->get_total();}
    Php::Value values_begin(Php::Parameters& params){return Php::Object("XapianTermIterator",new TermIterator(m->values_begin()));}
    Php::Value values_end(Php::Parameters& params){return Php::Object("XapianTermIterator",new TermIterator(m->values_end()));}
    Php::Value top_values_begin(Php::Parameters& params){return Php::Object("XapianTermIterator",new TermIterator(m->top_values_begin(params[0].numericValue())));}
    Php::Value top_values_end(Php::Parameters& params){return Php::Object("XapianTermIterator",new TermIterator(m->top_values_end(params[0].numericValue())));}
    Php::Value name(Php::Parameters& params){return m->name();}
    virtual void    operator() (const Xapian::Document &doc, double wt){
        (*m.get())(doc,wt);
        Php::Array fn({this,"apply"});
        if(fn.isCallable())
            fn(Php::Object("XapianDocument",new Document(doc)), Php::Value(wt));
    }
    void apply(Php::Parameters & params){
        Xapian::Document * doc=dynamic_cast<Xapian::Document*>(params[0].implementation());
        if(doc) {
            (*m.get())(*doc,params.size()<2 ? 1. : params[1].floatValue());
        }
    }
    static void ValueCountMatchSpy_apply(Php::Parameters& params){
        ValueCountMatchSpy *spy=dynamic_cast<ValueCountMatchSpy*>(params[0].implementation());
        Xapian::Document*doc=dynamic_cast<Xapian::Document*>(params[1].implementation());
        double wt = params.size()<3 ? 1. : params[2].floatValue();
        if(spy && doc) (*spy)(*doc,wt);
    }

    static void get_module_part(Php::Extension& extension,Php::Class<::MatchSpy>& cMatchSpy){
        Php::Class<ValueCountMatchSpy> cValueCountMatchSpy("XapianValueCountMatchSpy");
        cValueCountMatchSpy.method<&ValueCountMatchSpy::__construct>("__construct",{Php::ByVal("valueno",Php::Type::Numeric)});
        cValueCountMatchSpy.method<&ValueCountMatchSpy::get_description>("get_description",{});
        cValueCountMatchSpy.method<&ValueCountMatchSpy::get_total>("get_total",{});
        cValueCountMatchSpy.method<&ValueCountMatchSpy::values_begin>("values_begin",{});
        cValueCountMatchSpy.method<&ValueCountMatchSpy::values_end>("values_end",{});
        cValueCountMatchSpy.method<&ValueCountMatchSpy::top_values_begin>("top_values_begin",{Php::ByVal("maxitems",Php::Type::Numeric)});
        cValueCountMatchSpy.method<&ValueCountMatchSpy::top_values_end>("top_values_end",{Php::ByVal("maxitems",Php::Type::Numeric)});
        cValueCountMatchSpy.method<&ValueCountMatchSpy::name>("name",{});
        cValueCountMatchSpy.method<&ValueCountMatchSpy::apply>("apply",{Php::ByVal("doc","XapianDocument"),Php::ByVal("wt",Php::Type::Numeric,false)});
        cValueCountMatchSpy.extends(cMatchSpy);
        extension.add("ValueCountMatchSpy_apply",ValueCountMatchSpy_apply,{Php::ByVal("spy","XapianValueCountMatchSpy"),Php::ByVal("doc","XapianDocument"),Php::ByVal("wt",Php::Type::Numeric,false)});
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

class Database: public Php::Base , public Xapian::Database {
    typedef Xapian::Database B;
public:
    Database():B(){}
    Database(const B&db):B(db){}
    void __construct(Php::Parameters &params){
        Database *db = dynamic_cast<Database*>(params[0].implementation());
        if(db) {
            *this=*db;
            return;
        }
        *this = B(params[0].stringValue(),params.size()<2 ? 0 : params[1].numericValue());
    }
    void add_database(Php::Parameters &params){
        try {
            {
                Xapian::Database*db=dynamic_cast<Xapian::Database*>(params[0].implementation());
                if(db) {B::add_database(*db);return;}
            }
            throw Php::Exception("add_database: invalid arg");
        }catch(Xapian::Error e){
            throw new Php::Exception(std::string(e.get_type())+" "+e.get_msg());
        }
    }
    Php::Value reopen(Php::Parameters &params){
        try{
            return B::reopen();
        }catch(Xapian::Error e){
            throw new Php::Exception(std::string(e.get_type())+" "+e.get_msg());
        }
    }
    void close(Php::Parameters &params){ B::close();}
    Php::Value get_description(Php::Parameters &params){return B::get_description();}
    Php::Value postlist_begin(Php::Parameters &params){return Php::Object("XapianPostingIterator",new PostingIterator(B::postlist_begin(params[0].stringValue())));}
    Php::Value postlist_end(Php::Parameters &params){return Php::Object("XapianPostingIterator",new PostingIterator(B::postlist_end(params[0].stringValue())));}
    Php::Value termlist_end(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::termlist_end(params[0].numericValue())));}
    Php::Value termlist_begin(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::termlist_begin(params[0].numericValue())));}
    Php::Value has_positions(Php::Parameters &params){ return B::has_positions();}
    Php::Value positionlist_begin(Php::Parameters &params){return Php::Object("XapianPositionIterator",new PositionIterator(B::positionlist_begin(params[0].numericValue(),params[1].stringValue())));}
    Php::Value positionlist_end(Php::Parameters &params){return Php::Object("XapianPositionIterator",new PositionIterator(B::positionlist_end(params[0].numericValue(),params[1].stringValue())));}
    Php::Value get_doccount(Php::Parameters &params){ return (int64_t)B::get_doccount();}
    Php::Value get_lastdocid(Php::Parameters &params){ return (int64_t)B::get_lastdocid();}
    Php::Value get_avlength(Php::Parameters &params){ return (int32_t)B::get_avlength();}
    Php::Value get_termfreq(Php::Parameters &params){ return (int32_t)B::get_termfreq(params[0].stringValue());}
    Php::Value term_exists(Php::Parameters &params){ return B::term_exists(params[0].stringValue());}
    Php::Value get_collection_freq(Php::Parameters &params){ return (int32_t)B::get_collection_freq(params[0].stringValue());}
    Php::Value get_value_freq(Php::Parameters &params){ return (int32_t)B::get_value_freq(params[0].numericValue());}
    Php::Value get_value_lower_bound(Php::Parameters &params){ return B::get_value_lower_bound(params[0].numericValue());}
    Php::Value get_value_upper_bound(Php::Parameters &params){ return B::get_value_upper_bound(params[0].numericValue());}
    Php::Value get_doclength_lower_bound(Php::Parameters &params){ return (int32_t)B::get_doclength_lower_bound();}
    Php::Value get_doclength_upper_bound(Php::Parameters &params){ return (int32_t)B::get_doclength_upper_bound();}
    Php::Value get_wdf_upper_bound(Php::Parameters &params){ return (int32_t)B::get_wdf_upper_bound(params[0].stringValue());}
    Php::Value valuestream_begin(Php::Parameters &params){return Php::Object("XapianValueIterator",new ValueIterator(B::valuestream_begin(params[0].numericValue())));}
    Php::Value valuestream_end(Php::Parameters &params){return Php::Object("XapianValueIterator",new ValueIterator(B::valuestream_end(params[0].numericValue())));}
    Php::Value get_doclength(Php::Parameters &params){return (int32_t)B::get_doclength(params[0].numericValue());}
    Php::Value get_unique_terms(Php::Parameters &params){return (int32_t)B::get_unique_terms(params[0].numericValue());}
    Php::Value get_document(Php::Parameters &params){return Php::Object("XapianDocument",new Document(B::get_document(params[0].numericValue(), params.size()<2 ? 0 : params[1].numericValue())));}
    Php::Value get_spelling_suggestion(Php::Parameters &params){return B::get_spelling_suggestion(params[0].stringValue(), params.size()<2 ? 2 : params[1].numericValue());}
    Php::Value spellings_end(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::spellings_end()));}
    Php::Value spellings_begin(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::spellings_begin()));}
    Php::Value synonyms_end(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::synonyms_end(params[0].stringValue())));}
    Php::Value synonyms_begin(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::synonyms_begin(params[0].stringValue())));}
    Php::Value synonym_keys_end(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::synonym_keys_end(params[0].stringValue())));}
    Php::Value synonym_keys_begin(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::synonym_keys_begin(params[0].stringValue())));}
    Php::Value get_metadata(Php::Parameters &params){return B::get_metadata(params[0].stringValue());}
    Php::Value get_uuid(Php::Parameters &params){return B::get_uuid();}
    Php::Value get_revision(Php::Parameters &params){return (int64_t)B::get_revision();}
    Php::Value metadata_keys_end(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::metadata_keys_end(params[0].stringValue())));}
    Php::Value metadata_keys_begin(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::metadata_keys_begin(params[0].stringValue())));}
    Php::Value allterms_end(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::allterms_end(params[0].stringValue())));}
    Php::Value allterms_begin(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::allterms_begin(params[0].stringValue())));}
    void compact(Php::Parameters & params) {
        Xapian::Compactor c;
        B::compact(
            params[0].stringValue(),
            params.size()<2 ? 0 : params[1].numericValue(),
            params.size()<3 ? 0 : params[2].numericValue(),
            params.size()<4 ? c : *dynamic_cast<Xapian::Compactor*>(params[3].implementation())
            );
    }
    virtual ~Database(){}
    static Php::Class<Database>  get_module_part(Php::Extension& extension){
        Php::Class<Database> cDatabase("XapianDatabase");
        cDatabase.method<&Database::__construct>("__construct",{Php::ByVal("enquireOrDatabase")});
        cDatabase.method<&Database::add_database>("add_database");
        cDatabase.method<&Database::reopen>("reopen",{});
        cDatabase.method<&Database::close>("close",{});
        cDatabase.method<&Database::get_description>("get_description",{});
        cDatabase.method<&Database::postlist_end>("postlist_end",{Php::ByVal("tname",Php::Type::String)});
        cDatabase.method<&Database::postlist_begin>("postlist_begin",{Php::ByVal("tname",Php::Type::String)});
        cDatabase.method<&Database::termlist_end>("termlist_end",{Php::ByVal("did",Php::Type::Numeric)});
        cDatabase.method<&Database::termlist_begin>("termlist_begin",{Php::ByVal("did",Php::Type::Numeric)});
        cDatabase.method<&Database::has_positions>("has_positions",{});
        cDatabase.method<&Database::positionlist_end>("positionlist_end",{Php::ByVal("did",Php::Type::Numeric),Php::ByVal("tname",Php::Type::String)});
        cDatabase.method<&Database::positionlist_begin>("positionlist_begin",{Php::ByVal("did",Php::Type::Numeric),Php::ByVal("tname",Php::Type::String)});
        cDatabase.method<&Database::get_doccount>("get_doccount",{});
        cDatabase.method<&Database::get_lastdocid>("get_lastdocid",{});
        cDatabase.method<&Database::get_avlength>("get_avlength",{});
        cDatabase.method<&Database::get_termfreq>("get_termfreq",{Php::ByVal("term",Php::Type::String)});
        cDatabase.method<&Database::term_exists>("term_exists",{Php::ByVal("term",Php::Type::String)});
        cDatabase.method<&Database::get_collection_freq>("get_collection_freq",{Php::ByVal("term",Php::Type::String)});
        cDatabase.method<&Database::get_value_freq>("get_value_freq",{Php::ByVal("term",Php::Type::Numeric)});
        cDatabase.method<&Database::get_value_lower_bound>("get_value_lower_bound",{Php::ByVal("slot",Php::Type::Numeric)});
        cDatabase.method<&Database::get_value_upper_bound>("get_value_upper_bound",{Php::ByVal("slot",Php::Type::Numeric)});
        cDatabase.method<&Database::get_doclength_lower_bound>("get_doclength_lower_bound",{});
        cDatabase.method<&Database::get_doclength_upper_bound>("get_doclength_upper_bound",{});
        cDatabase.method<&Database::get_wdf_upper_bound>("get_wdf_upper_bound",{Php::ByVal("term",Php::Type::String)});
        cDatabase.method<&Database::valuestream_begin>("valuestream_begin",{Php::ByVal("slot",Php::Type::Numeric)});
        cDatabase.method<&Database::valuestream_end>("valuestream_end",{Php::ByVal("slot",Php::Type::Numeric)});
        cDatabase.method<&Database::get_doclength>("get_doclength",{Php::ByVal("did",Php::Type::Numeric)});
        cDatabase.method<&Database::get_unique_terms>("get_unique_terms",{Php::ByVal("did",Php::Type::Numeric)});
        cDatabase.method<&Database::get_document>("get_document",{Php::ByVal("did",Php::Type::Numeric),{Php::ByVal("flags",Php::Type::Numeric,false)}});
        cDatabase.method<&Database::get_spelling_suggestion>("get_spelling_suggestion",{Php::ByVal("word",Php::Type::String),Php::ByVal("max_edit_distance",Php::Type::Numeric,false)});
        cDatabase.method<&Database::spellings_end>("spellings_end",{});
        cDatabase.method<&Database::spellings_begin>("spellings_begin",{});
        cDatabase.method<&Database::synonyms_end>("synonyms_end",{Php::ByVal("value",Php::Type::String)});
        cDatabase.method<&Database::synonyms_begin>("synonyms_begin",{Php::ByVal("value",Php::Type::String)});
        cDatabase.method<&Database::synonym_keys_end>("synonym_keys_end",{Php::ByVal("value",Php::Type::String)});
        cDatabase.method<&Database::synonym_keys_begin>("synonym_keys_begin",{Php::ByVal("value",Php::Type::String)});
        cDatabase.method<&Database::get_metadata>("get_metadata",{Php::ByVal("value",Php::Type::String)});
        cDatabase.method<&Database::get_uuid>("get_uuid",{});
        cDatabase.method<&Database::get_revision>("get_revision",{});
        cDatabase.method<&Database::metadata_keys_end>("metadata_keys_end",{Php::ByVal("value",Php::Type::String)});
        cDatabase.method<&Database::metadata_keys_begin>("metadata_keys_begin",{Php::ByVal("value",Php::Type::String)});
        cDatabase.method<&Database::allterms_end>("allterms_end",{Php::ByVal("value",Php::Type::String)});
        cDatabase.method<&Database::allterms_begin>("allterms_begin",{Php::ByVal("value",Php::Type::String)});
        cDatabase.method<&Database::compact>("compact",{Php::ByVal("destdir",Php::Type::String)});
        extension.add(std::move(cDatabase));
        return cDatabase;
    }
};

class WritableDatabase: public Php::Base, public Xapian::WritableDatabase {
    typedef Xapian::WritableDatabase B;
public:
    WritableDatabase():B(){}
    WritableDatabase(const B&d):B(d){}
    void __construct(Php::Parameters& params){
        if(params.size()>0){
            if(params[0].isObject()){
                *this = *dynamic_cast<WritableDatabase*>(params[0].implementation());
                return;    
            }
            std::string path = params[0].stringValue();
            int action=params.size()>1 ? params[1].numericValue() : 0;
            *this = B(path,action);
        }
    }    
    virtual ~WritableDatabase(){}
    void add_database(Php::Parameters &params){
        try {
            {
                Xapian::Database*db=dynamic_cast<Xapian::Database*>(params[0].implementation());
                if(db) {B::add_database(*db);return;}
            }
            throw Php::Exception("add_database: invalid arg");
        }catch(Xapian::Error e){
            throw new Php::Exception(std::string(e.get_type())+" "+e.get_msg());
        }
    }
    void commit(){ B::commit();}
    void flush(){ B::flush();}
    void begin_transaction(){ B::begin_transaction();}
    void commit_transaction(){ B::commit_transaction();}
    void cancel_transaction(){ B::cancel_transaction();}
    void add_document(Php::Parameters &params){B::add_document(*dynamic_cast<Xapian::Document*>(params[0].implementation()));}
    void delete_document(Php::Parameters & params){
        try {
            if(params[0].isNumeric()) B::delete_document((Xapian::docid)params[0].numericValue());
            B::delete_document(params[0].stringValue());
        }catch(Xapian::DocNotFoundError e){}
    }
    Php::Value replace_document(Php::Parameters &params){
        if(params[0].isNumeric())  {
            B::replace_document((Xapian::docid)params[0].numericValue(),*dynamic_cast<Document*>(params[1].implementation()));
            return 0;
        }
        return (int32_t)B::replace_document(params[0].stringValue(),*dynamic_cast<Document*>(params[1].implementation()));
    }
    void add_spelling(Php::Parameters &params){B::add_spelling(params[0].stringValue(),params.size()<2 ? 1 : params[1].numericValue());}
    void remove_spelling(Php::Parameters &params){B::remove_spelling(params[0].stringValue(),params.size()<2 ? 1 : params[1].numericValue());}
    void add_synonym(Php::Parameters &params){B::add_synonym(params[0].stringValue(),params[1].stringValue());}
    void remove_synonym(Php::Parameters &params){B::remove_synonym(params[0].stringValue(),params[1].stringValue());}
    void clear_synonyms(Php::Parameters &params){B::clear_synonyms(params[0].stringValue());}
    void set_metadata(Php::Parameters & params){B::set_metadata(params[0].stringValue(),params[1].stringValue());}
    void close(){ B::close();}
    Php::Value get_description(){return B::get_description();}
    Php::Value postlist_begin(Php::Parameters &params){return Php::Object("XapianPostingIterator",new PostingIterator(B::postlist_begin(params[0].stringValue())));}
    Php::Value postlist_end(Php::Parameters &params){return Php::Object("XapianPostingIterator",new PostingIterator(B::postlist_end(params[0].stringValue())));}
    Php::Value termlist_end(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::termlist_end(params[0].numericValue())));}
    Php::Value termlist_begin(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::termlist_begin(params[0].numericValue())));}
    Php::Value has_positions(){ return B::has_positions();}
    Php::Value positionlist_begin(Php::Parameters &params){return Php::Object("XapianPositionIterator",new PositionIterator(B::positionlist_begin(params[0].numericValue(),params[1].stringValue())));}
    Php::Value positionlist_end(Php::Parameters &params){return Php::Object("XapianPositionIterator",new PositionIterator(B::positionlist_end(params[0].numericValue(),params[1].stringValue())));}
    Php::Value get_doccount(){ return (int64_t)B::get_doccount();}
    Php::Value get_lastdocid(){ return (int64_t)B::get_lastdocid();}
    Php::Value get_avlength(){ return (int32_t)B::get_avlength();}
    Php::Value get_termfreq(Php::Parameters &params){ return (int32_t)B::get_termfreq(params[0].stringValue());}
    Php::Value term_exists(Php::Parameters &params){ return B::term_exists(params[0].stringValue());}
    Php::Value get_collection_freq(Php::Parameters &params){ return (int32_t)B::get_collection_freq(params[0].stringValue());}
    Php::Value get_value_freq(Php::Parameters &params){ return (int32_t)B::get_value_freq(params[0].numericValue());}
    Php::Value get_value_lower_bound(Php::Parameters &params){ return B::get_value_lower_bound(params[0].numericValue());}
    Php::Value get_value_upper_bound(Php::Parameters &params){ return B::get_value_upper_bound(params[0].numericValue());}
    Php::Value get_doclength_lower_bound(){ return (int32_t)B::get_doclength_lower_bound();}
    Php::Value get_doclength_upper_bound(){ return (int32_t)B::get_doclength_upper_bound();}
    Php::Value get_wdf_upper_bound(Php::Parameters &params){ return (int32_t)B::get_wdf_upper_bound(params[0].stringValue());}
    Php::Value valuestream_begin(Php::Parameters &params){return Php::Object("XapianValueIterator",new ValueIterator(B::valuestream_begin(params[0].numericValue())));}
    Php::Value valuestream_end(Php::Parameters &params){return Php::Object("XapianValueIterator",new ValueIterator(B::valuestream_end(params[0].numericValue())));}
    Php::Value get_doclength(Php::Parameters &params){return (int32_t)B::get_doclength(params[0].numericValue());}
    Php::Value get_unique_terms(Php::Parameters &params){return (int32_t)B::get_unique_terms(params[0].numericValue());}
    Php::Value get_document(Php::Parameters &params){return Php::Object("XapianDocument",new Document(B::get_document(params[0].numericValue(), params.size()<2 ? 0 : params[1].numericValue())));}
    Php::Value get_spelling_suggestion(Php::Parameters &params){return B::get_spelling_suggestion(params[0].stringValue(), params.size()<2 ? 2 : params[1].numericValue());}
    Php::Value spellings_end(){return Php::Object("XapianTermIterator",new TermIterator(B::spellings_end()));}
    Php::Value spellings_begin(){return Php::Object("XapianTermIterator",new TermIterator(B::spellings_begin()));}
    Php::Value synonyms_end(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::synonyms_end(params[0].stringValue())));}
    Php::Value synonyms_begin(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::synonyms_begin(params[0].stringValue())));}
    Php::Value synonym_keys_end(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::synonym_keys_end(params[0].stringValue())));}
    Php::Value synonym_keys_begin(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::synonym_keys_begin(params[0].stringValue())));}

    Php::Value get_metadata(Php::Parameters &params){return (B::get_metadata(params[0].stringValue()));}
    Php::Value get_uuid(){return B::get_uuid();}
    Php::Value get_revision(){return (int64_t)B::get_revision();}
    Php::Value metadata_keys_end(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::metadata_keys_end(params[0].stringValue())));}
    Php::Value metadata_keys_begin(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::metadata_keys_begin(params[0].stringValue())));}

    Php::Value allterms_end(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::allterms_end(params[0].stringValue())));}
    Php::Value allterms_begin(Php::Parameters &params){return Php::Object("XapianTermIterator",new TermIterator(B::allterms_begin(params[0].stringValue())));}
    void compact(Php::Parameters & params) {
        Xapian::Compactor c;
        B::compact(
            params[0].stringValue(),
            params.size()<2 ? 0 : params[1].numericValue(),
            params.size()<3 ? 0 : params[2].numericValue(),
            params.size()<4 ? c : *dynamic_cast<Xapian::Compactor*>(params[3].implementation())
            );
    }
    Php::Value reopen(Php::Parameters &params){return B::reopen();}
    static void get_module_part(Php::Extension& extension,Php::Class<::Database>& cDatabase){
        Php::Class<WritableDatabase> cWritableDatabase("XapianWritableDatabase");
        cWritableDatabase.method<&WritableDatabase::__construct>("__construct");
        cWritableDatabase.method<&WritableDatabase::add_database>("add_database",{Php::ByVal("db",Php::Type::Object)});
        cWritableDatabase.method<&WritableDatabase::commit>("commit",{});
        cWritableDatabase.method<&WritableDatabase::flush>("flush",{});
        cWritableDatabase.method<&WritableDatabase::begin_transaction>("begin_transaction",{});
        cWritableDatabase.method<&WritableDatabase::commit_transaction>("commit_transaction",{});
        cWritableDatabase.method<&WritableDatabase::cancel_transaction>("cancel_transaction",{});
        cWritableDatabase.method<&WritableDatabase::add_document>("add_document",{Php::ByVal("doc","XapianDocument")});
        cWritableDatabase.method<&WritableDatabase::delete_document>("delete_document",{Php::ByVal("docIdOrUniqueTerm")});
        cWritableDatabase.method<&WritableDatabase::replace_document>("replace_document",{Php::ByVal("docIdOrUniqueTerm"),Php::ByVal("doc","XapianDocument")});
        cWritableDatabase.method<&WritableDatabase::add_spelling>("add_spelling",{Php::ByVal("word",Php::Type::String),Php::ByVal("freqinc",Php::Type::Numeric,false)});
        cWritableDatabase.method<&WritableDatabase::remove_spelling>("remove_spelling",{Php::ByVal("word",Php::Type::String),Php::ByVal("freqinc",Php::Type::Numeric,false)});
        cWritableDatabase.method<&WritableDatabase::add_synonym>("add_synonym",{Php::ByVal("term",Php::Type::String),Php::ByVal("synonym",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::remove_synonym>("remove_synonym",{Php::ByVal("term",Php::Type::String),Php::ByVal("synonym",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::clear_synonyms>("clear_synonyms",{Php::ByVal("term",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::set_metadata>("set_metadata",{Php::ByVal("key",Php::Type::String),Php::ByVal("value",Php::Type::String)});
        
        cWritableDatabase.method<&WritableDatabase::reopen>("reopen",{});
        cWritableDatabase.method<&WritableDatabase::close>("close",{});
        cWritableDatabase.method<&WritableDatabase::get_description>("get_description");
        cWritableDatabase.method<&WritableDatabase::postlist_end>("postlist_end",{Php::ByVal("tname",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::postlist_begin>("postlist_begin",{Php::ByVal("tname",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::termlist_end>("termlist_end",{Php::ByVal("did",Php::Type::Numeric)});
        cWritableDatabase.method<&WritableDatabase::termlist_begin>("termlist_begin",{Php::ByVal("did",Php::Type::Numeric)});
        cWritableDatabase.method<&WritableDatabase::positionlist_end>("positionlist_end",{Php::ByVal("did",Php::Type::Numeric),Php::ByVal("tname",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::positionlist_begin>("positionlist_begin",{Php::ByVal("did",Php::Type::Numeric),Php::ByVal("tname",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::get_uuid>("get_uuid",{});
        cWritableDatabase.method<&WritableDatabase::get_revision>("get_revision",{});
        cWritableDatabase.method<&WritableDatabase::has_positions>("has_positions",{});
        cWritableDatabase.method<&WritableDatabase::get_doccount>("get_doccount",{});
        cWritableDatabase.method<&WritableDatabase::get_lastdocid>("get_lastdocid",{});
        cWritableDatabase.method<&WritableDatabase::get_avlength>("get_avlength",{});
        cWritableDatabase.method<&WritableDatabase::get_termfreq>("get_termfreq",{Php::ByVal("term",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::term_exists>("term_exists",{Php::ByVal("term",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::get_collection_freq>("get_collection_freq",{Php::ByVal("term",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::get_value_freq>("get_value_freq",{Php::ByVal("term",Php::Type::Numeric)});
        cWritableDatabase.method<&WritableDatabase::get_value_lower_bound>("get_value_lower_bound",{Php::ByVal("slot",Php::Type::Numeric)});
        cWritableDatabase.method<&WritableDatabase::get_value_upper_bound>("get_value_upper_bound",{Php::ByVal("slot",Php::Type::Numeric)});
        cWritableDatabase.method<&WritableDatabase::get_doclength_lower_bound>("get_doclength_lower_bound",{});
        cWritableDatabase.method<&WritableDatabase::get_doclength_upper_bound>("get_doclength_upper_bound",{});
        cWritableDatabase.method<&WritableDatabase::get_wdf_upper_bound>("get_wdf_upper_bound",{Php::ByVal("term",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::valuestream_begin>("valuestream_begin",{Php::ByVal("slot",Php::Type::Numeric)});
        cWritableDatabase.method<&WritableDatabase::valuestream_end>("valuestream_end",{Php::ByVal("slot",Php::Type::Numeric)});
        cWritableDatabase.method<&WritableDatabase::get_doclength>("get_doclength",{Php::ByVal("did",Php::Type::Numeric)});
        cWritableDatabase.method<&WritableDatabase::get_unique_terms>("get_unique_terms",{Php::ByVal("did",Php::Type::Numeric)});
        cWritableDatabase.method<&WritableDatabase::get_document>("get_document",{Php::ByVal("did",Php::Type::Numeric),Php::ByVal("flags",Php::Type::Numeric,false)});
        cWritableDatabase.method<&WritableDatabase::get_spelling_suggestion>("get_spelling_suggestion",{Php::ByVal("word",Php::Type::String),Php::ByVal("max_edit_distance",Php::Type::Numeric,false)});
        cWritableDatabase.method<&WritableDatabase::metadata_keys_end>("metadata_keys_end",{Php::ByVal("value",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::metadata_keys_begin>("metadata_keys_begin",{Php::ByVal("value",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::allterms_end>("allterms_end",{Php::ByVal("value",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::allterms_begin>("allterms_begin",{Php::ByVal("value",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::spellings_end>("spellings_end",{});
        cWritableDatabase.method<&WritableDatabase::spellings_begin>("spellings_begin",{});
        cWritableDatabase.method<&WritableDatabase::synonyms_end>("synonyms_end",{Php::ByVal("value",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::synonyms_begin>("synonyms_begin",{Php::ByVal("value",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::synonym_keys_end>("synonym_keys_end",{Php::ByVal("value",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::synonym_keys_begin>("synonym_keys_begin",{Php::ByVal("value",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::get_metadata>("get_metadata",{Php::ByVal("value",Php::Type::String)});
        cWritableDatabase.method<&WritableDatabase::compact>("compact",{Php::ByVal("destdir",Php::Type::String)});
        cWritableDatabase.extends(cDatabase);
        extension.add(std::move(cWritableDatabase));
    }
};

class Query: public Php::Base {
    typedef Xapian::Query B;
    std::shared_ptr<B> m;
public:
    Query(){m.reset(new B());}
    Query(const B&e){m.reset(new B(e));}
    operator B*(){return m.get();}
    virtual ~Query(){}
    void __construct(Php::Parameters &params){
        //Php::out << "new Query...\n" << params.size() << std::flush;
        if(params.size()==1 && params[0].isString()){
            m.reset(new B(params[0].stringValue()));
            return;
        }
        if(params.size()==1 && params[0].isObject()){
            //Php::out << "new Query(query)\n" << std::flush;
            m.reset((B*)*dynamic_cast<Query*>(params[0].implementation()));
            return;
        }
        if(params.size()==3 && params[0].isNumeric()){
            m.reset(
                new B(
                    (B::op)params[0].numericValue(),
                    *(B*)*dynamic_cast<Query*>(params[1].implementation()),
                    *(B*)*dynamic_cast<Query*>(params[2].implementation())
                    )
            );
            return;
        }
        if(params.size()==4 && params[0].isNumeric()){
            m.reset(
                new B(
                    (B::op)params[0].numericValue(),
                    params[1].numericValue(),
                    params[2].stringValue(),
                    params[3].stringValue()
                    )
            );
            return;
        }
        throw Php::Exception("new Query:invalid arguments");

    }
    Php::Value get_description(Php::Parameters &params){return m?m->get_description():"null";}
    static void get_module_part(Php::Extension& extension){
        Php::Class<Query> cQuery("XapianQuery");
        cQuery.method<&Query::__construct>("__construct");
        cQuery.method<&Query::get_description>("get_description", {});
        cQuery.constant("OP_AND",(int32_t)B::OP_AND);
        cQuery.constant("OP_OR",(int32_t)B::OP_OR);
        cQuery.constant("OP_AND_NOT",(int32_t)B::OP_AND_NOT);
        cQuery.constant("OP_XOR",(int32_t)B::OP_XOR);
        cQuery.constant("OP_AND_MAYBE",(int32_t)B::OP_AND_MAYBE);
        cQuery.constant("OP_FILTER",(int32_t)B::OP_FILTER);
        cQuery.constant("OP_NEAR",(int32_t)B::OP_NEAR);
        cQuery.constant("OP_PHRASE",(int32_t)B::OP_PHRASE);
        cQuery.constant("OP_VALUE_RANGE",(int32_t)B::OP_VALUE_RANGE);
        cQuery.constant("OP_SCALE_WEIGHT",(int32_t)B::OP_SCALE_WEIGHT);
        cQuery.constant("OP_ELITE_SET",(int32_t)B::OP_ELITE_SET);
        cQuery.constant("OP_VALUE_GE",(int32_t)B::OP_VALUE_GE);
        cQuery.constant("OP_VALUE_LE",(int32_t)B::OP_VALUE_LE);
        cQuery.constant("OP_SYNONYM",(int32_t)B::OP_SYNONYM);

        extension.add(std::move(cQuery));
    }
};

class QueryParser: public Php::Base, public Xapian::QueryParser {
    typedef Xapian::QueryParser B;
public:
    QueryParser():Xapian::QueryParser(){}
    QueryParser(const Xapian::QueryParser&e):Xapian::QueryParser(e){}
    void __construct(Php::Parameters &params){}
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
    void set_stemming_strategy(Php::Parameters& params){
        B::set_stemming_strategy((B::stem_strategy)params[0].numericValue());
    }
    void set_stemmer(Php::Parameters& params){B::set_stemmer(dynamic_cast<Stem*>(params[0].implementation())->get_xapian_stem());}
    void set_stopper(Php::Parameters& params){
        Stopper *sto0 = dynamic_cast<Stopper*>(params[0].implementation());
        if(sto0){
            B::set_stopper((Xapian::Stopper*)sto0);
            return;
        }
        SimpleStopper* sto1 = dynamic_cast<SimpleStopper*>(params[0].implementation());
        if(sto1){
            B::set_stopper((Xapian::Stopper*)sto1);
            return;
        }
        throw Php::Exception("set_stopper: invalid arg");
    }
    void set_database(Php::Parameters &params){
        Database *db = dynamic_cast<Database*>(params[0].implementation());
        WritableDatabase *wdb = dynamic_cast<WritableDatabase*>(params[0].implementation());
        B::set_database(db? *db:*wdb);
    }
    void add_boolean_prefix(Php::Parameters &params){
        B::add_boolean_prefix(params[0].stringValue(),
            params[1].stringValue(),
            params.size()<3 ? false : params[2].boolValue());
    }
    virtual ~QueryParser(){}
    static void get_module_part(Php::Extension& extension){
        Php::Class<QueryParser> cQueryParser("XapianQueryParser");
        cQueryParser.constant("FLAG_BOOLEAN",(int32_t)1);
        cQueryParser.constant("FLAG_PHRASE",(int32_t)2);
        cQueryParser.constant("FLAG_LOVEHATE",(int32_t)4);
        cQueryParser.constant("FLAG_BOOLEAN_ANY_CASE",(int32_t)8);
        cQueryParser.constant("FLAG_WILDCARD",(int32_t)16);
        cQueryParser.constant("FLAG_PURE_NOT",(int32_t)32);
        cQueryParser.constant("FLAG_PARTIAL",(int32_t)64);
        cQueryParser.constant("FLAG_SPELLING_CORRECTION",(int32_t)128);
        cQueryParser.constant("FLAG_SYNONYM",(int32_t)256);
        cQueryParser.constant("FLAG_AUTO_SYNONYMS",(int32_t)512);
        cQueryParser.constant("FLAG_AUTO_MULTIWORD_SYNONYMS",(int32_t)1024);
        cQueryParser.constant("FLAG_CJK_NGRAM",(int32_t)2048);
        cQueryParser.constant("FLAG_DEFAULT",(int32_t)B::FLAG_PHRASE|B::FLAG_BOOLEAN|B::FLAG_LOVEHATE);
        cQueryParser.constant("STEM_NONE",(int32_t)B::STEM_NONE);
        cQueryParser.constant("STEM_SOME",(int32_t)B::STEM_SOME);
        cQueryParser.constant("STEM_ALL",(int32_t)B::STEM_ALL);
        cQueryParser.constant("STEM_ALL_Z",(int32_t)B::STEM_ALL_Z);

        cQueryParser.method<&QueryParser::__construct>("__construct",{});
        cQueryParser.method<&QueryParser::parse_query>("parse_query",{Php::ByVal("query",Php::Type::Null),Php::ByVal("flags",Php::Type::Null,false),Php::ByVal("prefix",Php::Type::Null,false)});
        cQueryParser.method<&QueryParser::get_corrected_query_string>("get_corrected_query_string",{});
        cQueryParser.method<&QueryParser::set_stemming_strategy>("set_stemming_strategy",{Php::ByVal("stem_strategy",Php::Type::Numeric)});
        cQueryParser.method<&QueryParser::set_stemmer>("set_stemmer",{Php::ByVal("stemmer",Php::Type::Object)});
        cQueryParser.method<&QueryParser::set_stopper>("set_stopper",{Php::ByVal("stopper",Php::Type::Object)});
        cQueryParser.method<&QueryParser::set_database>("set_database",{Php::ByVal("database",Php::Type::Object)});
        cQueryParser.method<&QueryParser::add_boolean_prefix>("add_boolean_prefix",{Php::ByVal("field",Php::Type::String),Php::ByVal("prefix",Php::Type::String),Php::ByVal("exclusive",Php::Type::Bool,false)});
        extension.add(std::move(cQueryParser));
    }
};

class Enquire: public Php::Base {
protected:
    typedef Xapian::Enquire B;
    std::shared_ptr<Xapian::Enquire> m;
public:
    Enquire(Database*db){m.reset(new Xapian::Enquire(*db));}
    Enquire(){}
    void __construct(Php::Parameters& params){
        //Php::out << "Enquire::__construct " << params.size() << " " << Php::call("get_class", params[0]) << std::endl << std::flush;
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

    virtual ~Enquire(){m.reset();}
    Php::Value get_description(Php::Parameters &params){return m ? m->get_description():"null";}
    void set_query(Php::Parameters& params){
        Query*Q=dynamic_cast<Query*>(params[0].implementation());
        if(!Q) throw Php::Exception("set_query:invalid arg");

        m->set_query(*(Xapian::Query*)*Q);
    }
    Php::Value get_query(Php::Parameters& params){
        Xapian::Query xq = m->get_query();
        return Php::Object("XapianQuery",new Query(xq));
    }
    Php::Value get_mset(Php::Parameters& params){
        if(params.size()<2) throw new Php::Exception("get_mset must have 2-5 args");
        Xapian::doccount first=params[0].numericValue();
        Xapian::doccount maxitems=params[1].numericValue();
        Xapian::doccount checkatleast=params.size()<3 ? 0 : params[2].numericValue();
        RSet* omrset = params.size()>3 ? dynamic_cast<RSet*>(params[3].implementation()) : NULL;
        MatchDecider* mdecider = params.size()>4 ? dynamic_cast<MatchDecider*>(params[4].implementation()) : NULL;
        Xapian::MSet mset=m->get_mset(first,maxitems,checkatleast,omrset,mdecider);
        return Php::Object("XapianMSet",new MSet(mset));
    }
    void add_matchspy(Php::Parameters& params){
        MatchSpy* spy0 = dynamic_cast<MatchSpy*>(params[0].implementation());
        if(spy0) {
            m->add_matchspy(spy0->getMatchSpy());
            return;
        }
        /*ValueCountMatchSpy* spy1 = dynamic_cast<ValueCountMatchSpy*>(params[0].implementation());
        if(spy1)
            m->add_matchspy(spy1->getMatchSpy());*/
    }
    void set_sort_by_relevance(Php::Parameters& params){m->set_sort_by_relevance();}
    void set_sort_by_value(Php::Parameters& params){m->set_sort_by_value(params[0].numericValue(),params.size()<2 ? false : params[1].boolValue());}
    void set_sort_by_value_then_relevance(Php::Parameters& params){m->set_sort_by_value_then_relevance(params[0].numericValue(),params.size()<2 ? false : params[1].boolValue());}
    void set_sort_by_relevance_then_value(Php::Parameters& params){m->set_sort_by_relevance_then_value(params[0].numericValue(),params.size()<2 ? false : params[1].boolValue());}
    void set_docid_order(Php::Parameters& params){m->set_docid_order((Xapian::Enquire::docid_order)params[0].numericValue());}
    void set_collapse_key(Php::Parameters& params){m->set_collapse_key(params[0].numericValue(),params[1].numericValue());}
    void set_cutoff(Php::Parameters& params){m->set_cutoff(params[0].numericValue(),params[1].floatValue());}
    void clear_matchspies(Php::Parameters& params){m->clear_matchspies();}
    Php::Value get_eset(Php::Parameters& params){
/*    ESet    get_eset (Xapian::termcount maxitems, const RSet &omrset, int flags=0, const Xapian::ExpandDecider *edecider=0, double min_wt=0.0) const
    Get the expand set for the given rset. 
ESet    get_eset (Xapian::termcount maxitems, const RSet &omrset, const Xapian::ExpandDecider *edecider) const
    Get the expand set for the given rset. 
ESet    get_eset (Xapian::termcount maxitems, const RSet &rset, int flags, double k, const Xapian::ExpandDecider *edecider=NULL, double min_wt=0.0) const
*/
        Xapian::termcount maxitems=params[0].numericValue();
        RSet*omrset = dynamic_cast<RSet*>(params[1].implementation());
        if(!omrset) throw Php::Exception("get_eset:invalid arg");
         int flags = params.size()>2 ? params[2].numericValue() : 0;
         Xapian::ExpandDecider *edecider=NULL;
            double min_wt=0.;
        return Php::Object("XapianESet",new ESet(m->get_eset(maxitems,*(Xapian::RSet*)omrset,flags,edecider,min_wt)));
    }
    void set_weighting_scheme(Php::Parameters & params){
        Weight * w = dynamic_cast<Weight*>(params[0].implementation());
        if(w) m->set_weighting_scheme(*w->getWeight());
    }
    static void get_module_part(Php::Extension& extension){
        Php::Class<Enquire> cEnquire("XapianEnquire");
        cEnquire.constant("ASCENDING",(int32_t)B::ASCENDING);
        cEnquire.constant("DESCENDING",(int32_t)B::DESCENDING);
        cEnquire.constant("DONT_CARE",(int32_t)B::DONT_CARE);
        cEnquire.method<&Enquire::__construct>("__construct",{Php::ByVal("enquireOrDatabase",Php::Type::Object)});
        cEnquire.method<&Enquire::set_query>("set_query",{Php::ByVal("query","XapianQuery")});
        cEnquire.method<&Enquire::get_query>("get_query",{});
        cEnquire.method<&Enquire::get_mset>("get_mset");
        cEnquire.method<&Enquire::get_eset>("get_eset");
        cEnquire.method<&Enquire::add_matchspy>("add_matchspy",{Php::ByVal("matchspy",Php::Type::Object)});
        cEnquire.method<&Enquire::clear_matchspies>("clear_matchspies",{});
        cEnquire.method<&Enquire::set_sort_by_relevance>("set_sort_by_relevance",{});
        cEnquire.method<&Enquire::set_sort_by_value>("set_sort_by_value",{Php::ByVal("valueno",Php::Type::Numeric)});
        cEnquire.method<&Enquire::set_sort_by_value_then_relevance>("set_sort_by_value_then_relevance",{Php::ByVal("valueno",Php::Type::Numeric)});
        cEnquire.method<&Enquire::set_sort_by_relevance_then_value>("set_sort_by_relevance_then_value",{Php::ByVal("valueno",Php::Type::Numeric)});
        cEnquire.method<&Enquire::set_docid_order>("set_docid_order",{Php::ByVal("docid_order",Php::Type::Numeric)});
        cEnquire.method<&Enquire::set_collapse_key>("set_collapse_key",{Php::ByVal("valueno",Php::Type::Numeric),Php::ByVal("collapse_max",Php::Type::Numeric)});
        cEnquire.method<&Enquire::set_cutoff>("set_cutoff",{Php::ByVal("percent",Php::Type::Numeric),Php::ByVal("weight",Php::Type::Float)});
        cEnquire.method<&Enquire::set_weighting_scheme>("set_weighting_scheme",{Php::ByVal("weight",Php::Type::Object)});
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
        static Php::Extension extension("xapian", Xapian::version_string());

        // @todo    add your own functions, classes, namespaces to the extension
        PhpXapian::get_module_part(extension); 
        Error::get_module_part(extension);
        Php::Class<Weight> cWeight = Weight::get_module_part(extension);
        BM25Weight::get_module_part(extension, cWeight);
        BM25PlusWeight::get_module_part(extension, cWeight);
        BoolWeight::get_module_part(extension, cWeight);
        TradWeight::get_module_part(extension, cWeight);
        BB2Weight::get_module_part(extension, cWeight);
        CoordWeight::get_module_part(extension, cWeight);
        Compactor::get_module_part(extension);
        TermIterator::get_module_part(extension);
        ValueIterator::get_module_part(extension);
        PositionIterator::get_module_part(extension);
        PostingIterator::get_module_part(extension);
        Stem::get_module_part(extension);
        Php::Class<Stopper> cStopper = Stopper::get_module_part(extension);
        SimpleStopper::get_module_part(extension, cStopper);
        TermGenerator::get_module_part(extension);
        Document::get_module_part(extension);
        MSet::get_module_part(extension);
        MSetIterator::get_module_part(extension);
        RSet::get_module_part(extension);
        ESetIterator::get_module_part(extension);
        ESet::get_module_part(extension);
        Php::Class<MatchSpy> cMatchSpy = MatchSpy::get_module_part(extension);
        ValueCountMatchSpy::get_module_part(extension,cMatchSpy);
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
