#include <thread>
#include <bits/stdc++.h>
#include <windows.h>
#include <chrono>
#include <conio.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

using namespace std;
using namespace std::chrono;


void enableColors(){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= 0X0004;
    SetConsoleMode(hOut,dwMode);

}

class Question {
    public:
        string questionText;
        vector<string> options;
        char correctOption;
        string hint;
    
        Question(string q,vector<string> opts,char correct,string h){
            questionText=q;
            options = opts;
            correctOption = correct;
            hint=h;

        }
        void showHint() {
                cout << " 💡 Hint: " << hint << "\n";
            }

        void displayQuestion(){
            cout << "\n" << BOLD << CYAN << questionText << RESET <<"\n";
            char optionLabel ='A';
            for(string opt: options){
                cout<< "  " << optionLabel++ << ") " << opt << "\n";
            }
        }
        bool checkAnswer(char ans){
            return toupper(ans)==toupper(correctOption);
        }

};

class Quiz{
    private:
        vector<Question> questions;
        int score;
        string username;
    public:
        Quiz(){
            questions.push_back(Question(
            "What is the capital of France?",
            {"Paris", "London", "Berlin", "Madrid"},
            'A',"It’s known as the City of Light."
        ));
            questions.push_back(Question(
            "Which data type is used to store decimals in C++?",
            {"int", "float", "char", "bool",},
            'B',"Use this type when precision is required."
        ));                                                         
        questions.push_back(Question(
            "Which keyword is used to create a class in C++?",
            {"object", "function", "class", "define"},
            'C',"It literally names what you're creating."
        ));
        questions.push_back(Question(
            "Who is the father of C++?",
            {"Dennis Ritchie", "James Gosling", "Bjarne Stroustrup", "Guido van Rossum"},
            'C',"He built C++ as an extension of C."
        ));
        questions.push_back(Question(
            "What does HTML stand for?",
            {"Hyper Trainer Marking Language", "Hyper Text Markup Language", "Hyper Text Marketing Language", "Hyperlinking Text Main Language"},
            'B',"It’s the backbone of web page structure."

        ));
        questions.push_back(Question(
            "What is the capital of India?",
            {"Mumbai","Bangkok","Delhi","Jaipur"},
            'C',"It is most polluted city of India."
        ));
        };
        void startQuiz(){
            cin.ignore();
            cout << YELLOW<<"👤Enter your name: ";
            getline(cin,username);
            cout<< GREEN <<"\n Welcome,"<<BOLD<<username<<RESET<<GREEN<<"!Let's begin the quiz...\n"<<RESET;

            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
            shuffle(questions.begin(),questions.end(),default_random_engine(seed));
            
            score = 0;
            char userAnswer;
            for(int i=0; i <questions.size();++i){
                Question q = questions[i];
                q.displayQuestion();

                cout << YELLOW << "You have 10 seconds to answer..." << RESET << endl;
                cout << "Your answer (A/B/C/D): ";
                auto start = chrono :: steady_clock::now();
                bool answered=false;
                while(true){
                    if(_kbhit()){
                        userAnswer = _getch();
                        cout << userAnswer <<"\n";
                        userAnswer=toupper(userAnswer);
                        answered=true;
                        break;
                    }
                    auto now = chrono::steady_clock::now();
                    int elapsed = chrono::duration_cast<chrono::seconds>(now-start).count();
                    if(elapsed>=10){
                        cout<< RED << "\nTime's up!" << RESET << endl;
                        break;
                    }
                    Sleep(100);            
                }
                userAnswer = toupper(userAnswer);

                if (userAnswer < 'A' || userAnswer > 'D') {
                    cout << " Invalid input! Please enter A, B, C, or D only.\n";
                    --i; 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (answered && q.checkAnswer(userAnswer)) {
                    cout << GREEN <<"Correct!\n" <<RESET;
                    ++score;
                } else if(!answered){
                        cout << RED << " You didn't answer in time. Correct answer was: " << q.correctOption << "\n" << RESET;

                    }
                else {
                    cout << RED << "Wrong! Correct answer was: " << q.correctOption << "\n" <<RESET;
                    q.showHint();
                }

            }
            
                displayFinalScore();  
                saveScore(); 
                if (score >= questions.size() * 0.9) {
                    cout << "\n🥇 Congratulations! You've earned the Gold Badge!\n";
                } else if (score >= questions.size() * 0.7) {
                    cout << "\n🥈 Congratulations! You've earned the Silver Badge!\n";
                } else if (score >= questions.size() * 0.5) {
                    cout << "\n🥉 Congratulations! You've earned the Bronze Badge!\n";
                } else {
                    cout << "\nTry again to earn a badge! 💪\n";
                }    
        };
        void displayFinalScore() {
            cout << YELLOW << "\n Your final score is: " << score << " out of " << questions.size() << RESET <<endl;
        }
        void saveScore(){
            ofstream file("score.txt",ios::app);
            if(file.is_open()){
                time_t now = time(0);
                char* dt = ctime(&now); 
                string timestamp =dt;
                if(!timestamp.empty() && timestamp.back()== '\n'){
                    timestamp.pop_back();
                }

                file <<  username << "," << score << "/" << questions.size()
                        << "," << timestamp << endl;
                file.close();
            }
            else{
                cout <<"Error writing to score file\n";
            }
        }

        void displayScoreboard(){
            ifstream infile("score.txt");
            string line;
            vector<pair<int,string>> scores;
            cout << "n=== Scoreboard ===\n";
            if(infile.is_open()){
                while(getline(infile,line)){
                    try{
                    stringstream ss(line);
                    string username,scoreStr,timestamp;
                    
                    getline(ss,username,',');
                    getline(ss,scoreStr,',');

                    size_t slashPos =scoreStr.find('/');
                    if(slashPos ==string::npos){
                        continue;
                    }
                    int score=stoi(scoreStr.substr(0,slashPos));
                    scores.push_back(make_pair(score,username));
                }
                catch(const std:: exception &e){
                    continue;
                }
                }

                infile.close();

                sort(scores.begin(),scores.end(),greater<pair<int,string>>());
                int rank=1;
                for(const auto& score:scores){
                    cout<<"Rank"<<rank++ << ": "<<score.second<<" - " << score.first <<"/"<<questions.size() << endl;

                }
            }
            else{
                cout << "No scores available yet.\n";
            }
        }

        void showMenu(){
            int choice;
            do{
                cout << BOLD<<CYAN<<"\n==== Quiz Menu ====\n"<<RESET;
                cout <<GREEN<<" 1️⃣  Start Quiz\n"<<RESET;
                cout << " 2️⃣  View Leaderboard\n";
                cout << " 3️⃣  Exit \n" ;
                cout << YELLOW<<"Enter your choice: "<<RESET;
                cin>> choice;
                cin.ignore();

               if (choice == 1) {
                    startQuiz();
                } else if (choice == 2) {
                    displayScoreboard();
                } else if (choice == 3) {
                    cout << CYAN<<"Thanks for playing! Goodbye.👋\n"<<RESET;
                }else {
                    cout << RED << "Invalid choice! Please select 1, 2, or 3.\n" << RESET;
                }

            }while (choice != 3);

        }
        
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    enableColors();
    Quiz quiz;
    quiz.showMenu();
    return 0;
}
