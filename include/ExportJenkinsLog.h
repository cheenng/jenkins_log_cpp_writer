#ifndef _EXPORTJENKINSLOG_H_ 
#define _EXPORTJENKINSLOG_H_ 
#include <string>
#include <functional>
#include <map>
#include <utility>
#include "../tinyxml/tinyxml.h"
#include <array>

using namespace std;
namespace JKS_LOG_GEN {
    enum LOG_TYPE {
        LOG_SUCCESS,
        LOG_ERROR,
        LOG_SUCCESS_ALL,
        LOG_NUM
    };

    struct Log_Msg {
        string classname;
        string testname;
        string err_msg;
    };

    class Log_Doc {
    public:
        explicit Log_Doc(string doc_name):m_doc_name(doc_name), m_failure_cnt(0)
        , m_success_cnt(0) {
            TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "UTF-8", "");
            m_doc.LinkEndChild(decl);
            m_root = new TiXmlElement("testsuite");
            m_doc.LinkEndChild(m_root);
            m_root->SetAttribute("errors", 0);
            m_root->SetAttribute("failures", 0);
            m_root->SetAttribute("name", "Testsuite_name");
            m_root->SetAttribute("tests", 0);
            m_root->SetAttribute("time", 0);
        }

        ~Log_Doc() {
            m_doc.SaveFile(m_doc_name);
        };

        TiXmlElement* getRoot() {return m_root;};

        template<LOG_TYPE ELOG_T>
        void AddTestCase(TiXmlElement* test_case);

        bool CloseFile() {
            return m_doc.SaveFile(m_doc_name);
        };

    private:
        string m_doc_name;
        TiXmlDocument m_doc;
        TiXmlElement* m_root;
        unsigned int m_failure_cnt;
        unsigned int m_success_cnt;
    };
    
    template<>
    void Log_Doc::AddTestCase<LOG_ERROR>(TiXmlElement* test_case) {
        m_root->LinkEndChild(test_case);
        ++m_failure_cnt;
        m_root->SetAttribute("failures", m_failure_cnt);
        m_root->SetAttribute("tests", m_failure_cnt + m_success_cnt);
    };

    template<>
    void Log_Doc::AddTestCase<LOG_SUCCESS>(TiXmlElement* test_case) {
        ++m_success_cnt;
        m_root->SetAttribute("tests", m_failure_cnt + m_success_cnt);
    }

    template<>
    void Log_Doc::AddTestCase<LOG_SUCCESS_ALL>(TiXmlElement* test_case) {
        m_root->LinkEndChild(test_case);
        ++m_success_cnt;
        m_root->SetAttribute("tests", m_failure_cnt + m_success_cnt);
    }

    struct Error_Log {
        explicit Error_Log(array<function<TiXmlElement* (const Log_Msg&)>, LOG_NUM>& func_array) {
            func_array[LOG_ERROR] = [this](const Log_Msg& log_msg) -> TiXmlElement* {return AddErrorEntry(log_msg);};
        }

        TiXmlElement*  AddErrorEntry(const Log_Msg& log_msg) {
            TiXmlElement * p_tc = new TiXmlElement("testcase");
            p_tc->SetAttribute("classname", log_msg.classname);
            p_tc->SetAttribute("name", log_msg.testname);
            p_tc->SetAttribute("time", "NA");
            TiXmlElement* failure_msg = new TiXmlElement("failure");
            p_tc->LinkEndChild(failure_msg);
            failure_msg->SetAttribute("message", "Test failed");
            failure_msg->SetAttribute("type", "AssertionError");
            TiXmlText* xml_txt = new TiXmlText(log_msg.err_msg);
            xml_txt->SetCDATA(true);
            failure_msg->LinkEndChild(xml_txt);
            return p_tc;
        };

    };

    struct Success_Log {
        explicit Success_Log(array<function<TiXmlElement* (const Log_Msg&)>, LOG_NUM>& func_array) {
            func_array[LOG_SUCCESS] = [this](const Log_Msg& log_msg) -> TiXmlElement* {return AddSuccessEntry(log_msg);};
        }

        TiXmlElement*  AddSuccessEntry(const Log_Msg& log_msg) {
            /*TiXmlElement * p_tc = new TiXmlElement("testcase");
            p_tc->SetAttribute("classname", "Testclass");
            p_tc->SetAttribute("name", "runTest");
            p_tc->SetAttribute("time", "NA");
            return p_tc;*/
            return nullptr;
        };
    };

    struct Success_ALL_Log {
        explicit Success_ALL_Log(array<function<TiXmlElement* (const Log_Msg&)>, LOG_NUM>& func_array) {
            func_array[LOG_SUCCESS_ALL] = [this](const Log_Msg& log_msg) -> TiXmlElement* {return AddSuccessEntry(log_msg);};
        }

        TiXmlElement*  AddSuccessEntry(const Log_Msg& log_msg) {
            TiXmlElement * p_tc = new TiXmlElement("testcase");
            p_tc->SetAttribute("classname", log_msg.classname);
            p_tc->SetAttribute("name", log_msg.testname);
            p_tc->SetAttribute("time", "NA");
            return p_tc;
        };
    };
}

#endif // _EXPORTJENKINSLOG_H_ 