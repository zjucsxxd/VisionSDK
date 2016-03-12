#include <oal.h>

#ifdef __STANDALONE__
	#include <gic400.h>
#endif
LIB_RESULT OAL_IRQInit(void (*pServiceRoutineFunc)(void), unsigned int irq, unsigned int priority, IRQ_MODE mode)
{
	g_INT_vectors[irq] = (int_function_t)pServiceRoutineFunc;
  gic400_setIntPriority(irq, priority);
  gic400_setIntTarget(irq, GIC400_TARGET_CPU0);
  if (mode == IRQ_LEVEL)
	gic400_configureSPI(irq, GIC400_CONFIG_LEVEL);
  else if (mode == IRQ_EDGE)
	gic400_configureSPI(irq, GIC400_CONFIG_EDGE);  
  return LIB_SUCCESS;
}

void OAL_IRQEnable(unsigned int irq)
{
	gic400_enableIntID(irq);
}

LIB_RESULT OAL_IRQDelete(unsigned int irq)
{
	g_INT_vectors[irq] = (int_function_t)default_interrupt_routine;
	return LIB_SUCCESS;
}

void OAL_IRQDisable(unsigned int irq)
{
	gic400_disableIntID(irq);
}