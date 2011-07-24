#ifndef _HANDLE_H_
#define _HANDLE_H_

template <typename _Key = unsigned long>
class basic_handle : public boost::enable_shared_from_this< basic_handle<_Key> >
                   , public boost::noncopyable
{    
public:
    typedef _Key Key;
    typedef boost::any Context;

    typedef basic_handle<_Key> Handle;
    typedef boost::shared_ptr<Handle> Ptr;
    typedef boost::shared_ptr<const Handle> ConstPtr;

    typedef enum {
          Zero = 0
        , Min = 0xFFFF
        , Max = 0x7FFFFFFF
    } KeyState;

    virtual ~basic_handle()
    {
        std::cout << "Handle: Destructors: " << this << "\n";
    }

    Context& getContext()
    {
        return _context;
    }

    Context& getContext() const
    {
        return const_cast<Context&>(_context);
    }

    Key& getKey()
    {
        return _key;
    }

    Key& getKey() const
    {
        return const_cast<Key&>(_key);
    }

    void setContext(Context context)
    {
        _context = context;
    }

    void setKey(Key key)
    {
        _key = key;
    }

    template <typename T>
    operator T()
    {
        return boost::any_cast<T>(_context);
    }

    static Ptr create()
    {
        return Ptr(new Handle());
    }

#if 0
    static Ptr create(Context context, Key key)
    {
        return Ptr(new Handle(context, key));
    }
#endif

    static Ptr create(Context& context, Key& key)
    {
        return Ptr(new Handle(context, key));
    }


    static Ptr null() {
        return Ptr();
    }

protected:
    basic_handle()
        : _context()
        , _key(0)
    {
    }

    basic_handle(Context context, Key key)
        : _context(context)
        , _key(key)
    {
    }

#if 0
    basic_handle(Context& context, Key& key)
        : _context(context)
        , _key(key)
    {
    }
#endif

    Context _context;
    Key _key;
};

typedef basic_handle<> Handle;

#endif /* _HANDLE_H_ */
