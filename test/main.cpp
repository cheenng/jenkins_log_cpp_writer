#include "ExportJenkinsLog.h"
#include "RegTestUtilities.h"
#include <iostream>

int main() {
	using namespace std;
	using namespace JKS_LOG_GEN;
	const string output_path("C:/Users/jenkins/Desktop/jenkins_log_writer/test/");
	const string jenkins_file_name =  output_path + "log.xml";
	if (!RegTestUtil::dirExists(output_path)) {
		printf("output path doesn't exist! \n");
		return RegTestUtil::outputErrorLog("path to save jenkins file doesn't exist!", RegTestUtil::REG_TEST_INVALID_PATH);
	}
	Log_Doc log_doc(jenkins_file_name);
	array<function<TiXmlElement* (const Log_Msg&)>, LOG_NUM> log_array;
	
	string time = RegTestUtil::currentDateTime();
	printf("current time: %s \n", time.c_str());

	Error_Log error_log(log_array);
	Success_Log success_log(log_array);
	Success_ALL_Log success_log_all(log_array);

	Log_Msg log_msg;
	log_msg.classname = string("example_");
	log_msg.testname = string("test");
	log_msg.err_msg = string("test fails");
	log_doc.AddTestCase<LOG_ERROR>(log_array[LOG_ERROR](log_msg));
	log_msg.err_msg = string("test fails again");
	log_doc.AddTestCase<LOG_ERROR>(log_array[LOG_ERROR](log_msg));
	log_msg.err_msg = string("test succeeds");
	log_doc.AddTestCase<LOG_SUCCESS>(log_array[LOG_SUCCESS](log_msg));
	log_msg.err_msg = string("test succeeds");
	log_doc.AddTestCase<LOG_SUCCESS_ALL>(log_array[LOG_SUCCESS_ALL](log_msg));

	cout << "my directory is " << RegTestUtil::getExePath() << "\n";
	
	if (!log_doc.CloseFile()) {
		return RegTestUtil::outputErrorLog("jenkins log xml can not be saved!", RegTestUtil::REG_TEST_SAVE_XML_FAIL);
	}

	system("pause");

	return 0;
}