// This file was generated by factory_helpers.gen.py, DO NOT EDIT
#ifndef TPIE_PIPELINING_FACTORY_HELPERS_H
#define TPIE_PIPELINING_FACTORY_HELPERS_H

#include <tpie/pipelining/factory_base.h>

namespace tpie {
namespace pipelining {

///////////////////////////////////////////////////////////////////////////////
/// \class factory_0
/// Node factory for 0-argument generator.
///////////////////////////////////////////////////////////////////////////////
template <template <typename dest_t> class R>
class factory_0 : public factory_base {
public:
	template<typename dest_t>
	struct constructed {
		typedef R<dest_t> type;
	};

	template <typename dest_t>
	inline R<dest_t> construct(const dest_t & dest) const {
		R<dest_t> r(dest);
		this->init_node(r);
		return r;
	}
};

///////////////////////////////////////////////////////////////////////////////
/// \class tempfactory_0
/// Node factory for 0-argument templated generator.
///////////////////////////////////////////////////////////////////////////////
template <typename Holder>
class tempfactory_0 : public factory_base {
public:
	template<typename dest_t>
	struct constructed {
		typedef typename Holder::template type<dest_t> type;
	};

	template <typename dest_t>
	inline typename Holder::template type<dest_t> construct(const dest_t & dest) const {
		typename Holder::template type<dest_t> r(dest);
		this->init_node(r);
		return r;
	}
};

///////////////////////////////////////////////////////////////////////////////
/// \class factory_1
/// Node factory for 1-argument generator.
///////////////////////////////////////////////////////////////////////////////
template <template <typename dest_t> class R, typename T1>
class factory_1 : public factory_base {
public:
	template<typename dest_t>
	struct constructed {
		typedef R<dest_t> type;
	};

	inline factory_1(T1 t1) : t1(t1) {}

	template <typename dest_t>
	inline R<dest_t> construct(const dest_t & dest) const {
		R<dest_t> r(dest, t1);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
};

///////////////////////////////////////////////////////////////////////////////
/// \class tempfactory_1
/// Node factory for 1-argument templated generator.
///////////////////////////////////////////////////////////////////////////////
template <typename Holder, typename T1>
class tempfactory_1 : public factory_base {
public:
	template<typename dest_t>
	struct constructed {
		typedef typename Holder::template type<dest_t> type;
	};

	inline tempfactory_1(T1 t1) : t1(t1) {}

	template <typename dest_t>
	inline typename Holder::template type<dest_t> construct(const dest_t & dest) const {
		typename Holder::template type<dest_t> r(dest, t1);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
};

///////////////////////////////////////////////////////////////////////////////
/// \class factory_2
/// Node factory for 2-argument generator.
///////////////////////////////////////////////////////////////////////////////
template <template <typename dest_t> class R, typename T1, typename T2>
class factory_2 : public factory_base {
public:
	template<typename dest_t>
	struct constructed {
		typedef R<dest_t> type;
	};

	inline factory_2(T1 t1, T2 t2) : t1(t1), t2(t2) {}

	template <typename dest_t>
	inline R<dest_t> construct(const dest_t & dest) const {
		R<dest_t> r(dest, t1, t2);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
	T2 t2;
};

///////////////////////////////////////////////////////////////////////////////
/// \class tempfactory_2
/// Node factory for 2-argument templated generator.
///////////////////////////////////////////////////////////////////////////////
template <typename Holder, typename T1, typename T2>
class tempfactory_2 : public factory_base {
public:
	template<typename dest_t>
	struct constructed {
		typedef typename Holder::template type<dest_t> type;
	};

	inline tempfactory_2(T1 t1, T2 t2) : t1(t1), t2(t2) {}

	template <typename dest_t>
	inline typename Holder::template type<dest_t> construct(const dest_t & dest) const {
		typename Holder::template type<dest_t> r(dest, t1, t2);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
	T2 t2;
};

///////////////////////////////////////////////////////////////////////////////
/// \class factory_3
/// Node factory for 3-argument generator.
///////////////////////////////////////////////////////////////////////////////
template <template <typename dest_t> class R, typename T1, typename T2, typename T3>
class factory_3 : public factory_base {
public:
	template<typename dest_t>
	struct constructed {
		typedef R<dest_t> type;
	};

	inline factory_3(T1 t1, T2 t2, T3 t3) : t1(t1), t2(t2), t3(t3) {}

	template <typename dest_t>
	inline R<dest_t> construct(const dest_t & dest) const {
		R<dest_t> r(dest, t1, t2, t3);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
	T2 t2;
	T3 t3;
};

///////////////////////////////////////////////////////////////////////////////
/// \class tempfactory_3
/// Node factory for 3-argument templated generator.
///////////////////////////////////////////////////////////////////////////////
template <typename Holder, typename T1, typename T2, typename T3>
class tempfactory_3 : public factory_base {
public:
	template<typename dest_t>
	struct constructed {
		typedef typename Holder::template type<dest_t> type;
	};

	inline tempfactory_3(T1 t1, T2 t2, T3 t3) : t1(t1), t2(t2), t3(t3) {}

	template <typename dest_t>
	inline typename Holder::template type<dest_t> construct(const dest_t & dest) const {
		typename Holder::template type<dest_t> r(dest, t1, t2, t3);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
	T2 t2;
	T3 t3;
};

///////////////////////////////////////////////////////////////////////////////
/// \class factory_4
/// Node factory for 4-argument generator.
///////////////////////////////////////////////////////////////////////////////
template <template <typename dest_t> class R, typename T1, typename T2, typename T3, typename T4>
class factory_4 : public factory_base {
public:
	template<typename dest_t>
	struct constructed {
		typedef R<dest_t> type;
	};

	inline factory_4(T1 t1, T2 t2, T3 t3, T4 t4) : t1(t1), t2(t2), t3(t3), t4(t4) {}

	template <typename dest_t>
	inline R<dest_t> construct(const dest_t & dest) const {
		R<dest_t> r(dest, t1, t2, t3, t4);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
};

///////////////////////////////////////////////////////////////////////////////
/// \class tempfactory_4
/// Node factory for 4-argument templated generator.
///////////////////////////////////////////////////////////////////////////////
template <typename Holder, typename T1, typename T2, typename T3, typename T4>
class tempfactory_4 : public factory_base {
public:
	template<typename dest_t>
	struct constructed {
		typedef typename Holder::template type<dest_t> type;
	};

	inline tempfactory_4(T1 t1, T2 t2, T3 t3, T4 t4) : t1(t1), t2(t2), t3(t3), t4(t4) {}

	template <typename dest_t>
	inline typename Holder::template type<dest_t> construct(const dest_t & dest) const {
		typename Holder::template type<dest_t> r(dest, t1, t2, t3, t4);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
};

///////////////////////////////////////////////////////////////////////////////
/// \class factory_5
/// Node factory for 5-argument generator.
///////////////////////////////////////////////////////////////////////////////
template <template <typename dest_t> class R, typename T1, typename T2, typename T3, typename T4, typename T5>
class factory_5 : public factory_base {
public:
	template<typename dest_t>
	struct constructed {
		typedef R<dest_t> type;
	};

	inline factory_5(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5) : t1(t1), t2(t2), t3(t3), t4(t4), t5(t5) {}

	template <typename dest_t>
	inline R<dest_t> construct(const dest_t & dest) const {
		R<dest_t> r(dest, t1, t2, t3, t4, t5);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
	T5 t5;
};

///////////////////////////////////////////////////////////////////////////////
/// \class tempfactory_5
/// Node factory for 5-argument templated generator.
///////////////////////////////////////////////////////////////////////////////
template <typename Holder, typename T1, typename T2, typename T3, typename T4, typename T5>
class tempfactory_5 : public factory_base {
public:
	template<typename dest_t>
	struct constructed {
		typedef typename Holder::template type<dest_t> type;
	};

	inline tempfactory_5(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5) : t1(t1), t2(t2), t3(t3), t4(t4), t5(t5) {}

	template <typename dest_t>
	inline typename Holder::template type<dest_t> construct(const dest_t & dest) const {
		typename Holder::template type<dest_t> r(dest, t1, t2, t3, t4, t5);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
	T5 t5;
};

///////////////////////////////////////////////////////////////////////////////
/// \class factory_6
/// Node factory for 6-argument generator.
///////////////////////////////////////////////////////////////////////////////
template <template <typename dest_t> class R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class factory_6 : public factory_base {
public:
	template<typename dest_t>
	struct constructed {
		typedef R<dest_t> type;
	};

	inline factory_6(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6) : t1(t1), t2(t2), t3(t3), t4(t4), t5(t5), t6(t6) {}

	template <typename dest_t>
	inline R<dest_t> construct(const dest_t & dest) const {
		R<dest_t> r(dest, t1, t2, t3, t4, t5, t6);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
	T5 t5;
	T6 t6;
};

///////////////////////////////////////////////////////////////////////////////
/// \class tempfactory_6
/// Node factory for 6-argument templated generator.
///////////////////////////////////////////////////////////////////////////////
template <typename Holder, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class tempfactory_6 : public factory_base {
public:
	template<typename dest_t>
	struct constructed {
		typedef typename Holder::template type<dest_t> type;
	};

	inline tempfactory_6(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6) : t1(t1), t2(t2), t3(t3), t4(t4), t5(t5), t6(t6) {}

	template <typename dest_t>
	inline typename Holder::template type<dest_t> construct(const dest_t & dest) const {
		typename Holder::template type<dest_t> r(dest, t1, t2, t3, t4, t5, t6);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
	T5 t5;
	T6 t6;
};

///////////////////////////////////////////////////////////////////////////////
/// \class termfactory_0
/// Node factory for 0-argument terminator.
///////////////////////////////////////////////////////////////////////////////
template <typename R>
class termfactory_0 : public factory_base {
public:
	typedef R constructed_type;

	inline R construct() const {
		R r;
		this->init_node(r);
		return r;
	}
};

///////////////////////////////////////////////////////////////////////////////
/// \class termfactory_1
/// Node factory for 1-argument terminator.
///////////////////////////////////////////////////////////////////////////////
template <typename R, typename T1>
class termfactory_1 : public factory_base {
public:
	typedef R constructed_type;

	inline termfactory_1(T1 t1) : t1(t1) {}

	inline R construct() const {
		R r(t1);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
};

///////////////////////////////////////////////////////////////////////////////
/// \class termfactory_2
/// Node factory for 2-argument terminator.
///////////////////////////////////////////////////////////////////////////////
template <typename R, typename T1, typename T2>
class termfactory_2 : public factory_base {
public:
	typedef R constructed_type;

	inline termfactory_2(T1 t1, T2 t2) : t1(t1), t2(t2) {}

	inline R construct() const {
		R r(t1, t2);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
	T2 t2;
};

///////////////////////////////////////////////////////////////////////////////
/// \class termfactory_3
/// Node factory for 3-argument terminator.
///////////////////////////////////////////////////////////////////////////////
template <typename R, typename T1, typename T2, typename T3>
class termfactory_3 : public factory_base {
public:
	typedef R constructed_type;

	inline termfactory_3(T1 t1, T2 t2, T3 t3) : t1(t1), t2(t2), t3(t3) {}

	inline R construct() const {
		R r(t1, t2, t3);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
	T2 t2;
	T3 t3;
};

///////////////////////////////////////////////////////////////////////////////
/// \class termfactory_4
/// Node factory for 4-argument terminator.
///////////////////////////////////////////////////////////////////////////////
template <typename R, typename T1, typename T2, typename T3, typename T4>
class termfactory_4 : public factory_base {
public:
	typedef R constructed_type;

	inline termfactory_4(T1 t1, T2 t2, T3 t3, T4 t4) : t1(t1), t2(t2), t3(t3), t4(t4) {}

	inline R construct() const {
		R r(t1, t2, t3, t4);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
};

///////////////////////////////////////////////////////////////////////////////
/// \class termfactory_5
/// Node factory for 5-argument terminator.
///////////////////////////////////////////////////////////////////////////////
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
class termfactory_5 : public factory_base {
public:
	typedef R constructed_type;

	inline termfactory_5(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5) : t1(t1), t2(t2), t3(t3), t4(t4), t5(t5) {}

	inline R construct() const {
		R r(t1, t2, t3, t4, t5);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
	T5 t5;
};

///////////////////////////////////////////////////////////////////////////////
/// \class termfactory_6
/// Node factory for 6-argument terminator.
///////////////////////////////////////////////////////////////////////////////
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class termfactory_6 : public factory_base {
public:
	typedef R constructed_type;

	inline termfactory_6(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6) : t1(t1), t2(t2), t3(t3), t4(t4), t5(t5), t6(t6) {}

	inline R construct() const {
		R r(t1, t2, t3, t4, t5, t6);
		this->init_node(r);
		return r;
	}
private:
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
	T5 t5;
	T6 t6;
};

} // namespace pipelining
} // namespace tpie

#endif // TPIE_PIPELINING_FACTORY_HELPERS_H
