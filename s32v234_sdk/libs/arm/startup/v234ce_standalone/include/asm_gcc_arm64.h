typedef unsigned long uint64_t;
typedef unsigned int uint32_t;
typedef	unsigned long size_t;

#define DEFINE_SYSOP_TYPE_FUNC(_op, _type)		\
static inline void _op ## _type(void)			\
{							\
	__asm__ (#_op " " #_type);			\
}

#define DEFINE_SYSOP_FUNC(_op)				\
static inline void _op(void)				\
{							\
	__asm__ (#_op);					\
}


#define _DEFINE_SYSREG_READ_FUNC(_name, _reg_name)	\
static inline uint64_t read_ ## _name(void)		\
{							\
	uint64_t v;					\
	__asm__ ("mrs %0, " #_reg_name : "=r" (v));	\
	return v;					\
}

#define _DEFINE_SYSREG_WRITE_FUNC(_name, _reg_name)		\
static inline void write_ ## _name(uint64_t v)		\
{							\
	__asm__ ("msr " #_reg_name ", %0" : : "r" (v));	\
}

#define _DEFINE_SYSREG_WRITE_CONST_FUNC(_name, _reg_name)		\
static inline void write_ ## _name(const uint64_t v)	\
{							\
	__asm__ ("msr " #_reg_name ", %0" : : "i" (v));	\
}

/* Define read function for system register */
#define DEFINE_SYSREG_READ_FUNC(_name) 			\
	_DEFINE_SYSREG_READ_FUNC(_name, _name)

/* Define read & write function for system register */
#define DEFINE_SYSREG_RW_FUNCS(_name)			\
	_DEFINE_SYSREG_READ_FUNC(_name, _name)		\
	_DEFINE_SYSREG_WRITE_FUNC(_name, _name)

/* Define read & write function for renamed system register */
#define DEFINE_RENAME_SYSREG_RW_FUNCS(_name, _reg_name)	\
	_DEFINE_SYSREG_READ_FUNC(_name, _reg_name)	\
	_DEFINE_SYSREG_WRITE_FUNC(_name, _reg_name)

/* Define write function for special system registers */
#define DEFINE_SYSREG_WRITE_CONST_FUNC(_name)		\
	_DEFINE_SYSREG_WRITE_CONST_FUNC(_name, _name)

DEFINE_SYSOP_TYPE_FUNC(dsb, sy)
DEFINE_SYSOP_FUNC(isb)
#define dsb()			dsbsy() 
