/*Instance of task t2*/

#include "embUnit.h"
#include "Os.h"

DeclareEvent(Event1);

/*test case:test the reaction of the system called with 
 an activation of a task*/
static void test_t2_instance(void)
{
	StatusType result_inst_1, result_inst_2;
	
	SCHEDULING_CHECK_INIT(9);
	result_inst_1 = WaitEvent(Event1);
	SCHEDULING_CHECK_AND_EQUAL_INT(19,E_OK, result_inst_1);
	
	SCHEDULING_CHECK_INIT(20);
	result_inst_2 = TerminateTask();
	SCHEDULING_CHECK_AND_EQUAL_INT(20,E_OK, result_inst_2);
		
}

/*create the test suite with all the test cases*/
TestRef AutosarSTSTest_seq1_t2_instance(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures) {
		new_TestFixture("test_t2_instance",test_t2_instance)
	};
	EMB_UNIT_TESTCALLER(AutosarSTSTest,"AutosarSTSTest_sequence1",NULL,NULL,fixtures);
	
	return (TestRef)&AutosarSTSTest;
}