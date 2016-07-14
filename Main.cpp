#include <phpcpp.h>
#include <xapian.h>

class PhpWritableDatabase: public Php::Base,public Xapian::WritableDatabase {
public:
    PhpWritableDatabase(const Xapian::WritableDatabase& Database):Xapian::WritableDatabase(Database){
        
    }
    virtual ~PhpWritableDatabase()=default;

    Php::Value get_description(Php::Parameters &params){return static_cast<Xapian::WritableDatabase*>(this)->get_description();}
    void close(Php::Parameters &params){ static_cast<Xapian::WritableDatabase*>(this)->close();}
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
        return Php::Object("XapianWritableDatabase",new PhpWritableDatabase(db));
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

        Php::Class<PhpWritableDatabase> WritableDatabase("XapianWritableDatabase");
        WritableDatabase.method<&PhpWritableDatabase::get_description>("get_description");
        WritableDatabase.method<&PhpWritableDatabase::close>("close");
        extension.add(std::move(WritableDatabase));
        

        // return the extension
        return extension;
    }
}
