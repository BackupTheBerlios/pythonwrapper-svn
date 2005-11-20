#ifndef _PWSequenceEntry_h_
#define _PWSequenceEntry_h_

namespace pw
{
    template <class SeqType, class IndexType>
    class SequenceEntry : public Object
    {
    public:
        SequenceEntry(const Object &obj, SeqType &seq, const IndexType &key);
        virtual ~SequenceEntry();

        virtual Object &operator=(const Object &rhs);

    protected:
        SeqType &mSeq;
        IndexType mKey;
    };
}


template <class SeqType, class IndexType>
pw::SequenceEntry<SeqType, IndexType>::SequenceEntry(const pw::Object &obj, SeqType &seq, const IndexType &key)
: Object(obj), mSeq(seq), mKey(key)
{
}


template <class SeqType, class IndexType>
pw::SequenceEntry<SeqType, IndexType>::~SequenceEntry()
{
}


template <class SeqType, class IndexType>
pw::Object &pw::SequenceEntry<SeqType, IndexType>::operator=(const pw::Object &rhs)
{
    mSeq.setItem(mKey, rhs);

    // this if takes care of the case when the pointer is the same; if we
    // did not do this check the following code below would bomb if
    // mPtr == rhs.mPtr and the refcount was at 1
    if (mPtr != rhs.borrowReference())
    {
        // mPtr could be 0 if we called this from the copy constructor
        Py_DECREF(mPtr);

        mPtr = rhs.borrowReference();
        Py_INCREF(mPtr);
    } // if

    return *this;
}


#endif
