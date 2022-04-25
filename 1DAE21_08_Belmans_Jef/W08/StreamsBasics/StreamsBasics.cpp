#include <iostream>
#include <fstream>
#include <string>

void ReadSentence(std::istream& istream, std::string& sentence);

int main()
{
    // std::string output;
    // ReadSentence(std::cin, output);
    // std::cout << "Your input: " << output;

    std::ifstream inputFile;
    inputFile.open("Resources/SoftwareQuotesInput.txt");

    std::ofstream outputFile;
    outputFile.open("Resources/SoftwareQuotesOutput.txt");

    if (inputFile.is_open() && outputFile.is_open())
    {
        while (inputFile.peek() != EOF)
        {
            std::string sentence;
            ReadSentence(inputFile, sentence);

            std::cout << sentence << std::endl;
            outputFile << sentence << '\n';
        }
    }

    inputFile.close();
    outputFile.close();
}

void ReadSentence(std::istream& istream, std::string& sentence)
{
    if (istream)
    {
       std::string input, output;

       do
       {
           std::getline(istream, input);
           output += input;
       } while (istream.peek() != EOF && (input.size() < 1 || input[input.size() - 1] != '.'));
       sentence = output;
    }
}
