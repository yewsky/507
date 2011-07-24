#ifndef _HANDLEMANAGER_H_
#define _HANDLEMANAGER_H_

#include "Handle.h"

/**
 * 句柄管理器;
 */
class HandleManager : public boost::noncopyable
{

public:
	typedef boost::unordered_map<Handle::Key, Handle::Ptr> HandleMap;
	
	/**
	 * 构造函数;
	 */
	HandleManager()
		: _keyDist(Handle::Min, Handle::Max)
		, _keyGenerator(_keyGen, _keyDist)
	{
	}
	
	/**
	 * 析构函数;
	 */
	~HandleManager()
	{
        std::cout<< "HandleManager Destructors..\n";
	}

	/**
	 * 创建句柄;
	 * @param [in] context 句柄关联上下文;
	 * @retval 句柄索引 成功;
	 * @retval 0 失败;
	 */
	const Handle::Key createHandle(Handle::Context context)
	{
		Handle::Key k = genKey();
		while (_handles.count(k))
			k = genKey();
		Handle::Ptr v = Handle::create(context, k);
		_handles[k] = v;
		return k;
	}
	
	/**
	 * 销毁句柄;
	 * @param [in] key 句柄索引;
	 * @return 无返回值;
	 */
	void destroyHandle(const Handle::Key key)
	{
		if (key >= Handle::Min && key <= Handle::Max) {
			if (_handles.count(key)) {
				_handles.erase(key);
			}
		}
        std::cout << "HandleManager: erase: " << key << "\n";
	}
	
	/**
	 * 检索句柄;
	 * @param [in] key 句柄索引;
	 * @retval 句柄智能指针 成功;
	 * @retval Handle::null() 失败;
	 */
	Handle::Ptr lookupHandle(const Handle::Key key)
	{
		if (key >= Handle::Min && key <= Handle::Max) {
			if (_handles.count(key))
				return _handles[key];
		}
		return Handle::null();
	}
	
	Handle::Ptr lookupHandle(const Handle::Key key) const
	{
		return Handle::null();
	}
	
	bool lockHandle(const Handle::Key key)
	{
		return true;
	}
	
	bool unlockHandle(const Handle::Key key)
	{
		return true;
	}
	
	const Handle::Key genKey()
	{
		return _keyGenerator();
	}

    friend HandleManager& theHandleManager();

private:
	HandleMap _handles; /**< 句柄映射表 */
	boost::mt19937 _keyGen; /**< 随机数生成器 */
	boost::uniform_int<> _keyDist; /**< 随机数分布 */
	boost::variate_generator< boost::mt19937&, boost::uniform_int<> > _keyGenerator; /**< 句柄索引生成器 */
};

HandleManager& theHandleManager();

#endif /* _HANDLEMANAGER_H_ */
