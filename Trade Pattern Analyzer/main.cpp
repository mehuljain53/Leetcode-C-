#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint> 
using namespace std;

class PatternDetector
{
public:

    int baseIndex;
    int totalRepetation;
    
    std::vector<double> processValue;
    std::vector<int> processTime;
    int getTimeMilisecond(const string& t){
        //HH:MM:SS.mmm
        int hour = stoi(t.substr(0,2));
        int minutes = stoi(t.substr(3,2));
        int second = stoi(t.substr(6,2));
        int milisecond = stoi(t.substr(9,3));
        return 60*60*1000*hour + 60*1000*minutes + 1000*second + milisecond;
    }
   PatternDetector(int pattern_length, int number_of_repetitions,int time_frame)
       : patternLength(pattern_length)
       , numOfRepetitions(number_of_repetitions)
   {    
       baseIndex = 0;
       totalRepetation=0;
       if(time_frame == 0)
            timeFrame = 100000000;
       else
       timeFrame = time_frame;
   }

   ~PatternDetector()
   {
   }

   bool detectPattern(const std::string& time, double price)
   {
       
       int currentIndex  = processValue.size();
       processValue.push_back(price);
       processTime.push_back(getTimeMilisecond(time));
        
        cout<<getTimeMilisecond(time)<<" "<<price<<endl;
        
       if(currentIndex-baseIndex < patternLength-1)
        return false;
    
        if(numOfRepetitions == 1)
            if(processTime[currentIndex] - processTime[currentIndex - patternLength +1] <= timeFrame)
                return true;
            return false;
        
        if(processValue[currentIndex] != processValue[currentIndex-patternLength]){
            baseIndex = currentIndex - patternLength + 1;
            return false;
        }
       
       if(currentIndex - baseIndex +1>= numOfRepetitions && patternLength==1)
            return true;


        if((currentIndex - baseIndex + 1)/patternLength >= numOfRepetitions){

            int checkLength = numOfRepetitions;
            int currentCheckIndex = currentIndex;
            bool checkFlag = true;
            while(checkLength--){
                if(processTime[currentCheckIndex] - processTime[currentCheckIndex - patternLength +1] > timeFrame){
                    checkFlag = false;
                    break;
                }
                currentCheckIndex-=patternLength;

            }
            return checkFlag;
        }

        return false;
   }

private:

    int patternLength;
    int numOfRepetitions;
    int timeFrame;
};

///////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    //Check inputs

    if(argc < 5)
    {
        std::cerr << "Usage: PatternDetector [pattern length] [repetition count] [CSV input file] [time Frame]"
                  << std::endl << std::endl
                  <<" example: PatternDetector 2 3 sample_input.csv"
                  << std::endl;
        return 1;
    }

    const int pattern_length = std::atoi(argv[1]);

    if(pattern_length <= 0)
    {
        std::cerr << "Invalid pattern length (parameter 1)"
                  << std::endl;
        return 1;
    }

    const int number_of_repetitions = std::atoi(argv[2]);

    if(number_of_repetitions <= 0)
    {
        std::cerr << "Invalid repetition count (parameter 2)"
                  << std::endl;
        return 1;
    }


    const std::string input_file(argv[3]);

    if(input_file.empty())
    {
        std::cerr << "Invalid input file (parameter 3)"
                  << std::endl;
        return 1;
    }

    const int time_frame = std::atoi(argv[4]);
    if(time_frame < 0)
    {
        std::cerr << "Invalid time frame (parameter 4)"
                  << std::endl;
        return 1;
    }

    std::ifstream input_stream(input_file);
    if(!input_stream.is_open())
    {
        std::cerr << "Could not open input file " << input_file << std::endl;
        return 1;
    }

    // Create an instance of pattern detector.

    PatternDetector detector(pattern_length, number_of_repetitions,time_frame);

    // Process input file.
    std::string line;
    std::string token;
    while(getline(input_stream, line))
    {
        std::string time;
        double price;

        std::istringstream string_stream(line);
        getline(string_stream, token, ',');
        time = token;

        getline(string_stream, token, ',');
        price = atof(token.c_str());

        // run price value through pattern detector

        const bool pattern_detected = detector.detectPattern(time, price);

        // *** Do not modify this output ***

        std::cout << time << ','
                  << price << ','
                  << (pattern_detected ? "True" : "False")
                  << std::endl;
    }

    return 0;
}
