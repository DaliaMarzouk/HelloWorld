#include <fstream>
#include <iostream>
class HelloWorldView
{
	/*
	abstract class to prototype different output methods
	*/
public:
	virtual void writeOutput(const std::string divisibleBy)= 0;//responsible for generate the output
	virtual void logInfo(const std::string message)= 0;//responsible for logging the information
};
class HelloWorldConsolView: public HelloWorldView
{
	/*
	sponsible for viewing the output on the consol
	*/
public:
	virtual void writeOutput(const std::string divisibleBy){std::cerr << divisibleBy << std::endl;}
	virtual void logInfo(const std::string message){std::clog << message << std::endl;}

};


class HelloWorldFileView: public HelloWorldView
{
	/*
	responsable for viewing the output on file
	*/
public:
	HelloWorldFileView(){
		fs = new std::ofstream;
		try{
			fs->open("output.txt", std::ios_base::binary);
		}
		catch (std::exception e){
			std::clog << "Failed to open file for writing!" << std::endl;
			fileIsOpened = false;
		}
		std::clog << "fileView Intialized successfully" << std::endl;
	}
	~HelloWorldFileView(){delete fs;}
	virtual void writeOutput(const std::string divisibleBy)
	{
		
		if(fileIsOpened)*fs << divisibleBy << std::endl ;
		else{std::cerr << divisibleBy << std::endl;}

	}
	virtual void logInfo(const std::string message){std::clog << message << std::endl;}
private:
	std::ofstream* fs;
	bool fileIsOpened = true; //flag referes to if the output stream was opened successfully or not

};


class HelloWorldModel
{/**
	test divisibility by 3 or by 5 or by 3 and 5 both
*/
public:
	HelloWorldModel(const int _begin, const int _end, HelloWorldView *_view): x(_begin), end(_end), view(_view){
		std::clog << "the model was intialized successfully" << std::endl;
	}
	void loop()//loops starting drom the begining till the end
	{
		while (x <= end)testDivisability_3_5();

	}
private:
	int x, end; //stores begin and end counting
	HelloWorldView *view;
	void testDivisability_3_5(){
		if (x % 3 == 0){
			if (x % 5 == 0){
				view->writeOutput("HelloWorld");
			}
			else{
				view->writeOutput("Hello");
			}
		}
		else if (x % 5 == 0)
			{
				view->writeOutput("World");
			}
			else{
				view->writeOutput(std::to_string(long(x)));
			}
			++x;
		}
	
};


int main()
{
	//test the consolView
	HelloWorldConsolView view;
	HelloWorldModel model(1, 100, &view);
	model.loop();

	//test the fileView
	HelloWorldFileView view_1;
	HelloWorldModel model_1(1, 100, &view_1);
	model_1.loop();

	return 0;
}