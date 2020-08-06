#include <Windows.h>
#include <string>
#include <time.h>

struct RegTestUtil {
    enum REG_TEST_ERROR_CODE {
        REG_TEST_NO_ERROR = 100,
        REG_TEST_INVALID_PATH,
        REG_TEST_SAVE_XML_FAIL
    };   
    static bool dirExists(const std::string& dirName_in);
    static std::string getExePath(); 
    static int outputErrorLog(const std::string& error_msg, RegTestUtil::REG_TEST_ERROR_CODE error_code);
    static const std::string currentDateTime();
};

bool RegTestUtil::dirExists(const std::string& dirName_in) {
    DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
      return false;  //something is wrong with your path!

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
      return true;   // this is a directory!

    return false;    // this is not a directory!
}

std::string RegTestUtil::getExePath() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::string::size_type pos = std::string( buffer ).find_last_of( "/\\" );
    return std::string( buffer ).substr( 0, pos);
}

int RegTestUtil::outputErrorLog(const std::string& error_msg, RegTestUtil::REG_TEST_ERROR_CODE error_code){
    FILE* error_logfile = fopen((RegTestUtil::getExePath() + "/error.txt").c_str(), "wb");
    fprintf(error_logfile, error_msg.c_str()); 
    fclose(error_logfile);
    return static_cast<int>(error_code);
}

const std::string RegTestUtil::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[100];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d_%H_%M_%S", &tstruct);
    return buf;
}

