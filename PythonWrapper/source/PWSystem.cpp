#include "PWSystem.h"
#include "PWObject.h"
#include "PWHandler.h"
#include "PWExceptions.h"
#include "PWDict.h"
#include "PWBuild.h"

using namespace pw;

Object *System::sModule = 0;
unsigned int System::sInstanceCount = 0;

System::System()
{
    if (sInstanceCount++ == 0)
    {
        Py_Initialize();

        assert(sModule == 0);
        sModule = new Object(BorrowedReference(PyImport_AddModule("__main__")));
    }

    init();
} // System


System::System(const System &pw)
{
    *this = pw;
    sInstanceCount++;
} // System(const System &)


const System &System::operator=(const System &sys)
{
    assert(sInstanceCount > 0);
    mNamespace = Dict(sys.mNamespace);

    return *this;
}


System::~System()
{
    deinit();

    if (--sInstanceCount == 0)
    {
        assert(sModule != 0);
        delete sModule;
        sModule = 0;

        Py_Finalize();
    }
} // ~System


void System::init()
{
    mNamespace = Dict(sModule->getAttr("__dict__")).copy();
} // init


void System::deinit()
{
} // deinit


Object System::runString(const char *str)
{
    PyObject *ret = PyRun_String(str, Py_file_input,
                                 mNamespace.borrowReference(),
                                 mNamespace.borrowReference());

    if (PyErr_Occurred())
    {
        Py_XDECREF(ret);
        PYTHON_EXCEPTION_THROW;
    } // if

    return Object(ret ? NewReference(ret) : BorrowedReference(Py_None));
} // runString(const std::string &)


void System::reset()
{
    mNamespace = Dict(sModule->getAttr("__dict__")).copy();
}


Object System::evaluate(const char *expression)
{
    PyObject *ret = PyRun_String(expression, Py_eval_input,
                                 mNamespace.borrowReference(),
                                 mNamespace.borrowReference());

    PyObject *namesp = mNamespace.borrowReference();

    if (PyErr_Occurred())
    {
        Py_XDECREF(ret);
        PYTHON_EXCEPTION_THROW;
    } // if

    return Object(ret ? NewReference(ret) : BorrowedReference(Py_None));
} // evaluate(const std::string &)


Object System::runFile(const char *fileName)
{
    // open the file
    FILE *fp = fopen(fileName, "r");
    if (!fp)
        EXCEPTION_THROW;

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


void System::loadModule(char *moduleName, Module::InitFunction f)
{
    if (PyImport_AppendInittab(moduleName, f) == -1)
    {
        // todo, does this even set the python exception?
        PYTHON_EXCEPTION_THROW;
    } // if
} // loadModule(const std::string &, void (*)(void))


Object System::getObject(char *object)
{
    if (! mNamespace.contains(build(object)))
    {
        // todo: make this meaningful
        PYTHON_EXCEPTION_THROW;
    } // if

    return mNamespace[object];
} // getObject(const std::string &)

const Dict &System::getNamespace() const
{
    return mNamespace;
}
