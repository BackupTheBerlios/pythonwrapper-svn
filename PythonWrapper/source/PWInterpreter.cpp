#include "PWInterpreter.h"
#include "PWObject.h"
#include "PWHandler.h"
#include "PWExceptions.h"
#include "PWDict.h"
#include "PWBuild.h"

using namespace pw;

Object *Interpreter::sModule = 0;

Interpreter::Interpreter()
{
    if (!sModule)
        PW_Except("Interpreter object created without calling Interpreter::Initialize first.",
                  "Interpreter::Interpreter");

    mNamespace = Dict(sModule->getAttr("__dict__")).copy();
} // Interpreter


Interpreter::Interpreter(const Interpreter &pw)
: mNamespace(pw.mNamespace)
{
} // Interpreter(const Interpreter &)


const Interpreter &Interpreter::operator=(const Interpreter &sys)
{
    return *this;
}


Interpreter::~Interpreter()
{
} // ~Interpreter


void Interpreter::Initialize()
{
    if (!Py_IsInitialized())
        Py_Initialize();

    if (!sModule)
        sModule = new Object(BorrowedReference(PyImport_AddModule("__main__")));
} // init


void Interpreter::Finalize()
{
    if (sModule)
    {
        delete sModule;
        sModule = 0;
    } // if

    if (Py_IsInitialized())
    {
        PyErr_Clear();
        Py_Finalize();
    } // if
} // deinit


Object Interpreter::runString(const String &str)
{
    PyObject *ret = PyRun_String(str.c_str(), Py_file_input,
                                 mNamespace.borrowReference(),
                                 mNamespace.borrowReference());

    if (PyErr_Occurred())
    {
        Py_XDECREF(ret);
        PW_PyExcept("Interpreter::runString");
    } // if

    return Object(ret ? NewReference(ret) : BorrowedReference(Py_None));
} // runString(const std::string &)


void Interpreter::reset()
{
    mNamespace = Dict(sModule->getAttr("__dict__")).copy();
}


Object Interpreter::evaluate(const String &expression)
{
    PyObject *ret = PyRun_String(expression.c_str(), Py_eval_input,
                                 mNamespace.borrowReference(),
                                 mNamespace.borrowReference());

    PyObject *namesp = mNamespace.borrowReference();

    if (PyErr_Occurred())
    {
        Py_XDECREF(ret);
        PW_PyExcept("Interpreter::evaluate");
    } // if

    return Object(ret ? NewReference(ret) : BorrowedReference(Py_None));
} // evaluate(const std::string &)


Object Interpreter::runFile(const String &fileName)
{
    // open the file
    FILE *fp = fopen(fileName.c_str(), "r");
    if (!fp)
        PW_Except("Could open file " + fileName + ".", "Interpreter::runFile");

    // get the length of the file
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    rewind(fp);

    // create an array of that length, null terminated
    char *buffer = new char[length];
    fread(buffer, 1, length, fp);
    buffer[length-1] = 0;

    fclose(fp);
    
    // run the string
    Object obj = runString(buffer);

    // clean up
    delete [] buffer;
    
    return obj;
} // runFile(const std::string &)


void Interpreter::loadModule(const String &moduleName, Module::InitFunction f)
{
    if (PyImport_AppendInittab((char *)moduleName.c_str(), f) == -1)
    {
        // todo, does this even set the python exception?
        PW_PyExcept("Interpreter::loadModule");
    } // if
} // loadModule(const std::string &, void (*)(void))


Object Interpreter::getObject(const String &object)
{
    if (! mNamespace.contains(build(object)))
        PW_Except("This system object does not contain an object.", "Interpreter::getObject");

    return mNamespace[object];
} // getObject(const std::string &)

const Dict &Interpreter::getNamespace() const
{
    return mNamespace;
}
